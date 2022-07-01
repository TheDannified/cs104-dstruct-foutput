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

void uiEasyMode() {
    bool isInGame = true;   // Determines if the game is ongoing
    Player user;    // User player object.
    Player comp;    // Computer player object.

    Code userGuess;     // Stores the most recent guess code of the "user" player
    Code compGuess;     // Stores the most recent guess code of the "comp" player

    map<string, int> result;    // guess evaluate tracker.

    // Prompt user to provide their own secret code.
    promptSecretCode(user);

    // Generate a code for the computer.
    comp.secretCode = generateCode(EASY, comp);
    cout << "[COMPUTER] Computer has generated its own secret code." << endl << endl;

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
        compGuess = generateCode(EASY, comp);
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
}


void uiMediumMode() {
    Player user;
    Player comp;
}