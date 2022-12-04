// @author: Amremad719
#include "Game.h"
#define s ' '
#pragma warning(disable : 4996)
using namespace std;
using namespace sf;

//initializers
void Game::initvar()
{
    this->window = nullptr;
    this->gameTimeCounterClock = nullptr;
}

void Game::initwindow()
{
    conSett.antialiasingLevel = 10;
    
    this->video.height = Height;
    this->video.width = Width;
    this->window = new RenderWindow(this->video, "Sudoku", Style::Close);
    
    this->AppImage.loadFromFile("icon.png");
    this->window->setIcon(this->AppImage.getSize().x, this->AppImage.getSize().y, this->AppImage.getPixelsPtr());
    
    this->window->setFramerateLimit(60);

    //if screen is small open in small window mode
    if (VideoMode::getDesktopMode().height < Height + 100) 
    {
        currWindowSize = small;
        WindowSmall.first.setFillColor(SelectColor);
        WindowLarge.first.setFillColor(normalColor);
    }

    //if selected window size is small scale the window
    if (currWindowSize == small) {
        this->window->setSize(Vector2u(450 + (LineThickness * 7), 450 + (LineThickness * 7) + 125 + gridPadding));
    }
}

void Game::initfont()
{
    this->font.loadFromFile("Fonts/BebasNeue-Regular.ttf");
}

void Game::initText()
{
    //globally used text object
    this->text.setFont(font);
    this->text.setCharacterSize(50);
    this->text.setColor(Color::Black);
    this->text.setString(" ");
    
    //time counter text
    this->timeText.setFont(font);
    this->timeText.setCharacterSize(gridSize / 10);
    this->timeText.setColor(Color::Black);
    this->timeText.setPosition(gridSize - 45, gridSize + (LineThickness * 7) - 10 + gridPadding);
    this->timeText.setString("0:00");
   
    //Sudoku text on the top of the page in game
    this->GameHudText.setFont(font);
    this->GameHudText.setCharacterSize(50);
    this->GameHudText.setColor(Color::Black);
    this->GameHudText.setPosition(230, -7);
    this->GameHudText.setString("Sudoku");

    //mistakes counter in game
    this->Mistakes.setFont(font);
    this->Mistakes.setPosition(230, -7);
    this->Mistakes.setColor(Color::Black);
    this->Mistakes.setCharacterSize(gridSize / 20);
    this->Mistakes.setPosition(7, gridSize + (LineThickness * 7) - 3 + gridPadding);
}

void Game::initMenu()
{
    Vector2f Playpos = Vector2f(193, 270);
    Vector2f Settingspos = Vector2f(193, Playpos.y + 150);
    Vector2f Exitpos = Vector2f(193, Settingspos.y + 150);

//button squares

    //play
    MainMenuPlayButton.first.setFillColor(Color::White);
    MainMenuPlayButton.first.setPosition(Playpos);
    MainMenuPlayButton.first.setSize(Vector2f(200, 70));
    MainMenuPlayButton.first.setOutlineThickness(7);
    MainMenuPlayButton.first.setOutlineColor(Color::Black);

    //Exit
    MainMenuExitButton.first.setFillColor(Color::White);
    MainMenuExitButton.first.setPosition(Exitpos);
    MainMenuExitButton.first.setSize(Vector2f(200, 70));
    MainMenuExitButton.first.setOutlineThickness(7);
    MainMenuExitButton.first.setOutlineColor(Color::Black);

    //Settings
    MainMenuSettingsButton.first.setFillColor(Color::White);
    MainMenuSettingsButton.first.setPosition(Settingspos);
    MainMenuSettingsButton.first.setSize(Vector2f(200, 70));
    MainMenuSettingsButton.first.setOutlineThickness(7);
    MainMenuSettingsButton.first.setOutlineColor(Color::Black);

//button text

    //Play
    MainMenuPlayButton.second.setFillColor(Color::Black);
    MainMenuPlayButton.second.setCharacterSize(70);
    MainMenuPlayButton.second.setPosition(Playpos.x + 47, Playpos.y - 10);
    MainMenuPlayButton.second.setString("Play");
    MainMenuPlayButton.second.setFont(font);

    //Exit
    MainMenuExitButton.second.setFillColor(Color::Black);
    MainMenuExitButton.second.setCharacterSize(70);
    MainMenuExitButton.second.setPosition(Exitpos.x + 52, Exitpos.y - 10);
    MainMenuExitButton.second.setString("Exit");
    MainMenuExitButton.second.setFont(font);

    //Settings
    MainMenuSettingsButton.second.setFillColor(Color::Black);
    MainMenuSettingsButton.second.setCharacterSize(65);
    MainMenuSettingsButton.second.setPosition(Settingspos.x + 7, Settingspos.y - 8);
    MainMenuSettingsButton.second.setString("Settings");
    MainMenuSettingsButton.second.setFont(font);

//Title
    MainMenuSudokuText.setFillColor(Color::Black);
    MainMenuSudokuText.setCharacterSize(140);
    MainMenuSudokuText.setPosition(125, 40);
    MainMenuSudokuText.setString("Sudoku");
    MainMenuSudokuText.setFont(font);
}

void Game::initgrid()
{
    RectangleShape rect;
    //Squares

    float x = LineThickness, y = LineThickness;
    rect.setFillColor(Color::White);
    Vector2f pos = {0, gridPadding * 1.0f}, size = {gridSize / 9, gridSize / 9 };
    for (int i = 0; i < 9; i++) 
    {
        vector<pair<RectangleShape, Text>> vec;
        //horizontal lines
        //check if it is time for a thick line or not
        if (i % 3 == 0) {
            pos.y += LineThickness;
        }
        else {
            pos.y += LineThickness / 2;
        }
        for (int j = 0; j < 9; j++) 
        {
            //vertical lines
            //check if it is time for a thick line or not
            if (j % 3 == 0) 
            {
                pos.x += LineThickness;
            }
            else 
            {
                pos.x += LineThickness / 2;
            }
            rect.setPosition(pos);
            rect.setSize(size);

            Vector2f tpos = pos;
            tpos.x += (gridSize / 9) / 3;

            text.setPosition(tpos);

            //increment x position for next vertical line
            pos.x += gridSize / 9;

            vec.push_back({rect, text});
        }
        //increment y position for next horizontal line
        pos.y += gridSize / 9;
        pos.x = 0;

        GridSquares.push_back(vec);
    }

    rect.setFillColor(Color(100, 100, 100, 255));
    
    //thin Lines
    int xpos = 0, ypos = gridPadding;
    for (int i = 0; i < 6; i++) 
    {
        //check if it is time for a thick line or not
        if (i % 2 == 0) 
        {
            xpos += LineThickness + (gridSize / 9);
            ypos += (gridSize / 9) + LineThickness;
        }

        //Vertical Lines
        rect.setSize(Vector2f(LineThickness / 2, gridSize + LineThickness * 5));
        rect.setPosition(Vector2f(xpos, LineThickness + gridPadding));
        GridLines.push_back(rect);

        //Horizontal Lines
        rect.setSize(Vector2f(gridSize + LineThickness * 5, LineThickness / 2));
        rect.setPosition(Vector2f(LineThickness, ypos));
        GridLines.push_back(rect);

        //increment
        xpos += (gridSize / 9) + (LineThickness / 2);
        ypos += (gridSize / 9) + (LineThickness / 2);
    }

    //thick lines
    xpos = 0, ypos = gridPadding;
    rect.setFillColor(Color::Black);
    for (int i = 1; i <= 4; i++) 
    {
        //Vertical Lines
        rect.setSize(Vector2f(LineThickness, gridSize + LineThickness * 7));
        rect.setPosition(Vector2f(xpos, gridPadding));
        GridLines.push_back(rect);

        //Horizontal Lines
        rect.setSize(Vector2f(gridSize + LineThickness * 7, LineThickness));
        rect.setPosition(Vector2f(0, ypos));
        GridLines.push_back(rect);

        //increment
        xpos += (gridSize / 3) + (2 * LineThickness);
        ypos += (gridSize / 3) + (2 * LineThickness);
    }
}

