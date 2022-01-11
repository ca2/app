// From compiler.cpp by camilo on 2021-11-15 15:44 BRT <3ThomasBorregaardS�rensen!!
#include "framework.h"
#ifdef WINDOWS_DESKTOP
#include "acme_windows/_.h"
#include "acme_windows/_acme_windows.h"
#endif
#include "acme/filesystem/filesystem/acme_dir.h"


namespace introjection
{


   library::library()
   {

      defer_create_mutex();

      //initialize(pobject);

      __zero(m_filetimeset);

   }


   library::~library()
   {


   }


   void library::initialize(::object* pobject)
   {

      auto estatus = ::object::initialize(pobject);

      if (!estatus)
      {

         return estatus;

      }

      estatus = __construct_new(m_plibrary);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


} // namespace introjection



