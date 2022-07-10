#include "interface.h"
#include "utils.h"

void uiMainMenu() {
    cout << "======== BULLS 'N COWS ========" << endl;
    cout << " Choose a difficulty mode: " << endl;
    cout << " [E] Easy      [M] Medium  " << endl;
    cout << "      [P] Practice         " << endl << endl;
    cout << "      [X] Close Game" << endl;
    cout << "=========== ver 1.5 ===========" << endl;
    cout << endl << "COMMAND: ";
}

void uiEasyMode() {
    Player user;    // User player object.
    Player comp;    // Computer player object.

    // Prompt user to provide their own secret code.
    promptSecretCode(user);

    // Generate a code for the computer.
    comp.secretCode = generateCode(comp);
    cout << "[COMPUTER] Computer has generated its own secret code." << endl << endl;

    initGame(user, comp, EASY, MANUAL);

}

void uiMediumMode() {
    fstream usrGuessesFile;     // fstream object that is responsible for handling our external (text) file
    stringstream UGF_fileName;  // stringstream object that stores the name of the usrGuessesFile (UGF)

    bool inAskingMode = true;   // Determines if the game system is asking for pre-made game settings

    Player user;                // User player object
    Player comp;                // Computer player object

    string tmpStr;              // only a temporary string
    Code tmpCode;               // only a temporary Code reader

    char modeOfPlay;            // Stores the game setting of "how to play the medium game mode"

    // Prompt user to provide their own secret code first.
    promptSecretCode(user);

    // Generate a code for the computer.
    comp.secretCode = generateCode(comp);
    cout << "[COMPUTER] Computer has generated its own secret code." << endl << endl;

    do {
        // PROMPT USER IF THEY WANT TO PLAY THE GAME:
        // (1) BY INPUTTING GUESS CODES MANUALLY; OR
        // (2) BY PROVIDING A PRE-SUPPLIED GUESS CODES FROM A TEXT FILE
        cout << "[GAME] How would you like to play this game?" << endl;
        cout << "[X] Let me provide guess codes manually." << endl;
        cout << "[C] Let me provide guess codes from a text file." << endl;
        cout << "[ARGUMENT] >> ";
        cin >> modeOfPlay;

        switch (toupper(modeOfPlay)) {
            case MANUAL:
                inAskingMode = false;
                break;
            case AUTOMATIC:
                do {
                    // PROMPT USER TO PROVIDE THE NAME OF THEIR TEXT FILE THAT CONTAINS THEIR GUESS CODE
                    cout << "[GAME] Please provide the name (or path) of your text file that contains your guess code: ";
                    cin >> tmpStr;
                    UGF_fileName.str(tmpStr);

                    usrGuessesFile.open(UGF_fileName.str(), fstream::in);

                    if (usrGuessesFile.is_open() && !usrGuessesFile.fail())
                    {
                        while (getline(UGF_fileName, tmpStr, '\\'));

                        cout << "[GAME] " << tmpStr << " has been loaded to the game system successfully." << endl << endl;

                        while(getline(usrGuessesFile, tmpCode) && user.guesses.size() != MAX_GUESS_ATTEMPTS) {
                            if (!(tmpCode.starts_with('#') || !validateCode(tmpCode) || hasPlayerUsedGuessCode(user, tmpCode)))
                                user.guesses.push_back(tmpCode);
                        }

                        inAskingMode = false;
                    }

                } while (inAskingMode);

                cout << "[SUCCESS] The first " << user.guesses.size() << " valid guess(es) were read from " << tmpStr << " file." << endl;

                break;
            default:
                cerr << "[ERROR] Invalid argument! Please try again." << endl;
        }
    } while (inAskingMode);

    // Close the streamline after using the file.
    usrGuessesFile.close();

    // Then, proceed to launching the game.
    initGame(user, comp, MEDIUM, (ModeOfPlay)modeOfPlay);
}

void uiPracticeMode() {
    Player user;
    Player comp;

    cout << "======== BULLS 'n COWS ========" << endl;
    cout << "[GAME] Difficulty set to Practice Mode." << endl << endl;
    comp.secretCode = generateCode(comp);
    cout << "[COMPUTER] Computer has generated its own secret code." << endl << endl;

    initGame(user, comp, PRACTICE, MANUAL);
}

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