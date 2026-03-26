#ifndef AUXMESH_H
#define AUXMESH_H

#include <vector>
#include <string>

#include "../defines.h"

#include "glprogram.h"
#include "temp/Mesh.h"

constexpr auto MAX_BONE_INFLUENCE = 4;

struct VertexData;
struct Texture;

struct VertexData
{
	v3 pos{ v3() };
	v3 n{ v3() };
	v2 tex{ v2() };
	v3 tan{ v3() };
	v3 biTan{ v3() };
	int boneIds[MAX_BONE_INFLUENCE];
	float weights[MAX_BONE_INFLUENCE];
};

struct Texture {
	uint id{ 0 };
	std::string type{ "" };
	std::string path{ "" };
};

struct Mesh {

	Mesh(const std::vector<uint>& indices,
		const std::vector<VertexData>& vertices,
		const std::vector<Texture>& textures) {

		this->EBO = 0;

		this->vertices = vertices;
		this->indices = indices;
		this->textures = textures;

		// create buffers/arrays
		glGenVertexArrays(1, &this->VAO);
		glGenBuffers(1, &this->VBO);
		// glGenBuffers(1, &this->EBO);

		glBindVertexArray(this->VAO);
		// load data into vertex buffers
		glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
		glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(VertexData), &this->vertices[0], GL_STATIC_DRAW);

		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(uint), &this->indices[0], GL_STATIC_DRAW);

		// set the vertex attribute pointers
		// vertex Positions
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)0);
		// vertex normals
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)offsetof(VertexData, VertexData::n));
		// vertex texture coords
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)offsetof(VertexData, VertexData::tex));
		// vertex tangent
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)offsetof(VertexData, VertexData::tan));
		// vertex bitangent
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)offsetof(VertexData, VertexData::biTan));
		// ids
		glEnableVertexAttribArray(5);
		glVertexAttribIPointer(5, 4, GL_INT, sizeof(VertexData), (void*)offsetof(VertexData, VertexData::boneIds));

		// weights
		glEnableVertexAttribArray(6);
		glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)offsetof(VertexData, VertexData::weights));

	}

	~Mesh() {
		glDeleteBuffers(1, &this->EBO);
		glDeleteBuffers(1, &this->VBO);
		glDeleteVertexArrays(1, &this->VAO);
	}

	std::vector<uint> indices;
	std::vector<VertexData> vertices;
	std::vector<Texture> textures;

	uint VAO, VBO, EBO;
};

namespace Geometry {

