#include "platform.h"
#include "draw2d.h"
#include "acme/exception/resource.h"
#include "acme/platform/application.h"
#include "acme/prototype/prototype/memory.h"

//::i32 g_iDpiY = -1;
//::i32 get_y_dpi()
//{
//   if (g_iDpiY < 0)
//   {
//      HDC hdc = ::GetDC(NULL);
//      g_iDpiY = GetDeviceCaps(hdc, LOGPIXELSY); // Usually Y axis DPI is used for font sizes
//      if (g_iDpiY < 0)
//      {
//
//         g_iDpiY = 96;
//
//      }
//
//      ReleaseDC(NULL, hdc);
//
//   }
//   return g_iDpiY;
//}
//


//CLASS_DECL_DRAW2D_GPU void initialize_opengl();
//CLASS_DECL_DRAW2D_GPU void terminate_opengl();


namespace draw2d_gpu
{


   //draw2d::private_font::private_font()
   //{


   //}


   //draw2d::private_font::~private_font()
   //{



   //}


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

   //::draw2d_gpu::face* draw2d::get_face(::write_text::font * pwritetextfont)
   //{

   //   ::i32 iPixelSize = 0;

   //   if (pwritetextfont->m_fontsize.eunit() == e_unit_point)
   //   {
   //      iPixelSize = points_to_pixels(pwritetextfont->m_fontsize.as_i32());
   //   }
   //   else
   //   {
   //      iPixelSize = pwritetextfont->m_fontsize.as_i32();
   //   }

   //   ::string strFontFamilyName = pwritetextfont->m_pfontfamily->family_name(this);

   //   auto& pface = m_mapFaceSize[strFontFamilyName][iPixelSize];

   //   if (!pface)
   //   {

   //      constructø(pface);

   //      pface->m_strFontName = strFontFamilyName;

   //      pface->m_iPixelSize = iPixelSize;

   //   }

   //   return pface;

   //}


   void draw2d::initialize(::particle * pparticle)
   {

      //auto estatus = 

      ::gpu::draw2d::initialize(pparticle);


      //application()->create_gpu();
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




   //void draw2d::on_before_create_window(::windowing::window* pwindow)
   //{



   //}



   //void draw2d::on_create_window(::windowing::window* pwindow)
   //{



   //}


   bool draw2d::graphics_context_does_full_redraw()
   {

      return true;

   }


   //void draw2d::defer_initialize_glad()
   //{

   //   if (m_bGladInitialized)
   //   {

   //      return;

   //   }



   //   if(!gladLoadGL())
   //   {
   //      // Problem: glewInit failed, something is seriously wrong.
   //      informationf("gladLoadGL failed");
   //      //return false;
   //      throw resource_exception();
   //   }

   //   m_bGladInitialized = true;


   //}


   string draw2d::write_text_get_default_implementation_name()
   {

      return "win32";

   }


   //draw2d::private_font * draw2d::get_file_private_font(::platform::context * pcontext, const ::file::path & path)
   //{

   //   auto & pwritetextfont = m_mapPrivateFont[path];

   //   if (::is_set(pwritetextfont))
   //   {

   //      return pwritetextfont;

   //   }

   //   construct_newø(pwritetextfont);

   //   pwritetextfont->m_pcollection = ___new Gdiplus::PrivateFontCollection();

   //   auto pmemory = system()->draw2d()->write_text()->get_file_memory(pcontext, path);

   //   if (pmemory->has_data())
   //   {

   //      pwritetextfont->m_pcollection->AddMemoryFont(pmemory->data(), (INT)pmemory->size());

   //      auto & fontCollection = *pwritetextfont->m_pcollection;

   //      auto iFamilyCount = fontCollection.GetFamilyCount();

   //      pwritetextfont->m_familya.set_size(iFamilyCount);

   //      fontCollection.GetFamilies(iFamilyCount, pwritetextfont->m_familya.data(), &pwritetextfont->m_iFamilyCount);

   //      pwritetextfont->m_familya.set_size(iFamilyCount);

   //      for (::i32 iFamily = 0; iFamily < iFamilyCount; iFamily++)
   //      {

   //         if (pwritetextfont->m_familya[iFamily].GetLastStatus() != Gdiplus::Ok)
   //         {

   //            warningf("font family nok");

   //         }

   //      }

   //   }

   //   return pwritetextfont;

   //}


   //LRESULT CALLBACK opengl_window_proc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
   //{
   //   return DefWindowProc(hwnd, message, wparam, lparam);
   //}


   //::i32  draw2d::opengl_init()
   //{

   //   //constructø(m_popenglcontext);

   //   //if (m_atomClass)
   //   //{

   //   //   return true;

   //   //}

   //   //WNDCLASSW wc;
   //   //ZeroMemory(&wc, sizeof(wc));
   //   //wc.style = CS_OWNDC;
   //   //wc.lpfnWndProc = opengl_window_proc;
   //   //wc.hInstance = (HINSTANCE) system()->m_hinstanceThis;
   //   //wc.lpszClassName = L"draw2d_gpu_offscreen_buffer_window";
   //   //m_atomClass = RegisterClassW(&wc);

   //   //if (!m_atomClass)
   //   //{

   //   //   return false;

   //   //}

   //   //defer_initialize_glad();

   //   return true;

   //}


   //void draw2d::adjust_composited_window_styles(::u32& nExStyle, ::u32& nStyle)
   //{

   //   nExStyle &= ~WS_EX_LAYERED;

   //}



} // namespace draw2d_gpu



