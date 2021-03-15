#include "framework.h"
#include "base/user/experience/_experience.h"


namespace experience
{


   department::department()
   {

   }


   department::~department()
   {

   }


   ::experience::experience * department::get_new_experience2(::object * pobject, const char * pszExperienceLibrary)
   {

      string strId(pszExperienceLibrary);

      string strBuild;

      __pointer(::base::system) psystem = get_system();
      
      strBuild = psystem->payload("build");

      if(strBuild.is_empty())
      {

         strBuild = "installed";

      }

#ifdef CUBE

      // should implemente

#else


#endif

      string strLibrary(strId);

      strLibrary.replace("-", "_");

      strLibrary.replace("/", "_");

      if (!strLibrary.begins_ci("experience_"))
      {

         strLibrary = "experience_" + strLibrary;

      }

#if defined(LINUX) || defined(APPLEOS)

      strLibrary = "lib" + strLibrary;

#elif defined(_UWP)


      //      strLibrary = "m_" + strLibrary;

#endif

      auto plibrary = psystem->get_library(strLibrary, true);

      if (!plibrary)
      {

         return nullptr;

      }

      //string_array stra;

      //plibrary->get_app_list(stra);

      //if (stra.get_size() != 1) // a department OSLibrary should have one department
      //{

      //   return nullptr;

      //}

      //string strAppId(stra[0]);

      //if (strAppId.is_empty()) // trivial validity check
      //{

      //   return nullptr;

      //}

      __pointer(::experience::experience) pexperience = plibrary->create_object("experience");

      if(pexperience == nullptr)
      {

         return nullptr;

      }

      pexperience->initialize(this);

      pexperience->m_plibrary = plibrary;

      return pexperience;

   }


   ::experience::experience * department::get_experience2(::object * pobject, const char * pszUinteraction)
   {

      auto & pexperience = m_mapExperience[pszUinteraction];

      if(pexperience == nullptr)
      {

         __compose(pexperience, get_new_experience2(pobject, pszUinteraction));

      }

      return pexperience;


   }


   ::experience::frame * department::experience_get_frame2(::object * pobject, const char * pszLibrary, const char * pszFrame)
   {

      string_array straLibrary;

      auto psystem = get_system();

      auto strExperience = psystem->payload("experience").get_string();

      if (strExperience.has_char())
      {

         string strLibrary(strExperience);

         strLibrary.trim();

         if (strLibrary.has_char())
         {

            if (!strLibrary.begins_ci("experience_"))
            {

               strLibrary = "experience_" + strLibrary;

            }

            straLibrary.add(strLibrary);

         }

      }

      {

         string strLibrary(pszLibrary);

         if (strLibrary.has_char())
         {

            straLibrary.add(strLibrary);

         }

      }

      auto papplication = get_application();

      {

         string strLibrary = papplication->preferred_experience();

         if (strLibrary.has_char())
         {

            straLibrary.add(strLibrary);

         }

      }


      {

         string strConfig;

         strConfig = papplication->payload("experience");

         if (strConfig.has_char())
         {

            string strLibrary = string("experience_") + strConfig;

            straLibrary.add(strConfig);

         }

      }

      auto pcontext = get_context();

      {

         string strWndFrm = pcontext->file().as_string(::dir::config() / papplication->m_strAppName / "experience.txt");

         if (strWndFrm.has_char())
         {

            straLibrary.add(strWndFrm);

         }

      }

      {

         string strWndFrm = pcontext->file().as_string(::dir::config() / ::file::path(papplication->m_strAppName).folder() / "experience.txt");

         if (strWndFrm.has_char())
         {

            straLibrary.add(strWndFrm);

         }

      }

      {

         string strWndFrm = pcontext->file().as_string(::dir::config() / ::file::path(papplication->m_strAppName).name() / "experience.txt");

         if (strWndFrm.has_char())
         {

            straLibrary.add(strWndFrm);

         }

      }

      {

         string strWndFrm = pcontext->file().as_string(::dir::config() / "system/experience.txt");

         if (strWndFrm.has_char())
         {

            straLibrary.add(strWndFrm);

         }

      }


      {

         string strConfig = pcontext->file().as_string(::dir::config() / "system/experience.txt");

         if (strConfig.has_char())
         {

            string strLibrary = string("experience_") + strConfig;

            straLibrary.add(strLibrary);

         }

      }

      straLibrary.add("experience_core");
      straLibrary.add("experience_metro");
      straLibrary.add("experience_rootkiller");
      straLibrary.add("experience_hyper");
      straLibrary.add("experience_anthill");

      straLibrary.remove_duplicates_ci();

      __pointer(::experience::experience) pexperience;

      string strLib;

      for(string strLibrary : straLibrary)
      {

         pexperience = get_experience2(pobject, strLibrary);

         if (pexperience.is_set())
         {

            strLib = strLibrary;

            break;

         }

      }

      if (pexperience.is_null())
      {

         auto psystem = get_system();

         __throw(exit_exception(psystem, "no experience_* plugin installed"));

      }

      auto pframe = pexperience->experience_get_frame(pszFrame);

      if(!pframe)
      {

         message_box("no department plugin able to produce u frame");

         return nullptr;

      }

      pframe->initialize(pexperience);

      pframe->m_pexperience = pexperience;

      pframe->m_strLibrary = strLib;

      pframe->m_strName = pszFrame;

      return pframe;

   }


} // namespace experience


namespace base
{


   ::e_status user::initialize1_experience()
   {

      INFO("start");

      auto estatus = __compose_new(m_pexperience);

      if (!estatus)
      {

         //m_result.add(estatus);

         ERR(".1");

         return estatus;

      }

      //m_pexperience->construct(this);

      estatus = m_pexperience->init();

      if(!estatus)
      {

         //m_result.add(estatus);

         ERR(".2");

         return estatus;

      }

      INFO("ok");

      return ::success;

   }


} // namespace base



