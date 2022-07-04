#include "utils.h"

// GOOD TO GO!
void clear()
{
    system("cls");
}

// GOOD TO GO!
bool isNumber(const char& ch)
{
    // If the given character is within the range of 0-9
    // in ASCII value.
    if (ch >= '0' && ch <= '9')
        return true;

    return false;
}

// GOOD TO GO!
bool validateCode(Code& code)
{
    map<char, int> digits; // frequency

    if (code.length() == MAX_CODE_LENGTH) {
        for (char ch: code) {
            if (isNumber(ch)) { // Check if the character being checked is a number.
                if (++digits[ch] == 2)
                    return false; // if there's a digit that has a duplicate
            }
            else return false; // if a non-numerical character was found.
        }
        return true;
    }
    else return false;

}

// GOOD TO GO!
string getDifficulty(Difficulty difficulty)
{
    switch (difficulty)
    {
        case EASY:
            return "EASY";
        case MEDIUM:
            return "MEDIUM";
        default:
            return "";
    }
}

// GOOD TO GO!
Code generateCode(Player& player)
{
    string digits;
    string result;

    srand(time(0));
    do {
        result.clear();
        digits = "0123456789";
        for (int i = 0; i < MAX_CODE_LENGTH; i++) {
            int randIndex = rand() % digits.length();
            result.append(1, digits.at(randIndex));
            digits.erase(remove(digits.begin(), digits.end(), digits.at(randIndex)), digits.end());
        }
    } while (hasPlayerUsedGuessCode(player, result));

    return result;
}

// IN DEVELOPMENT
Code generateCode(Player& player, Code& secretCode)
{
    string digits;
    string result = "****";

    srand(time(0));
    do {
        result.clear();
        digits = "0123456789";
        for (int i = 0; i < MAX_CODE_LENGTH; i++) {
            int randIndex = rand() % digits.length();
            result.append(1, digits.at(randIndex));
            digits.erase(remove(digits.begin(), digits.end(), digits.at(randIndex)), digits.end());
        }
    } while (hasPlayerUsedGuessCode(player, result));

    return result;
}

// GOOD TO GO!
map<string, int> evaluateCode(const Code& guessCode, const Code& secretCode)
{
    map<string, int> result;

    result.insert(pair<string, int>("bulls", 0));
    result.insert(pair<string, int>("cows", 0));

    for (char ch : guessCode) {
        int gcChPos = (int) guessCode.find(ch);
        int scChPos = (int) secretCode.find(ch);

        if (gcChPos != -1 && scChPos != -1)
        {
            if (gcChPos == scChPos)
                result["bulls"]++;
            else
                result["cows"]++;
        }
    }

    return result;
}

// GOOD TO GO!
void promptSecretCode(Player& player)
{
    string userCode;

    do {

        cout << "[USER] Please provide a secret code: ";
        cin >> userCode;

        if (userCode.length() < MAX_CODE_LENGTH)
            cerr << "[ERROR] Given code has less than " << MAX_CODE_LENGTH << " characters. Please try again." << endl;
        else if (userCode.length() > MAX_CODE_LENGTH)
            cerr << "[ERROR] Given code has more than " << MAX_CODE_LENGTH << " characters. Please try again." << endl;
        else if (!validateCode(userCode))
            cerr << "[ERROR] Given code is invalid. Please provide a code that has 4 distinct number code." << endl;
        else
            player.secretCode = userCode;

    } while (userCode.length() != 4 || !validateCode(userCode));
}

// GOOD TO GO!
void promptGuessCode(Player& player)
{
    string userCode;

    do {
        // PROMPT THE USER TO ENTER THEIR OWN GUESS
        cout << "YOUR GUESS: ";
        cin >> userCode;

        // IF THE GIVEN CODE HAS LESS THAN 4 CHARACTERS...
        if (userCode.length() < MAX_CODE_LENGTH)
            cerr << "[ERROR] Given code has less than " << MAX_CODE_LENGTH << " characters. Please try again." << endl;
        // IF THE GIVEN CODE EXCEEDED THE CHARACTER LIMIT
        else if (userCode.length() > MAX_CODE_LENGTH)
            cerr << "[ERROR] Given code has more than " << MAX_CODE_LENGTH << " characters. Please try again." << endl;
        // IF THE GIVEN CODE VIOLATES OUR CODE STANDARDS
        else if (!validateCode(userCode))
            cerr << "[ERROR] Given code is invalid. Please provide a code that has 4 distinct number code." << endl;
        // IF THE USER ALREADY USED THE GIVEN CODE FROM THEIR PREVIOUS ATTEMPTS
        else if (hasPlayerUsedGuessCode(player, userCode)) {
            cerr << "[ERROR] You have guessed this code from your previous attempts. Please provide another unique code." << endl;
            userCode = "";
        }
        // IF THE GIVEN CODE IS OKAY
        else
            player.guesses.push_back(userCode);

        // CHECK IF THE USERCODE'S LENGTH IS NOT 4 OR THE CODE STANDARD IS VIOLATED...
    } while (userCode.length() != 4 || !validateCode(userCode));
}

