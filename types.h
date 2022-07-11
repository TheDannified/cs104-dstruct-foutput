#pragma once

#ifndef DSAFO_TYPES_H
#define DSAFO_TYPES_H

#include <vector>
#define MAX_CODE_LENGTH 4
#define MAX_GUESS_ATTEMPTS 7
#define DEFAULT_FILE_EXTENSION ".txt"

using namespace std;

typedef string Code;

/**
 * Difficulty - an enumeration set that comprises of available game difficulties in this program.
 */
enum Difficulty {
    PRACTICE,   // Practice Mode
    EASY,       // Easy AI Mode
    MEDIUM      // Medium AI Mode
};

/**
 * Commands - an enumeration set that comprises of available options in the Main Menu of this program.
 */
enum Commands {
    EASY_MODE = 'E',
    MEDIUM_MODE = 'M',
    PRACTICE_MODE = 'P',
    EXIT = 'X'
};

/**
 * ModeOfPlay - an enumeration set that comprises of available options of how the player will submit
 *              guess codes when in Medium AI game mode.
 */
enum ModeOfPlay {
    MANUAL = 'X',       // Manual encoding
    AUTOMATIC = 'C'     // With file-reading
};

/**
 * Player - a class that contains the basic attributes a player must have in this game.
 * It consists of these following attributes:
 * @attributes secretCode - a string of 4-character long code that other player objects must guess
 * @attributes guesses - a vector object (accepts Code type) that contains guess codes made by this player object
 * @attributes isWinner - a boolean variable that determines if the player won its current game session.
 */
class Player {
public:
    Code secretCode;
    vector<Code> guesses;
    bool isWinner = false;
};

/**
 * Result - a structure that contains the information of an evaluated guess code after being compared
 *          to a player's secret code.
 * It consists of these following attributes:
 * @param bulls -
 */
struct Result {
    short bulls;
    short cows;
};


#endif //DSAFO_TYPES_H
