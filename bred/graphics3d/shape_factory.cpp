// Created by camilo on 2025-08-23 21:23 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "shape_factory.h"


BEGIN_GPU_PROPERTIES(::graphics3d::shape_factory::Vertex)
GPU_PROPERTY("position", ::gpu::e_type_seq3)
GPU_PROPERTY("color", ::gpu::e_type_seq3)
GPU_PROPERTY("uv", ::gpu::e_type_seq2)
END_GPU_PROPERTIES()



