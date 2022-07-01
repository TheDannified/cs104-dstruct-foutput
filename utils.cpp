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
    map<char, int> digits;

    if (code.length() == MAX_CODE_LENGTH) {
        for (char ch: code) {
            if (isNumber(ch)) { // Check if the character being checked is a number.
                if (++digits[ch] == 2) // If the
                    return false;
            }
            else return false; // if a non-numerical character was found.
        }
        return true;
    }
    else return false;

}

// GOOD TO GO!
Code generateCode(Difficulty difficulty, Player& player) {
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
    } while (find(player.guesses.begin(), player.guesses.end(), result) != player.guesses.end());

    return result;
}

// IN DEVELOPMENT
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

// IN DEVELOPMENT
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

// IN DEVELOPMENT
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
        else if (find(player.guesses.begin(), player.guesses.end(), userCode) != player.guesses.end()) {
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
    string message;
    message.append(to_string(result["bulls"]) + " bulls, " + to_string(result["cows"]) + " cows");
    return message;
}

// GOOD TO GO!
bool hasGuessedSecretCode(const Code& guessCode, const Code& secretCode)
{
    if (guessCode == secretCode)
        return true;

    return false;
}