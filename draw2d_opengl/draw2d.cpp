#include "framework.h"
#include "_opengl.h"
#include "draw2d.h"
#include "acme/exception/resource.h"
#include "acme/primitive/primitive/memory.h"


//CLASS_DECL_DRAW2D_OPENGL void initialize_opengl();
//CLASS_DECL_DRAW2D_OPENGL void terminate_opengl();


namespace draw2d_opengl
{


   //draw2d::private_font::private_font()
   //{


   //}


   //draw2d::private_font::~private_font()
   //{



   //}


   draw2d::draw2d()
   {

      m_atomClass = NULL;
      m_bGlewInitialized = false;

   }


   draw2d::~draw2d()
   {

      //m_mapPrivateFont.clear();

      //terminate_opengl();

   }


   void draw2d::initialize(::particle * pparticle)
   {

      //auto estatus = 

      ::draw2d::draw2d::initialize(pparticle);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //estatus = 


      opengl_init();


      //initialize_opengl();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   void draw2d::defer_initialize_glew()
   {

      if (m_bGlewInitialized)
      {

         return;

      }



      if(!gladLoadGL())
      {
         // Problem: glewInit failed, something is seriously wrong.
         information("gladLoadGL failed");
         //return false;
         throw resource_exception();
      }

      m_bGlewInitialized = true;


   }


   string draw2d::write_text_get_default_implementation_name()
   {

      return "win32";

   }


   //draw2d::private_font * draw2d::get_file_private_font(::acme::context * pcontext, const ::file::path & path)
   //{

   //   auto & pfont = m_mapPrivateFont[path];

   //   if (::is_set(pfont))
   //   {

   //      return pfont;

   //   }

   //   __construct_new(pfont);

   //   pfont->m_pcollection = new Gdiplus::PrivateFontCollection();

   //   auto pmemory = acmesystem()->m_paurasystem->draw2d()->write_text()->get_file_memory(pcontext, path);

   //   if (pmemory->has_data())
   //   {

   //      pfont->m_pcollection->AddMemoryFont(pmemory->data(), (INT)pmemory->size());

   //      auto & fontCollection = *pfont->m_pcollection;

   //      auto iFamilyCount = fontCollection.GetFamilyCount();

   //      pfont->m_familya.set_size(iFamilyCount);

   //      fontCollection.GetFamilies(iFamilyCount, pfont->m_familya.data(), &pfont->m_iFamilyCount);

   //      pfont->m_familya.set_size(iFamilyCount);

   //      for (int iFamily = 0; iFamily < iFamilyCount; iFamily++)
   //      {

   //         if (pfont->m_familya[iFamily].GetLastStatus() != Gdiplus::Ok)
   //         {

   //            warning("font family nok");

   //         }

   //      }

   //   }

   //   return pfont;

   //}


   LRESULT CALLBACK opengl_window_proc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
   {
      return DefWindowProc(hwnd, message, wparam, lparam);
   }


   int  draw2d::opengl_init()
   {

      if (m_atomClass)
      {

         return true;

      }

      WNDCLASSW wc;
      ZeroMemory(&wc, sizeof(wc));
      wc.style = CS_OWNDC;
      wc.lpfnWndProc = opengl_window_proc;
      wc.hInstance = (HINSTANCE) acmesystem()->m_psubsystem->m_hinstanceThis;
      wc.lpszClassName = L"draw2d_opengl_offscreen_buffer_window";
      m_atomClass = RegisterClassW(&wc);

      if (!m_atomClass)
      {

         return false;

      }
      return true;

   }


} // namespace draw2d_opengl