void Game::initDifficulty()
{
    Vector2f Easypos = Vector2f(193, 200);
    Vector2f Mediumpos = Vector2f(193, 350);
    Vector2f Hardpos = Vector2f(193, 500);

//Buttons rectangle
    Easy.first.setFillColor(Color::White);
    Easy.first.setPosition(Easypos);
    Easy.first.setSize(Vector2f(200, 70));
    Easy.first.setOutlineThickness(7);
    Easy.first.setOutlineColor(Color::Black);
    
    Medium.first.setFillColor(Color::White);
    Medium.first.setPosition(Mediumpos);
    Medium.first.setSize(Vector2f(200, 70));
    Medium.first.setOutlineThickness(7);
    Medium.first.setOutlineColor(Color::Black);
   
    Hard.first.setFillColor(Color::White);
    Hard.first.setPosition(Hardpos);
    Hard.first.setSize(Vector2f(200, 70));
    Hard.first.setOutlineThickness(7);
    Hard.first.setOutlineColor(Color::Black);
    
//Buttons text
    Easy.second.setFillColor(Color::Black);
    Easy.second.setCharacterSize(70);
    Easy.second.setPosition(Easypos.x + 47, Easypos.y - 10);
    Easy.second.setString("Easy");
    Easy.second.setFont(font);
    
    Medium.second.setFillColor(Color::Black);
    Medium.second.setCharacterSize(70);
    Medium.second.setPosition(Mediumpos.x + 15, Mediumpos.y - 10);
    Medium.second.setString("Medium");
    Medium.second.setFont(font);
    
    Hard.second.setFillColor(Color::Black);
    Hard.second.setCharacterSize(70);
    Hard.second.setPosition(Hardpos.x + 42, Hardpos.y - 10);
    Hard.second.setString("Hard");
    Hard.second.setFont(font);

//Title
    Difficulty.setFillColor(Color::Black);
    Difficulty.setCharacterSize(90);
    Difficulty.setPosition(40, 40);
    Difficulty.setString("Select Difficulty");
    Difficulty.setFont(font);
}

void Game::initNumbers() 
{
    RectangleShape rect;
    Vector2f pos = { 15, gridSize + (LineThickness * 7) + gridPadding + 55};

    //intitialise the rectangle
    rect.setFillColor(NumbersColor);
    rect.setOutlineThickness(5);
    rect.setOutlineColor(Color::Black);
    rect.setSize(Vector2f(Numsize, Numsize));

    for (int i = 1; i <= 9; i++) {

        //convert the integer
        stringstream ss;
        ss << i;
        string x;
        ss >> x;

        Vector2f textpos = pos;
        textpos.x += 18;
        textpos.y -= 11;

        text.setString(x);
        text.setPosition(textpos);

        rect.setPosition(pos);

        NumPadNumbers.push_back({ rect, text });

        //increment
        pos.x += Numsize + 5;
    }
    //Counters
    text.setCharacterSize(20);
    text.setString("Test");

    pos = { 27, gridSize + (LineThickness * 7) + gridPadding + 97 };

    for (int i = 0; i < 9; i++) 
    {
        rect.setPosition(pos);
        text.setPosition(pos.x - 1, pos.y - 6);
        NumbersCounter.push_back(text);

        //increment
        pos.x += Numsize + 5;
    }
}

void Game::initTextures()
{
//load textures
    MusicMutedHighlightedTexture.loadFromFile("Textures/MusicMutedHighlighted.png");
    BackArrowHighlightedText.loadFromFile("Textures/ArrowHighlighted.png");
    MusicHighlightedTexture.loadFromFile("Textures/MusicHighlighted.png");
    MusicMutedTexture.loadFromFile("Textures/MusicMuted.png");
    MusicTexture.loadFromFile("Textures/Music.png");

    BackArrowText.loadFromFile("Textures/Arrow.png");

//set textures
    BackArrow.setTexture(BackArrowText);
    BackArrow.setPosition(10, 4);

    MusicIcon.setPosition(515, 4);
    MusicIcon.setTexture(MusicTexture);

//set smooth
    MusicMutedHighlightedTexture.setSmooth(1);
    BackArrowHighlightedText.setSmooth(1);
    MusicHighlightedTexture.setSmooth(1);
    MusicMutedTexture.setSmooth(1);
    BackArrowText.setSmooth(1);
    MusicTexture.setSmooth(1);
}

void Game::initMusic() {
    this->musicBuffer.loadFromFile("Music/music.wav");
    this->Music.setBuffer(musicBuffer);
    this->Music.setLoop(true);

    if (currMusicStatus == Active) Music.play();
}

void Game::initSettings()
{
//Title
    SettingsText.setFont(font);
    SettingsText.setLetterSpacing(2);
    SettingsText.setCharacterSize(70);
    SettingsText.setPosition(180, -15);
    SettingsText.setString("Settings");
    SettingsText.setFillColor(Color::Black);

    Vector2f pos = { 30, 100 };

    settingsWindowSize.setFont(font);
    settingsWindowSize.setCharacterSize(45);
    settingsWindowSize.setPosition(pos);
    settingsWindowSize.setString("Window Size");
    settingsWindowSize.setFillColor(Color::Black);

//Large Window Button
    //rectangle
    WindowSmall.first.setOutlineThickness(5);
    WindowSmall.first.setOutlineColor(Color::Black);
    WindowSmall.first.setFillColor((currWindowSize == small ? SelectColor:Color::White));
    WindowSmall.first.setPosition(pos.x + 300, pos.y + 7);
    WindowSmall.first.setSize(Vector2f(90, 40));
    //text
    WindowSmall.second.setFont(font);
    WindowSmall.second.setCharacterSize(40);
    WindowSmall.second.setPosition(pos.x + 300 + 5, pos.y + 1);
    WindowSmall.second.setString("Small");
    WindowSmall.second.setFillColor(Color::Black);

//Large Window Button
    //rectangle
    WindowLarge.first.setOutlineThickness(5);
    WindowLarge.first.setOutlineColor(Color::Black);
    WindowLarge.first.setFillColor((currWindowSize == large ? SelectColor : Color::White));
    WindowLarge.first.setPosition(pos.x + 420, pos.y + 7);
    WindowLarge.first.setSize(Vector2f(90, 40));

    //text
    WindowLarge.second.setFont(font);
    WindowLarge.second.setCharacterSize(40);
    WindowLarge.second.setPosition(pos.x + 420 + 5, pos.y + 1);
    WindowLarge.second.setString("Large");
    WindowLarge.second.setFillColor(Color::Black);
}

