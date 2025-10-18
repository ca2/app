// Created by camilo on 2025-10-16 20:37 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "vertex.h"


BEGIN_GPU_PROPERTIES(::gpu::gltf::vertex)
GPU_PROPERTY("position", ::gpu::e_type_seq3)
GPU_PROPERTY("normal", ::gpu::e_type_seq3)
GPU_PROPERTY("uv", ::gpu::e_type_seq2)
GPU_PROPERTY("color", ::gpu::e_type_seq4)
GPU_PROPERTY("tangent", ::gpu::e_type_seq4)
END_GPU_PROPERTIES()


