// @author: Amremad719
#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"
#include "bits/stdc++.h"


using namespace std;
using namespace sf;


class Game {
private:

    //enums decleration
    enum GameOverButton {GameOverPlayAgain, GameOverMainMenu, GameOverQuit, GameOvernone};
    enum MenuButtons {play, exit, MenuStatistics, Menusettings, Menumusic, Menunone};
    enum Difficulty {easy, medium, hard, Diffback, Diffmusic, Diffnone};
    enum SettingsButtons {Settingsback, Settingsmusic, Settingsnone};
    enum Screen {menu, game, Statistics, difficulty, settings};
    enum StatisticsButton {Statnone, StatBack, StatMute};
    enum GameScreen {GameOver, GameWin, GamePlay};
    enum GameHud {Gameback, Gamemusic, Gamenone};
    enum MusicStatus {Active, Mute};
    enum WindowSize {small, large};

    //enums declaring current status of the game or objects
    SettingsButtons SelectedSettingsButton = Settingsnone;
    GameOverButton SelectedGameOverButton = GameOvernone;
    StatisticsButton SelectedStatisticsButton = Statnone;
    MenuButtons SelectedMenuButton = Menunone;
    Difficulty SelectedDifficulty = Diffnone;
    GameScreen currGameScreen = GamePlay;
    MusicStatus currMusicStatus = Active;
    GameHud SelectedGameHud = Gamenone;
    WindowSize currWindowSize = large;
    Screen currScreen = menu;

    //Colors
    Color highlightColor = Color(220, 220, 220, 255);
    Color SelectColor = Color(190, 190, 190, 255);
    Color NumbersColor = Color(220, 220, 220, 255);
    Color SelectBlue = Color(200, 200, 255, 255);
    Color invalidColor = Color(255, 170, 170, 255);
    Color normalColor = Color::White;
    Color preFilledColor = Color(235, 235, 235, 255);
    Color TextColor = Color::Black;
    Color internalGridLinesColor = Color(100, 100, 100, 255);
    Color ExternalGridLinesColor = Color::Black;
    Color transparentBlack = Color(0, 0, 0, 0);
    Color transparentGrey = Color(220, 220, 220, 0);


    //Music button objects and variables
    Texture MusicTexture, MusicMutedTexture, MusicHighlightedTexture, MusicMutedHighlightedTexture;
    
    //Time counter objects and variables
    bool timeCounterMoreThanFourDigits = 0;
    Clock* gameTimeCounterClock;
    Text timeText;
    
    //Main menu screen objects and variables
    pair<RectangleShape, Text> MainMenuPlayButton, MainMenuExitButton, MainMenuSettingsButton, StatisticsButton;
    Text MainMenuSudokuText;
    
    //Difficulty screen objects and variables
    pair<RectangleShape, Text> Easy, Medium, Hard;
    Text Difficulty;

    //Gameplay related objects and variables
    vector<vector<pair<RectangleShape, Text>>> GridSquares;
    map<string, vector<pair<int, int>>> NumPositions;
    pair<int, int> SelectedSquare = { -1, -1 };
    vector<pair<RectangleShape, Text>> NumPadNumbers;
    vector<RectangleShape> GridLines;
    int SelectedNumPadNumber = -1;
    vector<vector<int>> solution;
    int EmptyCellsRemaining = 0;
    bool isPreFilled[9][9] = {};
    vector<Text> NumbersCounter;
    Text GameHudText, Mistakes;
    float LineThickness = 6;
    int NumCount[10] = {};
    float gridSize = 540;
    int gridPadding = 50;
    int mistakesMade = 0;
    float Numsize = 57;

    //Game Over/Win screen related objects and variables
    pair<RectangleShape, Text> PlayAgain, MainMenu, Quit;
    Sprite blurSprite, PrevFrameSprite;
    Texture blurTexture, prevFrameText;
    Text GameOverDesc, GameOverText;
    Image blur, prevFrame, Final;
    bool fadeComplete = 0;

    //window / app realted objects and variables
    float Width = gridSize + (LineThickness * 7), Height = Width + 125 + gridPadding;
    ContextSettings conSett;
    RenderWindow* window;
    VideoMode video;
    Image AppImage;
    Event ev;
    
    //sound realted objects and variables
    SoundBuffer musicBuffer;
    Sound Music;
    Sprite MusicIcon;
    
    //settings screen related objects and variables
    pair<RectangleShape, Text> WindowSmall, WindowLarge;
    pair<RectangleShape, Text> ThemeDark, ThemeLight;
    Text settingsWindowSize, SettingsText, ThemeText;
    bool DarkThemeActive = 1;

    //Statistics screen realted objects and variables
    fstream StatisticsDatabase;
    vector<Text> topTenTimes;
    set<string> TimesSet;

    //Globally used objects and variables
    Texture BackArrowText, BackArrowHighlightedText;
    Sprite BackArrow;
    Font font;
    Text text;
    
//Functions

    //Event polling functions
    void pollDifficultyEvents();
    void pollGameOverEvents();
    void pollSettingsEvents();
    void pollGamePlayEvents();
    void pollMenuEvents();
    void pollGameEvents();

    //updating functions
    void updateDifficulty();
    void updateSettings();
    void updateGameOver();
    void updateGamePlay();
    void updateCounter();
    void updateGame();
    void updateMenu();

    //rendering functions
    void renderDifficulty();
    void renderGameOver();
    void renderSettings();
    void renderGamePlay();
    void renderGame();
    void renderMenu();

    //Grid numbers generating finctions
    bool checkForOneSultion(vector<vector<int>>);
    void chooseAmountToRemove(enum Difficulty);
    void removeCells(int);
    bool GenerateGrid();

    //Initialising functions
    void initStatisticsDatabase();
    void initSettings();
    void initTextures();
    void initGameOver();
    void initNumbers();
    void initwindow();
    void initMusic();
    void initMenu();
    void initText();
    void initgrid();
    void initfont();
    void initvar(); 
    void initAll();

    //highlighting functions
    void highlightStatisticsButton();
    void highlightMenuButton();
    void highlightDiffButton();
    void GameOverHighlight();
    void highlightSettings();
    void highlightGamehud();
    void removeHighlight();

    //Game play related functions
    void highlight(int, int, bool);
    void runGame(enum Difficulty);
    void SelectSquare(int, int);
    void ColorPreFilledCells();
    void editSquare(string);
    void SelectNumber(int);
    void Select(Vector2f);
    void setTime();

    //settings related functions
    void SelectSettingsButton(Vector2f);
    void ToggleDarkMode(bool);

    //difficulty scren related functions
    void initDifficulty();
    
    //Game over/win screen related functions
    void blurBackground();
    void takeScreenShot();
    bool fadeImage();

    //Statistics related functions
    void pollStatisticsEvents();
    void updateStatistics();
    void renderStatistics();
    void updateTimes();

    //Globally used functions
    bool withinRect(Vector2f, FloatRect);
    Vector2f GetMousePos();
    void ToggleMusic();

public:

    //Constructors & Destructors
    Game();
    ~Game();

    //Accessors
    bool running();

    //Functions
    void update();
    void render();
};