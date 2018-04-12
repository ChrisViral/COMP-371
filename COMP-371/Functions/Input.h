// Christophe Savard
// 40017812
// COMP-371 WW 
// Assignment 2
// March 15th 2018

#pragma once

#include <GLFW/glfw3.h>

/**
 * \brief Register all GLFW callbacks
 */
void registerCallbacks();

/**
 * \brief GL frame resize callback
 * \param window Window being resized
 * \param width  New width
 * \param height New height
 */
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

/**
 * \brief Mouse movement over the screen callback
 * \param window Window over which the cursor is moving
 * \param xpos X position of the mouse
 * \param ypos Y position of the mouse
 */
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

/**
 * \brief Keyboar press callback
 * \param window   Window in which the keys are pressed
 * \param key      Key being pressed
 * \param scancode Unique identifier
 * \param action   Type of press
 * \param mods     Key modifiers
 */
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

/**
 * \brief GLFW error callback
 * \param error		  Error code
 * \param description Error descritpion
 */
void error_callback(int error, const char* description);