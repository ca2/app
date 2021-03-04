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


   ::e_status file_context::initialize(::layered * pobjectContext)
   {

      auto estatus = ::file_context::initialize(pobjectContext);

      if (!estatus)
      {

         return estatus;

      }

      estatus = __refer(m_pdirsystem, System->m_pdirsystem);

      if (!estatus)
      {

         return estatus;

      }

      estatus = __refer(m_pfilesystem, System->m_pfilesystem);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   ::e_status file_context::update_module_path()
   {

      auto estatus = ::file_context::update_module_path();

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


} // namespace android



