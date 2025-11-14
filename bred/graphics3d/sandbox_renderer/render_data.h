#pragma once
#include <glm/glm.hpp>
//#include <vector>

struct RenderObject {
    uint32_t    meshId;       // an index or handle into the renderer's own model cache
    floating_matrix4   modelMatrix;
    int         materialId;   // e.g. which texture/descriptor to bind
};

struct CameraData {
    floating_matrix4 view;
    floating_matrix4 proj;
};

