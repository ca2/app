#pragma once


#include "acme/_.h"
#include "acme/platform/app_core.h"


class CLASS_DECL_ACME console :
   public acme_main_struct
{
public:

   class acme_acme                  m_acme;
   ::pointer<::acme::system>        system();
   //::pointer<::acme::application>   m_pacmeapplication;

   console(int argc, wchar_t * argv[]);
   console(int argc, char * argv[]);
   virtual ~console();


};
