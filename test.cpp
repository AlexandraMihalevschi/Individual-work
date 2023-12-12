#include <graphics.h>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <ctime>

using namespace std;

#define MAX_WORD_LENGTH 50
#define MAX_LIVES 6
#define NUM_LEVELS 5

char level1_words[][50] = {"apple", "melon", "strawberry", "blueberry", "watermelon", "grape", "apricot", "raspberry", "quince", "peach",
                            "fig", "coconut", "pear", "cherry", "mango", "kiwi", "banana", "lime", "lemon", "orange", "pineapple"};
char level2_words[][50] = {"chisinau", "berlin", "london", "kiev", "baku", "bruessels", "brasilia", "ottawa", "cairo", "tallinn", "helsinki",
                            "paris", "tbilisi", "athens", "budapest", "dublin", "rome", "tokyo", "oslo", "warsaw", "seoul", "singapore", "bratislava", "madrid"};
char level3_words[][50] = {"post", "tweet", "like", "comment", "share", "hashtag", "mention", "profile", "status",
                            "tag", "notification", "timeline", "story", "emoji", "viral", "influencer", "filter", "caption", "geotag", "link", "bio", "follow", "unfollow",
                            "subscribe", "unsubscribe",  "trending", "explore",  "feed", "group", "event", "live", "mention", "snap", "pin",  "reaction", "algorithm", "memes"};
char level4_words[][50] = {"margarita", "tequila", "lime", "shake", "martini", "gin", "olive", "mojito", "rum","mint", "syrup", "soda", "ice", "bourbon", "whiskey",
                            "sugar", "vodka", "juice", "glass", "blended", "cosmopolitan", "daiquiri", "wine", "salt", "coke", "cranberry", "orange", "lemon", "straw", "tonic", "sour", "lemonade",
                            "zest", "pineapple", "grenadine"};
char level5_words[][50] = {"set", "subset", "union", "intersection", "complement", "cardinality", "relation", "function", "injective", "surjective", "bijective",
                            "domain", "codomain", "range", "sequence", "permutation", "combination", "coefficient", "graph", "vertex", "edge", "path",
                            "cycle", "tree", "spanning", "connected", "directed", "adjacency", "matrix", "dijkstra", "algorithm", "eulerian", "hamiltonian", "boolean", "logic", "laws",
                            "predicate", "quantifiers", "modulo", "rsa", "counting", "recurrence"};

int numlv1 = sizeof(level1_words) / sizeof(level1_words[0]);
int numlv2 = sizeof(level2_words) / sizeof(level2_words[0]);
int numlv3 = sizeof(level3_words) / sizeof(level3_words[0]);
int numlv4 = sizeof(level4_words) / sizeof(level4_words[0]);
int numlv5 = sizeof(level5_words) / sizeof(level5_words[0]);

char wrongGuesses[MAX_LIVES];
int wrongGuessCount = 0;

void clearWrongGuesses() {
    memset(wrongGuesses, 0, sizeof(wrongGuesses));
    wrongGuessCount = 0;
}

void clearGraphicsWindow() {
    cleardevice(); 
}

void clearScreen()
{
    system("cls");
}

void drawThickHorizontalLine(int x, int y, int length, int thickness) {
    for (int i = 0; i < thickness; ++i) {
        setcolor(BROWN);
        line(x, y + i, x + length, y + i);
    }
}

void drawThickVerticalLine(int x, int y, int length, int thickness) {
    for (int i = 0; i < thickness; ++i) {
        setcolor(BROWN);
        line(x + i, y, x + i, y + length);
    }
}

