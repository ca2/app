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

         øconstruct(pface);

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


   //bool draw2d::graphics_context_supports_single_buffer_mode()
   //{

   //   return true;

   //}


   //bool draw2d::graphics_context_does_full_redraw()
   //{

   //   return true;

   //}


   ////void draw2d::defer_initialize_glad()
   ////{

   ////   if (m_bGladInitialized)
   ////   {

   ////      return;

   ////   }



   ////   if(!gladLoadGL())
   ////   {
   ////      // Problem: glewInit failed, something is seriously wrong.
   ////      informationf("gladLoadGL failed");
   ////      //return false;
   ////      throw resource_exception();
   ////   }

   ////   m_bGladInitialized = true;


   ////}


   //string draw2d::write_text_get_default_implementation_name()
   //{

   //   return "win32";

   //}


   ////draw2d::private_font * draw2d::get_file_private_font(::platform::context * pcontext, const ::file::path & path)
   ////{

   ////   auto & pfont = m_mapPrivateFont[path];

   ////   if (::is_set(pfont))
   ////   {

   ////      return pfont;

   ////   }

   ////   øconstruct_new(pfont);

   ////   pfont->m_pcollection = ___new Gdiplus::PrivateFontCollection();

   ////   auto pmemory = system()->draw2d()->write_text()->get_file_memory(pcontext, path);

   ////   if (pmemory->has_data())
   ////   {

   ////      pfont->m_pcollection->AddMemoryFont(pmemory->data(), (INT)pmemory->size());

   ////      auto & fontCollection = *pfont->m_pcollection;

   ////      auto iFamilyCount = fontCollection.GetFamilyCount();

   ////      pfont->m_familya.set_size(iFamilyCount);

   ////      fontCollection.GetFamilies(iFamilyCount, pfont->m_familya.data(), &pfont->m_iFamilyCount);

   ////      pfont->m_familya.set_size(iFamilyCount);

   ////      for (int iFamily = 0; iFamily < iFamilyCount; iFamily++)
   ////      {

   ////         if (pfont->m_familya[iFamily].GetLastStatus() != Gdiplus::Ok)
   ////         {

   ////            warningf("font family nok");

   ////         }

   ////      }

   ////   }

   ////   return pfont;

   ////}


   //LRESULT CALLBACK opengl_window_proc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
   //{
   //   return DefWindowProc(hwnd, message, wparam, lparam);
   //}


   //int  draw2d::opengl_init()
   //{

   //   //øconstruct(m_popenglcontext);

   //   //if (m_atomClass)
   //   //{

   //   //   return true;

   //   //}

   //   //WNDCLASSW wc;
   //   //ZeroMemory(&wc, sizeof(wc));
   //   //wc.style = CS_OWNDC;
   //   //wc.lpfnWndProc = opengl_window_proc;
   //   //wc.hInstance = (HINSTANCE) system()->m_hinstanceThis;
   //   //wc.lpszClassName = L"draw2d_opengl_offscreen_buffer_window";
   //   //m_atomClass = RegisterClassW(&wc);

   //   //if (!m_atomClass)
   //   //{

   //   //   return false;

   //   //}

   //   //defer_initialize_glad();

   //   return true;

   //}


} // namespace draw2d_gpu



