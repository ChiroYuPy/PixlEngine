//
// Created by ChiroYuki on 22/07/2025.
//

#include <format>
#include "voxelEngine/voxelWorld/chunk/ChunkMesh.h"
#include "voxelEngine/voxelWorld/voxel/VoxelArray.h"
#include "utils/Logger.h"

ChunkMesh::ChunkMesh()
        : vertexBuffer(BufferType::Vertex),
          instanceBuffer(BufferType::Instance) {

    vao.bind();

    setupVertexAttribs();

    vao.unbind();
    vertexBuffer.unbind();
    instanceBuffer.unbind();
}

ChunkMesh::~ChunkMesh() {

}

void ChunkMesh::setupVertexAttribs() {
    // VAO déjà bindé à l'appel

    // Vertex attrib position (location=0)
    vertexBuffer.bind();
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float)*3, (void*)0);

    // Instance attrib position (location=1)
    instanceBuffer.bind();

    glEnableVertexAttribArray(1);
    glVertexAttribIPointer(1, 3, GL_INT, sizeof(FaceInstance), (void*)0);
    glVertexAttribDivisor(1, 1);

    // Instance attrib faceID (location=2)
    glEnableVertexAttribArray(2);
    glVertexAttribIPointer(2, 1, GL_UNSIGNED_BYTE, sizeof(FaceInstance), (void*)(offsetof(FaceInstance, faceID)));
    glVertexAttribDivisor(2, 1);

    // Instance attrib voxelID (location=3)
    glEnableVertexAttribArray(3);
    glVertexAttribIPointer(3, 1, GL_UNSIGNED_BYTE, sizeof(FaceInstance), (void*)(offsetof(FaceInstance, voxelID)));
    glVertexAttribDivisor(3, 1);
}

void ChunkMesh::uploadInstances(const std::vector<FaceInstance>& instances) {
    instanceBuffer.bind();
    instanceBuffer.uploadData(instances.data(), instances.size() * sizeof(FaceInstance), GL_DYNAMIC_DRAW);
    instanceCount = instances.size();
    Logger::warn(std::format("{}", instanceCount));
}

void ChunkMesh::draw() const {
    vao.bind();
    glDrawArraysInstanced(GL_TRIANGLES, 0, 6, (GLsizei)instanceCount);
    vao.unbind();
}