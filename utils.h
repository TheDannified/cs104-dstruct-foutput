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
 * isNumber checks if a given character is a number.
 * @param ch - the character
 * @returns true if the character is a number character. Otherwise, false.
 */
bool isNumber(const char& ch);

/**
 * isAlpha checks if a given character is an alphabet. (case-insensitive)
 * @param ch - the character
 * @return true if the character is an alphabet character. Otherwise, false.
 */
bool isAlpha(const char& ch);

/**
 * isFalseDigit checks if a given character is a question mark (or a false digit) character.
 * @param ch - the character
 * @return true if the character is a question mark. Otherwise, false.
 */
bool isFalseDigit(const char& ch);

/**
 * removeUsedDigits removes the number characters that were used in a player's recent guess code.
 * @param string - the reference string
 * @param guessCode - the player's guess code
 * @return a modified reference string
 */
string removeUsedDigits(string string, Code& guessCode);

/**
 * getHint produces a hint code that contains symbols that represent bulls, cows, and false digits
 * in each index position, provided with a player's guess code and their opponent's secret code to
 * evaluate and compare both codes of their similarities and dissimilarities in form. <br /> <br />
 * For symbols context: <br />
 * <strong><code>0-9</code></strong> represent <strong>bull</strong> digits, <br />
 * <strong><code>A-J</code></strong> represent <strong>cow</strong> digits, <br />
 * <strong><code>?</code></strong> presents <strong>false</strong> digits (or digits that were not found in the secret code)
 * @param guessCode - a player's guess code
 * @param secretCode - a player's secret code
 * @return a hint code
 */
Code getHint(Code& guessCode, Code& secretCode);

/**
 * validateCode evaluates a given code if it follows the criteria that a guess code must have: <br />
 * - given code has exactly 4 characters <br />
 * - each character is a number digit; and <br />
 * - each digit is unique from other digits.
 * @param code - an array of 4 characters
 * @return <strong> true </strong> if given <code>code</code> follows all the criteria; otherwise <strong> false </strong>
 */
bool validateCode(Code &code);

/**
 * getDifficulty returns the string representation of a Difficulty enum constant
 * @param difficulty - a difficulty constant
 * @return a string version of a Difficulty
 */
string getDifficulty(Difficulty difficulty);

/**
 * shiftPosition is responsible for shifting the positions of a hint code to make the computer generate a guess code that
 * is relatively close from its previous guess codes and to its opponent's secret code. Its default shifting direction is
 * in a right (->) direction and is done only once.
 * @param hint - a hint code
 * @return a hint code with its characters shifted to the right
 */
Code shiftPosition(Code& hint);

/**
 * generateCode returns a 4-character string of Code type.
 * @param player - the target player
 * @return a string of generated Code
 */
Code generateCode(Player& player);

/**
 * generateCode returns a 4-character string of Code type.
 * (This overloaded function is specifically designed for Medium AI.)
 * @param player - the target player
 * @param secretCode - given secret code
 * @return a string of generated Code
 */
Code generateCode(Player& player, Code& secretCode);

/**
 * evaluateCode evaluates a guessCode how many bulls and cows were found
 * based on the given guessCode and secret guessCode
 * @param guessCode - guessCode guessed to crack the player's secret guessCode
 * @param secretCode - a player's secret guessCode
 * @return a map that contains "bulls" and "cows" elements with their respective counts
 */
Result evaluateCode(const Code& guessCode, const Code& secretCode);

/**
 * printResult produces a "bulls and cows" message result based on its findings from
 * evaluating a guess code.
 * This is only used after evaluateCode function has been invoked in a variable.
 * @param result - the outcome of evaluated guess code.
 * @return the string message of the outcome.
 */
string printResult(Result& result);

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
void saveGameResult(Player& player1, Player& player2, Difficulty difficulty, const string& filename);

/**
 * initGame initializes the game.
 * @param user - the user player.
 * @param comp - the comp player.
 * @param modeOfPlay - how to play the game
 */
void initGame(Player& user, Player& comp, Difficulty difficulty, ModeOfPlay modeOfPlay);

/**
 * isPracticeMode checks if the difficulty of the game session is in Practice Mode.
 * It restricts the computer to play against the player.
 * @param difficulty - game difficulty
 * @return true if the game difficulty is equal to PRACTICE constant of Difficulty enum.
 */
bool isPracticeMode(Difficulty difficulty);

/**
 * isBull checks if the position of a digit from the guessCode is exactly the same
 * as the position of that digit from the secretCode
 * @param guessCode - a player's guess code
 * @param secretCode - player opponent's secret code
 * @param ch - a number digit character
 * @return true if the given character is a bull digit on both guessCode and secretCode
 */
bool isBull(Code& guessCode, Code& secretCode, char ch);

/**
 * isCow checks if a digit from both guessCode and secretCode does exist
 * but are different in indexes from each given codes.
 * @param guessCode - a player's guess code
 * @param secretCode - player opponent's secret code
 * @param ch - a number digit character
 * @return true if the given character is found in a cow digit on guessCode
 */
bool isCow(Code& guessCode, Code& secretCode, char ch);

#endif //DSAFO_UTILS_H
