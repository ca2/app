#include "framework.h"
#include "base/user/simple/_simple.h"


void simple_frame_window::defer_set_icon()
{

#if defined(CUBE)

   return;

#endif

   if (get_parent() == nullptr
         && m_bWindowFrame
         && m_picon.is_null())
   {

      ::file::path strMatter = get_window_default_matter();
      //http://www.cplusplus.com/forum/general/28470/
      //blackcoder41 (1426)  Sep 12, 2010 at 2:43pm
      //hIconSm = (HICON)LoadImage(nullptr, "menu_two.ico", IMAGE_ICON, 16, 16, LR_LOADFROMFILE);

      string_array straMatter;

      if (strMatter.name(0) == "system")
      {

         straMatter.add("main");

         straMatter.add(strMatter);

      }
      else
      {

         straMatter.add(strMatter);

         straMatter.add("main");

      }

//      auto p
//
//      defer_set_icon();

      auto psession = Session;

      auto puser = psession->user();

      auto pwindowing = puser->windowing();

      //auto& image = app.image();

      auto picon = pwindowing->load_icon("matter://icon.ico");

//      HICON hicon = load_icon(get_context_application(), straMatter, "icon.ico", 16, 16);

      set_icon(picon);

      if (m_bWindowFrame)
      {

         //hicon = load_icon(get_context_application(), straMatter, "icon.ico", 24, 24);

         //__compose(m_picon, Application.load_icon("matter://icon.ico"));

         //__compose(m_picon, m_picon->);

      }

   }

}

