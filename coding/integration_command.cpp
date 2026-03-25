//
// From integration.cpp by camilo on 2024-03-24 03:42 <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "application.h"
#include "impact_interface.h"
#include "integration.h"
#include "integration_command.h"
#include "acme/filesystem/filesystem/file_system.h"
#include "acme/platform/node.h"


namespace coding
{


   integration_command::integration_command()
   {

      m_pintegration = nullptr;

   }


   integration_command::~integration_command()
   {


   }


   ::string integration_command::get_step_text()
   {

      ::string strStep;

      strStep.formatf("_%03d", m_iStep + 1);

      return strStep;

   }


   ::string integration_command::get_plain_label()
   {

      ::string strPlainLabel = m_strLabel;

      strPlainLabel.find_replace("/", "_");

      return strPlainLabel;

   }


   void integration_command::run()
   {

      auto timeTimeout = m_timeTimeout;

      m_tracefunction.set_timeout(timeTimeout);

      class ::time timeItem;

      timeItem.Now();

      auto strLabel = m_strLabel;

      m_pintegration->main_status(node()->operating_system_summary()->m_strSystemAmbientReleaseArchitecture + ":" + strLabel);

      auto strCommand = m_strCommand;

      {


         informationf("command_system: %s\n", strCommand.c_str());

         enum_posix_shell eposixshell;

         if (node()->posix_shell_protocol_begins_eat(eposixshell, strCommand))
         {

            m_iExitCode = node()->posix_shell_command(strCommand, eposixshell, m_tracefunction);

         }
         else
         {

            m_iExitCode = node()->command_system(strCommand, m_tracefunction);

         }

         informationf("exit_code: %d\n", m_iExitCode);

         string strItemResult;

         strItemResult += "\n";

         strItemResult += "-----         " + strLabel + "\n";
         strItemResult += "command     : " + strCommand + "\n";
         strItemResult += "exit code   : " + ::as_string(m_iExitCode) + "\n";
         strItemResult += "time    : " + ::as_string(timeItem.elapsed().floating_minute()) + " minute(s)\n";

         strItemResult += "\n";

         m_pfileLog->write(strItemResult);

         m_pintegration->m_pimpactinterface->on_lines_change();

         m_pintegration->m_strBuildResult += strItemResult;

         ::string strAppIdStore;

         strAppIdStore = strLabel;

         if (strAppIdStore.case_insensitive_begins_eat("build_project "))
         {

            if (m_iExitCode == 0)
            {

               ::string strMessage;

               strMessage << "add_store_copy : " << strAppIdStore;

               information() << strMessage;

               auto pathLogAddStoreCopy = m_pintegration->m_pathLogFolder / "add_store_copy.txt";

               file_system()->append(pathLogAddStoreCopy, strMessage);

               m_pintegration->add_store_copy(strAppIdStore);

            }
            else
            {


               ::string strMessage;

               strMessage << "add_store_copy : " << strAppIdStore;

               information() << strMessage;

               auto pathLogFailedToAddStoreCopy = m_pintegration->m_pathLogFolder / "failed_to_add_store_copy.txt";

               file_system()->append(pathLogFailedToAddStoreCopy, strMessage);

               //synchronous_lock synchronouslock(this->synchronization());

               //m_itemtimeaSummary.insert_at(0, {"✗ " + strAppIdStore, m_timeTopicStart.elapsed()});

               m_pintegration->integration_summary(strAppIdStore, "✗", true);

            }

         }

      }

   }




} // namespace coding



