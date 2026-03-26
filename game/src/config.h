#ifndef CONFIG_H
#define CONFIG_H

#include <iostream>
#include <vector>

#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION
#include "renderer/stb_image.h"

#include "renderer/glprogram.h"
#include "renderer/auxmesh.h"
#include "renderer/terrain.h"

//#include "systems/camera.h"

#include "systems/camera.h"

#endif /* CONFIG_H */
