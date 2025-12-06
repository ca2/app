// Created by camilo on 2025-08-23 21:19 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "bred/graphics3d/types.h"


BEGIN_GPU_PROPERTIES(::graphics3d::sequence2_uv)
GPU_PROPERTY("position", ::gpu::e_type_seq2)
GPU_PROPERTY("uv", ::gpu::e_type_seq2)
END_GPU_PROPERTIES()


BEGIN_GPU_PROPERTIES(::graphics3d::sequence3_color)
GPU_PROPERTY("position", ::gpu::e_type_seq3)
GPU_PROPERTY("color", ::gpu::e_type_seq4)
END_GPU_PROPERTIES()


BEGIN_GPU_PROPERTIES(::graphics3d::sequence2_color)
GPU_PROPERTY("position", ::gpu::e_type_seq2)
GPU_PROPERTY("color", ::gpu::e_type_seq4)
END_GPU_PROPERTIES()


BEGIN_GPU_PROPERTIES(::graphics3d::Vertex)
GPU_PROPERTY("position", ::gpu::e_type_seq3)
GPU_PROPERTY("color", ::gpu::e_type_seq3)
GPU_PROPERTY("normal", ::gpu::e_type_seq3)
GPU_PROPERTY("uv", ::gpu::e_type_seq2)
END_GPU_PROPERTIES()

BEGIN_GPU_PROPERTIES(::gpu::position2_uv)
GPU_PROPERTY("position", ::gpu::e_type_seq2)
GPU_PROPERTY("uv", ::gpu::e_type_seq2)
END_GPU_PROPERTIES()

