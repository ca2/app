// Created by camilo with Mom and Bilbo support on
// 2025-06-01 23:20 <3ThomasBorregaardSorensen!!
#pragma once


#include "bred/gpu/face.h"



namespace draw2d_gpu
{


   class CLASS_DECL_DRAW2D_GPU face:
      virtual public ::draw2d_gpu::face
   {
   public:

      
      unsigned int m_FaceVAO, m_FaceVBO;


      face();
      ~face() override;

      //virtual character& get_character(const ::scoped_string& scopedstr);


      virtual void create_character(::draw2d_gpu::character& ch, const ::scoped_string& scopedstr);

      void create_draw_buffers();

      void create_texture(::draw2d_gpu::character& ch, const unsigned char* p);


   };


} // namespace draw2d_gpu