void Game::initGameOver()
{
    Color transBlack = Color(0, 0, 0, 0);
    Color transGrey = Color(220, 220, 220, 0);

    GameOverText.setFont(font);
    GameOverText.setFillColor(transBlack);

    GameOverDesc.setFont(font);
    GameOverDesc.setCharacterSize(30);
    GameOverDesc.setFillColor(transBlack);

    Vector2f RestartPos = { 196, 275 };
    Vector2f QuitPos = { 196, 525 };
    Vector2f MainMenuPos = { 196, 400 };

    //rectangle
    PlayAgain.first.setPosition(RestartPos);
    PlayAgain.first.setOutlineThickness(5);
    PlayAgain.first.setSize(Vector2f(190, 60));
    PlayAgain.first.setOutlineColor(transBlack);
    PlayAgain.first.setFillColor(transGrey);
    //text
    PlayAgain.second.setFont(font);
    PlayAgain.second.setCharacterSize(50);
    PlayAgain.second.setString("Play Again");
    PlayAgain.second.setFillColor(transBlack);
    PlayAgain.second.setPosition(RestartPos.x + 6, RestartPos.y);


    //rectangle
    MainMenu.first.setPosition(MainMenuPos);
    MainMenu.first.setOutlineThickness(5);
    MainMenu.first.setSize(Vector2f(190, 60));
    MainMenu.first.setOutlineColor(transBlack);
    MainMenu.first.setFillColor(transGrey);
    //text
    MainMenu.second.setFont(font);
    MainMenu.second.setCharacterSize(50);
    MainMenu.second.setString("Main Menu");
    MainMenu.second.setFillColor(transBlack);
    MainMenu.second.setPosition(MainMenuPos.x + 8, MainMenuPos.y);

    //rectangle
    Quit.first.setPosition(QuitPos);
    Quit.first.setOutlineThickness(5);
    Quit.first.setSize(Vector2f(190, 60));
    Quit.first.setOutlineColor(transBlack);
    Quit.first.setFillColor(transGrey);
    //text
    Quit.second.setFont(font);
    Quit.second.setCharacterSize(50);
    Quit.second.setString("Quit");
    Quit.second.setFillColor(transBlack);
    Quit.second.setPosition(QuitPos.x + 58, QuitPos.y);
}

//Highlighters
void Game::GameOverHighlight()
{
    bool withinAnyButton = 0;
    Vector2f pos = GetMousePos();

    //play again 
    if (withinRect(pos, PlayAgain.first.getGlobalBounds())) 
    {
        PlayAgain.first.setFillColor(Color(120, 120, 120, 100));
        SelectedGameOverButton = GameOverPlayAgain;
        withinAnyButton = 1;
    }
    else
    {
        PlayAgain.first.setFillColor(Color(200, 200, 200, 100));
    }

    //Main menu
    if (withinRect(pos, MainMenu.first.getGlobalBounds())) 
    {
        MainMenu.first.setFillColor(Color(120, 120, 120, 100));
        SelectedGameOverButton = GameOverMainMenu;
        withinAnyButton = 1;
    }
    else
    {
        MainMenu.first.setFillColor(Color(200, 200, 200, 100));
    }

    //Quit
    if (withinRect(pos, Quit.first.getGlobalBounds())) 
    {
        Quit.first.setFillColor(Color(120, 120, 120, 100));
        SelectedGameOverButton = GameOverQuit;
        withinAnyButton = 1;
    }
    else
    {
        Quit.first.setFillColor(Color(200, 200, 200, 100));
    }

    if (!withinAnyButton)
    {
        SelectedGameOverButton = GameOvernone;
    }
}

void Game::highlightMenuButton()
{
    Vector2f mousePos = GetMousePos();
    bool withinAnyButton = 0;

    //Play
    if (withinRect(mousePos, MainMenuPlayButton.first.getGlobalBounds())) 
    {
        MainMenuPlayButton.first.setFillColor(highlightColor);
        SelectedMenuButton = play;
        withinAnyButton = 1;
    }
    else 
    {
        MainMenuPlayButton.first.setFillColor(Color::White);
    }

    //Settings
    if (withinRect(mousePos, MainMenuSettingsButton.first.getGlobalBounds())) 
    {
        MainMenuSettingsButton.first.setFillColor(highlightColor);
        SelectedMenuButton = Menusettings;
        withinAnyButton = 1;
    }
    else 
    {
        MainMenuSettingsButton.first.setFillColor(Color::White);
    }

    //Exit
    if (withinRect(mousePos, MainMenuExitButton.first.getGlobalBounds())) 
    {
        MainMenuExitButton.first.setFillColor(highlightColor);
        SelectedMenuButton = exit;
        withinAnyButton = 1;
    }
    else 
    {
        MainMenuExitButton.first.setFillColor(Color::White);
    }

    //Music 
    if (withinRect(mousePos, MusicIcon.getGlobalBounds())) 
    {
        if (currMusicStatus == Mute) 
        {
            MusicIcon.setTexture(MusicMutedHighlightedTexture);
        }
        else 
        {
            MusicIcon.setTexture(MusicHighlightedTexture);
        }
        SelectedMenuButton = Menumusic;
        withinAnyButton = 1;
    }
    else 
    {
        if (currMusicStatus == Mute) 
        {
            MusicIcon.setTexture(MusicMutedTexture);
        }
        else 
        {
            MusicIcon.setTexture(MusicTexture);
        }
    }

    if (!withinAnyButton)
    {
        SelectedMenuButton = Menunone;
    }
}

void Game::highlight(int indr, int indc, bool remove = 0)
{
    Text squareNum;
    Color fillColor, prevColor;

    if (!remove) 
    {
        //highlight row and column
        for (int i = 0; i < 9; i++) 
        {
            //column
            squareNum = GridSquares[indr][i].second;
            GridSquares[indr][i].first.setFillColor(SelectColor);

            //row
            squareNum = GridSquares[i][indc].second;
            GridSquares[i][indc].first.setFillColor(SelectColor);
        }

        //highlight 3x3
        for (int i = (indr / 3) * 3; i < ((indr / 3) * 3) + 3; i++) 
        {
            for (int j = (indc / 3) * 3; j < ((indc / 3) * 3) + 3; j++) 
            {
                squareNum = GridSquares[i][j].second;
                GridSquares[i][j].first.setFillColor(SelectColor);
            }
        }
    }

    //highlight same numbers
    string og = GridSquares[indr][indc].second.getString();
    for (int i = 0; i < 9; i++) 
    {
        for (int j = 0; j < 9; j++) 
        {
            string curr = GridSquares[i][j].second.getString();
            if (curr != " " && stoi(curr) != solution[i][j])
            {
                GridSquares[i][j].first.setFillColor(invalidColor);
            }
            else if (i == indr && j == indc && !remove)
            {
                GridSquares[i][j].first.setFillColor(SelectBlue);
            }
            else
            {
                if(remove)
                {
                    if (isPreFilled[i][j])
                    {
                        fillColor = preFilledColor;
                    }
                    else
                    {
                        fillColor = normalColor;
                    }

                    GridSquares[i][j].first.setFillColor(fillColor);
                }
                else if (curr == og && og != " ")
                {
                    GridSquares[i][j].first.setFillColor(SelectBlue);
                }
            }
        }
    }
}

