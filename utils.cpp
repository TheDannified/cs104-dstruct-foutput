/**
 * THIS UTILS (A.K.A. "UTILITIES") FILE
 * IS A CPP FILE DEDICATED TO DEFINE EXISTING
 * FUNCTION PROTOTYPES FOUND IN UTILS HEADER.
 *
 * DESCRIPTIONS ABOUT THESE FUNCTIONS ARE ALL
 * DOCUMENTED IN UTILS.H FILE. FURTHER DOCS
 * ABOUT THE ALGORITHMS IMPLEMENTED IN EACH
 * FUNCTIONS CAN BE FOUND HERE.
 */

#include "utils.h"
#include "interface.h"

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
    // If the given character is basically an alphabet. (case-insensitive)
    // in ASCII value.
    if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))
        return true;

    return false;
}

bool isFalseDigit(const char& ch)
{
    if (ch == '?')
        return true;

    return false;
}

string removeUsedDigits(string digits, Code& guessCode)
{
    // Reads each character found in the given guess code reference and
    // deletes that character in the "digits" string.
    for (char ch: guessCode)
        digits.erase(remove(digits.begin(), digits.end(), ch), digits.end());

    return digits;
}

Code getHint(Code& guessCode, Code& secretCode)
{
    Code result;

    for (char ch : guessCode)
    {
        // if the current character is seen as a bull digit in the guess code,
        // preserve its numerical form to denote that this digit is a bull digit.
        if (isBull(guessCode, secretCode, ch))
            result.append(1, ch);
        // if the current character is evaluated as a cow digit, modify its form
        // into an alphabet character to denote that this digit is a cow digit.
        else if (isCow(guessCode, secretCode, ch))
            result.append(1, (char)(ch + 17));
        // if the current character is neither a bull nor cow digit, then insert a
        // '?' character to that position to denote that this position needs to have
        // a new digit.
        else
            result.append(1, '?');
    }

    return result;
}

bool validateCode(Code& code)
{
    map<char, int> digits; // frequency map

    // check if the length of the given code is "MAX_CODE_LENGTH" (4 characters) long.
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
            return ""; // none.
    }
}

Code shiftPosition(Code& hint) {

    Code result = hint; // temporary variable to hold the original hint format.

    // Traverse inside the hint's contents
    for (int i = 0; i < MAX_CODE_LENGTH; i++) {
        // At the start part of the hint code...
        if (i == 0) {
            // Check if the first digit is an alphabet or a false digit
            if (isAlpha(hint[i]) || isFalseDigit(hint[i])) {
                // traverse inside the hint's contents again.
                for (int h = 1; h <= MAX_CODE_LENGTH - 1; h++) {
                    if (isAlpha(hint[h]) || isFalseDigit(hint[h])) {
                        result[h] = hint[i];
                        result[i] = hint[h];
                        break;
                    }
                }
            }
        }
        // At the end part of the hint code.
        else if (i == MAX_CODE_LENGTH - 1) {
            // Check if the last digit is not a bull digit.
            if (!isNumber(hint[i]))
                for (int j = 0; j < MAX_CODE_LENGTH - 1; j++) {
                    if (isAlpha(hint[j]) || isFalseDigit(hint[j])) {
                        result[j] = hint[i];
                        if (j == 0) {
                            if (isAlpha(result[MAX_CODE_LENGTH - 1])) {
                                if (isAlpha(hint[MAX_CODE_LENGTH - 1])) {
                                    break;
                                }
                                else if (isFalseDigit(result[MAX_CODE_LENGTH - 1])) {
                                    result[MAX_CODE_LENGTH - 1] = '?';
                                }
                            }
                            else if (isFalseDigit(result[MAX_CODE_LENGTH - 1]))
                                break;
                            else
                                result[MAX_CODE_LENGTH - 1] = hint[0];
                        }
                        break;
                    }
                }
        }
        // In the middle part of the hint code
        else {
            // Check if the current digit is not a bull digit.
            if (!isNumber(hint[i])){
                if ((isAlpha(hint[i + 1]) || isFalseDigit(hint[i + 1])))
                    result[i + 1] = hint[i];
                else if ((isAlpha(hint[i - 1]) || isFalseDigit(hint[i - 1])))
                    for (int k = 0; k < MAX_CODE_LENGTH - 1; k++) {
                        if (isAlpha(hint[k]) || isFalseDigit(hint[k])) {
                            result[k] = hint[i];
                            break;
                        }
                    }
                else if (isNumber(hint[i - 1])) {
                    if (isNumber(hint[i + 1])) {
                        if (!isNumber(result[i + 2]))
                            result[i + 2] = hint[i];
                        else
                            continue;
                    }
                    else
                        continue;
                }
                else if (isNumber(hint[i + 1]))
                    result[i - 2] = hint[i];
                else
                    result[0] = hint[i];
            }
        }

    }

    return result;
}

