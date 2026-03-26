#ifndef TERRAIN_H
#define TERRAIN_H

#include "auxmesh.h"
#include "../defines.h"

#include "temp/Mesh.h"

struct TerrainConfig
{
	GLint numVerticesPerGLPatch;
	unsigned numGLPatchesAcrossTerrain;
	int terrainWidth;
	int terrainHeight;
};

struct Terrain
{
	Terrain(const TerrainConfig& tc, const std::vector<Texture>& textures) {

		// copy terrain data configuration
		this->config.numGLPatchesAcrossTerrain = tc.numGLPatchesAcrossTerrain;
		this->config.numVerticesPerGLPatch = tc.numVerticesPerGLPatch;
		this->config.terrainHeight = tc.terrainHeight;
		this->config.terrainWidth = tc.terrainWidth;

		//using namespace BS;

		this->mesh = nullptr;

		const unsigned rez = tc.numGLPatchesAcrossTerrain;
		const int tw = tc.terrainWidth;
		const int th = tc.terrainHeight;

		std::vector<VERTEX_PNT> vertices = {};
		vertices.reserve(rez * rez * 4);

		for (unsigned i = 0; i <= rez - 1; i++)
		{
			for (unsigned j = 0; j <= rez - 1; j++)
			{
				VERTEX_PNT v1 = {};

				v1.x1 = -tw / 2.0f + tw * i / (float)rez;
				v1.x2 = 0.0f;
				v1.x3 = -th / 2.0f + th * j / (float)rez;

				v1.t1 = i / (float)rez;
				v1.t2 = j / (float)rez;

				VERTEX_PNT v2 = {};

				v2.x1 = -tw / 2.0f + tw * (i + 1) / (float)rez;
				v2.x2 = 0.0f;
				v2.x3 = -th / 2.0f + th * j / (float)rez;

				v2.t1 = (i + 1) / (float)rez;
				v2.t2 = j / (float)rez;

				VERTEX_PNT v3 = {};

				v3.x1 = -tw / 2.0f + tw * i / (float)rez;
				v3.x2 = 0.0f;
				v3.x3 = -th / 2.0f + th * (j + 1) / (float)rez;

				v3.t1 = i / (float)rez;
				v3.t2 = (j + 1) / (float)rez;

				VERTEX_PNT v4 = {};

				v4.x1 = -tw / 2.0f + tw * (i + 1) / (float)rez;
				v4.x2 = 0.0f;
				v4.x3 = -th / 2.0f + th * (j + 1) / (float)rez;

				v4.t1 = (i + 1) / (float)rez;
				v4.t2 = (j + 1) / (float)rez;

				vertices.push_back(v1);
				vertices.push_back(v2);
				vertices.push_back(v3);
				vertices.push_back(v4);

			}
		}

		// mesh = new Mesh({}, vertices, textures);
		
		this->mesh = object_mesh_create(vertices);

		glPatchParameteri(GL_PATCH_VERTICES, tc.numVerticesPerGLPatch);

	}
	~Terrain(){
		object_mesh_destroy(&this->mesh);
	}
public:
	void draw(void) const;
public:
	TerrainConfig config;
	MESH* mesh;
	// BS::Texture textures;
};

#endif TERRAIN_H
