#pragma once

#ifndef DSAFO_INTERFACE_H
#define DSAFO_INTERFACE_H

#include <iostream>
#include <vector>
#include <map>
#include "types.h"

using namespace std;

void uiMainMenu();
void uiEasyMode();
void uiMediumMode();
/**
 * uiPracticeMode
 */
void uiPracticeMode();

/**
 * promptSecretCode prompts the user to give out their own secret code.
 * This is specifically designed for human players to interact with the program.
 * @param player - the target player
 */
void promptSecretCode(Player& player);

/**
 * promptGuessCode prompts the user to give out their own guess code.
 * This is specifically design for human players to interact with the program.
 * @param player - the target player
 */
void promptGuessCode(Player& player);

#endif //DSAFO_INTERFACE_H
