// Created by camilo on 2025-08-23 21:14 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "types.h"


BEGIN_GPU_PROPERTIES(::gpu::projection_quad_texcoords_textColor)
GPU_PROPERTY("projection", ::gpu::e_type_mat4)
GPU_PROPERTY("quad", ::gpu::e_type_seq4)
GPU_PROPERTY("texcoords", ::gpu::e_type_seq4)
GPU_PROPERTY("textColor", ::gpu::e_type_seq4)
END_GPU_PROPERTIES()


BEGIN_GPU_PROPERTIES(::gpu::quad_texcoords_textColor)
GPU_PROPERTY("quad", ::gpu::e_type_seq4)
GPU_PROPERTY("texcoords", ::gpu::e_type_seq4)
GPU_PROPERTY("textColor", ::gpu::e_type_seq4)
END_GPU_PROPERTIES()



