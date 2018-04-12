// Christophe Savard
// 40017812
// COMP-371 WW 
// Assignment 2
// March 15th 2018

#pragma once

#define HORSE_COUNT 20

class Shader;
class Mesh;

/// \brief Hord of simulated horses
extern Mesh* hord[];

/**
 * \brief  Initialize GLFW, GLEW, and OpenGL
 * \return True if the initialization was successful, false otherwise
 */
static bool init();

/**
 * \brief Loads all the joints into the joints vector
 */
static void loadJoints();

/**
 * \brief Renders all the ojects in the scene
 * \param shader Shader to render with
 */
static void renderAll(Shader* shader = nullptr);

/**
 * \brief Clears all current memory then closes the application
 * \param code Exit code
 */
static void quit(const int code);