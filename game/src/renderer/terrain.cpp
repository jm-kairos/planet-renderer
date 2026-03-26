#include "terrain.h"

void Terrain::draw(void) const
{
	// Render terrain
	glBindVertexArray(this->mesh->VAO);
	glDrawArrays(GL_PATCHES, 0, 
		this->config.numVerticesPerGLPatch * 
		this->config.numGLPatchesAcrossTerrain * this->config.numGLPatchesAcrossTerrain
	);
	glBindVertexArray(0);
}
