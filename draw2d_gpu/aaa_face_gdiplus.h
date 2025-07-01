// Created by camilo with Mom and Bilbo support on
// 2025-06-01 23:19 <3ThomasBorregaardSorensen!!
#pragma once

#include "face.h"
#include <gdiplus.h>


namespace draw2d_gpu
{


   class face_gdiplus :
      virtual public ::draw2d_gpu::face
   {
   public:

      //bool m_bFace;
      
      Gdiplus::FontFamily *m_pfamily;
      Gdiplus::Font *m_pfont;



      face_gdiplus();
      ~face_gdiplus() override;

      void create_character(::draw2d_gpu::character& ch,const ::scoped_string& scopedstr);
   };


} // namespace draw2d_gpu