void Game::highlightDiffButton()
{
    Vector2f mousePos = GetMousePos();
    bool withinAnyButton = 0;

    //Easy
    if (withinRect(mousePos, Easy.first.getGlobalBounds())) 
    {
        Easy.first.setFillColor(highlightColor);
        SelectedDifficulty = easy;
        withinAnyButton = 1;
    }
    else 
    {
        Easy.first.setFillColor(Color::White);
    }

    //Medium
    if (withinRect(mousePos, Medium.first.getGlobalBounds())) 
    {
        Medium.first.setFillColor(highlightColor);
        SelectedDifficulty = medium;
        withinAnyButton = 1;
    }
    else 
    {
        Medium.first.setFillColor(Color::White);
    }

    //Hard
    if (withinRect(mousePos, Hard.first.getGlobalBounds())) 
    {
        Hard.first.setFillColor(highlightColor);
        SelectedDifficulty = hard;
        withinAnyButton = 1;
    }
    else 
    {
        Hard.first.setFillColor(Color::White);
    }

    //Back Arrow
    if (withinRect(mousePos, BackArrow.getGlobalBounds())) 
    {
        BackArrow.setTexture(BackArrowHighlightedText);
        SelectedDifficulty = Diffback;
        withinAnyButton = 1;
    }
    else 
    {
        BackArrow.setTexture(BackArrowText);
    }

    //Music button
    if (withinRect(mousePos, MusicIcon.getGlobalBounds())) 
    {
        if (currMusicStatus == Mute) 
        {
            MusicIcon.setTexture(MusicMutedHighlightedTexture);
        }
        else 
        {
            MusicIcon.setTexture(MusicHighlightedTexture);
        }
        SelectedDifficulty = Diffmusic;
        withinAnyButton = 1;
    }
    else 
    {
        if (currMusicStatus == Mute) 
        {
            MusicIcon.setTexture(MusicMutedTexture);
        }
        else 
        {
            MusicIcon.setTexture(MusicTexture);
        }
    }

    if (!withinAnyButton)
    {
        SelectedDifficulty = Diffnone;
    }
}

void Game::highlightGamehud()
{
    Vector2f Pos = GetMousePos();
    bool withinAnyButton = 0;
    
    //Back arrow
    if (withinRect(Pos, BackArrow.getGlobalBounds())) 
    {
        BackArrow.setTexture(BackArrowHighlightedText);
        SelectedGameHud = Gameback;
        withinAnyButton = 1;
    }
    else 
    {
        BackArrow.setTexture(BackArrowText);
    }

    //Music
    if (withinRect(Pos, MusicIcon.getGlobalBounds())) 
    {
        if (currMusicStatus == Mute) 
        {
            MusicIcon.setTexture(MusicMutedHighlightedTexture);
        }
        else 
        {
            MusicIcon.setTexture(MusicHighlightedTexture);
        }

        SelectedGameHud = Gamemusic;
        withinAnyButton = 1;
    }
    else 
    {
        if (currMusicStatus == Mute) 
        {
            MusicIcon.setTexture(MusicMutedTexture);
        }
        else 
        {
            MusicIcon.setTexture(MusicTexture);
        }
    }

    if (!withinAnyButton) SelectedGameHud = Gamenone;
}

void Game::highlightSettings()
{
    Vector2f Pos = GetMousePos();
    bool withinAnyButton = 0;

    //Back arrow
    if (withinRect(Pos, BackArrow.getGlobalBounds()))
    {
        BackArrow.setTexture(BackArrowHighlightedText);
        SelectedSettingsButton = Settingsback;
        withinAnyButton = 1;
    }
    else 
    {
        BackArrow.setTexture(BackArrowText);
    }

    //Music
    if (withinRect(Pos, MusicIcon.getGlobalBounds())) 
    {
        if (currMusicStatus == Mute) 
        {
            MusicIcon.setTexture(MusicMutedHighlightedTexture);
        }
        else 
        {
            MusicIcon.setTexture(MusicHighlightedTexture);
        }
        SelectedSettingsButton = Settingsmusic;
        withinAnyButton = 1;
    }
    else 
    {
        if (currMusicStatus == Mute) 
        {
            MusicIcon.setTexture(MusicMutedTexture);
        }
        else 
        {
            MusicIcon.setTexture(MusicTexture);
        }
    }

    if (!withinAnyButton) SelectedSettingsButton = Settingsnone;
}

//Gameplay logic
bool Game::checkForOneSultion(vector<vector<int>> tempSolution)
{
    
    bitset<10> st((1 << 10) - 1);
    vector<bitset<10>> rows(9, st), columns(9, st);
    vector<vector<bitset<10>>> squares(3, vector<bitset<10>>(3, st));

    //mark taken numbers as taken in bitsets
    for (int i = 0; i < 9; i++) 
    {
        for (int j = 0; j < 9; j++) 
        {
            rows[i][tempSolution[i][j]] = 0;
            columns[j][tempSolution[i][j]] = 0;
            squares[i / 3][j / 3][tempSolution[i][j]] = 0;
        }
    }

    //iterate for every row
    for (int i = 0; i < 9; i++) 
    {
        vector<vector<int>> cntr(10);
        for (int j = 0; j < 9; j++) 
        {
            //if cell is pre filled continue
            if (tempSolution[i][j]) continue;
            
            //get available numbers for this cell
            bitset<10> inter = rows[i] & columns[j] & squares[i / 3][j / 3];

            //put numbers in vector to be able to choose randomly from them
            for (int k = 1; k <= 9; k++) 
            {
                if (inter[k]) 
                {
                    cntr[k].push_back(j);
                }
            }
        }

        //check if there is any row with a number having only one valid cell to be put in
        for (int j = 1; j <= 9; j++) 
        {
            //if found
            if (cntr[j].size() == 1) 
            {
                tempSolution[i][cntr[j][0]] = j;
                rows[i][j] = 0;
                columns[cntr[j][0]][j] = 0;
                squares[i / 3][cntr[j][0] / 3][j] = 0;

                //iterate from beginning to not miss anything
                i = 0;
                break;
            }
        }
    }

    //iterate for every column
    for (int i = 0; i < 9; i++) 
    {
        vector<vector<int>> cntr(10);

        for (int j = 0; j < 9; j++) 
        {
            //if cell is pre filled continue
            if (tempSolution[j][i]) continue;

            //get available numbers for this cell
            bitset<10> inter = rows[j] & columns[i] & squares[j / 3][i / 3];

            //put numbers in vector to be able to choose randomly from them
            for (int k = 1; k <= 9; k++) 
            {
                if (inter[k]) 
                {
                    cntr[k].push_back(j);
                }
            }
        }

        //check if there is any row with a number having only one valid cell to be put in
        for (int j = 0; j < 9; j++) 
        {
            //if found
            if (cntr[j].size() == 1) 
            {
                tempSolution[cntr[j][0]][i] = j;
                rows[cntr[j][0]][j] = 0;
                columns[i][j] = 0;
                squares[cntr[j][0] / 3][i / 3][j] = 0;

                //iterate from beginning to not miss anything
                i = 0;
                break;
            }
        }
    }
    return tempSolution == solution;
}

