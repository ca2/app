//
// Created by camilo on 2025-08-21.
//
#include "framework.h"
#include "point_light.h"

namespace graphics3d {
} // graphics3d




BEGIN_GPU_PROPERTIES(::gpu::point_light)
GPU_PROPERTY("position", ::gpu::e_type_seq4)
GPU_PROPERTY("color", ::gpu::e_type_seq4)
END_GPU_PROPERTIES()
