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

bool isAlpha(const char& ch)
{
    if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))
        return true;

    return false;
}

// IN DEVELOPMENT!
string removeUsedDigits(string digits, Code& guessCode)
{
    for (char ch: guessCode)
        digits.erase(remove(digits.begin(), digits.end(), ch), digits.end());

    return digits;
}

// IN DEVELOPMENT!
Code getHint(Code& guessCode, Code& secretCode)
{
    Code result;

    for (char ch : guessCode)
    {
        if (isBull(guessCode, secretCode, ch))
            result.append(1, ch);
        else if (isCow(guessCode, secretCode, ch))
            result.append(1, (char)(ch + 17));
        else
            result.append(1, '?');
    }

    return result;
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
        case PRACTICE:
            return "PRACTICE";
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
    int randIndex;
    string digits;
    string result;

    srand(time(NULL));
    do {
        result.clear();
        digits = "0123456789";
        for (int i = 0; i < MAX_CODE_LENGTH; i++) {
            randIndex = rand() % digits.length();
            result.append(1, digits.at(randIndex));
            digits.erase(remove(digits.begin(), digits.end(), digits.at(randIndex)), digits.end());
        }
    } while (hasPlayerUsedGuessCode(player, result) || !validateCode(result));

    return result;
}

// IN DEVELOPMENT
Code generateCode(Player& player, Code& secretCode)
{
    int randIndex;
    string digits;
    string result;
    Code hint;
    Code prevGuessCode;
    vector<char> cowDigits;

    srand(time(NULL));

    if (!player.guesses.empty()) {
        prevGuessCode = player.guesses.at(player.guesses.size() - 1);
        hint = getHint(prevGuessCode, secretCode); // get hints from user's secret code.

        do {
            result.clear();
            digits = removeUsedDigits("0123456789", secretCode);
            for (int i = 0; i < MAX_CODE_LENGTH; i++) {
                if (isNumber(hint[i])) // A 'bull' number
                    result.append(1, prevGuessCode[i]);
                else if (isAlpha(hint[i])) { // A 'cow' (possible) number
                    cowDigits.push_back((char)(hint[i] - 17));
                    hint.replace(i, 1, "#");
                }
                else if (hint.at(i) == '?') { // Just a random number
                    randIndex = rand() % digits.length();
                    result.append(1, digits.at(randIndex));
                    digits.erase(remove(digits.begin(), digits.end(), digits.at(randIndex)), digits.end());
                }
            }

            if (!cowDigits.empty()) {
                if (cowDigits.size() == 1)
                    hint[hint.find('#')] = cowDigits.at(0);
                else {
                    do {
                        randIndex = rand() % cowDigits.size();
                        hint[hint.find('#')] = cowDigits.at(randIndex);
                        cowDigits.erase(remove(cowDigits.begin(), cowDigits.end(), cowDigits.at(randIndex)), cowDigits.end());
                    } while (!cowDigits.empty());
                }
            }

        } while (hasPlayerUsedGuessCode(player, result) || !validateCode(result));
    }
    else
        result = generateCode(player);

    return result;
}

