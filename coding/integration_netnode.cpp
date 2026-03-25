//
// Created by camilo on 12/12/21 05:08 PM <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "group_machine_box.h"
#include "group_netnode.h"
#include "group_new_release_prefix.h"
#include "group_operating_system.h"
#include "impact.h"
#include "integration.h"
#include "item.h"
#include "application.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/filesystem/filesystem/file_system.h"
#include "acme/operating_system/process.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/node.h"
#include "acme/prototype/datetime/_text_stream.h"
#include "acme/prototype/datetime/datetime.h"
#include "acme/filesystem/file/buffered_file.h"
#include "apex/database/stream.h"
#include "acme/filesystem/filesystem/directory_context.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "apex/networking/http/context.h"
#include "acme/platform/application.h"
#include "apex/platform/node.h"
#include "apex/platform/system.h"
#include "aura/user/user/check_box.h"
#include "aura/user/user/still.h"


#include "acme/_operating_system.h"


namespace coding
{


   void integration::integrate_netnode(const ::scoped_string& scopedstrNetnode)
   {

      start_netnode(scopedstrNetnode);

      m_pimpactinterface->enable_pulse(scopedstrNetnode);

      monitor_netnode(scopedstrNetnode);

   }

   
   ::string integration::netnode_short_name(const ::scoped_string& strNetnode)
   {

      ::string strId;

      strId = strNetnode;

      strId.case_insensitive_ends_eat(m_papp->m_strDnsSuffix);

      strId.case_insensitive_begins_eat("integration-");

      return strId;

   }


   ::string integration::netnode_long_name(const ::scoped_string& scopedstrPulse)
   {

      ::string strId = netnode_short_name(scopedstrPulse);

      strId = "integration-" + strId + m_papp->m_strDnsSuffix;

      return strId;

   }


   void integration::start_netnode(const ::scoped_string& scopedstrNetnode)
   {

      ::string strUrl;

      ::string strIntegration;

      strIntegration = m_strIntegration;

      strUrl = "http://" + scopedstrNetnode + "/call_integration?integration=" + ::url::encode(strIntegration);

      ::string strId = netnode_short_name(scopedstrNetnode);

      main_status("integrate netnode : " + strId);

      m_straLine3.add("integrate netnode : " + strId);

      m_pimpactinterface->on_lines_change();

      ::property_set set;

      http()->get(strUrl, set);

      {

         _synchronous_lock synchronous_lock(this->synchronization());

         m_straLine3.add("commanded integrate netnode : " + strId);

      }

      m_pimpactinterface->on_lines_change();


   }


   ::string integration::netnode_running_status(const ::scoped_string& strNetnode)
   {

      //synchronous_lock synchronouslock(m_pparticleHttpSynchronization);

      ::string strRunningStatus;

      ::string strUrl;

      ::string strIntegration;

      strIntegration = m_strIntegration;

      strUrl = "http://" + strNetnode + "/running_status?integration=" + ::url::encode(strIntegration);

      ::property_set set;

      ::string strResponse = http()->get(strUrl, set);

      ::string strId = netnode_short_name(strNetnode);

      if (strResponse == "yes")
      {

         strRunningStatus = strId + " is running.";

      }
      else if (strResponse.is_empty())
      {

         strRunningStatus = strId + " returned empty response.";

      }
      else if (strResponse == "no")
      {

         return "no";

      }
      else
      {

         strRunningStatus = strId + " : " + strResponse;

      }

      return strRunningStatus;

   }

   
   void integration::monitor_netnode(const ::scoped_string& scopedstrNetnode)
   {

      while (true)
      {

         ::string strRunningStatus = netnode_running_status(scopedstrNetnode);

         if (strRunningStatus == "no")
         {

            break;

         }

         ::string_array stra;

         stra.add_lines(strRunningStatus);

         {

            _synchronous_lock synchronous_lock(this->synchronization());

            m_straLine3.append_container(stra);

         }

         m_pimpactinterface->on_lines_change();

         preempt(3_s);

         {

            _synchronous_lock synchronouslock(this->synchronization());

            if (m_straNetnodePulse.contains(scopedstrNetnode))
            {

               m_straNetnodePulse.erase(scopedstrNetnode);

               synchronouslock.unlock();

               start_netnode(scopedstrNetnode);

               preempt(3_s);

               m_pimpactinterface->enable_pulse(scopedstrNetnode);

            }

         }

      }

   }


} // namespace coding



