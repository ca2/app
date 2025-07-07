// From opengl/draw2d by camilo on 2025-06-02 03:22 <3ThomasBorregaardSørensen!!
#pragma once


#include "acme/platform/auto_pointer.h"
#include "aura/graphics/draw2d/draw2d.h"
#include "bred/typeface/face.h"


namespace gpu
{


   class CLASS_DECL_BRED draw2d :
      virtual public ::draw2d::draw2d
   {
   public:


      ::string_map <::int_map<::pointer <::typeface::face>>> m_mapFaceSize;


      draw2d();
      ~draw2d() override;


      void initialize(::particle* pparticle) override;

      virtual ::typeface::face* _get_face(::write_text::font* pfont);

      //void on_create_window(::windowing::window* pwindow) override;
    

   };


} // namespace sgpu



