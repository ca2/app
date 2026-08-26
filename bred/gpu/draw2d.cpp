// From opengl/draw2d by camilo on 2025-06-02 03:26 <3ThomasBorregaardSørensen!!
#include "platform.h"
#include "bred_approach.h"
#include "device.h"
#include "draw2d.h"
#include "swap_chain.h"
#include "texture.h"
#include "acme/exception/resource.h"
#include "acme/platform/application.h"
#include "acme/platform/system.h"
#include "acme/prototype/prototype/memory.h"
#include "acme/windowing/windowing.h"
#include "aura/graphics/image/image.h"
#include "bred/platform/system.h"
#include "bred/typeface/character.h"
#include "bred/typeface/allocator.h"


namespace gpu
{


   draw2d::draw2d()
   {

      //m_atomClass = NULL;
      //m_bGladInitialized = false;

   }


   draw2d::~draw2d()
   {

      //m_mapPrivateFont.clear();

      //terminate_opengl();

   }


   ::typeface::face* draw2d::_get_face(::write_text::font* pfont)
   {

      ::i32 iPixelSize = 0;

      if (pfont->m_fontsize.eunit() == e_unit_point)
      {
         iPixelSize = (::i32) system()->acme_windowing()->default_screen_points_to_pixels(pfont->m_fontsize.as_f32());
      }
      else
      {
         iPixelSize = pfont->m_fontsize.as_i32();
      }

      ::i32 iFontWeight = pfont->m_fontweight.as_i32();

      ::string strFontFamilyName = pfont->m_pfontfamily->family_name(this);

      auto& pface = m_mapFaceSizeWeight[strFontFamilyName][iPixelSize][iFontWeight];

      if (!pface)
      {

         ::cast < ::bred::system > psystem = ::system();

         pface = psystem->typeface_allocator()->create_face("");

         ///pface = ::system()->create_typeface_face();

         pface->m_strFontName = strFontFamilyName;

         pface->m_iPixelSize = iPixelSize;

         pface->m_iFontWeight = iFontWeight;

      }

      return pface;

   }


   void draw2d::initialize(::particle* pparticle)
   {

      //auto estatus = 

      ::draw2d::draw2d::initialize(pparticle);


      //application()->create_gpu_approach();
      //if (!estatus)
      //{

      //   return estatus;

      //}

      //estatus = 


      //opengl_init();


      //initialize_opengl();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   //void draw2d::on_create_window(::windowing::window* pwindow)
   //{

   //   //if (m_papplication->m_gpu.m_bUseSwapChainWindow)
   //   //{

   //   //   auto pgpuapproach = m_papplication->get_gpu_approach();

   //   //   auto pgpudevice = pgpuapproach->get_gpu_device();

   //   //   auto pswapchain = pgpudevice->get_swap_chain();

   //   //   if (!pswapchain->m_bWindowInitialized)
   //   //   {

   //   //      pswapchain->initialize_swap_chain_window(pgpudevice, pwindow);

   //   //   }


   //   //}

   //}

   ::image::image_pointer draw2d::image_from_gpu_texture(::gpu::texture * pgputexture, ::draw2d::graphics * pdraw2dgraphics)
   {

      defer_constructø(pgputexture->m_pimageGpuTexture);

      pgputexture->m_pimageGpuTexture->update_as_backed_by_gpu_texture(pgputexture->m_textureattributes.m_sizeRaw, pgputexture, pdraw2dgraphics);

      return pgputexture->m_pimageGpuTexture;

   }




} // namespace gpu



