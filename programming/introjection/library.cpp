// From compiler.cpp by camilo on 2021-11-15 15:44 BRT <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "library.h"
#include "acme/filesystem/filesystem/acme_directory.h"


namespace introjection
{


   library::library()
   {

      defer_create_synchronization();

      //initialize(pparticle);

      __zero(m_filetimeset);

   }


   library::~library()
   {


   }


   void library::initialize(::particle * pparticle)
   {

      //auto estatus =
      
      ::object::initialize(pparticle);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //estatus = 
      
      __construct_new(m_plibrary);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


} // namespace introjection



