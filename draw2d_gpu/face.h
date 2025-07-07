// Created by camilo with Mom and Bilbo support on
// 2025-06-01 23:20 <3ThomasBorregaardSorensen!!
#pragma once


#include "bred/typeface/face.h"



namespace draw2d_gpu
{


   class CLASS_DECL_DRAW2D_GPU face:
      virtual public ::typeface::face
   {
   public:

      
      //sunsigned int m_FaceVAO, m_FaceVBO;

      ::pointer < ::gpu::model_buffer >   m_pmodelbuffer;


      face();
      ~face() override;



      virtual void create_character(::typeface::character& ch, const ::scoped_string& scopedstr);

      void create_draw_buffers();

      virtual void create_texture(::typeface::character& ch, const unsigned char* p);


   };


} // namespace draw2d_gpu