bool Game::GenerateGrid()
{
    vector<vector<int>> vec(9, vector<int>(9, 0));
    map<string, vector<pair<int, int>>> TempNumPositions;

    //Bitsets to mark if a certain number is available 1 is available to put
    bitset<10> st((1 << 10) - 1);
    vector<bitset<10>> rows(9, st), columns(9, st);
    vector<vector<bitset<10>>> squares(3, vector<bitset<10>>(3, st));

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            //take the common available numbers between them
            bitset<10> inter = rows[i] & columns[j] & squares[i / 3][j / 3];
            vector<int> nums;

            //put the indices into a vector
            for (int k = 1; k <= 9; k++)
            {
                if (inter[k]) nums.push_back(k);
            }
            if (nums.size() == 0) return 0;

            //choose random index
            int chosenind = rand() % nums.size();
            int chosen = nums[chosenind];
            vec[i][j] = chosen;

            //mark as taken
            rows[i][chosen] = 0;
            columns[j][chosen] = 0;
            squares[i / 3][j / 3][chosen] = 0;

            //put into string to be able to put in text object
            string x;
            x.push_back(chosen + '0');
            GridSquares[i][j].second.setString(x);
            TempNumPositions[x].push_back({ i, j });
        }
    }

    NumPositions = TempNumPositions;
    solution = vec;
    return 1;
}

void Game::ToggleMusic()
{
    if (currMusicStatus == Active)
    {
        currMusicStatus = Mute;
        Music.pause();
    }
    else
    {
        currMusicStatus = Active;
        Music.play();
    }
}

void Game::removeCells(int Amount)
{
    const int ogAmount = Amount;
    vector<vector<int>> vec = solution;
    vector<pair<int, int>> ogProb, prob;

    //initialize vector with every cell in grid
    for (int i = 0; i < 9; i++) 
    {
        for (int j = 0; j < 9; j++) 
        {
            ogProb.push_back({ i, j });
        }
    }

    //try to remove cells until found valid one
    do 
    {
        //initialize
        prob = ogProb;
        Amount = ogAmount;
        vec = solution;

        while (Amount--) 
        {
            //if no remaining cells break
            if (!prob.size()) break;

            //choose index randomly
            int ind = rand() % prob.size();
            int temp = vec[prob[ind].first][prob[ind].second];

            //remove number from grid
            vec[prob[ind].first][prob[ind].second] = 0;

            //if there is no one solution after removing this cell ignore it and try another one
            if(!checkForOneSultion(vec)) 
            {
                vec[prob[ind].first][prob[ind].second] = temp;
                Amount++;
            }

            //erase cell from options to not choose it again
            prob.erase(prob.begin() + ind, prob.begin() + ind + 1);
        }
    } while (!checkForOneSultion(vec));

    //update changes to live grid
    for (int i = 0; i < 9; i++) 
    {
        for (int j = 0; j < 9; j++) 
        {
            //count numbers
            NumCount[vec[i][j]]++;

            if (vec[i][j] == 0) 
            {
                GridSquares[i][j].second.setString(" ");
            }
        }
    }
    return;
}

void Game::chooseAmountToRemove(enum Difficulty diff)
{
    int Amount;
    if (diff == easy) 
    {
        vector<int> amounts;

        //remove from 25 to 35 cells
        for (int i = 25; i <= 35; i++) 
        {
            amounts.push_back(i);
        }
        Amount = amounts[rand() % amounts.size()];
    }
    else if (diff == medium) 
    {
        vector<int> amounts;

        //remove from 43 to 48 cells
        for (int i = 43; i <= 48; i++) 
        {
            amounts.push_back(i);
        }
        Amount = amounts[rand() % amounts.size()];
    }

    else if (diff == hard) 
    {
        vector<int> amounts;

        //remove from 60 to 64 cells
        for (int i = 60; i <= 64; i++) 
        {
            amounts.push_back(i);
        }
        Amount = amounts[rand() % amounts.size()];
    }

    removeCells(Amount);
    updateCounter();
    EmptyCellsRemaining = Amount;
    ColorPreFilledCells();

    //mark pre filled cells
    for (int i = 0; i < 9; i++) 
    {
        for (int j = 0; j < 9; j++) 
        {
            if (GridSquares[i][j].second.getString() != " ")
            {
                isPreFilled[i][j] = 1;
            }
        }
    }
}

void Game::ColorPreFilledCells()
{
    for (int i = 0; i < 9; i++) 
    {
        for (int j = 0; j < 9; j++)
        {
            if (GridSquares[i][j].second.getString() != " ")
            {
                GridSquares[i][j].first.setFillColor(preFilledColor);
            }
            else
            {
                GridSquares[i][j].first.setFillColor(normalColor);
            }
        }
    }
}

void Game::updateCounter()
{
    stringstream ss;
    for (int i = 1; i <= 9; i++) 
    {
        //convert from int to string 
        ss.clear();
        string x;
        ss << 9 - NumCount[i];
        ss >> x;
        x += "/9";

        Vector2f pos = NumbersCounter[i - 1].getPosition();

        //if number is negative shift position to look good
        if (x.size() == 4 && NumbersCounter[i - 1].getString().getSize() == 3) 
        {
            NumbersCounter[i - 1].setPosition(pos.x - 6, pos.y);
        }
        else if (x.size() == 3 && NumbersCounter[i - 1].getString().getSize() == 4) 
        {
            NumbersCounter[i - 1].setPosition(pos.x + 6, pos.y);
        }

        NumbersCounter[i - 1].setString(x);
    }
    ss.clear();
    string x, final;
    final = "Mistakes: ";
    ss << mistakesMade;
    ss >> x;
    x += " / 3";
    final += x;
    Mistakes.setString(final);
}

void Game::setTime() 
{
    string temp, seconds, minutes;
    stringstream ss;

    int secs = this->gameTimeCounterClock->getElapsedTime().asSeconds();

    //convert seconds into minutes
    ss << secs % 60;
    ss >> seconds;
    ss.clear();
    ss << secs / 60;
    ss >> minutes;

    if (seconds.size() < 2) seconds.insert(0, "0");
    if (minutes.size() < 1) minutes = "0";

    //if more than 3 digits shift left 
    if (minutes.size() + seconds.size() >= 4 && !timeCounterMoreThanFourDigits) 
    {
        Vector2f prevPos = timeText.getPosition();
        prevPos.x -= 20;
        timeText.setPosition(prevPos);
        timeCounterMoreThanFourDigits = 1;
    }
    temp += minutes;
    temp.push_back(':');
    temp += seconds;
    this->timeText.setString(temp);
}