void displayRules() {
    clearGraphicsWindow();

    setcolor(WHITE);
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);

    outtextxy(50, 50, "Hangman Game Rules:");
    outtextxy(50, 80, "1. You can play in either singleplayer or multiplayer mode.");
    outtextxy(50, 100, "2. In singleplayer mode, you need to guess words based on different themes.");
    outtextxy(50, 120, "3. In multiplayer mode, Player 1 enters a word, and Player 2 tries to guess it.");
    outtextxy(50, 140, "4. You have 6 attemps to guess the word correctly.");
    outtextxy(50, 160, "5. For each incorrect guess, a part of the hangman is drawn.");
    outtextxy(50, 180, "6. Guess the word before running out of lives to win!");

    delay(12000);  

    clearGraphicsWindow();
}

void drawHangmanBase() {
    int thickness = 5;

    drawThickHorizontalLine(50, 50, 200, thickness);
    drawThickVerticalLine(50, 50, 350, thickness);
    drawThickVerticalLine(250, 50, 20, thickness);
    drawThickHorizontalLine(30, 400, 400, 10);
}

void drawHangmanHead(int x, int y){
    setcolor(YELLOW);
    circle(x, y, 30);
    setfillstyle(SOLID_FILL, YELLOW);
    floodfill(x, y, YELLOW);
}

void drawHangmanBody(int x, int y){
    setcolor(YELLOW);
    setlinestyle(SOLID_LINE, 0, 5);
    line(x, y, x, y+140);
    setlinestyle(SOLID_LINE, 0, 1);
}

void drawRightHand(int x, int y){
    setcolor(YELLOW);
    setlinestyle(SOLID_LINE, 0, 5);
    line(x, y+20, x-20, y+60);
}

void drawLeftHand(int x, int y){
    setcolor(YELLOW);
    setlinestyle(SOLID_LINE, 0, 5);
    line(x, y+20, x+20, y+60);
}

void drawRightLeg(int x, int y){
    setcolor(YELLOW);
    setlinestyle(SOLID_LINE, 0, 5);
    line(x, y+70, x-20, y+100);
}

void drawLeftLeg(int x, int y){
    setcolor(YELLOW);
    setlinestyle(SOLID_LINE, 0, 5);
    line(x, y+70, x+20, y+100);
}

void displayLevelInfo(int level) {
    cleardevice(); // Clear the graphics window

    setcolor(WHITE);
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);

    std::ostringstream oss;
    oss << " Theme - ";

    switch (level) {
        case 1:
            oss << "Fruits";
            break;
        case 2:
            oss << "Popular Cities";
            break;
        case 3:
            oss << "Social Media";
            break;
        case 4:
            oss << "Cocktails and Ingredients";
            break;
        case 5:
            oss << "Discrete Math Notions";
            break;
        default:
            break;
    }

    char* text = const_cast<char*>(oss.str().c_str());

    // Display level number separately
    char levelText[20];
    sprintf(levelText, "Level %d", level);

    // Adjusted the position for levels 4 and 5
    int xPos = (level == 4 || level == 5) ? 50 : 100;

    // Display level number
    outtextxy(xPos, 20, levelText);

    // Display theme
    outtextxy(xPos + 80, 20, text);
    delay(5000); // Add a delay to see the level information

    cleardevice(); // Clear the graphics window again
}

char* chooseRandomWord(int level) {
    srand(time(NULL));

    int randomIndex;

    switch (level) {
        case 1:
            randomIndex = rand() % numlv1;
            return level1_words[randomIndex];
        case 2:
            randomIndex = rand() % numlv2;
            return level2_words[randomIndex];
        case 3:
            randomIndex = rand() % numlv3;
            return level3_words[randomIndex];
        case 4:
            randomIndex = rand() % numlv4;
            return level4_words[randomIndex];
        case 5:
            randomIndex = rand() % numlv5;
            return level5_words[randomIndex];
        default:
            return nullptr;
    }
}