// GOOD TO GO!
string printResult(map<string, int>& result)
{
    stringstream message;
    int numBulls = result["bulls"];
    int numCows = result["cows"];

    message << numBulls << ((numBulls == 1) ? " bull, " : " bulls, ") << numCows << ((numCows == 1) ? " cow" : " cows");
    return message.str();
}

// GOOD TO GO!
bool hasGuessedSecretCode(const Code& guessCode, const Code& secretCode)
{
    if (guessCode == secretCode)
        return true;

    return false;
}

// GOOD TO GO
bool hasPlayerUsedGuessCode(Player& player, Code& guessCode)
{
    return find(player.guesses.begin(), player.guesses.end(), guessCode) != player.guesses.end();
}

// GOOD TO GO
void saveGameResult(Player& player1, Player& player2, Difficulty difficulty) {
    time_t dateTime = time(nullptr);        // time object for file name
    stringstream fileName;  // stores the initial name of our log file
    ofstream logFile;       // output stream object for the log file

    string gameWinner;
    map<string, int> result;

    fileName << "outputtest.txt";

    if ((player1.isWinner && player2.isWinner) || (!player1.isWinner && !player2.isWinner))
        gameWinner = "DRAW";
    else if (player1.isWinner && !player2.isWinner)
        gameWinner = "USER";
    else if (!player1.isWinner && player2.isWinner)
        gameWinner = "COMPUTER";

    logFile.open(fileName.str(), fstream::out);

    if (logFile.is_open() && !logFile.fail()) {
        logFile << "****************** GAME   SUMMARY *****************" << endl;
        logFile << "DATE OF GAME SESSION: " << ctime(&dateTime);
        logFile << "DIFFICULTY MODE: " << getDifficulty(difficulty) << endl;
        logFile << "GAME WINNER: " << gameWinner << endl;
        logFile << "***************************************************" << endl << endl;

        logFile << "***************** GAME  SESSION *******************" << endl;
        logFile << "SECRET CODES: \tUSER: " << player1.secretCode << "\tCOMPUTER: " << player2.secretCode << endl << endl;
        for (size_t i = 0; i < player1.guesses.size(); i++) {
            logFile << ">> GAME #" << i + 1 << endl;
            result = evaluateCode(player1.guesses.at(i), player2.secretCode);
            logFile << "USER GUESSED: " << player1.guesses.at(i) << " - scoring " << printResult(result) << endl;
            result = evaluateCode(player2.guesses.at(i), player1.secretCode);
            logFile << "COMPUTER GUESSED: " << player2.guesses.at(i) << " - scoring " << printResult(result) << endl << endl;
        }
    }

    logFile.close();

}

