// From opengl/draw2d by camilo on 2025-06-02 03:26 <3ThomasBorregaardSørensen!!
#include "framework.h"
//#include "_opengl.h"
#include "draw2d.h"
#include "acme/exception/resource.h"
#include "acme/platform/application.h"
#include "acme/platform/system.h"
#include "acme/prototype/prototype/memory.h"
#include "acme/windowing/windowing.h"


namespace draw2d_gpu
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


   face* draw2d::get_face(::write_text::font* pfont)
   {

      int iPixelSize = 0;

      if (pfont->m_fontsize.eunit() == e_unit_point)
      {
         iPixelSize = (int) system()->acme_windowing()->default_screen_points_to_pixels(pfont->m_fontsize.as_float());
      }
      else
      {
         iPixelSize = pfont->m_fontsize.as_int();
      }

      ::string strFontFamilyName = pfont->m_pfontfamily->family_name(this);

      auto& pface = m_mapFaceSize[strFontFamilyName][iPixelSize];

      if (!pface)
      {

         __øconstruct(pface);

         pface->m_strFontName = strFontFamilyName;

         pface->m_iPixelSize = iPixelSize;

      }

      return pface;

   }


   void draw2d::initialize(::particle* pparticle)
   {

      //auto estatus = 

      ::draw2d::draw2d::initialize(pparticle);


      application()->create_gpu();
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


} // namespace draw2d_gpu



