#include "interface.h"
#include "utils.h"

void uiMainMenu() {
    cout << "======== BULLS 'N COWS ========" << endl;
    cout << " Choose a difficulty mode: " << endl;
    cout << " [E] Easy      [M] Medium  " << endl << endl;
    cout << "      [X] Close Game" << endl;
    cout << "=========== ver 1.0 ===========" << endl;
    cout << endl << "COMMAND: ";
}

// GOOD TO GO!
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

// IN DEVELOPMENT
void uiMediumMode() {
    fstream usrGuessesFile;     // fstream object that is responsible for handling our external (text) file
    stringstream UGF_fileName;  // stringstream object that stores the name of the usrGuessesFile (UGF)

    bool inAskingMode = true;   // Determines if the game system is asking for pre-made game settings

    Player user;                // User player object
    Player comp;                // Computer player object

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
                    string tmpStr; // only a temporary string

                    // PROMPT USER TO PROVIDE THE NAME OF THEIR TEXT FILE THAT CONTAINS THEIR GUESS CODE
                    cout << "[GAME] Please provide the name (or path) of your text file that contains your guess code: ";
                    cin >> tmpStr;
                    UGF_fileName.str(tmpStr);

                    usrGuessesFile.open(UGF_fileName.str(), fstream::in);

                    if (usrGuessesFile.is_open() && !usrGuessesFile.fail())
                    {
                        while (getline(UGF_fileName, tmpStr, '\\'));

                        cout << "[GAME] " << tmpStr << " has been loaded to the game system successfully." << endl << endl;
                        inAskingMode = false;
                    }

                } while (inAskingMode);
                break;
            default:
                cerr << "[ERROR] Invalid argument! Please try again." << endl;
        }

    } while (inAskingMode);

    initGame(user, comp, MEDIUM, (ModeOfPlay)modeOfPlay);

    usrGuessesFile.close();
}