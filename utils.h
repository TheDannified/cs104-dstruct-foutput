#pragma once

#ifndef DSAFO_UTILS_H
#define DSAFO_UTILS_H

#include <iostream>
#include <random>
#include <vector>
#include <cstring>
#include <algorithm>
#include <map>
#include <fstream>
#include <ctime>
#include <sstream>

#include "utils.h"
#include "types.h"

using namespace std;

/**
 * clear "clears" the entire CLI's messages.
 */
void clear();

/**
 * isNumber checks if a given character is a number.
 * @param ch - the character
 * @return
 */
bool isNumber(const char& ch);

/**
 * validateCode evaluates a given code if it follows the criteria that a guess code must have: <br />
 * - each character is a number digit; and <br />
 * - each digit is unique from other digits.
 * @param code - an array of 4 characters
 * @return <strong> true </strong> if given <code>code</code> follows all the criteria; otherwise <strong> false </strong>
 */
bool validateCode(Code &code);

/**
 * getDifficulty returns...
 * @param difficulty
 * @return a string version of a Difficulty
 */
string getDifficulty(Difficulty difficulty);

/**
 * generateCode returns a 4-character string of Code type.
 * @param player - the target player
 * @return a string of generated Code
 */
// FOR EASY MODE
Code generateCode(Player& player);

/**
 * generateCode returns a 4-character string of Code type.
 * This overloaded function is specifically designed for Medium AI.
 * @param player - the target player
 * @param secretCode - given secret code
 * @return a string of generated Code
 */
// FOR MEDIUM MODE
Code generateCode(Player& player, Code& secretCode);

/**
 * evaluateCode evaluates a guessCode how many bulls and cows were found
 * based on the given guessCode and secret guessCode
 * @param guessCode - guessCode guessed to crack the player's secret guessCode
 * @param secretCode - a player's secret guessCode
 * @return a map that contains "bulls" and "cows" elements with their respective counts
 */
map<string, int> evaluateCode(const Code& guessCode, const Code& secretCode);

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

/**
 * printResult produces a "bulls and cows" message result based on its findings from
 * evaluating a guess code.
 * This is only used after evaluateCode function has been invoked in a variable.
 * @param result - a result of Map type
 * @return
 */
string printResult(map<string, int>& result);

/**
 * hasGuessedSecretCode evaluates if both guessCode and secretCode is exactly the same.
 * @param guessCode - the guess code
 * @param secretCode - the secret code
 * @returns <strong>true</strong> if and only if the guessCode is exactly the same with the secretCode;
 * @returns otherwise, <strong>false</strong>
 */
bool hasGuessedSecretCode(const Code& guessCode, const Code& secretCode);

/**
 * hasPlayerUsedGuessCode checks if the player has already used the guess code they provided
 * @param player - the target player
 * @param guessCode - the given guess code
 * @return <strong>true</strong> if the code is already guessed by the user. Otherwise, <strong>false</strong>.
 */
bool hasPlayerUsedGuessCode(Player& player, Code& guessCode);

/**
 * saveGameResult creates an output file that contains the entire log of its game session
 * @param player1 - a target Player (user)
 * @param player2 - a target Player (computer)
 */
void saveGameResult(Player& player1, Player& player2, Difficulty difficulty);

/**
 * initGame initializes the game.
 * @param user - the user player.
 * @param comp - the comp player.
 * @param modeOfPlay - how to play the game
 */
void initGame(Player& user, Player& comp, Difficulty difficulty, ModeOfPlay modeOfPlay);

/**
 * isBull checks if the position of a digit from the guessCode is exactly the same
 * as the position of that digit from the secretCode
 * @param ch - a number digit character
 * @param guessCode - a player's guess code
 * @param secretCode - player opponent's secret code
 * @return
 */
bool isBull(Code& guessCode, Code& secretCode, char ch);

/**
 * isCow checks if a digit from both guessCode and secretCode does exist
 * but are different in indexes from each given codes.
 * @param ch - a number digit character
 * @param guessCode - a player's guess code
 * @param secretCode - player opponent's secret code
 * @return
 */
bool isCow(Code& guessCode, Code& secretCode, char ch);

#endif //DSAFO_UTILS_H