void displayHangman(int incorrectGuesses, char* guessedWord, char* wrongGuesses) {
    clearGraphicsWindow();
    cout << "Incorrect Guesses: " << incorrectGuesses << endl;

    switch (incorrectGuesses) {
        case 0:
            drawHangmanBase();
            break;
        case 1:
            drawHangmanBase();
            drawHangmanHead(255, 100);
            break;
        case 2:
            drawHangmanBase();
            drawHangmanHead(255, 100);
            drawHangmanBody(255, 130);
            break;
        case 3:
            drawHangmanBase();
            drawHangmanHead(255, 100);
            drawHangmanBody(255, 130);
            drawLeftHand(255, 150);
            break;
        case 4:
            drawHangmanBase();
            drawHangmanHead(255, 100);
            drawHangmanBody(255, 130);
            drawRightHand(255, 150);
            drawLeftHand(255, 150);;
            break;
        case 5:
            drawHangmanBase();
            drawHangmanHead(255, 100);
            drawHangmanBody(255, 130);
            drawRightHand(255, 150);
            drawLeftHand(255, 150);
            drawLeftLeg(255, 200);
            break;
        case 6:
            drawHangmanBase();
            drawHangmanHead(255, 100);
            drawHangmanBody(255, 130);
            drawRightHand(255, 150);
            drawLeftHand(255, 150);
            drawRightLeg(255, 200);
            drawLeftLeg(255, 200);
            break;
    }

    // Display guessed word below the hangman
    setcolor(WHITE);
    settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
    outtextxy(100, 420, "Guessed Word: ");
    outtextxy(300, 420, guessedWord);

    // Display wrong guesses below the hangman
    outtextxy(100, 450, "Wrong Guesses: ");
    outtextxy(300, 450, wrongGuesses);
}

void playMultiplayerHangman() {
    char word[MAX_WORD_LENGTH];
    char guessedWord[MAX_WORD_LENGTH];
    int incorrectGuesses = 0;
    int wordLength;

    cout << "Player 1, enter the word: ";
    cin >> word;
    clearScreen();

    wordLength = strlen(word);

    // Initialize guessedWord with underscores
    memset(guessedWord, '*', wordLength);
    guessedWord[wordLength] = '\0';

    // Array to store wrong guesses
    char wrongGuesses[MAX_LIVES];
    int wrongGuessCount = 0;

    while (incorrectGuesses < MAX_LIVES) {
        // Display current state of the Hangman and guessed word
        displayHangman(incorrectGuesses, guessedWord, wrongGuesses);

        // Player 2 guesses a letter
        cout << "Player 2, guess a letter: ";
        char guess;
        cin >> guess;

        // Check if the guessed letter is in the word
        int found = 0;
        for (int i = 0; i < wordLength; ++i) {
            if (word[i] == guess) {
                guessedWord[i] = guess;
                found = 1;
            }
        }

        // Increment incorrectGuesses if the letter is not in the word
        if (!found) {
            ++incorrectGuesses;

            // Store wrong guess
            if (wrongGuessCount < MAX_LIVES) {
                wrongGuesses[wrongGuessCount++] = guess;
            }
        }

        // Check if the word is completely guessed
        int allLettersGuessed = 1;
        for (int i = 0; i < wordLength; ++i) {
            if (guessedWord[i] == '*') {
                allLettersGuessed = 0;
                break;
            }
        }

        if (allLettersGuessed) {
            // Display final state with guessed word
            displayHangman(incorrectGuesses, guessedWord, wrongGuesses);
            cout << "Player 2 wins! The word is " << word << endl;
            clearWrongGuesses();  // Clear wrong guesses for the next level
            return;
        }
    }

    // Player 2 ran out of lives
    displayHangman(incorrectGuesses, guessedWord, wrongGuesses);
    cout << "Player 2 loses! The word was " << word << endl;
    clearWrongGuesses();  // Clear wrong guesses for the next level
}

