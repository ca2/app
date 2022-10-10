#pragma once


#include "apex/_.h"
#include "apex/platform/app_core.h"


class CLASS_DECL_APEX console :
   public apex_main_struct
{
public:

   class apex_apex                  m_apex;
   ::pointer<::apex::system>        m_psystem;
   //::pointer<::apex::application>   m_pacmeapplication;

   console(int argc, wchar_t * argv[]);
   console(int argc, char * argv[]);
   virtual ~console();


};
