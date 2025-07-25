//
// Created by ChiroYuki on 22/07/2025.
//

#include <format>
#include "voxelEngine/voxelWorld/chunk/ChunkMesh.h"
#include "voxelEngine/voxelWorld/voxel/VoxelArray.h"
#include "core/Logger.h"

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
    glEnableVertexAttribArray(0);
    glVertexAttribIPointer(0, 1, GL_UNSIGNED_INT, sizeof(FaceInstance), (void*)nullptr);
    glVertexAttribDivisor(0, 1);

    instanceBuffer.unbind();
    vao.unbind();
}

void ChunkMesh::uploadInstances(const std::vector<FaceInstance>& instances) {
    static int i = 0;
    i++;
    instanceBuffer.bind();
    instanceBuffer.uploadData(instances.data(), instances.size() * sizeof(FaceInstance), GL_DYNAMIC_DRAW);
    instanceCount = instances.size();
    instanceBuffer.unbind();
    Logger::info() << "instanceCount: " << instanceCount << " | i = " << i;
}

void ChunkMesh::setupBuffers() {

}

void ChunkMesh::draw() const {
    if (instanceCount == 0) return;

    vao.bind();
    glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, static_cast<GLsizei>(instanceCount));
    vao.unbind();
}