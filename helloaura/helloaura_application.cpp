#include "framework.h"
#include <commctrl.h >


INT_PTR CALLBACK DialogProc(HWND h, UINT u, WPARAM, LPARAM)
{

   if (u == WM_CLOSE)
   {
      return DestroyWindow(h);
   }
   else if(u == WM_INITDIALOG)
   {
      return 1;
   }
   else if(u==WM_PAINT)
   {
      //return 1;
   }

   return 0;
}


namespace helloaura
{


   application::application(::object * pobject) :
      ::object(this),
      ::thread(this),
      ::aura::application(pobject),
      ::axis::application(pobject),
      ::base::application(pobject),
      ::aura::application(pobject),
      ::sphere::application(pobject) //:
//      m_mutexAiFont(this)
   {

      m_strAppName = "app/helloaura";
      m_strLibraryName = "app/helloaura";
      m_strBaseSupportId = "ca2_flag";
      m_bLicense = false;

      m_etype = type_normal;

      m_strHelloAuraDefault = "Hello Aura!!";
      m_strAlternateHelloAuraDefault = "Hello Aura!!";

      m_strHelloAura = m_strHelloAuraDefault;
      m_strAlternateHelloAura = m_strAlternateHelloAuraDefault;

//      m_iErrorAiFont = -1;

      //    m_bLoadAiFont = false;

      //  m_faceAi = nullptr; // FT_Face m_faceAi;

//      m_bAuraChat = true;



   }


   application::~application()
   {
   }


   ::estatus application::init_instance()
   {

      ::aura::session * pcoression = get_context_application()->m_psession;

      if (!::aura::application::init_instance())
      {

         return false;

      }

      m_dFps = 60;



      string str = m_varTopicQuery["helloaura"];

      if (str.has_char())
      {

         m_strHelloAura = str;

      }

//      set_local_data_key_modifier();



      return true;

   }


   i32 application::exit_application()
   {

      return ::aura::application::exit_application();

   }


   void application::on_request(::create * pcreate)
   {

#if 0

#ifdef _DEBUG

      output_debug_string("_DEBUG build? (basis)");

      ASSERT(FALSE);

#else

      output_debug_string("RELEASE build? (stage)");

      ASSERT(FALSE);

#endif

#endif


//      m_bAuraChat = !m_varTopicQuery["no_hello_edit"].is_set();

      output_debug_string("\nfinished helloaura::on_request");

      //property_set set;

      //set["raw_http"] = true;
      //set["disable_common_name_cert_check"] = true;

      //string str = Context.http().get("https://ca2.cc/", set);

      //Context.file().put_contents("C:/archive/hhh.html", str);

      //fork([&]()
      //{

      //   HWND hDlg;
      //   hDlg = CreateDialogParam(System.m_hinstance, MAKEINTRESOURCE(IDD_DIALOG1), 0, DialogProc, 0);
      //   //ShowWindow(hDlg, display_normal);

      //   rect r;
      //   get_window_rect(get_desktop_window(), rect);
      //   rect r2;
      //   get_window_rect(hDlg, r2);

      //   r2.Align(align_horizontal_center, rect);

      //   r2.top = (rect.height() - r2.height()) / 3;

      //   set_window_pos(hDlg, HWND_TOP, r2.left, r2.top, 0, 0, SWP_SHOWWINDOW | SWP_NOSIZE);

      //   BOOL ret;
      //   MSG msg;
      //   while ((ret = GetMessage(&msg, 0, 0, 0)) != 0)
      //   {
      //      if (ret == -1) /* error found */
      //         return -1;

      //      if (!IsDialogMessage(hDlg, &msg))
      //      {
      //         TranslateMessage(&msg); /* translate virtual-key messages */
      //         DispatchMessage(&msg); /* send it to dialog procedure */
      //      }
      //   }
      //});

      m_prender = new render(this);

      ::helloaura::main_window(m_prender);

      System.set_finish();

   }





   i64 application::add_ref()
   {

      return ::object::add_ref(OBJ_REF_DBG_ARGS);

   }

   i64 application::dec_ref()
   {

      return ::object::dec_ref(OBJ_REF_DBG_ARGS);

   }



   string application::get_helloaura()
   {

      return "Hello Aura!!";

   }

} // namespace helloaura




extern "C"
::aura::library * app_helloaura_get_new_library(::object * pobject)
{

   return new ::aura::single_application_library < ::helloaura::application > (pobject, "app/helloaura");

}




