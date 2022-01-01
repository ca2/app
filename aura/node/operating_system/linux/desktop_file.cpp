#include "framework.h"
#include "_linux.h"
#include "_user.h"
#include "acme/filesystem/filesystem/acme_dir.h"
#include "acme/filesystem/filesystem/acme_file.h"


namespace linux
{


   desktop_file::desktop_file()
   {

   }


   desktop_file::~desktop_file()
   {


   }


   //AudioVideo   papplication for presenting, creating, or processing multimedia (audio/video)
   //Audio        An audio application                                                          Desktop entry must include AudioVideo as well
   //Video        A video application	                                                         Desktop entry must include AudioVideo as well
   //Development  An application for development
   //Education    Educational software
   //Game         A game
   //Graphics     papplication for viewing, creating, or processing graphics
   //Network      Network application such as a web browser
   //Office       An office type application
   //Science      Scientific software
   //Settings     Settings applications                                                         Entries may appear in a separate menu or as part of a "Control Center"
   //::aura::get_system()       ::aura::get_system() application, "::aura::get_system() Tools" such as say a log viewer or network monitor
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

      if(str.compare_ci("Multimedia") == 0)
      {

         return "AudioVideo";

      }
      else if(str.compare_ci("Accessory") == 0)
      {

         return "Utility";

      }
      else if(str.compare_ci("Accessories") == 0)
      {

      return "Utility";

      }
      else if(str.compare_ci("Utility") == 0)
      {

         return "Utility";

      }
      else if(str.compare_ci("Utilities") == 0)
      {

         return "Utility";

      }
      else
      {

         string_array stra = registered_categories();

         index iFind = stra.find_first_ci(str);

         if(iFind >= 0)
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


   ::file::path desktop_file::get_board_path()
   {

      ::file::path path;

      auto psystem = m_psystem;

      auto pacmedir = psystem->m_pacmedir;

      path = pacmedir->localconfig() / "desk/monitor-0/2desk";

      auto papplication = get_application();

      string strPrgName = papplication->get_wm_class();

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


   void desktop_file::create_default()
   {

      string_array & straLine = m_straLine;

      auto papplication = get_application();

      string strWMClass = papplication->get_wm_class();

      straLine.add("[Desktop Entry]");
      straLine.add("Version=1.0");
      straLine.add("Type=application");
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

      ::file::path path = pcontext->m_papexcontext->dir().matter("app.desktop");

      pcontext->m_papexcontext->file().lines(m_straLine, path);

      if(m_straLine.is_empty())
      {

         create_default();

      }

      auto papplication = get_application();

      string strTitle = papplication->title();

      string_array straCategories = proper_category(papplication->get_categories());

      string strWMClass = papplication->get_wm_class();

      ::file::path pathUserBin;

      string strName;

      strName = papplication->m_strAppId;

      strName.replace("-", "_");

      strName.replace("/", "_");

      strName.replace(".", "_");

      //pathLaunch = pacmedir->home() / ".config/ca2/bin" / (strName + ".sh");

      auto psystem = m_psystem;

      auto pacmedir = psystem->m_pacmedir;

      pathUserBin = pacmedir->home() / "bin" / strName;

      ::file::path pathIcon = pcontext->m_papexcontext->dir().matter("main/icon-256.png");

      {

         pcontext->m_papexcontext->file().get_file(pathIcon, ::file::e_open_read);

      }

      string_array & straLine = m_straLine;

      string strScript;

      //string strScript = "#!/bin/bash\n";

      /*strScript += "\n";

      strScript += "run_app()\n";

      strScript += "{\n";

      strScript += "\n";

      strScript += "   cd " + string(pcontext->m_papexcontext->file().module().folder()) + "/\n";

      strScript += "\n";

      strScript += "   export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.:" + string(pcontext->m_papexcontext->file().module().folder()) + "\n";

      */

      //strScript += "\n";

      //strScript += "   /bin/bash -i -c \"" + string(pcontext->m_papexcontext->file().module()) + "\" ${@:1:99}\n";

      /*

      strScript += "\n";

      strScript += "}\n";

      strScript += "\n";

      strScript += "run_app ${@:1:99}\n";

      strScript += "\n"; */

      //m_psystem->m_pacmefile->put_contents(pathLaunch, strScript);

      strScript = "#!/bin/bash\n";

      strScript += "\n";

//      strScript += "export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:.:" + string(pcontext->m_papexcontext->file().module().folder()) + "\n";
//
//      strScript += "\n";
//

      //strScript += "/bin/bash -l -c " + string(pcontext->m_papexcontext->file().module()) + " ${@:1:99}\n";

      strScript += string(pcontext->m_papexcontext->file().module()) + " ${@:1:99}\n";

      strScript += "\n";

      m_psystem->m_pacmefile->put_contents(pathUserBin, strScript);

      //chmod(pathLaunch, 0755);
      chmod(pathUserBin, 0600);

      string strModule = pcontext->m_papexcontext->file().module();

      straLine._007SetLine("[Desktop Entry]", "GenericName", strTitle);
      straLine._007SetLine("[Desktop Entry]", "Name", strTitle);
      straLine._007SetLine("[Desktop Entry]", "Comment", strTitle + " Comment");
      //straLine._007SetLine("[Desktop Entry]", "Exec", pathLaunch + " %U");
      //straLine._007SetLine("[Desktop Entry]", "Exec", strName + " %U");
      //straLine._007SetLine("[Desktop Entry]", "Exec", string(pcontext->m_papexcontext->file().module()) + " %U");
      straLine._007SetLine("[Desktop Entry]", "Exec", strModule + " %U");
      //straLine._007SetLine("Path", string(pcontext->m_papexcontext->file().module().folder()));

      if(pcontext->m_papexcontext->file().exists(pathIcon))
      {

         straLine._007SetLine("[Desktop Entry]", "Icon", pathIcon);

      }

      if(straCategories.has_elements() && straCategories.implode("").has_char())
      {

         straLine._007SetLine("[Desktop Entry]", "Categories", straCategories.implode(";") + ";");

      }


      straLine._007SetLine("[Desktop Entry]", "StartupWMClass", strWMClass);

      // straLine._007SetLine("[Desktop Entry]", "Actions", "transparent-frame;");

      // for(index i = 0; i < papplication->applicationmenu().get_count(); i++)
      // {

      //    auto & item = papplication->applicationmenu()[i];

      //    if()


      // }

      // straLine._007SetLine("[Desktop Action transparent-frame]", "Name", "Transparent Frame");
      // //straLine._007SetLine("[Desktop Action transparent-frame]", "StartupWMClass", "com." + strPrgName);
      // //straLine._007SetLine("[Desktop Action transparent-frame]", "Exec", pathLaunch + " : post transparent_frame");
      // //straLine._007SetLine("[Desktop Action transparent-frame]", "Exec", strName + " : post transparent_frame");
      // //straLine._007SetLine("[Desktop Action transparent-frame]", "Exec", string(pcontext->m_papexcontext->file().module()) + " : post transparent_frame");
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

      pcontext->m_papexcontext->file().put_lines(path, m_straLine);

      chmod(path, S_IRUSR | S_IWUSR | S_IXUSR);

      path = get_board_path();

      pcontext->m_papexcontext->file().put_lines(path, m_straLine);

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


} // namespace linux



