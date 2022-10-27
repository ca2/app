#pragma once


#include "aura/graphics/draw2d/draw2d.h"


namespace draw2d_cairo
{


   class CLASS_DECL_DRAW2D_CAIRO draw2d  :
      virtual public ::draw2d::draw2d
   {
   public:


      class private_font :
         virtual public ::element
      {
      public:

         FT_Face  m_ftface;
         cairo_font_face_t  * m_pfontface;

      };

      string_map < ::pointer<private_font >>m_mapPrivateFont;

      draw2d();
      ~draw2d() override;


      virtual void initialize(::particle * pparticle) override;

      virtual void process_init() override;

      virtual void init() override;
      virtual void init1() override;

      virtual void term() override;

      virtual void destroy() override;


      cairo_font_face_t * private_ftface_from_memory(const ::block & block, const ::string & strName);
      cairo_font_face_t * private_ftface_from_file(::acme::context * pcontext, const ::payload & payloadFile);


   };


} // namespace draw2d_cairo


