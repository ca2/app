#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "base/user/user/_user.h"
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


   void document_manager_container::initialize(::object * pobject)
   {

      //auto estatus = 
      
      ::object::initialize(pobject);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //estatus = 
      
      __compose_new(m_pdocmanager);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }

   void document_manager_container::add_document_template(::user::impact_system* ptemplate)
   {

      if (ptemplate == nullptr)
      {

         throw ::exception(error_bad_argument, "impact system template should be valid");

         return;

      }

      if (!m_pdocmanager)
      {

         __compose_new(m_pdocmanager);

      }

      //m_pdocmanager->increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

      document_manager()->add_document_template(ptemplate);

   }


} // namespace user



