#pragma once


#include "apex/_.h"
#include "apex/platform/app_core.h"


class CLASS_DECL_APEX console :
   public apex_main_struct
{
public:

   class apex_apex                  m_apex;
   ::pointer<::apex::system>        system();
   //::pointer<::apex::application>   m_papplication;

   console(int argc, wchar_t * argv[]);
   console(int argc, char * argv[]);
   virtual ~console();


};
