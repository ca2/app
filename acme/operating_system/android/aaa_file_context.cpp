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


   void file_context::initialize(::particle * pparticle)
   {

      auto estatus = ::file_context::initialize(pparticle);

      if (!estatus)
      {

         return estatus;

      }

      estatus = __refer(m_pdirsystem, ::acmeacmesystem()->m_pdirsystem);

      if (!estatus)
      {

         return estatus;

      }

      estatus = __refer(m_pfilesystem, ::acmeacmesystem()->m_pfilesystem);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   void file_context::update_module_path()
   {

      auto estatus = ::file_context::update_module_path();

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


} // namespace android



