#include "framework.h"
#include "desktop_file.h"
#include "acme/filesystem/filesystem/acme_directory.h"
#include "acme/filesystem/filesystem/acme_file.h"
#include "acme/platform/system.h"
#include "apex/filesystem/filesystem/dir_context.h"
#include "apex/filesystem/filesystem/file_context.h"
#include "apex/platform/application.h"
#include "apex/platform/context.h"
//#include "apex/operating_system.h"
#include <sys/stat.h>


namespace freedesktop
{


   desktop_file::desktop_file()
   {

   }


   desktop_file::~desktop_file()
   {


   }


   //AudioVideo   papp for presenting, creating, or processing multimedia (audio/video)
   //Audio        An audio application                                                          Desktop entry must include AudioVideo as well
   //Video        A video application	                                                         Desktop entry must include AudioVideo as well
   //Development  An application for development
   //Education    Educational software
   //Game         A game
   //Graphics     papp for viewing, creating, or processing graphics
   //Network      Network application such as a web browser
   //Office       An office type application
   //Science      Scientific software
   //Settings     Settings applications                                                         Entries may appear in a separate menu or as part of a "Control Center"
   //::auraacmesystem()       ::auraacmesystem() application, "::auraacmesystem() Tools" such as say a log viewer or network monitor
   //Utility      Small utility application, "Accessories"

   string_array desktop_file::registered_categories()
   {

      string_array stra;

      stra.add("AudioVideo");
      stra.add("Audio");
      stra.add("Video");
      stra.add("Development");
      stra.add("Education");
      stra.add("Game");
      stra.add("Graphics");
      stra.add("Network");
      stra.add("Office");
      stra.add("Science");
      stra.add("Settings");
      stra.add("System");
      stra.add("Utility");

      return stra;

   }


   string desktop_file::proper_category(string str)
   {

      if(str.case_insensitive_order("Multimedia") == 0)
      {

         return "AudioVideo";

      }
      else if(str.case_insensitive_order("Accessory") == 0)
      {

         return "Utility";

      }
      else if(str.case_insensitive_order("Accessories") == 0)
      {

      return "Utility";

      }
      else if(str.case_insensitive_order("Utility") == 0)
      {

         return "Utility";

      }
      else if(str.case_insensitive_order("Utilities") == 0)
      {

         return "Utility";

      }
      else
      {

         string_array stra = registered_categories();

         auto iFind = stra.find_first_ci(str);

         if(found(iFind))
         {

            return stra[iFind];

         }

      }

      return "";

   }


   string_array desktop_file::proper_category(string_array straCategoryParam)
   {

      string_array straCategory;

      for(auto strCategoryParam : straCategoryParam)
      {

         string strCategory = proper_category(strCategoryParam);

         if(strCategory.has_char())
         {

            straCategory.add(strCategory);

            if(strCategory == "Audio" || strCategory == "Video")
            {

               straCategory.add("AudioVideo");

            }

         }
         else
         {

            string strMessage;

            strMessage.format("Category \"%s\"has not been found", strCategoryParam.c_str());

            TRACE(strMessage);

         }

      }

      straCategory.erase_duplicates_ci();

      return straCategory;

   }


   string desktop_file::get_wm_class()
   {

      string strWmClass;

      strWmClass = m_strAppId;

      strWmClass.find_replace("/", ".");

      return strWmClass;

   }


   ::file::path desktop_file::get_board_path()
   {

      ::file::path path;

      auto psystem = acmesystem();

      auto pacmedirectory = psystem->m_pacmedirectory;

      path = pacmedirectory->localconfig() / "desk/monitor-0/2desk";

      auto papp = get_app();

      string strPrgName = get_wm_class();

      path /= (strPrgName + ".desktop");

      return path;

   }


   void desktop_file::set_file_path(const ::file::path & path)
   {

      m_path = path;

   }


   ::file::path desktop_file::get_file_path()
   {

      return m_path;

   }


   void desktop_file::set_app_id(const ::string & strAppId)
   {

      m_strAppId = strAppId;

   }


   string desktop_file::get_app_id()
   {

      return m_strAppId;

   }


