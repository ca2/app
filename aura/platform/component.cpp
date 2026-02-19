// Created by camilo on 2025-03-09 02:03 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "component.h"
#include "acme/constant/id.h"
#include "acme/handler/topic.h"
#include "acme/platform/component_implementation.h"
#include "aura/graphics/image/wallpaper_transform.h"
#include "aura/user/user/check_box.h"
#include "aura/user/user/still.h"


namespace aura
{


   void component::_001CreateForm(::user::interaction* puserinteractionParent)
   {

      for (auto strImplementation : m_straImplementationAll)
      {

         bool bInstalled = is_implementation_installed(strImplementation);

         bool bEnabled = is_implementation_enabled(strImplementation);

         auto pimplementation = implementation(strImplementation);

         auto strImplementationName = system()->http_text(m_strComponentPath, "component_implementation_name");

         auto pcheckbox = create_check_box<::user::check_box>(puserinteractionParent, "");

         if (bEnabled)
         {

            pcheckbox->set_check(true, ::e_source_initialize);

         }

         pcheckbox->check_changed(this) += [this, strImplementation, pcheckbox](auto & check)
            {

               bool bCheck = check.payload().as_bool();

               auto ptopic = create_topic(bCheck ? id_implementation_enabled : id_implementation_disabled);

               ptopic->payload("implementation") = strImplementation;

               try
               {

                  route(ptopic);

               }
               catch (...)
               {

                  _update_installed_implementations();

                  _update_enabled_implementations();

                  pcheckbox->set_check(is_implementation_enabled(strImplementation), e_source_clear);

                  return;

               }

            };

         create_label<::user::still>(puserinteractionParent, "Enable \"" + strImplementationName + "\"");

      }

   }


} // namespace aura
