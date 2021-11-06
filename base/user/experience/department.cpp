#include "framework.h"
#include "base/user/experience/_experience.h"
#include "acme/filesystem/filesystem/acme_dir.h"


namespace experience
{


   department::department()
   {

   }


   department::~department()
   {

   }


   __pointer(::experience::experience) department::create_experience2(::object * pobject, const ::string & pszExperienceLibrary)
   {

      string strId(pszExperienceLibrary);

      string strBuild;

      auto psystem = get_system()->m_pbasesystem;
      
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

      string strComponent = "experience";

      string strImplementation = strLibrary;

      strImplementation.begins_eat_ci("experience_");

      auto plibrary = psystem->do_containerized_factory_exchange(strComponent, strImplementation);

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

      auto pexperience = plibrary->m_pfactorymap->create <::experience::experience>();

      if(pexperience == nullptr)
      {

         return nullptr;

      }

      pexperience->initialize(pobject);

      pexperience->m_plibrary = plibrary;

      return pexperience;

   }


   __pointer(::experience::experience) department::get_experience2(::object * pobject, const ::string & pszUinteraction)
   {

      auto & pexperience = m_mapExperience[pszUinteraction];

      if(pexperience == nullptr)
      {

         __compose(pexperience, create_experience2(pobject, pszUinteraction));

      }

      return pexperience;


   }


   __pointer(::experience::frame) department::experience_get_frame2(::object * pobject, const ::string & pszLibrary, const ::string & pszFrame)
   {

      string_array straLibrary;

      auto psystem = m_psystem->m_pbasesystem;

      auto strExperience = psystem->payload("experience").string();

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

      auto papplication = pobject->get_application();

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

         string strWndFrm = pcontext->m_papexcontext->file().as_string(m_psystem->m_pacmedir->config() / papplication->m_strAppName / "experience.txt");

         if (strWndFrm.has_char())
         {

            straLibrary.add(strWndFrm);

         }

      }

      {

         string strWndFrm = pcontext->m_papexcontext->file().as_string(m_psystem->m_pacmedir->config() / ::file::path(papplication->m_strAppName).folder() / "experience.txt");

         if (strWndFrm.has_char())
         {

            straLibrary.add(strWndFrm);

         }

      }

      {

         string strWndFrm = pcontext->m_papexcontext->file().as_string(m_psystem->m_pacmedir->config() / ::file::path(papplication->m_strAppName).name() / "experience.txt");

         if (strWndFrm.has_char())
         {

            straLibrary.add(strWndFrm);

         }

      }

      {

         string strWndFrm = pcontext->m_papexcontext->file().as_string(m_psystem->m_pacmedir->config() / "system/experience.txt");

         if (strWndFrm.has_char())
         {

            straLibrary.add(strWndFrm);

         }

      }


      {

         string strConfig = pcontext->m_papexcontext->file().as_string(m_psystem->m_pacmedir->config() / "system/experience.txt");

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

      straLibrary.erase_duplicates_ci();

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

         auto psystem = m_psystem->m_pbasesystem;

         throw exit_exception(psystem, "no experience_* plugin installed");

      }

      auto pframe = pexperience->experience_get_frame(pszFrame);

      if(!pframe)
      {

         output_error_message("no department plugin able to produce u frame");

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

      INFORMATION("start");

      auto estatus = __compose_new(m_pexperience);

      if (!estatus)
      {

         //m_result.add(estatus);

         ERROR(".1");

         return estatus;

      }

      //m_pexperience->construct(this);

      estatus = m_pexperience->init();

      if(!estatus)
      {

         //m_result.add(estatus);

         ERROR(".2");

         return estatus;

      }

      INFORMATION("ok");

      return ::success;

   }


} // namespace base



