#include "framework.h"
#include "server.h"
#include "impact_data.h"
#include "place_holder.h"
#include "document.h"
#include "impact.h"
#include "acme/platform/request.h"
#include "aura/platform/application.h"
#include "aura/user/user/interaction.h"


namespace user
{


   server::server()
   {

   }


   server::~server()
   {

   }


   ::user::document* server::open_new_document(::acme::application* pappOnBehalfOf, bool bMakeVisible, ::user::interaction* puiParent, ewindowflag eflag, ::atom atom)
   {

      return open_document_file(pappOnBehalfOf, nullptr, bMakeVisible, puiParent, eflag, atom);

   }


   void server::on_request(::request * prequestParam)
   {

      ::pointer<::request>prequest(prequestParam);
      
      if (prequest == nullptr)
      {

         //auto estatus = 
         
         __construct_new(prequest);

         //if (!estatus)
         //{

         //   throw ::exception(estatus);

         //}

         auto papplication = get_app();

         prequest->initialize_create(papplication->m_strAppId, ::e_type_empty, true);

         //if (!estatus)
         //{

         //   throw ::exception(estatus);

         //}

      }

      request(prequest);

      //      return pcreate->payload("document").cast < ::user::document >();

   }


   ::user::document* server::open_document_file(::acme::application * pappOnBehalfOf, ::payload payloadFile, bool bMakeVisible, ::user::interaction* puiParent, ewindowflag eflag, ::atom atom)
   {

      auto prequest = pappOnBehalfOf->__create_new< ::request>();
      
      prequest->initialize_create(pappOnBehalfOf->m_strAppId, payloadFile, bMakeVisible, puiParent, eflag, atom);

      request(prequest);

      return ::user::__document(prequest);

   }


   ::user::document* server::create_subdocument(::user::impact_data* pimpactdata)
   {

      auto pdocument = open_document_file(
         pimpactdata->m_pplaceholder->get_app(),
         ::e_type_null,
         true,
         pimpactdata->m_pplaceholder);

      pimpactdata->m_pdocument = pdocument;

      return pdocument;

   }


} // namespace user