void Game::runGame(enum Difficulty diff)
{
    //remove slected square
    if (SelectedSquare.first != -1) 
    {
        highlight(SelectedSquare.first, SelectedSquare.second, 1);
        GridSquares[SelectedSquare.first][SelectedSquare.second].first.setFillColor(Color::White);
        SelectedSquare = { -1, -1 };
    }

    currScreen = game;
    this->gameTimeCounterClock = new Clock;

    mistakesMade = 0;
    memset(NumCount, 0, sizeof(NumCount));
    memset(isPreFilled, 0, sizeof(isPreFilled));

    while (!GenerateGrid());
    chooseAmountToRemove(diff);
}

void Game::blurBackground()
{
    //capture the frame
    blur = this->window->capture();

    //make a non-edited frame for the transition
    prevFrame = blur;
    prevFrameText.loadFromImage(prevFrame);
    PrevFrameSprite.setTexture(prevFrameText);

    //create a result image to avoid interference in the blur
    Final.create(blur.getSize().x, blur.getSize().y);

    int kernelSize = 4, passes = 3, resx = 2, resy = 2;
    for(int pass = 0; pass < passes; pass++)
    {
        //Vertical blur
        for (int i = 0; i < blur.getSize().x; i++) 
        {
            //iterate over neighbouring pixels
            for (int j = 0; j < blur.getSize().y - (resy - 1); j += resy) 
            {
                //Get sum
                int r = 0, g = 0, b = 0, cntr = 0;
                for (int k = max(0, j - kernelSize); k <= min(j + kernelSize, (int)blur.getSize().y - 1); k++) 
                {
                    Color pixelColor = (!pass ? blur.getPixel(i, k): Final.getPixel(i, k));
                    r += pixelColor.r;
                    g += pixelColor.g;
                    b += pixelColor.b;
                    cntr++;
                }

                //Average pixels
                r /= cntr, g /= cntr, b /= cntr;
                Color fillColor = Color(r, g, b, 0);

                //set all pixels according to resolution of blur
                for (int l = 0; l < resy; l++) 
                {
                    Final.setPixel(i, j + l, fillColor);
                }
            }
        }

        //Horizontal blur
        for (int i = 0; i < blur.getSize().y; i++) 
        {
            //iterate over neighbouring pixels
            for (int j = 0; j < blur.getSize().x - (resx - 1); j += resx) 
            {
                //Get sum
                int r = 0, g = 0, b = 0, cntr = 0;
                for (int k = max(0, j - kernelSize); k <= min(j + kernelSize, (int)blur.getSize().x - 1); k++) 
                {
                    Color pixelColor = (!pass ? blur.getPixel(k, i) : Final.getPixel(k, i));
                    r += pixelColor.r;
                    g += pixelColor.g;
                    b += pixelColor.b;
                    cntr++;
                }

                //Average pixels
                r /= cntr, g /= cntr, b /= cntr;
                Color fillColor = Color(r, g, b, 0);

                //set all pixels according to resolution of blur
                for (int l = 0; l < resx; l++) {
                    Final.setPixel(j + l, i, fillColor);
                }
            }
        }
    }

    blurTexture.setSmooth(1);
    blurTexture.loadFromImage(Final);
    blurSprite.setTexture(blurTexture);

    //scale according to window size
    if (currWindowSize == small) 
    {
        float factorx = Width / (450 + (LineThickness * 7));
        float factory = Height / ((450 + (LineThickness * 7) + 125 + gridPadding));

        blurSprite.setScale(Vector2f(factorx, factory));
        PrevFrameSprite.setScale(Vector2f(factorx, factory));
    }
    else 
    {
        blurSprite.setScale(Vector2f(1, 1));
        PrevFrameSprite.setScale(Vector2f(1, 1));
    }
}

bool Game::fadeImage()
{
    int coff = 20;
    for (int i = 0; i < blur.getSize().x; i++) {
        for (int j = 0; j < blur.getSize().y; j++) {
            Color fillColor = Final.getPixel(i, j);
            if (fillColor.a >= 255) {
                return 0;
            }
            fillColor.a = min(255, fillColor.a + coff);
            Final.setPixel(i, j, fillColor);
        }
    }
    blurTexture.loadFromImage(Final);
    blurSprite.setTexture(blurTexture);

    Color fillColor = GameOverText.getFillColor();
    fillColor.a = min(255, fillColor.a + coff);
    GameOverText.setFillColor(fillColor);

    //////////////////////////////////
    fillColor = GameOverDesc.getFillColor();
    fillColor.a = min(255, fillColor.a + coff);
    GameOverDesc.setFillColor(fillColor);

    //////////////////////////////////
    fillColor = PlayAgain.first.getFillColor();
    fillColor.a = min(255, fillColor.a + coff);
    PlayAgain.first.setFillColor(fillColor);

    fillColor = PlayAgain.first.getOutlineColor();
    fillColor.a = min(255, fillColor.a + coff);
    PlayAgain.first.setOutlineColor(fillColor);

    fillColor = PlayAgain.second.getFillColor();
    fillColor.a = min(255, fillColor.a + coff);
    PlayAgain.second.setFillColor(fillColor);

    //////////////////////////////////
    fillColor = MainMenu.first.getFillColor();
    fillColor.a = min(255, fillColor.a + coff);
    MainMenu.first.setFillColor(fillColor);

    fillColor = MainMenu.first.getOutlineColor();
    fillColor.a = min(255, fillColor.a + coff);
    MainMenu.first.setOutlineColor(fillColor);

    fillColor = MainMenu.second.getFillColor();
    fillColor.a = min(255, fillColor.a + coff);
    MainMenu.second.setFillColor(fillColor);

    //////////////////////////////////
    fillColor = Quit.first.getFillColor();
    fillColor.a = min(255, fillColor.a + coff);
    Quit.first.setFillColor(fillColor);

    fillColor = Quit.first.getOutlineColor();
    fillColor.a = min(255, fillColor.a + coff);
    Quit.first.setOutlineColor(fillColor);

    fillColor = Quit.second.getFillColor();
    fillColor.a = min(255, fillColor.a + coff);
    Quit.second.setFillColor(fillColor);

    ///////////////////////////////////
    return 1;
}

//Selecting / editing
void Game::SelectSquare(int indr, int indc)
{
    //if there is a selected square
    if (SelectedSquare.first != -1) 
    {
        //if pressing on the same square we deselect it
        if (SelectedSquare.first == indr && SelectedSquare.second == indc) 
        {
            highlight(indr, indc, 1);
            SelectedSquare = { -1, -1 };
            return;
        }
        else // deselct previous square to select new one
        { 
            highlight(SelectedSquare.first, SelectedSquare.second, 1);
            GridSquares[indr][indc].first.setFillColor(SelectBlue);
            SelectedSquare = { indr, indc };
        }
    }
    //select square
    highlight(indr, indc);
    SelectedSquare = { indr, indc };
}

void Game::SelectNumber(int ind)
{
    NumPadNumbers[ind].first.setFillColor(Color(180, 180, 180, 255));

    string x;
    x.push_back(ind + 1 + '0');
    this->editSquare(x);

    SelectedNumPadNumber = ind;
}

