#include "fullscreenquad.h"

#include <glad/glad.h>

FullscreenQuad::FullscreenQuad() {
    loadVertexData();
};

void
FullscreenQuad::Draw() {
    glDisable(GL_DEPTH_TEST);
    glBindVertexArray(mVAO);
    glDrawArrays(GL_TRIANGLES, 0, QUAD_NUM_TRIANGLES);
    glEnable(GL_DEPTH_TEST);
    glBindVertexArray(0);
};

void
FullscreenQuad::loadVertexData() {
    // create our data structures
    glGenVertexArrays(1, &mVAO);
    glGenBuffers(1, &mVBO);

    glBindVertexArray(mVAO); // use this VAO for subsequent calls

    glBindBuffer(GL_ARRAY_BUFFER, mVBO); // use this VBO for subsequent calls
    glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(float), &mVertices[0], GL_STATIC_DRAW); // copy over the vertex data

    // setup the locations of vertex data
    // positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);

    // texture coordinates
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

    glBindVertexArray(0);
}