Code generateCode(Player& player)
{
    int randIndex;
    string digits;
    string result;

    srand(time(NULL));
    // Every time the player needs to generate a code.
    do {
        // Clear out the contents of the "result" string.
        result.clear();
        // Set an ordered sequence of numerical digits from 0 to 9.
        digits = "0123456789";

        // Creating a guess code at this point:
        for (int i = 0; i < MAX_CODE_LENGTH; i++) {
            // Generate a random index number based on the current length of the "digits" string.
            randIndex = rand() % digits.length();
            // Append a character accessed in the "digits" string using the generated random index.
            result.append(1, digits.at(randIndex));
            // Delete that accessed character in the "digits" string to avoid digit redundancy.
            digits.erase(remove(digits.begin(), digits.end(), digits.at(randIndex)), digits.end());
        }

    // Check if the generated guess code has been already guessed by the player,
    // or the code did not follow the code standards. (just in case)
    } while (hasPlayerUsedGuessCode(player, result) || !validateCode(result));

    return result;
}

Code generateCode(Player& player, Code& secretCode)
{
    int randIndex;
    string digits;
    string result;
    // Additional variables
    Code hint;
    Code prevGuessCode;
    vector<char> cowDigits;

    srand(time(NULL));

    // If this player has provided guess codes before...
    if (!player.guesses.empty()) {
        prevGuessCode = player.guesses.at(player.guesses.size() - 1); // get the most recent guess code made by the player.
        hint = getHint(prevGuessCode, secretCode); // get hints from user's secret code.

        do {
            // Clear out the contents of the "result" string.
            result.clear();
            // Remove all used digits found from the previous guess code of the player.
            digits = removeUsedDigits("0123456789", prevGuessCode);

            // Modify the hint's form by changing the positions of cows and wrong digits.
            hint = shiftPosition(hint);

            // Interpret the hint string into a valid guess code.
            for (char ch : hint) {
                if (!isNumber(ch)) {
                    if (isAlpha(ch))
                        result.append(1, (char) (ch - 17));
                    else {
                        randIndex = rand() % digits.length();
                        result.append(1, digits.at(randIndex));
                        digits.erase(remove(digits.begin(), digits.end(), digits.at(randIndex)), digits.end());
                    }
                }
                else
                    result.append(1, ch);
            }

        // Check if the generated guess code has been already guessed by the player,
        // or the code did not follow the code standards. (just in case)
        } while (hasPlayerUsedGuessCode(player, result) || !validateCode(result));
    }
    // Otherwise, generate their first guess code.
    else
        result = generateCode(player);

    return result;
}

Result evaluateCode(const Code& guessCode, const Code& secretCode)
{
    Result result = {0, 0};

    for (char ch : guessCode) {
        int gcChPos = (int) guessCode.find(ch);     // get the position of the current character in guessCode
        int scChPos = (int) secretCode.find(ch);    // get the position of the current character in secretCode

        if (scChPos != -1) // if the current character exists somewhere in the secretCode
        {
            // Check if its position in the secretCode is the same with its position in guessCode
            if (gcChPos == scChPos)
                result.bulls++; // if true, increment bulls attribute
            else
                result.cows++; // otherwise, increment cows attribute
        }
    }

    return result;
}

string printResult(Result& result)
{
    stringstream message;
    int numBulls = result.bulls;
    int numCows = result.cows;

    message << numBulls << ((numBulls == 1) ? " bull, " : " bulls, ") << numCows << ((numCows == 1) ? " cow" : " cows");
    return message.str();
}

bool hasGuessedSecretCode(const Code& guessCode, const Code& secretCode)
{
    if (guessCode == secretCode)
        return true;

    return false;
}

bool hasPlayerUsedGuessCode(Player& player, Code& guessCode)
{
    return find(player.guesses.begin(), player.guesses.end(), guessCode) != player.guesses.end();
}

