// Christophe Savard
// 40017812
// COMP-371 WW 
// Assignment 2
// March 8th 2018

#pragma once

/// \brief Horse offset
extern glm::vec3 offset;
/// \brief Horse scale factor
extern float size;
/// \brief Horse yaw angle
extern float yawAngle;
/// \brief Horse pitch angle
extern float pitchAngle;
/// \brief Cubes GL containers
extern GLuint cubesVAO, cubesVBO, cubesEBO;
/// \brief Lines GL containers
extern GLuint linesVAO, linesVBO;
/// \brief Axises GL containers
extern GLuint axisVAO, axisVBO;
/// \brief Current projection * view matrix
extern glm::mat4 vpMatrix;

/**
 * \brief Setup the cubes VAO, VBO, and EBO
 */
void setupCubes();

/**
 * \brief Setup the grid lines VAO and VBO
 */
void setupLines();

/**
 * \brief Setup the axises VAO and VBO
 */
void setupAxis();

/**
 * \brief Render all the horse cubes
 */
void renderCubes();

/**
 * \brief Render all the grid lines
 */
void renderLines();

/**
 * \brief Render the XYZ axises
 */
void renderAxis();