	struct SphericalCube
	{
		SphericalCube(GLfloat radius, uint numGLPatchesPerPlane, const std::vector<Texture>& textures, GLint numVerticesPerGLPatch = (GLint)4) {

			this->radius = radius;
			this->numGLPatchesPerPlane = numGLPatchesPerPlane;

			const int numFaces = 6;

			std::vector<VERTEX_PNT> vertices;
			vertices.reserve(numFaces * numVerticesPerGLPatch * numGLPatchesPerPlane * numGLPatchesPerPlane);
			// std::vector<uint> indices;

			this->mesh = (MESH*)NULL;

			{
				const v3 origin = v3(0.f);
				const GLfloat sofo = radius;

				// Directions per face: +X, -X, +Y, -Y, +Z, -Z
				v3 faceNormals[6] = {
					v3(1, 0, 0),  // +X
					v3(-1, 0, 0), // -X
					v3(0, 1, 0),  // +Y
					v3(0, -1, 0), // -Y
					v3(0, 0, 1),  // +Z
					v3(0, 0, -1)  // -Z
				};

				// For each face, define its "right" and "up" vector

				v3 faceUps[6] = {
					v3(0, 1, 0),  // +X
					v3(0, 1, 0),  // -X
					v3(0, 0, -1), // +Y
					v3(0, 0, 1),  // -Y
					v3(0, 1, 0),  // +Z
					v3(0, 1, 0)   // -Z
				};

				// compute positions and indices
				for (int face = 0; face < 6; ++face) {
					v3 normal = faceNormals[face];
					v3 up = faceUps[face];
					v3 right = glm::cross(normal, up);

					for (unsigned y = 0; y <= numGLPatchesPerPlane - 1; y++) {

						for (unsigned x = 0; x <= numGLPatchesPerPlane - 1; x++) {

							const GLfloat u = (x / (GLfloat)numGLPatchesPerPlane - 0.5f) * 2.0f; // [-1,1]
							const GLfloat v = (y / (GLfloat)numGLPatchesPerPlane - 0.5f) * 2.0f;
							const GLfloat uu = ((x + 1) / (GLfloat)numGLPatchesPerPlane - 0.5f) * 2.0f;
							const GLfloat vv = ((y + 1) / (GLfloat)numGLPatchesPerPlane - 0.5f) * 2.0f;

							VERTEX_PNT vert1 =
							{
								sofo * normal.x + u * right.x * (sofo) + v * up.x * (sofo),
								sofo * normal.y + u * right.y * (sofo) + v * up.y * (sofo),
								sofo * normal.z + u * right.z * (sofo) + v * up.z * (sofo),
								0.f, 0.f, 0.f,
								u, v
							};
							VERTEX_PNT vert2 =
							{
								sofo * normal.x + uu * right.x * (sofo) + v * up.x * (sofo),
								sofo * normal.y + uu * right.y * (sofo) + v * up.y * (sofo),
								sofo * normal.z + uu * right.z * (sofo) + v * up.z * (sofo),
								0.f, 0.f, 0.f,
								uu, v
							};
							VERTEX_PNT vert3 =
							{
								sofo * normal.x + u * right.x * (sofo) + vv * up.x * (sofo),
								sofo * normal.y + u * right.y * (sofo) + vv * up.y * (sofo),
								sofo * normal.z + u * right.z * (sofo) + vv * up.z * (sofo),
								0.f, 0.f, 0.f,
								u, vv
							};
							VERTEX_PNT vert4 =
							{
								sofo * normal.x + uu * right.x * (sofo) + vv * up.x * (sofo),
								sofo * normal.y + uu * right.y * (sofo) + vv * up.y * (sofo),
								sofo * normal.z + uu * right.z * (sofo) + vv * up.z * (sofo),
								0.f, 0.f, 0.f,
								uu, vv
							};

							vertices.push_back(vert1);
							vertices.push_back(vert2);
							vertices.push_back(vert3);
							vertices.push_back(vert4);
						}
					}
				}
			}

			this->mesh = object_mesh_create(vertices);

			glPatchParameteri(GL_PATCH_VERTICES, numVerticesPerGLPatch);

			if (this->mesh == nullptr)
				return;

		}
		~SphericalCube() {
			object_mesh_destroy(&this->mesh);
		}

		MESH* mesh;
		uint numGLPatchesPerPlane;
		GLfloat radius;
	};

	template<typename GeometryType>
	void draw_geometry(GeometryType*& geo, const GLProgram& tarProg) {

		// bind appropriate textures
		uint diffuseNr = 1;
		uint specularNr = 1;
		uint normalNr = 1;
		uint heightNr = 1;

		const size_t numTextures = geo->mesh->textures.size();

		for (size_t i = 0; i < numTextures; i++)
		{
			glActiveTexture(GL_TEXTURE0 + (int)i); // active proper texture unit before binding
			// retrieve texture number (the N in diffuse_textureN)
			std::string number;
			const std::string name = geo->mesh->textures[i].type;

			if (name == "texture_diffuse")
				number = std::to_string(diffuseNr++);
			else if (name == "texture_specular")
				number = std::to_string(specularNr++); // transfer uint to string
			else if (name == "texture_normal")
				number = std::to_string(normalNr++); // transfer uint to string
			else if (name == "texture_height")
				number = std::to_string(heightNr++); // transfer uint to string

			// now set the sampler to the correct texture unit
			glUniform1i(glGetUniformLocation(tarProg.getProgramId(), (name + number).c_str()), (int)i);
			// and finally bind the texture
			glBindTexture(GL_TEXTURE_2D, geo->mesh->textures[i].id);
		}

		// draw mesh
		glBindVertexArray(geo->mesh->VAO);
		glDrawElements(GL_TRIANGLES, static_cast<uint>(geo->mesh->indices.size()), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		// always good practice to set everything back to defaults once configured.
		glActiveTexture(GL_TEXTURE0);
	}

}

#endif AUXMESH_H