   void desktop_file::create_default()
   {

      string_array & straLine = m_straLine;

      string strWMClass = get_wm_class();

      straLine.add("[Desktop Entry]");
      straLine.add("Version=1.0");
      straLine.add("Type=Application");
      straLine.add("Name=");
      straLine.add("GenericName=");
      straLine.add("Comment=");
      straLine.add("Exec=");
      straLine.add("Icon=");
      straLine.add("Terminal=false");
      straLine.add("X-MultipleArgs=false");
      straLine.add("Categories=Network;");
      straLine.add("MimeType=");

   }


   void desktop_file::create()
   {

      auto pcontext = m_pcontext;

      ::file::path path = dir()->matter("app.desktop");

      m_straLine = pcontext->m_papexcontext->file()->lines(path);

      if(m_straLine.is_empty())
      {

         create_default();

      }

      auto papp = get_app()->m_papexapplication;

      string strTitle = papp->title();

      string_array straCategories = proper_category(papp->get_categories());

      string strWMClass = papp->get_wm_class();

      ::file::path pathUserBin;

      string strName;

      strName = papp->m_strAppId;

      strName.find_replace("-", "_");

      strName.find_replace("/", "_");

      strName.find_replace(".", "_");

      //pathLaunch = pacmedirectory->home() / ".config/ca2/bin" / (strName + ".sh");

      auto psystem = acmesystem();

      auto pacmedirectory = psystem->m_pacmedirectory;

      pathUserBin = pacmedirectory->home() / "bin" / strName;

      //::file::path pathIcon = dir()->matter("main/icon-256.png");

      ::file::path pathModule = acmedirectory()->module();

      ::file::path pathModuleIcon256 = pathModule / (strName + "-256.png");

      ::output_debug_string("\npathModuleIcon256=" + pathModuleIcon256 + "\n");

      ::fflush(stdout);

      if(!acmefile()->exists(pathModuleIcon256))
      {

         auto pfileMainIcon256 = pcontext->m_papexcontext->file()->get_file("matter://main/icon-256.png",
                                                                           ::file::e_open_read);

         bool bNok = pfileMainIcon256.nok();

         if(bNok)
         {

            ::output_debug_string("matter icon nok");

         }

         papp->file()->copy(pathModuleIcon256, pfileMainIcon256);

      }

      string_array & straLine = m_straLine;

      string strScript;

      //string strScript = "#!/bin/bash\n";

      /*strScript += "\n";

      strScript += "run_app()\n";

      strScript += "{\n";

      strScript += "\n";

      strScript += "   cd " + string(pcontext->m_papexcontext->file()->module().folder()) + "/\n";

      strScript += "\n";

      strScript += "   export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.:" + string(pcontext->m_papexcontext->file()->module().folder()) + "\n";

      */

      //strScript += "\n";

      //strScript += "   /bin/bash -i -c \"" + string(pcontext->m_papexcontext->file()->module()) + "\" ${@:1:99}\n";

      /*

      strScript += "\n";

      strScript += "}\n";

      strScript += "\n";

      strScript += "run_app ${@:1:99}\n";

      strScript += "\n"; */

      //acmefile()->put_contents(pathLaunch, strScript);

      strScript = "#!/bin/bash\n";

      strScript += "\n";

//      strScript += "export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.:" + string(pcontext->m_papexcontext->file()->module().folder()) + "\n";
//
//      strScript += "\n";
//

      //strScript += "/bin/bash -l -c " + string(pcontext->m_papexcontext->file()->module()) + " ${@:1:99}\n";

      strScript += string(pcontext->m_papexcontext->file()->module()) + " ${@:1:99}\n";

      strScript += "\n";

      acmefile()->put_contents(pathUserBin, strScript);

      //chmod(pathLaunch, 0755);
      chmod(pathUserBin, 0600);

      string strModule = pcontext->m_papexcontext->file()->module();

      straLine._007SetLine("[Desktop Entry]", "GenericName", strTitle);
      straLine._007SetLine("[Desktop Entry]", "Name", strTitle);
      straLine._007SetLine("[Desktop Entry]", "Comment", strTitle + " Comment");
      //straLine._007SetLine("[Desktop Entry]", "Exec", pathLaunch + " %U");
      //straLine._007SetLine("[Desktop Entry]", "Exec", strName + " %U");
      //straLine._007SetLine("[Desktop Entry]", "Exec", string(pcontext->m_papexcontext->file()->module()) + " %U");
      straLine._007SetLine("[Desktop Entry]", "Exec", strModule + " %U");
      //straLine._007SetLine("Path", string(pcontext->m_papexcontext->file()->module().folder()));

      if(pcontext->m_papexcontext->file()->exists(pathModuleIcon256))
      {

         straLine._007SetLine("[Desktop Entry]", "Icon", pathModuleIcon256);

      }

      if(straCategories.has_elements() && straCategories.implode("").has_char())
      {

         straLine._007SetLine("[Desktop Entry]", "Categories", straCategories.implode(";") + ";");

      }


      straLine._007SetLine("[Desktop Entry]", "StartupNotify", "true");
      straLine._007SetLine("[Desktop Entry]", "StartupWMClass", strWMClass);

      // straLine._007SetLine("[Desktop Entry]", "Actions", "transparent-frame;");

      // for(index i = 0; i < papp->applicationmenu().get_count(); i++)
      // {

      //    auto & item = papp->applicationmenu()[i];

      //    if()


      // }

      // straLine._007SetLine("[Desktop Action transparent-frame]", "Name", "Transparent Frame");
      // //straLine._007SetLine("[Desktop Action transparent-frame]", "StartupWMClass", "com." + strPrgName);
      // //straLine._007SetLine("[Desktop Action transparent-frame]", "Exec", pathLaunch + " : post transparent_frame");
      // //straLine._007SetLine("[Desktop Action transparent-frame]", "Exec", strName + " : post transparent_frame");
      // //straLine._007SetLine("[Desktop Action transparent-frame]", "Exec", string(pcontext->m_papexcontext->file()->module()) + " : post transparent_frame");
      // //straLine._007SetLine("[Desktop Action transparent-frame]", "Exec", strName + " : post transparent_frame");
      // straLine._007SetLine("[Desktop Action transparent-frame]", "Exec", strModule + " : post transparent_frame");

      if(straLine.last().has_char())
      {

         straLine.add("");

      }

   }


