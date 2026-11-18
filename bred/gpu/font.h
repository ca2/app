// Created by camilo on 2026-10-25 00:36 <3ThomasBorregaardSørensen!! Mummi!! bilbo!!
#pragma once


#include "acme/_operating_system.h"


#include "aura/graphics/write_text/font.h"

namespace gpu
{


   class CLASS_DECL_BRED font :
      virtual public ::write_text::font
   {
   public:


      ::pointer < ::typeface::face > m_pface;

     
      font();
      ~font() override;


      void construct(const ::write_text::font & pfontParam);

      
      // void dump(dump_context & dumpcontext) const override;


      void update(::draw2d::graphics * pdraw2dgraphics) override;
      void destroy() override;


   };


} // namespace draw2d_opengl



