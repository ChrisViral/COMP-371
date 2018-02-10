// Christophe Savard
// 40017812
// COMP-371 WW 
// Assignment 1
// Feburary 8th 2018

#pragma once

/**
 * \brief  Initialize GLFW, GLEW, and OpenGL
 * \return True if the initialization was successful, false otherwise
 */
static bool init();

/**
 * \brief Clears all current memory then closes the application
 * \param code Exit code
 */
static void quit(const int code);