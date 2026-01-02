// First try common GlobalUBO1 structure for 3D graphics applications
// by camilo on 2025-12-02 22:25 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "global_ubo1.h"


BEGIN_GPU_PROPERTIES(::graphics3d::global_ubo1)
GPU_PROPERTY("projection", ::gpu::e_type_mat4)
GPU_PROPERTY("view", ::gpu::e_type_mat4)
GPU_PROPERTY("invView", ::gpu::e_type_mat4)
GPU_PROPERTY("ambientLightColor", ::gpu::e_type_seq4)
GPU_PROPERTY("cameraPosition", ::gpu::e_type_seq3)
GPU_PROPERTY("pointLights", ::gpu_properties<::gpu::point_light>(), ::graphics3d::global_ubo1::MAX_LIGHTS)
GPU_PROPERTY("numLights", ::gpu::e_type_int)
GPU_PROPERTY("padding1", ::gpu::e_type_float)
GPU_PROPERTY("padding2", ::gpu::e_type_float)
GPU_PROPERTY("padding3", ::gpu::e_type_float)
END_GPU_PROPERTIES()