void saveGameResult(Player& player1, Player& player2, Difficulty difficulty, const string& filename = "") {
    time_t dateTime = time(NULL);   // time object for file name
    tm *tf = localtime(&dateTime);

    stringstream initFileName;      // stores the initial name of our log file
    ofstream logFile;               // output stream object for the log file

    string gameWinner;
    Result result = {0, 0};

    if (filename.length() == 0)
        initFileName << "BNC_GAME_LOG " << tf->tm_mon << "-" << (tf->tm_mday + 1) << "-" << (1900 + tf->tm_year)
                     << " " << tf->tm_hour << "-" << tf->tm_min << "-" << tf->tm_sec << DEFAULT_FILE_EXTENSION;
    else
        initFileName << filename << DEFAULT_FILE_EXTENSION;

    // Determine who won in this game session...
    if (isPracticeMode(difficulty))
        // if in Practice Mode, only the chances are: the player succeeded or failed to guess computer's guess code
        gameWinner = player1.isWinner ? "USER" : "NONE";
    else if ((player1.isWinner && player2.isWinner) || (!player1.isWinner && !player2.isWinner))
        gameWinner = "DRAW";
    else if (player1.isWinner && !player2.isWinner)
        gameWinner = "USER";
    else if (!player1.isWinner && player2.isWinner)
        gameWinner = "COMPUTER";

    logFile.open(initFileName.str(), fstream::out);

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

        for (size_t i = 0; i < (isPracticeMode(difficulty) ? player1 : player2).guesses.size(); i++) {
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

void initGame(Player& user, Player& comp, Difficulty difficulty, ModeOfPlay modeOfPlay)
{
    bool isInGame = true;       // Determines if the game is ongoing
    bool inAskingMode = true;   // State where the user is asked if they want to save a game log.
    char willSaveGame;          // Command choice handler for "Save Game" prompt.

    Code userGuess;             // Stores the most recent guess code of the "user" player
    Code compGuess;             // Stores the most recent guess code of the "comp" player

    Result result = {0, 0};     // guess evaluate tracker.

    short attemptCounter = 0;   // round counter

    auto ugvPtr = (!user.guesses.empty()) ? user.guesses.begin() : user.guesses.end();

    cout << "************** COMMENCE PLAYGROUND **************" << endl << endl;
    do {
        // GAME HEADER/COUNTER
        cout << "******************** GAME #" << attemptCounter + 1 << " ********************" << endl;

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

        if (ugvPtr != user.guesses.end()) {
            cout << "[USER] Please provide a secret code: ";
            userGuess = *ugvPtr;
            ++ugvPtr;
            cout << userGuess << endl;
            result = evaluateCode(userGuess, comp.secretCode);
            cout << "USER'S RESULT: " << printResult(result) << endl;
        }
        else {
            // Prompt the user to guess the computer's secret code.
            promptGuessCode(user);
            userGuess = user.guesses.at(user.guesses.size() - 1);
            result = evaluateCode(userGuess, comp.secretCode);
            cout << "USER'S RESULT: " << printResult(result) << endl;

            ugvPtr = user.guesses.end();
        }

        if (!isPracticeMode(difficulty)) {
            // Generate a code for the computer.
            compGuess = (difficulty == EASY) ? generateCode(comp) : generateCode(comp, user.secretCode);
            comp.guesses.push_back(compGuess);
            result = evaluateCode(compGuess, user.secretCode);
            cout << "COMPUTER GUESS: " << compGuess << endl;
            cout << "COMPUTER'S RESULT: " << printResult(result) << endl;
        }

        cout << "*************************************************" << endl;

            // CHECK IF THE GAME DIFFICULTY IS JUST IN PRACTICE MODE
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
            user.isWinner = true;
            comp.isWinner = true;
            isInGame = false;

            cout << "***************** GAME  SUMMARY *****************" << endl;
            cout << "[GAME] It's a draw! Both player were able to guess each other's secret code!"  << endl;
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
            cout << "Computer's Last Guess: " << compGuess << endl;
            cout << "User's Secret Code: " << user.secretCode << endl;
            cout << "*************************************************" << endl;
        }

        attemptCounter++;

        // CHECK IF THE USER AND/OR COMPUTER HAS/HAVE NOT EXHAUSTED THEIR ATTEMPTS YET AND THE GAME IS STILL ONGOING
    } while ((user.guesses.size() != MAX_GUESS_ATTEMPTS || (!isPracticeMode(difficulty) && comp.guesses.size() != MAX_GUESS_ATTEMPTS)) && isInGame);

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

    if (!isPracticeMode(difficulty)){
        do {
            cout << "[SYSTEM] Do you want to save this game? ([Y]es/[N]o): ";
            cin >> willSaveGame;
            if ((char) toupper(willSaveGame) == 'Y') {
                string fileName;

                cout << "Please enter your desired file name for this game log: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, fileName, '\n');

                saveGameResult(user, comp, difficulty, fileName);
                inAskingMode = false;
            } else if ((char) toupper(willSaveGame) == 'N')
                inAskingMode = false;
            else
                cerr << "[ERROR] Invalid argument. Please enter a proper character." << endl;
        } while (inAskingMode);
    }

    cout << endl << "[GAME] Game finished! Reverting back to Main Menu..." << endl;

}

bool isPracticeMode(Difficulty difficulty)
{
    return difficulty == PRACTICE;
}

bool isBull(Code& guessCode, Code& secretCode, char ch)
{
    // Character being searched on both code exists and are in the same index.
    return guessCode.find(ch) == secretCode.find(ch);
}

bool isCow(Code& guessCode, Code& secretCode, char ch)
{
    // Character being searched on both codes exists, and they are from different indexes.
    return (guessCode.find(ch) != -1ULL && secretCode.find(ch) != -1ULL) && (guessCode.find(ch) != secretCode.find(ch));
}