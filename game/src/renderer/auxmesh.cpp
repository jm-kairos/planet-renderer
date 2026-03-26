#include "auxmesh.h"

//auto BS::mesh_static_build(Mesh& tarMesh) -> void
//{
//    //using namespace BSMesh;
//
//    // create buffers/arrays
//    glGenVertexArrays(1, &tarMesh.VAO);
//    glGenBuffers(1, &tarMesh.VBO);
//    glGenBuffers(1, &tarMesh.EBO);
//
//    glBindVertexArray(tarMesh.VAO);
//    // load data into vertex buffers
//    glBindBuffer(GL_ARRAY_BUFFER, tarMesh.VBO);
//    glBufferData(GL_ARRAY_BUFFER, tarMesh.vertices.size() * sizeof(VertexData), &tarMesh.vertices[0], GL_STATIC_DRAW);
//
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, tarMesh.EBO);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, tarMesh.indices.size() * sizeof(unsigned int), &tarMesh.indices[0], GL_STATIC_DRAW);
//
//    // set the vertex attribute pointers
//    // vertex Positions
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)0);
//    // vertex normals
//    glEnableVertexAttribArray(1);
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)offsetof(VertexData, VertexData::n));
//    // vertex texture coords
//    glEnableVertexAttribArray(2);
//    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)offsetof(VertexData, VertexData::tex));
//    // vertex tangent
//    glEnableVertexAttribArray(3);
//    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)offsetof(VertexData, VertexData::tan));
//    // vertex bitangent
//    glEnableVertexAttribArray(4);
//    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)offsetof(VertexData, VertexData::biTan));
//    // ids
//    glEnableVertexAttribArray(5);
//    glVertexAttribIPointer(5, 4, GL_INT, sizeof(VertexData), (void*)offsetof(VertexData, VertexData::boneIds));
//
//    // weights
//    glEnableVertexAttribArray(6);
//    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)offsetof(VertexData, VertexData::weights));
//
//    glBindVertexArray(0);
//}

//auto BS::mesh_static_draw(const Mesh& tarMesh, GLProgram &tarShader) -> void
//{
//	// bind appropriate textures
//    
//
//    // draw mesh
//    glBindVertexArray(tarMesh.VAO);
//    glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(tarMesh.indices.size()), GL_UNSIGNED_INT, 0);
//    glBindVertexArray(0);
//
//    // always good practice to set everything back to defaults once configured.
//    // glActiveTexture(GL_TEXTURE0);
//}