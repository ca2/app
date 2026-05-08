//
//  integration_application_build_tool.cpp
//  coding
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2025-01-06.
//  Copyright © 2025 ca2 Software Development. All rights reserved.
//  <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "application.h"
#include "group_checkout_for_another_system.h"
#include "group_machine_box.h"
#include "group_netnode.h"
#include "group_new_release_prefix.h"
#include "group_operating_system.h"
#include "impact.h"
#include "integration.h"
#include "integration_command.h"
#include "item.h"
#include "task.h"
#include "task_group.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/filesystem/filesystem/file_system.h"
#include "acme/nano/nano.h"
#include "acme/nano/speech/speech.h"
#include "acme/user/micro/user.h"
#include "acme/operating_system/process.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/node.h"
#include "acme/platform/scoped_restore.h"
#include "acme/handler/sequence.h"
#include "acme/prototype/collection/_string.h"
#include "acme/prototype/datetime/_text_stream.h"
#include "acme/prototype/datetime/datetime.h"
#include "acme/prototype/string/from_integer.h"
#include "acme/filesystem/file/buffered_file.h"
#include "apex/database/stream.h"
#include "acme/filesystem/filesystem/directory_context.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "acme/prototype/mathematics/mathematics.h"
#include "apex/networking/http/context.h"
#include "apex/platform/node.h"
#include "apex/platform/system.h"
#include "aura/user/user/check_box.h"
#include "aura/user/user/still.h"


#include "acme/_operating_system.h"


CLASS_DECL_ACME::earth::time earth_time_from_international_string(const ::scoped_string& scopedstrTime);
CLASS_DECL_ACME bool sort_of_ok_earth_time_from_international_string(const ::scoped_string& scopedstrTime);


namespace coding
{


   void integration::on_initialize_application_build_tool()
   {

      on_initialize_application_build_tool_task_groups();
      //on_initialize_operating_system_integrate_list(m_eintegrateaOperatingSystem);
      on_initialize_application_build_tool_operating_system_integrate_list();

      initialize_integrate_operating_system();

      for (::collection::index i = 0; i < m_straTaskOrdinal.size(); i++)
      {

         m_papp->datastream()->get(m_straTaskOrdinal[i], m_baTaskOrdinalEnable[i]);

      }

      m_papp->defer_task_groups(this);

      on_load();

   }


   void integration::on_open_build_tool()
   {

      _synchronous_lock synchronouslock(this->synchronization());

      for (auto& ptaskgroup : m_taskgroup.payloads())
      {

         ptaskgroup->m_strTopic12 = m_strIntegration;

      }

   }


} // namespace coding



