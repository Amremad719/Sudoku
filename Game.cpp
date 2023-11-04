// @author: Amremad719
#include "Game.h"
#include "SQL.h"
#define s ' '
#pragma warning(disable : 4996)
using namespace std;
using namespace sf;

#define pi 3.14159265359

//initializers
void Game::initvar()
{
    this->window = nullptr;
    this->gameTimeCounterClock = nullptr;
}

void Game::initwindow()
{
    conSett.antialiasingLevel = 16;
    
    this->video.height = Height;
    this->video.width = Width;
    this->window = new RenderWindow(this->video, "Sudoku", Style::Close);
    
    this->AppImage.loadFromFile("icon.png");
    this->window->setIcon(this->AppImage.getSize().x, this->AppImage.getSize().y, this->AppImage.getPixelsPtr());
    
    this->window->setFramerateLimit(60);

    //if screen is small open in small window mode
    if (VideoMode::getDesktopMode().height < Height + 100) 
    {
        currWindowSize = Small;
        WindowSmall.first.setFillColor(SelectColor);
        WindowLarge.first.setFillColor(normalColor);
    }

    //if selected window size is small scale the window
    if (currWindowSize == Small) {
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
    this->text.setColor(TextColor);
    this->text.setString(" ");
    
    //time counter text
    this->timeText.setFont(font);
    this->timeText.setCharacterSize(gridSize / 10);
    this->timeText.setColor(TextColor);
    this->timeText.setPosition(gridSize - 45, gridSize + (LineThickness * 7) - 10 + gridPadding);
    this->timeText.setString("0:00");
   
    //Sudoku text on the top of the page in game
    this->GameHudText.setFont(font);
    this->GameHudText.setCharacterSize(50);
    this->GameHudText.setColor(TextColor);
    this->GameHudText.setPosition(230, -7);
    this->GameHudText.setString("Sudoku");

    //mistakes counter in game
    this->Mistakes.setFont(font);
    this->Mistakes.setColor(TextColor);
    this->Mistakes.setCharacterSize(30);
    this->Mistakes.setPosition(7, gridSize + (LineThickness * 7) - 3 + gridPadding);
}

void Game::initMenu()
{
    Vector2f Playpos = Vector2f(193, 220);
    Vector2f Settingspos = Vector2f(193, Playpos.y + 130);
    Vector2f Statisticspos = Vector2f(193, Settingspos.y + 130);
    Vector2f Exitpos = Vector2f(193, Statisticspos.y + 130);

//button squares

    //play
    MainMenuPlayButton.first.setFillColor(normalColor);
    MainMenuPlayButton.first.setPosition(Playpos);
    MainMenuPlayButton.first.setSize(Vector2f(200, 70));
    MainMenuPlayButton.first.setOutlineThickness(7);
    MainMenuPlayButton.first.setOutlineColor(TextColor);

    //Exit
    MainMenuExitButton.first.setFillColor(normalColor);
    //temporarly Statisticspos because not finished yet supposed to be Exitpos
    MainMenuExitButton.first.setPosition(Exitpos);
    MainMenuExitButton.first.setSize(Vector2f(200, 70));
    MainMenuExitButton.first.setOutlineThickness(7);
    MainMenuExitButton.first.setOutlineColor(TextColor);

    //Settings
    MainMenuSettingsButton.first.setFillColor(normalColor);
    MainMenuSettingsButton.first.setPosition(Settingspos);
    MainMenuSettingsButton.first.setSize(Vector2f(200, 70));
    MainMenuSettingsButton.first.setOutlineThickness(7);
    MainMenuSettingsButton.first.setOutlineColor(TextColor);

    //Statistics
    StatisticsButton.first.setFillColor(normalColor);
    StatisticsButton.first.setPosition(Statisticspos);
    StatisticsButton.first.setSize(Vector2f(200, 70));
    StatisticsButton.first.setOutlineThickness(7);
    StatisticsButton.first.setOutlineColor(TextColor);

//button text

    //Play
    MainMenuPlayButton.second.setFillColor(TextColor);
    MainMenuPlayButton.second.setCharacterSize(70);
    MainMenuPlayButton.second.setPosition(Playpos.x + 47, Playpos.y - 10);
    MainMenuPlayButton.second.setString("Play");
    MainMenuPlayButton.second.setFont(font);

    //Exit
    MainMenuExitButton.second.setFillColor(TextColor);
    MainMenuExitButton.second.setCharacterSize(70);
    //temporarly Statisticspos because not finished yet supposed to be Exitpos
    MainMenuExitButton.second.setPosition(Exitpos.x + 52, Exitpos.y - 10);
    MainMenuExitButton.second.setString("Exit");
    MainMenuExitButton.second.setFont(font);

    //Settings
    MainMenuSettingsButton.second.setFillColor(TextColor);
    MainMenuSettingsButton.second.setCharacterSize(65);
    MainMenuSettingsButton.second.setPosition(Settingspos.x + 7, Settingspos.y - 8);
    MainMenuSettingsButton.second.setString("Settings");
    MainMenuSettingsButton.second.setFont(font);

    //Statistics
    StatisticsButton.second.setFillColor(TextColor);
    StatisticsButton.second.setCharacterSize(55);
    StatisticsButton.second.setPosition(Statisticspos.x + 7, Statisticspos.y - 1);
    StatisticsButton.second.setString("Statistics");
    StatisticsButton.second.setFont(font);

//Title
    MainMenuSudokuText.setFillColor(TextColor);
    MainMenuSudokuText.setCharacterSize(140);
    MainMenuSudokuText.setPosition(125, 20);
    MainMenuSudokuText.setString("Sudoku");
    MainMenuSudokuText.setFont(font);
}

void Game::initgrid()
{
    RectangleShape rect;
    //Squares

    float x = LineThickness, y = LineThickness;
    rect.setFillColor(normalColor);
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

    rect.setFillColor(internalGridLinesColor);
    
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
    rect.setFillColor(ExternalGridLinesColor);
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
    Vector2f Easypos = Vector2f(193, 220);
    Vector2f Mediumpos = Vector2f(193, Easypos.y + 130);
    Vector2f Hardpos = Vector2f(193, Mediumpos.y + 130);

//Buttons rectangle
    Easy.first.setFillColor(normalColor);
    Easy.first.setPosition(Easypos);
    Easy.first.setSize(Vector2f(200, 70));
    Easy.first.setOutlineThickness(7);
    Easy.first.setOutlineColor(TextColor);
    
    Medium.first.setFillColor(normalColor);
    Medium.first.setPosition(Mediumpos);
    Medium.first.setSize(Vector2f(200, 70));
    Medium.first.setOutlineThickness(7);
    Medium.first.setOutlineColor(TextColor);
   
    Hard.first.setFillColor(normalColor);
    Hard.first.setPosition(Hardpos);
    Hard.first.setSize(Vector2f(200, 70));
    Hard.first.setOutlineThickness(7);
    Hard.first.setOutlineColor(TextColor);
    
//Buttons text
    Easy.second.setFillColor(TextColor);
    Easy.second.setCharacterSize(70);
    Easy.second.setPosition(Easypos.x + 47, Easypos.y - 10);
    Easy.second.setString("Easy");
    Easy.second.setFont(font);
    
    Medium.second.setFillColor(TextColor);
    Medium.second.setCharacterSize(70);
    Medium.second.setPosition(Mediumpos.x + 15, Mediumpos.y - 10);
    Medium.second.setString("Medium");
    Medium.second.setFont(font);
    
    Hard.second.setFillColor(TextColor);
    Hard.second.setCharacterSize(70);
    Hard.second.setPosition(Hardpos.x + 42, Hardpos.y - 10);
    Hard.second.setString("Hard");
    Hard.second.setFont(font);

//Title
    Difficulty.setFillColor(TextColor);
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
    rect.setFillColor(normalColor);
    rect.setOutlineThickness(5);
    rect.setOutlineColor(ExternalGridLinesColor);
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

void Game::initSound() {
    this->ClickSoundBuffer.loadFromFile("Sounds/Click Sound Effect.wav");
    this->ClickSound.setBuffer(ClickSoundBuffer);

    this->musicBuffer.loadFromFile("Sounds/Music.wav");
    this->Music.setBuffer(musicBuffer);
    this->Music.setLoop(true);

    Music.setVolume(0);

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
    SettingsText.setFillColor(TextColor);

    Vector2f pos = { 30, 100 };

    settingsWindowSize.setFont(font);
    settingsWindowSize.setCharacterSize(45);
    settingsWindowSize.setPosition(pos);
    settingsWindowSize.setString("Window Size");
    settingsWindowSize.setFillColor(TextColor);

    ThemeText.setFont(font);
    ThemeText.setCharacterSize(45);
    ThemeText.setPosition(pos.x, pos.y + 100);
    ThemeText.setString("Theme");
    ThemeText.setFillColor(TextColor);

//Small Window Button
    //rectangle
    WindowSmall.first.setOutlineThickness(5);
    WindowSmall.first.setOutlineColor(TextColor);
    WindowSmall.first.setFillColor((currWindowSize == Small ? SelectColor:normalColor));
    WindowSmall.first.setPosition(pos.x + 300, pos.y + 7);
    WindowSmall.first.setSize(Vector2f(90, 40));
    //text
    WindowSmall.second.setFont(font);
    WindowSmall.second.setCharacterSize(40);
    WindowSmall.second.setPosition(pos.x + 300 + 5, pos.y + 1);
    WindowSmall.second.setString("Small");
    WindowSmall.second.setFillColor(TextColor);

//Large Window Button
    //rectangle
    WindowLarge.first.setOutlineThickness(5);
    WindowLarge.first.setOutlineColor(TextColor);
    WindowLarge.first.setFillColor((currWindowSize == large ? SelectColor : normalColor));
    WindowLarge.first.setPosition(pos.x + 420, pos.y + 7);
    WindowLarge.first.setSize(Vector2f(90, 40));

    //text
    WindowLarge.second.setFont(font);
    WindowLarge.second.setCharacterSize(40);
    WindowLarge.second.setPosition(pos.x + 420 + 5, pos.y + 1);
    WindowLarge.second.setString("Large");
    WindowLarge.second.setFillColor(TextColor);

//Dark Theme Button
    //rectangle
    ThemeDark.first.setOutlineThickness(5);
    ThemeDark.first.setOutlineColor(TextColor);
    ThemeDark.first.setFillColor(DarkThemeActive ? SelectColor : normalColor);
    ThemeDark.first.setPosition(pos.x + 300, pos.y + 7 + 101);
    ThemeDark.first.setSize(Vector2f(90, 40));
    //text
    ThemeDark.second.setFont(font);
    ThemeDark.second.setCharacterSize(40);
    ThemeDark.second.setPosition(pos.x + 305 + 6, pos.y + 100 + 3);
    ThemeDark.second.setString("Dark");
    ThemeDark.second.setFillColor(TextColor);

//Light Theme Button
    //rectangle
    ThemeLight.first.setOutlineThickness(5);
    ThemeLight.first.setOutlineColor(TextColor);
    ThemeLight.first.setFillColor(DarkThemeActive ? normalColor : SelectColor);
    ThemeLight.first.setPosition(pos.x + 420, pos.y + 7 + 101);
    ThemeLight.first.setSize(Vector2f(90, 40));
    //text
    ThemeLight.second.setFont(font);
    ThemeLight.second.setCharacterSize(40);
    ThemeLight.second.setPosition(pos.x + 430, pos.y + 100 + 3);
    ThemeLight.second.setString("Light");
    ThemeLight.second.setFillColor(TextColor);
}

void Game::initGameOver()
{
    

    GameOverText.setFont(font);
    GameOverText.setFillColor(transparentBlack);

    GameOverDesc.setFont(font);
    GameOverDesc.setCharacterSize(30);
    GameOverDesc.setFillColor(transparentBlack);

    Vector2f RestartPos = { 196, 275 };
    Vector2f QuitPos = { 196, 525 };
    Vector2f MainMenuPos = { 196, 400 };

    //rectangle
    PlayAgain.first.setPosition(RestartPos);
    PlayAgain.first.setOutlineThickness(5);
    PlayAgain.first.setSize(Vector2f(190, 60));
    PlayAgain.first.setOutlineColor(transparentBlack);
    PlayAgain.first.setFillColor(transparentGrey);
    //text
    PlayAgain.second.setFont(font);
    PlayAgain.second.setCharacterSize(50);
    PlayAgain.second.setString("Play Again");
    PlayAgain.second.setFillColor(transparentBlack);
    PlayAgain.second.setPosition(RestartPos.x + 6, RestartPos.y);


    //rectangle
    MainMenu.first.setPosition(MainMenuPos);
    MainMenu.first.setOutlineThickness(5);
    MainMenu.first.setSize(Vector2f(190, 60));
    MainMenu.first.setOutlineColor(transparentBlack);
    MainMenu.first.setFillColor(transparentGrey);
    //text
    MainMenu.second.setFont(font);
    MainMenu.second.setCharacterSize(50);
    MainMenu.second.setString("Main Menu");
    MainMenu.second.setFillColor(transparentBlack);
    MainMenu.second.setPosition(MainMenuPos.x + 8, MainMenuPos.y);

    //rectangle
    Quit.first.setPosition(QuitPos);
    Quit.first.setOutlineThickness(5);
    Quit.first.setSize(Vector2f(190, 60));
    Quit.first.setOutlineColor(transparentBlack);
    Quit.first.setFillColor(transparentGrey);
    //text
    Quit.second.setFont(font);
    Quit.second.setCharacterSize(50);
    Quit.second.setString("Quit");
    Quit.second.setFillColor(transparentBlack);
    Quit.second.setPosition(QuitPos.x + 58, QuitPos.y);
}

void Game::initStatistics()
{
//Title
    StatisticsTitle.setFont(font);
    StatisticsTitle.setCharacterSize(50);
    StatisticsTitle.setColor(TextColor);
    StatisticsTitle.setPosition(192, -7);
    StatisticsTitle.setString("Statistics");
    StatisticsTitle.setLetterSpacing(1.8);

    Vector2f Easypos, Mediumpos, Hardpos;
    Easypos = { 35, 80 };
    Mediumpos = { Easypos.x + 175, 80 };
    Hardpos = { Mediumpos.x + 220, 80 };


//Easy
    StatEasy.setFont(font);
    StatEasy.setCharacterSize(60);
    StatEasy.setColor(TextColor);
    StatEasy.setPosition(Easypos);
    StatEasy.setString("Easy");
    StatEasy.setLetterSpacing(1.8);

//Medium
    StatMedium.setFont(font);
    StatMedium.setCharacterSize(60);
    StatMedium.setColor(TextColor);
    StatMedium.setPosition(Mediumpos);
    StatMedium.setString("Medium");
    StatMedium.setLetterSpacing(1.8);

//Hard
    StatHard.setFont(font);
    StatHard.setCharacterSize(60);
    StatHard.setColor(TextColor);
    StatHard.setPosition(Hardpos);
    StatHard.setString("Hard");
    StatHard.setLetterSpacing(1.8);

//Grid
    RectangleShape rect;
    rect.setSize(Vector2f(160, LineThickness / 2));
    rect.setFillColor(LineBlue);
    Vector2f pos = { 10, 217 };
    for (int j = 0; j < 3; j++)
    {
        //do each column
        for (int i = 0; i < 9; i++)
        {
            rect.setPosition(pos);
            StatGridLines.push_back(rect);
            pos.y += 60;
        }
        //go to next column
        pos.x += 200;
        pos.y = 217;
    }
    // vertical seperators
    rect.setSize(Vector2f(LineThickness / 2, 560));
    rect.setFillColor(LineGreen);

    rect.setPosition({ 189, 180});
    StatGridLines.push_back(rect);

    rect.setPosition({ 389, 180 });
    StatGridLines.push_back(rect);
}

void Game::initAll()
{
    this->initText();
    this->initMenu();
    this->initgrid();
    this->initNumbers();
    this->initSettings();
    this->initGameOver();
    this->initStatistics();
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

void Game::highlightStatisticsButton()
{
    bool withinAnyButton = 0;
    Vector2f pos = GetMousePos();

    //Back Arrow
    if (withinRect(pos, BackArrow.getGlobalBounds()))
    {
        BackArrow.setTexture(BackArrowHighlightedText);
        SelectedStatisticsButton = StatBack;
        withinAnyButton = 1;
    }
    else
    {
        BackArrow.setTexture(BackArrowText);
    }

    //Music 
    if (withinRect(pos, MusicIcon.getGlobalBounds()))
    {
        if (currMusicStatus == Mute)
        {
            MusicIcon.setTexture(MusicMutedHighlightedTexture);
        }
        else
        {
            MusicIcon.setTexture(MusicHighlightedTexture);
        }
        SelectedStatisticsButton = StatMute;
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

    if (!withinAnyButton) SelectedStatisticsButton = Statnone;
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
        MainMenuPlayButton.first.setFillColor(normalColor);
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
        MainMenuSettingsButton.first.setFillColor(normalColor);
    }

    //Statistics
    if (withinRect(mousePos, StatisticsButton.first.getGlobalBounds()))
    {
        StatisticsButton.first.setFillColor(highlightColor);
        SelectedMenuButton = MenuStatistics;
        withinAnyButton = 1;
    }
    else
    {
        StatisticsButton.first.setFillColor(normalColor);
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
        MainMenuExitButton.first.setFillColor(normalColor);
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
                else if (curr != " " && curr == og && og != " ")
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
    bool withinAnyButton = false;

    //Easy
    if (withinRect(mousePos, Easy.first.getGlobalBounds())) 
    {
        Easy.first.setFillColor(highlightColor);
        SelectedDifficulty = easy;
        withinAnyButton = 1;
    }
    else 
    {
        Easy.first.setFillColor(normalColor);
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
        Medium.first.setFillColor(normalColor);
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
        Hard.first.setFillColor(normalColor);
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

void Game::removeHighlight()
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            Color color = isPreFilled[i][j] ? preFilledColor : normalColor;
            GridSquares[i][j].first.setFillColor(color);
        }
    }
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
            
            //get all available numbers for this cell
            bitset<10> inter = rows[i] & columns[j] & squares[i / 3][j / 3];

            //put numbers in vector to be able to choose from them
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

void Game::loadConfig()
{
    char* docdir = getenv("USERPROFILE");
    string dir = docdir;
    dir += "\\Documents\\Sudoku\\config.cfg";
   
    ifstream config(dir);

    string setting;

    config >> setting;
    if (setting == "large") {
        //currWindowSize = large;
    }
    else if (setting == "small") {
        //currWindowSize = Small;
    }

    config >> setting;
    if (setting == "yes") {
        DarkThemeActive = 1;
    }
    else if (setting == "no") {
        DarkThemeActive = 0;
    }

    config >> setting;
    if (setting == "active") {
        currMusicStatus = Active;
    }
    else if (setting == "mute") {
        currMusicStatus = Mute;
    }
}

void Game::saveConfig()
{
    char* docdir = getenv("USERPROFILE");
    string dir = docdir;
    dir += "\\Documents\\Sudoku\\config.cfg";

    ofstream config(dir);
    
    config << (currWindowSize == large ? "large" : "small") << endl;
    config << (DarkThemeActive ? "yes" : "no") << endl;
    config << (currMusicStatus == Active ? "active" : "mute") << endl;
}

void Game::DrawWave()
{
    VertexArray vert(PrimitiveType::TriangleStrip);
    VertexArray vert1(PrimitiveType::TriangleStrip);

    Transform trans, rotation;
    trans.translate(Vector2f(0, 0));
    rotation.rotate(rot);

    Transform rota = trans * rotation;

    int lenght = ceil(sqrt(pow(window->getSize().x, 2) + pow(window->getSize().y, 2)));
    for (int i = 0; i < lenght; i++)
    {
        float x = i * freq - WaveOffset;
        float y = (sin(x * pi / 180) * Amp);

        Vertex a = rota.transformPoint(Vector2f(i, y + Thickness));
        Vertex b = rota.transformPoint(Vector2f(i, y - Thickness));
        a.color = b.color = Color(150, 150, 150);
        vert.append(a);
        vert.append(b);
    }

    WaveOffset += speed;
    if (WaveOffset >= 360) WaveOffset -= 360;

    window->draw(vert);
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
            if (!checkForOneSultion(vec))
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
    int Amount = 0;
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
            else EmptyCellsRemaining++;
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
        GridSquares[SelectedSquare.first][SelectedSquare.second].first.setFillColor(normalColor);
        SelectedSquare = { -1, -1 };
    }

    currScreen = game;
    this->gameTimeCounterClock = new Clock;

    mistakesMade = 0;
    EmptyCellsRemaining = 0;
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
    if (currWindowSize == Small) 
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

void Game::updateTimes()
{
    SelectData(TopTimes);

    text.setFont(font);
    text.setCharacterSize(48);
    text.setColor(StatTextColor);
    Vector2f pos = { 57, 164 };
    TopTimesText.clear();
    stringstream ss;
    for (auto i : TopTimes)
    {
        for (int k = 0; k < min(9, (int)i.second.size()); k++)
        {
            if (!i.second[k]) continue;
            string j, temp;

            ss.clear();
            ss << i.second[k] / 60;
            ss >> j;
            ss.clear();
            ss << i.second[k] % 60;
            ss >> temp;
            j += ":";
            if (temp.size() < 2) temp.insert(0, "0");
            j += temp;

            text.setPosition(pos);
            text.setString(j);
            TopTimesText[i.first].push_back(text);

            pos.y += 60;
        }
        pos.x += 200;
        pos.y = 164;
    }
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
    NumPadNumbers[ind].first.setFillColor(SelectColor);

    string x;
    x.push_back(ind + 1 + '0');
    if (SelectedSquare.first == -1) {
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                string num = GridSquares[i][j].second.getString();
                Color fillColor;
                if (num != " " && num == x && ind + 1 != nonSelectHIghlightNum)
                {
                    fillColor = SelectBlue;
                }
                else
                {
                    if (isPreFilled[i][j])
                    {
                        fillColor = preFilledColor;
                    }
                    else
                    {
                        fillColor = normalColor;
                    }
                }
                GridSquares[i][j].first.setFillColor(fillColor);
            }
        }
        if (nonSelectHIghlightNum == ind + 1) nonSelectHIghlightNum = 0;
        else nonSelectHIghlightNum = ind + 1;
    }
    else {
        this->editSquare(x);
    }

    SelectedNumPadNumber = ind;
}

void Game::editSquare(string num)
{
    if (SelectedSquare.first != -1) {
        if (num == GridSquares[SelectedSquare.first][SelectedSquare.second].second.getString()) return;
        

        //return if trying to slect a pre filled cell or a valid one
        string squareNumString = GridSquares[SelectedSquare.first][SelectedSquare.second].second.getString();
        if (squareNumString != " " && stoi(squareNumString) == solution[SelectedSquare.first][SelectedSquare.second]) return;

        //decrement the count of th replaced number and incremnt the count for the placed number
        string prev = GridSquares[SelectedSquare.first][SelectedSquare.second].second.getString();
        if(prev != " ") NumCount[stoi(prev)]--;
        if(num != " ") NumCount[stoi(num)]++;
        
        //set new number and highlight appropriate cells
        GridSquares[SelectedSquare.first][SelectedSquare.second].second.setString(num);
        highlight(SelectedSquare.first, SelectedSquare.second, 1);
        highlight(SelectedSquare.first, SelectedSquare.second);
        
        //if the placed number is invalid increment the mistakes and highlight invalid
        if (num != " " && stoi(num) != solution[SelectedSquare.first][SelectedSquare.second]) 
        {
            mistakesMade++;
        }
        else if(num != " ")// else if valid color it and mark it
        {   

            isPreFilled[SelectedSquare.first][SelectedSquare.second] = 1;
            EmptyCellsRemaining--;
            if (EmptyCellsRemaining <= 0)
            {
                //Add time to database
                string Table, Column = "Time";
                switch (SelectedDifficulty)
                {
                    case Game::easy:
                        Table = "Easy";
                        break;
                    case Game::medium:
                        Table = "Medium";
                        break;
                    case Game::hard:
                        Table = "Hard";
                        break;
                    default:
                        break;
                }
                string time = timeText.getString();
                int Value = 0;
                if (time.size() == 5) {
                    Value += stoi(time.substr(0, 2)) * 60;
                    Value += stoi(time.substr(3, 2));
                }
                else {
                    Value += stoi(time.substr(0, 1)) * 60;
                    Value += stoi(time.substr(2, 2));
                }
                insertData(Table, Column, Value);

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

                GameOverDesc.setString("You completed the Sudoku in " + timeText.getString());
                GameOverDesc.setPosition(120, 190);

                currGameScreen = GameOver;
            }
        }

        //if enough mistakes made go to game over screen
        if (mistakesMade >= 3) 
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
    if(SelectedSquare.first != -1) highlight(SelectedSquare.first, SelectedSquare.second, 1);
    else highlight(0, 0, 1);
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
        currWindowSize = Small;
        WindowSmall.first.setFillColor(SelectColor);
        WindowLarge.first.setFillColor(normalColor);
        this->window->setSize(Vector2u(450 + (LineThickness * 7), 450 + (LineThickness * 7) + 125 + gridPadding));
    }
    if (withinRect(pos, WindowLarge.first.getGlobalBounds())) 
    {
        currWindowSize = large;
        WindowSmall.first.setFillColor(normalColor);
        WindowLarge.first.setFillColor(SelectColor);
        this->window->setSize(Vector2u(540 + (LineThickness * 7), 540 + (LineThickness * 7) + 125 + gridPadding));
    }
    if (withinRect(pos, ThemeDark.first.getGlobalBounds()))
    {
        DarkThemeActive = 1;
        ToggleDarkMode(1);
        ThemeLight.first.setFillColor(normalColor);
        ThemeDark.first.setFillColor(SelectColor);
    }
    if (withinRect(pos, ThemeLight.first.getGlobalBounds()))
    {
        DarkThemeActive = 0;
        ToggleDarkMode(0);
        ThemeDark.first.setFillColor(normalColor);
        ThemeLight.first.setFillColor(SelectColor);
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

//Misc
void Game::ToggleDarkMode(bool DarkMode)
{
    internalGridLinesColor = (DarkThemeActive ? Color(100, 100, 100, 255) : Color(100, 100, 100, 255));
    NumbersColor = (DarkThemeActive ? Color(10, 10, 10, 200) : Color(220, 220, 220, 200));
    normalColor = (DarkThemeActive ? Color(10, 10, 10, 200) : Color(255, 255, 255, 180));
    SelectColor = (DarkThemeActive ? Color(45, 45, 45, 255) : Color(190, 190, 190, 200));
    transparentGrey = (DarkThemeActive ? Color(10, 10, 10, 0) : Color(220, 220, 220, 0));
    transparentBlack = (DarkThemeActive ? Color(230, 230, 230, 0) : Color(0, 0, 0, 0));
    ExternalGridLinesColor = (DarkThemeActive ? Color(120, 120, 120) : Color::Black);
    highlightColor = (DarkThemeActive ? Color(35, 35, 35) : Color(220, 220, 220));
    preFilledColor = (DarkThemeActive ? Color(20, 20, 20) : Color(235, 235, 235));
    StatTextColor = (DarkThemeActive ? Color(120, 120, 120) : Color(40, 40, 40));
    invalidColor = (DarkThemeActive ? Color(75, 30, 30) : Color(255, 170, 170));
    LineGreen = (DarkThemeActive ? Color(140, 255, 140) : Color(40, 200, 40));
    SelectBlue = (DarkThemeActive ? Color(30, 30, 75) : Color(200, 200, 255));
    LineBlue = (DarkThemeActive ? Color(140, 140, 255) : Color(40, 40, 200));
    TextColor = (DarkThemeActive ? Color(230, 230, 230) : Color::Black);

    NumbersCounter.clear();
    NumPadNumbers.clear();
    StatGridLines.clear();
    NumPositions.clear();
    GridSquares.clear();
    GridLines.clear();

    if (DarkThemeActive) {
        MusicMutedTexture.loadFromFile("Textures/MusicMutedLight.png");
        BackArrowText.loadFromFile("Textures/ArrowLight.png");
        MusicTexture.loadFromFile("Textures/MusicLight.png");
    }
    else {
        MusicMutedTexture.loadFromFile("Textures/MusicMuted.png");
        BackArrowText.loadFromFile("Textures/Arrow.png");
        MusicTexture.loadFromFile("Textures/Music.png");
    } 

    initAll();
}

bool Game::FadeMusic()
{
    float vol = Music.getVolume();
    float val = 0.5;
    if (vol + val > 100) return 1;
    Music.setVolume(min(vol + val, 100.0f));
    return 0;
}

// Constructor & Destructor

Game::Game()
{
    loadConfig();
    this->initTextures();
    ToggleDarkMode(DarkThemeActive);
    this->initvar();
    this->initwindow();
    this->initSound();
    this->initfont();
    initDatabase();
}

Game::~Game()
{
    saveConfig();
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
                        ClickSound.play();
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
                ClickSound.play();
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
                        ClickSound.play();
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
                        ClickSound.play();
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
                            case MenuStatistics:
                                updateTimes();
                                currScreen = Statistics;
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
                        ClickSound.play();
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
                        ClickSound.play();
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

void Game::pollStatisticsEvents()
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
                        ClickSound.play();
                        switch (SelectedStatisticsButton)
                        {
                            case Game::StatBack:
                                currScreen = menu;
                                break;
                            case Game::StatMute:
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

void Game::updateStatistics()
{
    pollStatisticsEvents();
    highlightStatisticsButton();
}

void Game::update()
{
    if (!FadeMusicOver) {
        FadeMusicOver = FadeMusic();
    }
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
        case Game::Statistics:
            this->updateStatistics();
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
    this->window->draw(StatisticsButton.first);
    this->window->draw(StatisticsButton.second);
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

void Game::renderStatistics()
{
    this->window->draw(BackArrow);
    this->window->draw(StatisticsTitle);
    this->window->draw(StatEasy);
    this->window->draw(StatMedium);
    this->window->draw(StatHard);
    for (auto it : StatGridLines)
    {
        this->window->draw(it);
    }
    for (auto it : TopTimesText)
    {
        for (auto j : it.second)
        {
            this->window->draw(j);
        }
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
    this->window->draw(ThemeText);
    this->window->draw(ThemeLight.first);
    this->window->draw(ThemeLight.second);
    this->window->draw(ThemeDark.first);
    this->window->draw(ThemeDark.second);
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
    
    this->window->clear(normalColor);

    DrawWave();
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
        case Game::Statistics:
            this->renderStatistics();
        default:
            break;
    }
    this->window->display();
}