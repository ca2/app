#include "framework.h"
#include "department.h"
#include "acme/exception/exit.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "apex/platform/application.h"
#include "aura/user/user/interaction.h"
#include "axis/platform/session.h"
#include "berg/platform/system.h"
#include "berg/user/user/user.h"
#include "experience.h"
#include "frame.h"


namespace experience
{


   department::department() {}


   department::~department() {}


   ::pointer<::experience::experience> department::create_experience(::particle *pparticle,
                                                                     const ::scoped_string &scopedstrExperienceRequest)
   {

      string strExperience = experience_name(scopedstrExperienceRequest);

      auto &pfactory = system()->factory("experience", strExperience);

      if (!pfactory)
      {

         return nullptr;
      }

      auto pexperience = øcreate<::experience::experience>(pfactory);

      if (pexperience == nullptr)
      {

         return nullptr;
      }

      pexperience->initialize(pparticle);

      pexperience->m_pfactory = pfactory;

      pexperience->m_strExperience = strExperience;

      return ::transfer(pexperience);
   }


   ::pointer<::experience::experience> department::experience(::particle *pparticle,
                                                              const ::scoped_string &scopedstrExperienceRequest)
   {

      auto &pexperience = m_mapExperience[experience_name(scopedstrExperienceRequest)];

      if (pexperience == nullptr)
      {

         string_array_base straExperience;

         {

            straExperience.add(scopedstrExperienceRequest);
         }

         {

            auto psystem = system();

            auto strExperience = psystem->payload("experience").as_string();

            straExperience.add(strExperience);
         }

         {

            auto papp = pparticle->application();

            {

               auto strExperience = papp->preferred_experience();

               straExperience.add(strExperience);
            }

            {

               auto strExperience = papp->payload("experience");

               straExperience.add(strExperience);
            }

            {

               //// auto pcontext = get_context();

               {

                  auto strExperience =
                     file()->safe_get_string(directory_system()->config() / papp->m_strAppName / "experience.txt");

                  straExperience.add(strExperience);
               }

               {

                  auto strExperience = file()->safe_get_string(
                     directory_system()->config() / ::file::path(papp->m_strAppName).folder() / "experience.txt");

                  straExperience.add(strExperience);
               }

               {

                  auto strExperience = file()->safe_get_string(
                     directory_system()->config() / ::file::path(papp->m_strAppName).name() / "experience.txt");

                  straExperience.add(strExperience);
               }

               {

                  auto strExperience = file()->safe_get_string(directory_system()->config() / "system/experience.txt");

                  straExperience.add(strExperience);
               }

               {

                  string strExperience =
                     file()->safe_get_string(directory_system()->config() / "system/experience.txt");

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

         straExperience.case_insensitive_erase_duplicates();

         ::pointer<::experience::experience> pexperienceSelected;

         for (auto &str: straExperience)
         {

            pexperienceSelected = create_experience(pparticle, str);

            if (pexperienceSelected.is_set())
            {

               break;
            }
         }

         if (pexperienceSelected.is_null())
         {

            auto psystem = system();

            throw exit_exception(::error_exit_system, psystem, "no experience_* plugin installed");
         }

         pexperience = pexperienceSelected;
      }

      return pexperience;
   }


   ::pointer<::experience::frame> department::frame_experience(::particle *pparticle,
                                                               const ::scoped_string &scopedstrExperienceRequest,
                                                               const ::scoped_string &scopedstrFrameSchema)
   {

      auto strExperience = experience_name(scopedstrExperienceRequest);

      auto pexperience = experience(pparticle, strExperience);

      if (!pexperience)
      {

         return nullptr;
      }

      auto pframe = pexperience->frame_experience(scopedstrFrameSchema);

      if (!pframe)
      {

         output_error_message("no department plugin able to produce u frame");

         return nullptr;
      }

      pframe->initialize(pexperience);

      pframe->m_pexperience = pexperience;

      pframe->m_strExperience = strExperience;

      pframe->m_strFrameSchema = scopedstrFrameSchema;

      return pframe;
   }


   CLASS_DECL_BERG string experience_name(const ::scoped_string &scopedstr)
   {

      string strExperience;

      strExperience = scopedstr;

      strExperience.trim();

      strExperience.case_insensitive_begins_eat("experience_");

      return strExperience;
   }


} // namespace experience


namespace berg
{


   void user::initialize1_experience()
   {

      information() << "berg::user::initialize1_experience start";

      // auto estatus =

      øconstruct_new(m_pexperience);

      // if (!estatus)
      //{

      //   //m_result.add(estatus);

      //   error() <<".1";

      //   return estatus;

      //}

      // m_pexperience->construct(this);

      // estatus =

      m_pexperience->init();

      // if(!estatus)
      //{

      //   //m_result.add(estatus);

      //   error() <<".2";

      //   return estatus;

      //}

      information() << "ok";

      // return ::success;
   }


} // namespace berg
