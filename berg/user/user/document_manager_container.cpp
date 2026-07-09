#include "framework.h"
#include "document_manager_container.h"
#include "document_manager.h"
#include "impact_system.h"
#include "user.h"
////#include "acme/exception/exception.h"

//#if defined(FREEBSD) || defined(OPENBSD) || defined(__APPLE__)
//#include <stdio.h>
//#endif


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

      if (!m_pdocumentmanager)
      {

         m_pdocumentmanager = create_user_document_manager();

      }

      return m_pdocumentmanager;

   }


   ::pointer < ::user::document_manager > document_manager_container::create_user_document_manager()
   {

      return create_newø<::user::document_manager>();

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



      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   void document_manager_container::destroy()
   {

      m_pdocumentmanager.release();

      ::object::destroy();

   }


   void document_manager_container::add_impact_system(const ::atom & atom, const ::pointer < ::user::impact_system > & pimpactsystem)
   {

      document_manager()->add_impact_system(atom, pimpactsystem);

   }


   //::pointer<::user::impact_system> document_manager_container::impact_system(const ::atom & atom)
   //{

   //   //if (ptemplate == nullptr)
   //   //{

   //   //   throw ::exception(error_bad_argument, "impact system template should be valid");

   //   //   return;

   //   //}

   //   //if (!m_pdocmanager)
   //   //{

   //   //   construct_newø(m_pdocmanager);

   //   //}

   //   //m_pdocmanager->increment_reference_count();

   //   return document_manager()->__impact_system(atom);

   //}


   bool document_manager_container::has_impact_system(const ::atom & atom)
   {

               auto &pimpactsystem = document_manager()->impact_system(atom);

      // if (atom == "child_form")
      //{

      if (pimpactsystem.is_null())
      {
         return false;
      }

      return true;

   }


   ::pointer<::user::impact_system> document_manager_container::impact_system(const ::atom &atom)
   {

      //::cast<::berg::application> pbergapplication = m_papplication

         auto & pimpactsystem = document_manager()->impact_system(atom);

      //if (atom == "child_form")
      //{

         if (!pimpactsystem)
         {

            pimpactsystem = create_impact_system(atom);

         }

        // pimpactsystem = document_manager_container::impact_system(atom);
      //}

      return pimpactsystem;

   }   


   ::pointer<::user::impact_system> document_manager_container::create_impact_system(const ::atom & atom)
   {

      ::cast<::berg::user> pberguser = user();

      auto pimpactsystem = pberguser->create_impact_system(atom);

      return pimpactsystem;

   }


} // namespace user



