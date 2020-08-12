#include "framework.h"
#include "_android.h"


namespace android
{


   file_context::file_context()
   {

   }


   file_context::~file_context()
   {

   }


   ::estatus file_context::initialize(::object * pobjectContext)
   {

      auto estatus = ::file_context::initialize(pobjectContext);

      if (!estatus)
      {

         return estatus;

      }

      estatus = __refer(m_pdirsystem, ::aura::system::g_p->m_pdirsystem);

      if (!estatus)
      {

         return estatus;

      }

      estatus = __refer(m_pfilesystem, ::aura::system::g_p->m_pfilesystem);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   ::estatus file_context::update_module_path()
   {

      auto estatus = ::file_context::update_module_path();

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


} // namespace android



