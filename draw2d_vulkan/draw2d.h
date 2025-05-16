// From gdiplus/draw2d by camilo on 2023-04-27 15:19 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/platform/auto_pointer.h"
#include "aura/graphics/draw2d/draw2d.h"
#include "gpu_opengl/context.h"

namespace draw2d_opengl
{


   class CLASS_DECL_DRAW2D_OPENGL draw2d :
      virtual public ::draw2d::draw2d
   {
   public:


      //class private_font :
      //   virtual public ::matter
      //{
      //public:

      //   auto_pointer < Gdiplus::PrivateFontCollection >    m_pcollection;
      //   raw_array < Gdiplus::FontFamily >                  m_familya;
      //   int                                                m_iFamilyCount;

      //   private_font();
      //   ~private_font() override;

      //};


      //ATOM m_atomClass;



      //__creatable_from_base(draw2d, ::draw2d::draw2d);
      //string_map < ::pointer<private_font >>m_mapPrivateFont;

      //bool        m_bGladInitialized;

      //::pointer<::opengl::context>          m_popenglcontext;


      draw2d();
      ~draw2d() override;


      void initialize(::particle * pparticle) override;


      bool graphics_context_supports_single_buffer_mode() override;
      bool graphics_context_does_full_redraw() override;

      void on_create_window(::windowing::window * pwindow) override;
      //void defer_initialize_glad();


      virtual string write_text_get_default_implementation_name() override;


      //virtual private_font * get_file_private_font(::platform::context * pcontext, const ::file::path & path);
      virtual int  opengl_init();

   };


} // namespace draw2d_opengl



