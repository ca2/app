//
// Created by camilo on 2026-04-06 10:58 <3ThomasBorregaardSørensen!!
//

#pragma once


#include "acme/operating_system/windows/subsystem/subsystem.h"
#include "apex/innate_subsystem/subsystem.h"

namespace windows
{
   namespace innate_subsystem
   {


      class CLASS_DECL_APEX subsystem :
         virtual public ::windows::subsystem::subsystem,
         virtual public ::innate_subsystem::subsystem
      {
      public:



         subsystem();
         ~subsystem() override;





          int message_box(
            WindowInterface * pwindow,
            const ::scoped_string & scopedstrMessage,
            const ::scoped_string & scopedstrCaption,
            unsigned int uType) override;



      };



   } // namespace innate_subsystem




} // namespace windows