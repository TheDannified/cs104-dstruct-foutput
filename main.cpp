#include <iostream>

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
                break;
            case MEDIUM_MODE:
                uiMediumMode();
                break;
            case PRACTICE_MODE:
                uiPracticeMode();
                break;
            case EXIT:
                keepUI = false;
                break;
            default:
                cerr << "[ERROR] Invalid argument! Please try again." << endl;
        }
        cout << endl;
    } while (keepUI);

    return EXIT_SUCCESS;
}
