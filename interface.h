#pragma once

#ifndef DSAFO_INTERFACE_H
#define DSAFO_INTERFACE_H

#include <iostream>
#include <vector>
#include <map>
#include "types.h"

using namespace std;

/**
 * uiMainMenu is a UI function that presents our users some available game options.
 * This function is always invoked when the program boots up and every after a game
 * is finished.
 */
void uiMainMenu();

/**
 * uiEasyMode, when invoked, enters the players to a game state where they will compete
 * with an AI on Easy difficulty. In this game mode, the player and computer must guess
 * each other's secret code. Whoever guesses a player's secret code first will win the
 * current game.
 */
void uiEasyMode();

/**
 * uiEasyMode, when invoked, enters the players to a game state where they will compete
 * with an AI on Medium difficulty. Just like the Easy difficulty, the player and computer
 * must compete in guessing each other's secret code. However, this time, the computer is
 * equipped with an extra step to guess its opponent's secret code. Gameplay is relatively
 * the same with Easy difficulty.
 */
void uiMediumMode();

/**
 * uiPracticeMode, when invoked, enters the players to a practice game state where they
 * can practice how the game works and test their guessing skills. In this game mode,
 * only human players can guess a computer-generated secret code.
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