// Function to play Hangman in singleplayer mode
void playSingleplayerHangman() {
    int level = 1;
    int lives = MAX_LIVES;
    char* word;

     while (level <= NUM_LEVELS) {
        // Choose a random word for the current level
        word = chooseRandomWord(level);

        // Display level information
        displayLevelInfo(level);
        clearWrongGuesses();  // Clear wrong guesses for the next level

        // Initialize guessedWord with underscores
        char guessedWord[MAX_WORD_LENGTH];
        int wordLength = strlen(word);
        memset(guessedWord, '*', wordLength);
        guessedWord[wordLength] = '\0';

        // Array to store wrong guesses
        char wrongGuesses[MAX_LIVES];
        int wrongGuessCount = 0;

        // Play Hangman for the current word
        while (lives > 0) {
            // Display current state of the Hangman and guessed word
            displayHangman(MAX_LIVES - lives, guessedWord, wrongGuesses);

            // Player guesses a letter or requests to reveal the word
            cout << "Guess a letter (or type 'quit' to stop, 'reveal' to reveal the word): ";
            char input[20];
            cin >> input;

            // Check if the player wants to quit
            if (strcmp(input, "quit") == 0) {
                cout << "Game stopped. Goodbye!\n";
                return;
            }

            // Check if the player wants to reveal the word
            if (strcmp(input, "reveal") == 0) {
                // Display final state with guessed word
                displayHangman(MAX_LIVES - lives, guessedWord, wrongGuesses);
                cout << "The word was " << word << ".\n";
                if (level < NUM_LEVELS) {
                    cout << "You won this level. Moving to the next level.\n";
                    ++level;
                    lives = MAX_LIVES; // Reset lives for the next level
                    break;
                } else {
                    cout << "You won the game! Congratulations!\n";
                    return;
                }
            } else {
                // Process the guessed letter
                char guess = input[0];
                int found = 0;

                for (int i = 0; i < wordLength; ++i) {
                    if (word[i] == guess) {
                        guessedWord[i] = guess;
                        found = 1;
                    }
                }

                // Decrement lives if the letter is not in the word
                if (!found) {
                    --lives;
                    cout << "Incorrect guess. Lives remaining: " << lives << endl;

                    // Store wrong guess
                    if (wrongGuessCount < MAX_LIVES) {
                        wrongGuesses[wrongGuessCount++] = guess;
                    }
                } else {
                    cout << "Correct guess!\n";
                }

                // Check if the word is completely guessed
                int allLettersGuessed = 1;

                for (int i = 0; i < wordLength; ++i) {
                    if (guessedWord[i] == '*') {
                        allLettersGuessed = 0;
                        break;
                    }
                }

                if (allLettersGuessed) {
                    // Display final state with guessed word
                    displayHangman(MAX_LIVES - lives, guessedWord, wrongGuesses);
                    cout << "Congratulations! You guessed the word.\n";
                    cout << "The word was " << word << ".\n";
                    if (level < NUM_LEVELS) {
                        cout << "Moving to the next level.\n";
                        ++level;
                        lives = MAX_LIVES; // Reset lives for the next level
                    } else {
                        cout << "You won the game! Congratulations!\n";
                        return;
                    }
                    break;
                }
            }
        }

        if (lives == 0) {
            // Display final state with guessed word
            displayHangman(MAX_LIVES, guessedWord, wrongGuesses);
            cout << "You ran out of lives. The word was " << word << ".\n";
            cout << "Restarting from Level 1.\n";
            level = 1;
            lives = MAX_LIVES;
        }
    }
}

int main() {
    int gd = DETECT, gm;

    initgraph(&gd, &gm, "C:\\TC\\BGI");

    int choice;
    displayRules();
    do {
        cout << "Hangman Game\n";
        cout << "1. Multiplayer\n";
        cout << "2. Singleplayer\n";
        cout << "3. Quit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                clearGraphicsWindow();
                playMultiplayerHangman();
                break;
            case 2:
                clearGraphicsWindow();
                playSingleplayerHangman();
                break;
            case 3:
                cout << "Exiting Hangman Game. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please enter a valid option.\n";
        }

    } while (choice != 3);

    getch();
    closegraph();

    return 0;
}