// GOOD TO GO!
Result evaluateCode(const Code& guessCode, const Code& secretCode)
{
    Result result = {0, 0};

    for (char ch : guessCode) {
        int gcChPos = (int) guessCode.find(ch);
        int scChPos = (int) secretCode.find(ch);

        if (gcChPos != -1 && scChPos != -1)
        {
            if (gcChPos == scChPos)
                result.bulls++;
            else
                result.cows++;
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
string printResult(Result& result)
{
    stringstream message;
    int numBulls = result.bulls;
    int numCows = result.cows;

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
    time_t dateTime = time(NULL);        // time object for file name
    stringstream fileName;  // stores the initial name of our log file
    ofstream logFile;       // output stream object for the log file

    string gameWinner;
    Result result = {0, 0};

    fileName << "outputtest.txt";

    if (isPracticeMode(difficulty))
        gameWinner = player1.isWinner ? "USER" : "NONE";
    else if ((player1.isWinner && player2.isWinner) || (!player1.isWinner && !player2.isWinner))
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
        logFile << "SECRET CODES: " <<
                    // IF THE GAME DIFFICULTY IS NOT IN PRACTICE MODE, PRINT THE USER'S SECRET CODE.
                    (!isPracticeMode(difficulty) ? ("\tUSER: " + player1.secretCode) : "") <<
                    "\tCOMPUTER: " << player2.secretCode << endl << endl;

        for (size_t i = 0; i < player1.guesses.size(); i++) {
            logFile << ">> GAME #" << i + 1 << endl;
            result = evaluateCode(player1.guesses.at(i), player2.secretCode);
            logFile << "USER GUESSED: " << player1.guesses.at(i) << " - scoring " << printResult(result) << endl;
            // CHECK IF THE GAME DIFFICULTY IS IN PRACTICE MODE. IF TRUE, DO NOT PRINT COMPUTER GUESSES.
            if (!isPracticeMode(difficulty)){
                result = evaluateCode(player2.guesses.at(i), player1.secretCode);
                logFile << "COMPUTER GUESSED: " << player2.guesses.at(i) << " - scoring " << printResult(result) << endl << endl;
            }
            else
                logFile << "COMPUTER'S SECRET CODE: " << player2.secretCode << endl << endl;
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

    Result result = {0, 0};    // guess evaluate tracker.

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
        if (!isPracticeMode(difficulty)){
            cout << "COMP GUESSES: ";
            for (const Code &cmpGuess: comp.guesses)
                cout << cmpGuess << " ";
            cout << endl;
        }
        cout << "*************************************************" << endl;

        // Prompt the user to guess the computer's secret code.
        promptGuessCode(user);
        userGuess = user.guesses.at(user.guesses.size() - 1);
        result = evaluateCode(userGuess, comp.secretCode);
        cout << "USER'S RESULT: " << printResult(result) << endl;

        if (!isPracticeMode(difficulty)) {
            // Generate a code for the computer.
            compGuess = (difficulty == EASY) ? generateCode(comp) : generateCode(comp, user.secretCode);
            comp.guesses.push_back(compGuess);
            result = evaluateCode(compGuess, user.secretCode);
            cout << "COMPUTER GUESS: " << compGuess << endl;
            cout << "COMPUTER'S RESULT: " << printResult(result) << endl;
        }

        cout << "*************************************************" << endl;

        if (isPracticeMode(difficulty)) {
            if (hasGuessedSecretCode(userGuess, comp.secretCode)){
                user.isWinner = true;
                isInGame = false;

                cout << "***************** GAME  SUMMARY *****************" << endl;
                cout << "[GAME] The USER has guessed the COMPUTER's secret code!" << endl;
                cout << "User's Last Guess: " << userGuess << endl;
                cout << "Computer's Secret Code: " << comp.secretCode << endl;
                cout << "*************************************************" << endl;
            }
        }
        // CHECK IF THE USER AND COMPUTER WERE ABLE TO GUESS EACH OTHER'S SECRET CODE
        else if (hasGuessedSecretCode(userGuess, comp.secretCode) && hasGuessedSecretCode(compGuess, user.secretCode))
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
    if (isPracticeMode(difficulty) && !user.isWinner)
    {
        cout << "***************** GAME  SUMMARY *****************" << endl;
        cout << "[GAME] The USER failed to guess the COMPUTER'S secret code!" << endl;
        cout << "User's Last Guess: " << userGuess << endl;
        cout << "Computer's Secret Code: " << comp.secretCode << endl;
        cout << "*************************************************" << endl;
    }
    else if (!user.isWinner && !comp.isWinner)
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

bool isPracticeMode(Difficulty difficulty)
{
    return difficulty == PRACTICE;
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