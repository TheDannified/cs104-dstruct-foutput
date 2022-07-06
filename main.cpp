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
                keepUI = false;
                break;
            case MEDIUM_MODE:
                uiMediumMode();
                keepUI = false;
                break;
            case PRACTICE_MODE:
                uiPracticeMode();
                keepUI = false;
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
