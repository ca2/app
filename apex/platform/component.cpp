// Created by camilo on 2025-03-09 01:27 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "component.h"
#include "acme/filesystem/file/folder.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/handler/topic.h"
#include "acme/parallelization/synchronous_lock.h"
#include "apex/database/stream.h"
#include "apex/networking/http/context.h"


namespace apex
{


   void component::_update_enabled_implementations()
   {

      _synchronous_lock synchronouslock(this->synchronization());

      for (auto & component : m_straImplementationInstalled)
      {

         bool bEnabled = false;

         if (datastream()->get(m_strComponent + "_" + component, bEnabled) && bEnabled)
         {

            m_straImplementationEnabled.add(component);

         }

      }

   }


   void component::handle(::topic * ptopic, ::context * pcontext)
   {

      if (ptopic->id() == id_implementation_enabled)
      {

         auto strImplementation = ptopic->payload("implementation").as_string();

         auto pimplementation = implementation(strImplementation);

         if(::is_null(pimplementation))
         {
         
            auto pfileZip = create_memory_file();

            ::property_set set;

            set["raw_http"] = true;

            http()->download(pfileZip, "https://windows.ca2.store/" + m_strComponentPath + "_" + strImplementation + ".zip", set);

            auto pfolder = system()->create < ::folder >("folder", "zip");

            pfolder->initialize(m_papplication);

            pfolder->open_for_reading(pfileZip);

            pfolder->e_extract_all(directory_system()->module(), nullptr, nullptr, nullptr, nullptr);

            _update_installed_implementations();

            pimplementation = implementation(strImplementation);

            if (::is_null(pimplementation))
            {

               throw ::exception(error_failed);

            }

         }

         datastream()->set(m_strComponent + "_" + strImplementation, true);

      }
      else if (ptopic->id() == id_implementation_disabled)
      {

         auto strImplementation = ptopic->payload("implementation").as_string();

         datastream()->set(m_strComponent + "_" + strImplementation, false);

      }

   }


   void component::destroy()
   {

      ::database::client::destroy();


      ::component::destroy();

   }


} // namespace apex



