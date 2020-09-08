#pragma once


namespace process
{


   struct CLASS_DECL_AQUA exit_status
   {


      int      m_iExitCode;
      int      m_iExitSignal;
      int      m_iExitStop;

      exit_status();


   };


   CLASS_DECL_AQUA bool set_priority(::e_priority epriority);

   CLASS_DECL_AQUA string app_id_to_app_name(string strId);


} // namespace process



#include "process_pipe.h"
#include "process_bidi_pipe.h"
#include "process_process.h"
#include "process_department.h"
