//
// Created by ChiroYuki on 22/07/2025.
//

#include <format>
#include "voxelEngine/voxelWorld/chunk/ChunkMesh.h"
#include "voxelEngine/voxelWorld/voxel/VoxelArray.h"
#include "utils/Logger.h"

ChunkMesh::ChunkMesh()
: instanceBuffer(BufferType::Instance) {
    setupVertexAttribs();
    setupBuffers();
}

ChunkMesh::~ChunkMesh() {

}

void ChunkMesh::setupVertexAttribs() {
    vao.bind();

    instanceBuffer.bind();
    glEnableVertexAttribArray(1);
    glVertexAttribIPointer(1, 1, GL_UNSIGNED_INT, sizeof(FaceInstance), (void*)nullptr);
    glVertexAttribDivisor(1, 1);

    instanceBuffer.unbind();
    vao.unbind();
}

void ChunkMesh::uploadInstances(const std::vector<FaceInstance>& instances) {
    instanceBuffer.bind();
    instanceBuffer.uploadData(instances.data(), instances.size() * sizeof(FaceInstance), GL_DYNAMIC_DRAW);
    instanceCount = instances.size();
    instanceBuffer.unbind();
}

void ChunkMesh::setupBuffers() {

}

void ChunkMesh::draw() const {
    if (instanceCount == 0) return;

    vao.bind();
    glDrawArraysInstanced(GL_TRIANGLES, 0, 6, static_cast<GLsizei>(instanceCount));
    vao.unbind();
}