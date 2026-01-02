//// From github:/tristancalderbank/OpenGL-PBR-Renderer/Cube.h by
//// camilo on 2025-09-26 ~21:00 <3ThomasBorregaardSorensen!!
//#pragma once
// //Maybe gpu::model can be used (it can model a cube )
//
// #include "bred/gpu/context_object.h"
// #include "bred/graphics3d/renderable.h"
//#include "bred/gpu/model_buffer.h"
//
//
// namespace gpu
// {
//
//
//    /**
//     * A unit cube mesh with only position coordinates.
//     */
//    class CLASS_DECL_GPU cube :
//       virtual public context_object,
//       virtual public ::graphics3d::renderable
//    {
//    public:
//
//       //unsigned int m_uVAO, m_uVBO;
//
//       ::gpu::model_data < ::gpu::position3 > m_modeldata;
//       ::pointer<::gpu::model_buffer> m_pmodelbuffer;
//
//
//       cube();
//       ~cube() override;
//
//
//       virtual void initialize_gpu_cube(::gpu::context* pgpucontext);
//
//
//       void draw(::gpu::command_buffer *pcommandbuffer) override;
//
//
//
//    };
//
//
// } // namespace gpu
//
//