void Game::editSquare(string num)
{

    if (SelectedSquare.first != -1) {
        
        //return if trying to slect a pre filled cell or a valid one
        string squareNumString = GridSquares[SelectedSquare.first][SelectedSquare.second].second.getString();
        if (squareNumString != " " && stoi(squareNumString) == solution[SelectedSquare.first][SelectedSquare.second]) return;

        //decrement the count of th replaced number and incremnt the count for the placed number
        string prev = GridSquares[SelectedSquare.first][SelectedSquare.second].second.getString();
        if(prev != " ") NumCount[stoi(prev)]--;
        if(num != " ") NumCount[stoi(num)]++;
        
        //set new number and highlight appropriate cells
        GridSquares[SelectedSquare.first][SelectedSquare.second].second.setString(num);
        highlight(SelectedSquare.first, SelectedSquare.second);
        
        //if the placed number is invalid increment the mistakes and highlight invalid
        if (num != " " && stoi(num) != solution[SelectedSquare.first][SelectedSquare.second]) 
        {
            mistakesMade++;
        }
        else // else if valid color it and mark it
        {   

            isPreFilled[SelectedSquare.first][SelectedSquare.second] = 1;
            EmptyCellsRemaining--;
            if (EmptyCellsRemaining <= 0)
            {
                //update and render new frame before blurring it
                update();

                //render twice because of doublle buffering to make sure the blur is applied top the latest frame
                render();
                render();

                blurBackground();

                //change text because same functions are used for game over screen
                GameOverText.setString("Congratulations!");
                GameOverText.setCharacterSize(93);
                GameOverText.setPosition(20, 60);

                GameOverDesc.setString("You completed the Sudoku.");
                GameOverDesc.setPosition(145, 190);

                currGameScreen = GameOver;
            }
        }

        //if enough mistakes made go to game over screen
        if (mistakesMade > 3) 
        {
            //update and render new frame before blurring it
            update();

            //render twice because of doublle buffering to make sure the blur is applied top the latest frame
            render();
            render();

            blurBackground();
            currGameScreen = GameOver;

            //change text because same functions are used for game win screen
            GameOverText.setString("Game Over!");
            GameOverText.setCharacterSize(120);
            GameOverText.setPosition(70, 60);

            GameOverDesc.setString("You made too many mistakes.");
            GameOverDesc.setPosition(140, 190);
        }
    }
}

void Game::Select(Vector2f Pos)
{
    for (int i = 0; i < 9; i++) 
    {
        for (int j = 0; j < 9; j++) 
        {
            if (withinRect(Pos, GridSquares[i][j].first.getGlobalBounds())) 
            {
                SelectSquare(i, j);
                return;
            }
        }
    }
    for (int i = 0; i < 9; i++) 
    {
        if (withinRect(Pos, NumPadNumbers[i].first.getGlobalBounds())) 
        {
            SelectNumber(i);
            return;
        }
    }
    if (SelectedGameHud != Gamenone) 
    {
        switch (SelectedGameHud)
        {
            case Game::Gameback:
                currScreen = difficulty;
                if (SelectedSquare.first != -1) highlight(SelectedSquare.first, SelectedSquare.second, 1);
                SelectedSquare = { -1, -1 };
                break;
            case Game::Gamemusic:
                ToggleMusic();
                break;
            default:
                break;
        }
    }
}

void Game::SelectSettingsButton(Vector2f pos)
{
    if (withinRect(pos, WindowSmall.first.getGlobalBounds())) 
    {
        currWindowSize = small;
        WindowSmall.first.setFillColor(SelectColor);
        WindowLarge.first.setFillColor(Color::White);
        this->window->setSize(Vector2u(450 + (LineThickness * 7), 450 + (LineThickness * 7) + 125 + gridPadding));
    }
    if (withinRect(pos, WindowLarge.first.getGlobalBounds())) 
    {
        currWindowSize = large;
        WindowSmall.first.setFillColor(Color::White);
        WindowLarge.first.setFillColor(SelectColor);
        this->window->setSize(Vector2u(540 + (LineThickness * 7), 540 + (LineThickness * 7) + 125 + gridPadding));
    }
}

//Globally used 
Vector2f Game::GetMousePos()
{
    Vector2i pos = Mouse::getPosition(*this->window);
    return this->window->mapPixelToCoords(pos);
}

bool Game::withinRect(Vector2f pos, FloatRect rect)
{
    if (pos.x >= rect.left && pos.x <= rect.left + rect.width) 
    {
        if (pos.y >= rect.top && pos.y <= rect.top + rect.height) 
        {
            return 1;
        }
    }
    return 0;
}

void Game::takeScreenShot()
{
    Image ScreenShot = this->window->capture();
    ScreenShot.saveToFile("ScreenShot.png");
}

// Constructor & Destructor

Game::Game()
{
    this->initTextures();
    this->initMusic();
    this->initvar();
    this->initfont();
    this->initText();
    this->initMenu();
    this->initgrid();
    this->initNumbers();
    this->initSettings();
    this->initwindow();
    this->initGameOver();
}

Game::~Game()
{
    delete this->window;
}

//Accessors

bool Game::running()
{
    return this->window->isOpen();
}

//Fucntions

//Event polling
void Game::pollGamePlayEvents()
{
    while (this->window->pollEvent(this->ev))
    {
        switch (this->ev.type)
        {
            case Event::Closed:
                this->window->close();
                break;
            case Event::MouseButtonPressed:
                switch (ev.mouseButton.button)
                {
                    case Mouse::Left:
                        this->Select(GetMousePos());
                        break;
                }
                break;
            case Event::MouseButtonReleased:
                switch (ev.mouseButton.button)
                {
                    case Mouse::Left:
                        for (int i = 0; i < 9; i++) {
                            NumPadNumbers[i].first.setFillColor(NumbersColor);
                        }
                        break;
                }
                break;
            case Event::KeyPressed:
                switch (ev.key.code) {
                    case Keyboard::Num1:
                    case Keyboard::Numpad1:
                        this->editSquare("1");
                        break;
                    case Keyboard::Num2:
                    case Keyboard::Numpad2:
                        this->editSquare("2");
                        break;
                    case Keyboard::Num3:
                    case Keyboard::Numpad3:
                        this->editSquare("3");
                        break;
                    case Keyboard::Num4:
                    case Keyboard::Numpad4:
                        this->editSquare("4");
                        break;
                    case Keyboard::Num5:
                    case Keyboard::Numpad5:
                        this->editSquare("5");
                        break;
                    case Keyboard::Num6:
                    case Keyboard::Numpad6:
                        this->editSquare("6");
                        break;
                    case Keyboard::Num7:
                    case Keyboard::Numpad7:
                        this->editSquare("7");
                        break;
                    case Keyboard::Num8:
                    case Keyboard::Numpad8:
                        this->editSquare("8");
                        break;
                    case Keyboard::Num9:
                    case Keyboard::Numpad9:
                        this->editSquare("9");
                        break;
                    case Keyboard::BackSpace:
                        this->editSquare(" ");
                        break;
                }
                break;
        }
    }
}