   void desktop_file::write()
   {

      ::file::path path = get_file_path();

      auto pcontext = m_pcontext;

      pcontext->m_papexcontext->file()->put_lines(path, m_straLine);

      chmod(path, S_IRUSR | S_IWUSR | S_IXUSR);

      path = get_board_path();

      pcontext->m_papexcontext->file()->put_lines(path, m_straLine);

      chmod(path, S_IRUSR | S_IWUSR | S_IXUSR);

   }


//   bool desktop_file::bamf_set_icon(oswindow oswindow)
//   {
//
//      ::file::path path = get_file_path();
//
//      output_debug_string("\nlinux::interaction_impl::set_window_text");
//
//      fflush(stdout);
//
//      auto puser = user();
//
//      auto pwindowing = puser->windowing();
//
//      if(!pwindowing)
//      {
//
//         return false;
//
//      }
//
//
//      if(!pwindowing->set_window_icon(oswindow, path))
//      {
//
//         return false;
//
//      }
//
//      return true;
//
//   }


   void desktop_file::open(const ::file::path & path)
   {

      m_straLine = file()->lines(path);

   }


   ::string desktop_file::get_SessionKeyPayload(const ::scoped_string & scopedstrSession, const ::scoped_string & scopedstrKey)
   {

      auto iStart = m_straLine._007FindSection(scopedstrSession);

      if(iStart < 0)
      {

         iStart = 0;

      }

      ::string strPayload;

      m_straLine._007GetLine(strPayload, scopedstrKey, iStart);

      return strPayload;


   }


   ::string desktop_file::get_Target()
   {

      return get_SessionKeyPayload("[Desktop Entry]", "Exec");

   }


   ::string desktop_file::get_Icon()
   {

      return get_SessionKeyPayload("[Desktop Entry]", "Icon");

   }



} // namespace freedesktop



