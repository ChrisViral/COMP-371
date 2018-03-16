// Christophe Savard
// 40017812
// COMP-371 WW 
// Assignment 2
// March 15th 2018

#include "Object.h"

using glm::vec3;

//Default material properties
const vec3 Object::ambient = vec3(0.3f);
const vec3 Object::diffuse = vec3(1.0f);
const vec3 Object::specular = vec3(1.0f);
const float Object::shininess = 32.0f;

Object::Object(): VAO(0), VBO(0), EBO(0), tex(0), set(false) { }

Object::~Object() { }
