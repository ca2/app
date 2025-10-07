// From gdiplus/draw2d by camilo on 2023-04-27 15:19 <3ThomasBorregaardSorensen!!
#pragma once


#include "bred/gpu/draw2d.h"
#include "acme/platform/auto_pointer.h"
#include "aura/graphics/draw2d/draw2d.h"
#include "gpu_opengl/context.h"
#include "face.h"


namespace typeface_freetype
{


   class CLASS_DECL_TYPEFACE_FREETYPE draw2d :
      virtual public ::draw2d_gpu::draw2d
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
      //string_map_base < ::pointer<private_font >>m_mapPrivateFont;

      //bool        m_bGladInitialized;

      //::pointer<::opengl::context>          m_popenglcontext;

      ::string_map_base <::int_map<::pointer <face>>> m_mapFaceSize;
      draw2d();
      ~draw2d() override;


      void initialize(::particle * pparticle) override;

      //face* get_face(::write_text::font * pfont);

      bool graphics_context_supports_single_buffer_mode() override;
      bool graphics_context_does_full_redraw() override;

      void on_before_create_window(::windowing::window* pwindow) override;
      void on_create_window(::windowing::window * pwindow) override;
      //void defer_initialize_glad();


      virtual string write_text_get_default_implementation_name() override;


      //virtual private_font * get_file_private_font(::platform::context * pcontext, const ::file::path & path);
      virtual int  opengl_init();


      void adjust_composited_window_styles(unsigned int& nExStyle, unsigned int& nStyle) override;


   };


} // namespace typeface_freetype



