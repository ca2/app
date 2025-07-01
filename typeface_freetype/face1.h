// Created by camilo with Mom and Bilbo support on
// 2025-06-01 23:20 <3ThomasBorregaardSorensen!!
#pragma once


#include "bred/typeface/face.h"



namespace typeface_freetype
{


   class CLASS_DECL_TYPEFACE_FREETYPE face:
      virtual public ::typeface::face
   {
   public:

      
      //unsigned int m_FaceVAO, m_FaceVBO;


      face();
      ~face() override;

      //virtual character& get_character(const ::scoped_string& scopedstr);


      virtual void create_character(::typeface::character& ch, const ::scoped_string& scopedstr);

      void create_draw_buffers();

      void create_texture(::typeface::character& ch, const unsigned char* p);


   };


} // namespace typeface_freetype

