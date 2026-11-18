// Created by camilo with Mom and Bilbo support on
// 2025-06-01 23:20 <3ThomasBorregaardSorensen!!
#pragma once


#include "bred/typeface/face.h"



namespace draw2d_opengl
{


   class CLASS_DECL_DRAW2D_OPENGL face:
      virtual public ::typeface::face
   {
   public:

      
      //unsigned int m_FaceVAO, m_FaceVBO;


      face();
      ~face() override;

      //virtual character& get_character(const ::scoped_string& scopedstr);


      virtual void create_character(::typeface::character& ch, const ::scoped_string& scopedstr) override;

      void create_draw_buffers();

      void create_texture(::typeface::character& ch, const unsigned char* p) override;


   };


} // namespace draw2d_opengl

