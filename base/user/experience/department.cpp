#include "framework.h"
#include "department.h"
#include "experience.h"
#include "frame.h"
#include "acme/exception/exit.h"
#include "acme/filesystem/filesystem/acme_directory.h"
#include "apex/filesystem/filesystem/file_context.h"
#include "apex/platform/application.h"
#include "aura/user/user/interaction.h"
#include "axis/platform/session.h"
#include "base/platform/system.h"
#include "base/user/user/user.h"



namespace experience
{


   department::department()
   {

   }


   department::~department()
   {

   }


   ::pointer<::experience::experience>department::create_experience(::particle * pparticle, const ::string & strExperienceRequest)
   {

      string strExperience = experience_name(strExperienceRequest);

      auto & pfactory = acmesystem()->factory("experience", strExperience);

      if (!pfactory)
      {

         return nullptr;

      }

      auto pexperience = pfactory->create <::experience::experience>();

      if(pexperience == nullptr)
      {

         return nullptr;

      }

      pexperience->initialize(pparticle);

      pexperience->m_pfactory = pfactory;

      pexperience->m_strExperience = strExperience;

      return ::transfer(pexperience);

   }


   ::pointer<::experience::experience>department::experience(::particle * pparticle, const ::string & strExperienceRequest)
   {

      auto & pexperience = m_mapExperience[experience_name(strExperienceRequest)];

      if(pexperience == nullptr)
      {

         string_array straExperience;

         {

            straExperience.add(strExperienceRequest);

         }

         {

            auto psystem = acmesystem()->m_pbasesystem;

            auto strExperience = psystem->payload("experience").get_string();

            straExperience.add(strExperience);

         }

         {

            auto papp = pparticle->acmeapplication();

            {

               auto strExperience = papp->m_papexapplication->preferred_experience();

               straExperience.add(strExperience);

            }

            {

               auto strExperience = papp->payload("experience");

               straExperience.add(strExperience);

            }

            {

               auto pcontext = get_context();

               {

                  auto strExperience = pcontext->m_papexcontext->file()->safe_get_string(acmedirectory()->config() / papp->m_papexapplication->m_strAppName / "experience.txt");

                  straExperience.add(strExperience);

               }

               {

                  auto strExperience = pcontext->m_papexcontext->file()->safe_get_string(acmedirectory()->config() / ::file::path(papp->m_papexapplication->m_strAppName).folder() / "experience.txt");

                  straExperience.add(strExperience);

               }

               {

                  auto strExperience = pcontext->m_papexcontext->file()->safe_get_string(acmedirectory()->config() / ::file::path(papp->m_papexapplication->m_strAppName).name() / "experience.txt");

                  straExperience.add(strExperience);

               }

               {

                  auto strExperience = pcontext->m_papexcontext->file()->safe_get_string(acmedirectory()->config() / "system/experience.txt");

                  straExperience.add(strExperience);

               }

               {

                  string strExperience = pcontext->m_papexcontext->file()->safe_get_string(acmedirectory()->config() / "system/experience.txt");

                  straExperience.add(strExperience);

               }

            }

         }

         straExperience.add(" core  ");
         straExperience.add("  metro  ");
         straExperience.add("   experience_rootkiller  ");
         straExperience.add("     experience_hyper   ");
         straExperience.add("       experience_anthill   ");
         straExperience.add("         ");
         straExperience.add("");

         straExperience.trim();

         straExperience.erase_empty();

         straExperience.erase_duplicates_ci();

         ::pointer<::experience::experience>pexperienceSelected;

         for (auto& str : straExperience)
         {

            pexperienceSelected = create_experience(pparticle, str);

            if (pexperienceSelected.is_set())
            {

               break;

            }

         }

         if (pexperienceSelected.is_null())
         {

            auto psystem = acmesystem()->m_pbasesystem;

            throw exit_exception(::error_exit_system, psystem, "no experience_* plugin installed");

         }

         __construct(pexperience, pexperienceSelected);

      }

      return pexperience;

   }


   ::pointer<::experience::frame>department::frame_experience(::particle * pparticle, const ::string & strExperienceRequest, const ::string & strFrameSchema)
   {

      auto strExperience = experience_name(strExperienceRequest);

      auto pexperience = experience(pparticle, strExperience);

      if (!pexperience)
      {

         return nullptr;

      }

      auto pframe = pexperience->frame_experience(strFrameSchema);

      if(!pframe)
      {

         output_error_message("no department plugin able to produce u frame");

         return nullptr;

      }

      pframe->initialize(pexperience);

      pframe->m_pexperience = pexperience;

      pframe->m_strExperience = strExperience;

      pframe->m_strFrameSchema = strFrameSchema;

      return pframe;

   }


   CLASS_DECL_BASE string experience_name(const ::string& str)
   {

      string strExperience;

      strExperience = str;

      strExperience.trim();

      strExperience.case_insensitive_begins_eat("experience_");

      return strExperience;

   }


} // namespace experience


namespace base
{


   void user::initialize1_experience()
   {

      INFORMATION("start");

      //auto estatus = 
      
      __construct_new(m_pexperience);

      //if (!estatus)
      //{

      //   //m_result.add(estatus);

      //   ERROR(".1");

      //   return estatus;

      //}

      //m_pexperience->construct(this);

      //estatus = 
      
      m_pexperience->init();

      //if(!estatus)
      //{

      //   //m_result.add(estatus);

      //   ERROR(".2");

      //   return estatus;

      //}

      INFORMATION("ok");

      //return ::success;

   }

   
} // namespace base



