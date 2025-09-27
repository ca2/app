#pragma once

#include <vector>

#include "shader.h"

const unsigned int QUAD_NUM_TRIANGLES = 6;

/**
 * A unit square that covers the whole screen.
 *
 * Includes texture coordinates.
 */
class FullscreenQuad {
public:
	FullscreenQuad();
    void Draw();

private:
    void loadVertexData();

private: 
    unsigned int mVAO;
    unsigned int mVBO;

    std::vector<float> mVertices = {
		// positions   // textureCoordinates
		-1.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,

		-1.0f,  1.0f,  0.0f, 1.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,
		 1.0f,  1.0f,  1.0f, 1.0f
    };
};