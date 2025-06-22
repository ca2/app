// Created by camilo on 2025-06-22 12:22 <3ThomasBorregaardSørensen!!
#pragma once


namespace gpu_opengl
{


   class CLASS_DECL_GPU_OPENGL opengl_lock
   {
   public:


      context* m_pcontext;
      opengl_lock* m_plockUpper;
      ::particle_pointer m_pparticleSynchronization;


      opengl_lock(::gpu::context * pcontext);
      ~opengl_lock();




   };



} // namespace gpu_opengl



