#pragma once


#include "acid/_.h"
#include "acid/platform/app_core.h"


class CLASS_DECL_ACID console :
   public ace_main_struct
{
public:

   class ace_ace                  m_ace;
   ::pointer<::acid::system>        system();
   //::pointer<::acid::application>   m_paceapplication;

   console(int argc, wchar_t * argv[]);
   console(int argc, char * argv[]);
   virtual ~console();


};
