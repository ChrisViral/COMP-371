// Christophe Savard
// 40017812
// COMP-371 WW 
// Term Project
// April 12th 2018

#pragma once

/**
* \brief Generates a random integer value between the min and max values inclusively
* \param min Minimum value
* \param max Maximum value
* \return    The randomly generated integer
*/
int randomRange(const int min, const int max);

/**
* \brief Generates a random floating point value between the min and max values inclusively
* \param min Minimum value
* \param max Maximum value
* \return    The randomly generated floating point value
*/
float randomRangef(const float min, const float max);

/**
 * \brief Returns either -1 or 1, randomly
 * \return -1 or 1
 */
int randomSign();