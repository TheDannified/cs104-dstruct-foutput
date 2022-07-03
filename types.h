#pragma once

#ifndef DSAFO_TYPES_H
#define DSAFO_TYPES_H

#include <vector>
#define MAX_CODE_LENGTH 4
#define MAX_GUESS_ATTEMPTS 7

using namespace std;

typedef string Code;

enum Difficulty {
    EASY,
    MEDIUM
};

enum Commands {
    EASY_MODE = 'E',
    MEDIUM_MODE = 'M',
    EXIT = 'X'
};

enum ModeOfPlay {
    MANUAL = 'X',
    AUTOMATIC = 'C'
};

struct Player {
    Code secretCode;
    vector<Code> guesses;
    bool isWinner;
};


#endif //DSAFO_TYPES_H
