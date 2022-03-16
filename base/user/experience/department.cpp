#include "framework.h"
#include "base/user/experience/_experience.h"
#include "acme/filesystem/filesystem/acme_directory.h"


namespace experience
{


   department::department()
   {

   }


   department::~department()
   {

   }


   __pointer(::experience::experience) department::create_experience(::object * pobject, const ::string & strExperienceRequest)
   {

      string strExperience = experience_name(strExperienceRequest);

      auto & pfactory = m_psystem->factory("experience", strExperience);

      if (!pfactory)
      {

         return nullptr;

      }

      auto pexperience = pfactory->create <::experience::experience>();

      if(pexperience == nullptr)
      {

         return nullptr;

      }

      pexperience->initialize(pobject);

      pexperience->m_pfactory = pfactory;

      pexperience->m_strExperience = strExperience;

      return ::move(pexperience);

   }


   __pointer(::experience::experience) department::experience(::object * pobject, const ::string & strExperienceRequest)
   {

      auto & pexperience = m_mapExperience[experience_name(strExperienceRequest)];

      if(pexperience == nullptr)
      {

         string_array straExperience;

         {

            straExperience.add(strExperienceRequest);

         }

         {

            auto psystem = m_psystem->m_pbasesystem;

            auto strExperience = psystem->payload("experience").string();

            straExperience.add(strExperience);

         }

         {

            auto papp = pobject->get_app();

            {

               auto strExperience = papp->m_papplication->preferred_experience();

               straExperience.add(strExperience);

            }

            {

               auto strExperience = papp->payload("experience");

               straExperience.add(strExperience);

            }

            {

               auto pcontext = get_context();

               {

                  auto strExperience = pcontext->m_papexcontext->file().as_string(m_psystem->m_pacmedirectory->config() / papp->m_papplication->m_strAppName / "experience.txt");

                  straExperience.add(strExperience);

               }

               {

                  auto strExperience = pcontext->m_papexcontext->file().as_string(m_psystem->m_pacmedirectory->config() / ::file::path(papp->m_papplication->m_strAppName).folder() / "experience.txt");

                  straExperience.add(strExperience);

               }

               {

                  auto strExperience = pcontext->m_papexcontext->file().as_string(m_psystem->m_pacmedirectory->config() / ::file::path(papp->m_papplication->m_strAppName).name() / "experience.txt");

                  straExperience.add(strExperience);

               }

               {

                  auto strExperience = pcontext->m_papexcontext->file().as_string(m_psystem->m_pacmedirectory->config() / "system/experience.txt");

                  straExperience.add(strExperience);

               }

               {

                  string strExperience = pcontext->m_papexcontext->file().as_string(m_psystem->m_pacmedirectory->config() / "system/experience.txt");

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

         __pointer(::experience::experience) pexperienceSelected;

         for (auto& str : straExperience)
         {

            pexperienceSelected = create_experience(pobject, str);

            if (pexperienceSelected.is_set())
            {

               break;

            }

         }

         if (pexperienceSelected.is_null())
         {

            auto psystem = m_psystem->m_pbasesystem;

            throw exit_exception(psystem, "no experience_* plugin installed");

         }

         __compose(pexperience, pexperienceSelected);

      }

      return pexperience;

   }


   __pointer(::experience::frame) department::frame_experience(::object * pobject, const ::string & strExperienceRequest, const ::string & strFrameSchema)
   {

      auto strExperience = experience_name(strExperienceRequest);

      auto pexperience = experience(pobject, strExperience);

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

      strExperience.begins_eat_ci("experience_");

      return strExperience;

   }


} // namespace experience


namespace base
{


   void user::initialize1_experience()
   {

      INFORMATION("start");

      //auto estatus = 
      
      __compose_new(m_pexperience);

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



