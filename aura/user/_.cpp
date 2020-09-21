#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "aura/user/_user.h"
#endif


CLASS_DECL_AURA::estatus message_box(::user::primitive* puiOwner, const char* pszMessage, const char* pszTitle, ::emessagebox emessagebox, ::future future)
{

   ::estatus estatus = ::error_failed;

   auto psystem = ::get_context_system();

   if(psystem)
   {

      psystem->message_box(puiOwner, pszMessage, pszTitle, emessagebox, future);

   }

   return estatus;

}



