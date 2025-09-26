#pragma once
#include <glm/glm.hpp>
//#include <vector>

struct RenderObject {
    uint32_t    meshId;       // an index or handle into the renderer's own model cache
    glm::mat4   modelMatrix;
    int         materialId;   // e.g. which texture/descriptor to bind
};

struct CameraData {
    glm::mat4 view;
    glm::mat4 proj;
};

