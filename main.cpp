#include <iostream>

#include "utils.h"
#include "interface.h"

int main() {
    bool keepUI = true;
    char command;

    do  {
        uiMainMenu();

        cin >> command;

        cout << endl;
        switch (toupper(command))
        {
            case EASY_MODE:
                uiEasyMode();
                keepUI = false;
                break;
            case MEDIUM_MODE:
                // uiMediumMode(); -- not yet available in this version.
                cout << "[UNAVAILABLE] This game mode is not yet available. Stay tuned in the next version." << endl;
                break;
            case EXIT:
                keepUI = false;
                break;
            default:
                cerr << "[ERROR] Invalid argument! Please try again." << endl;
        }
        cout << endl;
    } while (keepUI);

    system("pause > 0");

    return EXIT_SUCCESS;
}
