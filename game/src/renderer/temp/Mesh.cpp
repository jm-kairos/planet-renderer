#include "Mesh.h"

MESH* object_mesh_create(const std::vector<VERTEX_PNT>& vertices)
{
	MESH* res = (MESH*)NULL;

	res = new MESH;

	if (res == (MESH*)NULL)
	{
		std::cout << "Unable to allocate memory for an object of type 'MESH'" << "\n";
		return (MESH*)NULL;
	}

	res->vertices = vertices;

	glGenVertexArrays(1, &res->VAO);
	glGenBuffers(1, &res->VBO);

	glBindVertexArray(res->VAO);

	glBindBuffer(GL_ARRAY_BUFFER, res->VBO);
	glBufferData(GL_ARRAY_BUFFER, res->vertices.size() * sizeof(VERTEX_PNT), &res->vertices[0], GL_STATIC_DRAW);

	// set the vertex attribute pointers
	// vertex Positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VERTEX_PNT), (GLvoid*)0);
	// vertex normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VERTEX_PNT), (GLvoid*)(3 * sizeof(GLfloat)));
	// vertex texture coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VERTEX_PNT), (GLvoid*)(6 * sizeof(GLfloat)));

	return res;
}

void object_mesh_destroy(MESH** mesh)
{
	if (*mesh != (MESH*)(NULL))
	{

		glDeleteBuffers(1, &((*mesh)->VBO));
		glDeleteVertexArrays(1, &((*mesh)->VAO));

		delete *mesh;
		*mesh = (MESH*)(NULL);
	}
}