void Game::pollGameOverEvents()
{
    while (this->window->pollEvent(this->ev))
    {
        switch (ev.type)
        {
            case Event::Closed:
                this->window->close();
                break;
            case Event::MouseButtonPressed:
                switch (ev.mouseButton.button)
                {
                    /*case Mouse::Right:
                        Final.saveToFile("ScreenShotBlurry.png");
                        break;*/
                    case Mouse::Left:
                        switch (SelectedGameOverButton)
                        {
                            case Game::GameOverPlayAgain:
                                currGameScreen = GamePlay;
                                runGame(easy);
                                fadeComplete = 0;

                                break;
                            case Game::GameOverMainMenu:
                                currGameScreen = GamePlay;
                                fadeComplete = 0;
                                currScreen = menu;
                                break;
                            case Game::GameOverQuit:
                                this->window->close();
                                break;
                            default:
                                break;
                        }
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
        }
    }
}

void Game::pollMenuEvents()
{
    while (this->window->pollEvent(this->ev))
    {
        switch (ev.type)
        {
            case Event::Closed:
                this->window->close();
                break;
            case Event::MouseButtonPressed:
                switch (ev.mouseButton.button)
                {
                    case Mouse::Left:
                        switch (SelectedMenuButton)
                        {
                            case Game::play:
                                this->initDifficulty();
                                currScreen = difficulty;
                                break;
                            case Game::exit:
                                this->window->close();
                            case Menusettings:
                                currScreen = settings;
                                break;
                            case Menumusic:
                                ToggleMusic();
                                break;
                            default:
                                break;
                        }
                        break;
                    default:
                        break;
                }
                break;
        }
    }
}

void Game::pollDifficultyEvents()
{
    while (this->window->pollEvent(this->ev))
    {
        switch (ev.type)
        {
            case Event::Closed:
                this->window->close();
                break;
            case Event::MouseButtonPressed:
                switch (ev.mouseButton.button)
                {
                    case Mouse::Left:
                        switch (SelectedDifficulty)
                        {
                            case Diffnone:
                                break;
                            case Diffback:
                                currScreen = menu;
                                break;
                            case Diffmusic:
                                ToggleMusic();
                                break;
                            default:
                                runGame(SelectedDifficulty);
                                break;
                        }
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
        }
    }
}

void Game::pollGameEvents()
{
    switch (currGameScreen)
    {
        case Game::GameOver:
            pollGameOverEvents();
            break;
        case Game::GameWin:
            break;
        case Game::GamePlay:
            pollGamePlayEvents();
            break;
        default:
            break;
    }
}

void Game::pollSettingsEvents()
{
    while (this->window->pollEvent(ev))
    {
        switch (ev.type)
        {
            case Event::Closed:
                this->window->close();
                break;
            case Event::MouseButtonPressed:
                switch (ev.mouseButton.button)
                {
                    case Mouse::Left:
                        switch (SelectedSettingsButton)
                        {
                            case Game::Settingsback:
                                currScreen = menu;
                                break;
                            case Settingsmusic:
                                ToggleMusic();
                                break;
                            case Settingsnone:
                                SelectSettingsButton(GetMousePos());
                                break;
                            default:
                                break;
                        }
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
        }
    }
}

//updating
void Game::updateMenu()
{
    this->pollMenuEvents();
    this->highlightMenuButton();
}

void Game::updateGame()
{
    switch (currGameScreen)
    {
        case Game::GameOver:
            updateGameOver();
            break;
        case Game::GameWin:
            break;
        case Game::GamePlay:
            updateGamePlay();
            break;
        default:
            break;
    }
}

void Game::updateDifficulty()
{
    this->pollDifficultyEvents();
    this->highlightDiffButton();
}

void Game::updateSettings()
{
    this->pollSettingsEvents();
    this->highlightSettings();
}

void Game::updateGameOver()
{
    pollGameOverEvents();
    GameOverHighlight();
}

void Game::updateGamePlay()
{
    this->pollGameEvents();
    this->setTime();
    this->highlightGamehud();
    this->updateCounter();
}

void Game::update()
{
    switch (currScreen)
    {
        case Game::menu:
            this->updateMenu();
            break;
        case Game::game:
            this->updateGame();
            break;
        case Game::difficulty:
            this->updateDifficulty();
            break;
        case Game::settings:
            this->updateSettings();
            break;
        default:
            break;
    }
}

//rendering
void Game::renderMenu()
{
    this->window->draw(MainMenuSudokuText);
    this->window->draw(MainMenuPlayButton.first);
    this->window->draw(MainMenuPlayButton.second);
    this->window->draw(MainMenuSettingsButton.first);
    this->window->draw(MainMenuSettingsButton.second);
    this->window->draw(MainMenuExitButton.first);
    this->window->draw(MainMenuExitButton.second);
}

void Game::renderGame()
{
    switch (currGameScreen)
    {
        case Game::GameOver:
            renderGameOver();
            break;
        case Game::GameWin:
            break;
        case Game::GamePlay:
            renderGamePlay();
            break;
        default:
            break;
    }
}

void Game::renderDifficulty()
{
    //draw
    this->window->draw(Difficulty);
    this->window->draw(Easy.first);
    this->window->draw(Easy.second);
    this->window->draw(Medium.first);
    this->window->draw(Medium.second);
    this->window->draw(Hard.first);
    this->window->draw(Hard.second);
    this->window->draw(BackArrow);
}

void Game::renderSettings()
{
    this->window->draw(BackArrow);
    this->window->draw(SettingsText);
    this->window->draw(WindowSmall.first);
    this->window->draw(WindowSmall.second);
    this->window->draw(WindowLarge.first);
    this->window->draw(WindowLarge.second);
    this->window->draw(settingsWindowSize);
}

void Game::renderGameOver()
{
    if (!fadeComplete) {
        fadeComplete = !fadeImage();
        this->window->draw(PrevFrameSprite);
    }
    this->window->draw(blurSprite);
    this->window->draw(GameOverText);
    this->window->draw(PlayAgain.first);
    this->window->draw(PlayAgain.second);
    this->window->draw(MainMenu.first);
    this->window->draw(MainMenu.second);
    this->window->draw(Quit.first);
    this->window->draw(Quit.second);
    this->window->draw(GameOverDesc);
}

void Game::renderGamePlay()
{
    for (auto vec : GridSquares) {
        for (auto rect : vec) {
            this->window->draw(rect.first);
            this->window->draw(rect.second);
        }
    }
    for (auto it : NumPadNumbers) {
        this->window->draw(it.first);
        this->window->draw(it.second);
    }
    this->window->draw(timeText);
    for (RectangleShape rect : GridLines) {
        this->window->draw(rect);
    }
    for (auto text : NumbersCounter) {
        this->window->draw(text);
    }
    this->window->draw(BackArrow);
    this->window->draw(GameHudText);
    this->window->draw(Mistakes);
}

void Game::render()
{
    
    this->window->clear(Color::White);

    this->window->draw(MusicIcon);
    switch (currScreen)
    {
        case Game::menu:
            this->renderMenu();
            break;
        case Game::game:
            this->renderGame();
            break;
        case Game::difficulty:
            this->renderDifficulty();
            break;
        case Game::settings:
            this->renderSettings();
            break;
        default:
            break;
    }
    this->window->display();
}