#ifndef MESH_H
#define MESH_H

#include "stdlib.h"
#include <iostream>

#include <vector>

#include "../glprogram.h"

struct VERTEX_PNT // position, normal and texture coordinates 
{
	GLfloat x1, x2, x3, n1, n2, n3, t1, t2;
};

struct MESH // a basic mesh
{
	std::vector<VERTEX_PNT> vertices; // pntpntpnt...
	GLuint VAO, VBO;
};

MESH* object_mesh_create(const std::vector<VERTEX_PNT>& vertices);
void object_mesh_destroy(MESH** mesh);

#endif MESH_H