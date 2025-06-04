// From opengl/draw2d by camilo on 2025-06-02 03:22 <3ThomasBorregaardSørensen!!
#pragma once


#include "acme/platform/auto_pointer.h"
#include "aura/graphics/draw2d/draw2d.h"
#include "face.h"


namespace draw2d_gpu
{


   class CLASS_DECL_AURA draw2d :
      virtual public ::draw2d::draw2d
   {
   public:


      ::string_map <::int_map<::pointer <face>>> m_mapFaceSize;


      draw2d();
      ~draw2d() override;


      void initialize(::particle* pparticle) override;

      face* get_face(::write_text::font* pfont);


    

   };


} // namespace draw2d_gpu



