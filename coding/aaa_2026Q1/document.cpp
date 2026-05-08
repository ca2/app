#include "framework.h"
#include "document.h"
#include "impact.h"
#include "integration.h"
#include "acme/platform/node.h"


namespace coding
{


   document::document()
   {


   }


   document::~document()
   {

   }


   bool document::on_new_document()
   {

      auto pathIntegrationFolder = node()->get_default_base_integration_folder();

      return on_open_document(pathIntegrationFolder);

   }


   bool document::on_save_document(::file::file * pwriter)
   {

      return true;

   }


   bool document::on_open_document(const ::payload & payloadFile)
   {

      m_path = payloadFile.as_file_path();

      defer_constructø(m_pintegration);

      m_pintegration->initialize_integration();

      return true;

   }


#ifdef _DEBUG


   long long document::increment_reference_count()
   {

      return  ::user::document::increment_reference_count();

   }

   long long document::decrement_reference_count()
   {

      return  ::user::document::decrement_reference_count();

   }


#endif


} // namespace coding



