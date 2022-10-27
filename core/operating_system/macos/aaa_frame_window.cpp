#include "framework.h"
//#include "core/user/simple/_.h"


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

      auto picon = papp->load_icon("matter://icon.ico");

//      HICON hicon = load_icon(get_app(), straMatter, "icon.ico", 16, 16);

      set_icon(picon, true);

      set_icon(picon, false);

      if (m_bWindowFrame)
      {

         //hicon = load_icon(get_app(), straMatter, "icon.ico", 24, 24);

         __construct(m_picon, papp->load_icon("matter://icon.ico"));

      }

   }

}