// IN DEVELOPMENT
void initGame(Player& user, Player& comp, Difficulty difficulty, ModeOfPlay modeOfPlay)
{
    fstream usrGuessesFile;     // fstream object that is responsible for handling our external (text) file
    stringstream UGF_fileName;  // stringstream object that stores the name of the usrGuessesFile (UGF)

    bool isInGame = true;       // Determines if the game is ongoing

    Code userGuess;             // Stores the most recent guess code of the "user" player
    Code compGuess;             // Stores the most recent guess code of the "comp" player

    map<string, int> result;    // guess evaluate tracker.

    if (modeOfPlay == AUTOMATIC) {/* empty for now */};

    cout << "************** COMMENCE PLAYGROUND **************" << endl << endl;
    do {
        // GAME HEADER/COUNTER
        cout << "******************** GAME #" << user.guesses.size() + 1 << " ********************" << endl;

        // Print all guesses made by players first.
        cout << "YOUR GUESSES: ";
        for (const Code& usrGuess : user.guesses)
            cout << usrGuess << " ";
        cout << endl;
        cout << "COMP GUESSES: ";
        for (const Code& cmpGuess : comp.guesses)
            cout << cmpGuess << " ";
        cout << endl;
        cout << "*************************************************" << endl;

        // Prompt the user to guess the computer's secret code.
        promptGuessCode(user);
        userGuess = user.guesses.at(user.guesses.size() - 1);
        result = evaluateCode(userGuess, comp.secretCode);
        cout << "USER'S RESULT: " << printResult(result) << endl;

        // Generate a code for the computer.
        compGuess = generateCode(comp);
        comp.guesses.push_back(compGuess);
        result = evaluateCode(compGuess, user.secretCode);
        cout << "COMPUTER GUESS: " << compGuess << endl;
        cout << "COMPUTER'S RESULT: " << printResult(result) << endl;

        cout << "*************************************************" << endl;

        // CHECK IF THE USER AND COMPUTER WERE ABLE TO GUESS EACH OTHER'S SECRET CODE
        if (hasGuessedSecretCode(userGuess, comp.secretCode) && hasGuessedSecretCode(compGuess, user.secretCode))
        {
            cout << "***************** GAME  SUMMARY *****************" << endl;
            cout << "[GAME] It's a draw! No one guessed each other's secret code!"  << endl;
            cout << "User's Last Guess: " << userGuess << endl;
            cout << "Computer's Secret Code: " << comp.secretCode << endl << endl;
            cout << "Computer's Last Guess: " << compGuess << endl;
            cout << "User's Secret Code: " << user.secretCode << endl;
            cout << "*************************************************" << endl;
        }
            // CHECK IF THE USER WAS THE FIRST TO GUESS THE COMPUTER'S SECRET CODE
        else if (hasGuessedSecretCode(userGuess, comp.secretCode))
        {
            user.isWinner = true;
            comp.isWinner = false;
            isInGame = false;

            cout << "***************** GAME  SUMMARY *****************" << endl;
            cout << "[GAME] The USER has guessed the COMPUTER'S secret code!"  << endl;
            cout << "User's Last Guess: " << userGuess << endl;
            cout << "Computer's Secret Code: " << comp.secretCode << endl;
            cout << "*************************************************" << endl;
        }
            // CHECK IF THE COMPUTER WAS THE FIRST TO GUESS THE USER'S SECRET CODE
        else if (hasGuessedSecretCode(compGuess, user.secretCode))
        {
            comp.isWinner = true;
            user.isWinner = false;
            isInGame = false;

            cout << "***************** GAME  SUMMARY *****************" << endl;
            cout << "[GAME] The COMPUTER has guessed the USER'S secret code!"  << endl;
            cout << "Computer's Last Guess: " << userGuess << endl;
            cout << "User's Secret Code: " << comp.secretCode << endl;
            cout << "*************************************************" << endl;
        }

        // CHECK IF THE USER HAS NOT EXHAUSTED THEIR ATTEMPTS YET AND THE GAME IS STILL ONGOING
    } while (user.guesses.size() != MAX_GUESS_ATTEMPTS && isInGame);

    // IF NONE OF THE PLAYERS WERE ABLE TO GUESS ONE ANOTHER'S CODE...
    if (!user.isWinner && !comp.isWinner)
    {
        cout << "***************** GAME  SUMMARY *****************" << endl;
        cout << "[GAME] It's a draw! No one guessed each other's secret code!"  << endl;
        cout << "User's Last Guess: " << userGuess << endl;
        cout << "Computer's Secret Code: " << comp.secretCode << endl << endl;
        cout << "Computer's Last Guess: " << compGuess << endl;
        cout << "User's Secret Code: " << user.secretCode << endl;
        cout << "*************************************************" << endl;
    }

    saveGameResult(user, comp, difficulty);
}

// GOOD TO GO
bool isBull(Code& guessCode, Code& secretCode, char ch)
{
    // Character being searched on both code exists and are in the same index.
    return guessCode.find(ch) == secretCode.find(ch);
}

// GOOD TO GO!
bool isCow(Code& guessCode, Code& secretCode, char ch)
{
    // Character being searched on both codes exists, and they are from different indexes.
    return (guessCode.find(ch) != -1ULL && secretCode.find(ch) != -1ULL) && (guessCode.find(ch) != secretCode.find(ch));
}