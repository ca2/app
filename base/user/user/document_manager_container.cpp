#include "framework.h"
#include "document_manager_container.h"
#include "document_manager.h"
#include "impact_system.h"
////#include "acme/exception/exception.h"

#if defined(FREEBSD) || defined(OPENBSD)
#include <stdio.h>
#endif


namespace user
{


   document_manager_container::document_manager_container()
   {


   }


   document_manager_container::~document_manager_container()
   {


   }



   ::user::document_manager* document_manager_container::document_manager()
   {

      return m_pdocmanager;

   }


   void document_manager_container::initialize(::particle * pparticle)
   {

      //auto estatus = 
      
      ::object::initialize(pparticle);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //estatus =

      printf("base::user::document_manager_container Going to create new document manager\n");
      
      __construct_new(m_pdocmanager);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   void document_manager_container::destroy()
   {

      m_pdocmanager.release();

      ::object::destroy();

   }


   void document_manager_container::add_impact_system(const ::atom & atom, const ::pointer < ::user::impact_system > & pimpactsystem)
   {

      document_manager()->add_impact_system(atom, pimpactsystem);

   }


   ::pointer<::user::impact_system> document_manager_container::impact_system(const ::atom & atom)
   {

      //if (ptemplate == nullptr)
      //{

      //   throw ::exception(error_bad_argument, "impact system template should be valid");

      //   return;

      //}

      if (!m_pdocmanager)
      {

         __construct_new(m_pdocmanager);

      }

      //m_pdocmanager->increment_reference_count();

      return document_manager()->__impact_system(atom);

   }


   


} // namespace user



