// From group_checkout_for_another_system.cpp by camilo on 2024-03-24 22:38 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "application.h"
#include "group_checkout_for_another_system.h"
#include "integration.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/prototype/prototype/url.h"


namespace coding
{


   group_checkout_for_another_system::group_checkout_for_another_system()
   {

   }


   group_checkout_for_another_system::~group_checkout_for_another_system()
   {

   }


   void group_checkout_for_another_system::initialize_group_checkout_for_another_system(
           const ::scoped_string &scopedstrSlashedSystem)
   {

      m_strSlashedSystem = scopedstrSlashedSystem;

   }


   ::collection::count group_checkout_for_another_system::get_size()
   {

      return 1;

   }


   enum_integrate group_checkout_for_another_system::get_eintegrate(::collection::index i)
   {

      return e_integrate_checkout_for_another_system;

   }


   ::string group_checkout_for_another_system::get_name(::collection::index i)
   {

      return "Checkout: " + m_strSlashedSystem;

   }


   ::string group_checkout_for_another_system::get_short_name(::collection::index i)
   {

      return "checkout:" + m_strSlashedSystem;

   }


   void group_checkout_for_another_system::integrate()
   {

      if (m_strSlashedSystem.is_empty())
      {

         throw ::exception(error_wrong_state);
      }

      auto pathFolder = directory_system()->home() / "shared";

      pathFolder /= m_strSlashedSystem;

      ::string strOpSys;

      strOpSys = pathFolder.get_word("/");

      //m_pintegration->main_status(node()->operating_system_summary()->m_strSlashedIntegration + ":" + strLabel);

      information() << "group_checkout_for_another_system::integrate (pathFolder) : " << pathFolder;

//      directory_system()->change_current(pathFolder);

      m_pintegration->add_command("checkout integration",
                                  "unix:checkout " + pathFolder + "/cmake/integration",
                                  10_minute);

      m_pintegration->add_command("checkout main",
                                  "unix:checkout " + pathFolder + "/cmake/main",
                                  10_minute);

      m_pintegration->add_command("checkout opsys/tool",
                                  "unix:checkout " + pathFolder + "/cmake/operating-system/tool-" + strOpSys,
                                  10_minute);

      m_pintegration->integrate_command_list();

   }


} // namespace integration_integration



