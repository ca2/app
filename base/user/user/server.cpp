#include "framework.h"
#include "server.h"
#include "impact_data.h"
#include "place_holder.h"
#include "document.h"
#include "impact.h"
#include "acme/handler/request.h"
#include "aura/platform/application.h"
#include "aura/user/user/interaction.h"
#include "aura/user/user/system.h"


namespace user
{


   server::server()
   {

   }


   server::~server()
   {

   }


   ::user::document* server::open_new_document(::platform::application* pappOnBehalfOf, bool bMakeVisible, ::user::interaction* puiParent, e_window_flag eflag, ::atom atom)
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


   ::user::document * server::open_data(::data::data * pdata, bool bMakeVisible, ::user::interaction * puiParent, e_window_flag eflag, ::atom atom)
   {

      auto prequest = pdata->__create_new< ::request>();

      ::payload payloadOptions;

      payloadOptions["visible"] = bMakeVisible;

      prequest->initialize_create(pdata, payloadOptions, puiParent, eflag, atom);

      request(prequest);

      return ::user::__document(prequest);

   }




   ::user::document* server::open_document_file(::platform::application * pappOnBehalfOf, ::payload payloadFile, bool bMakeVisible, ::user::interaction* puiParent, e_window_flag eflag, ::atom atom)
   {

      auto prequest = pappOnBehalfOf->__create_new< ::request>();

      ::payload payloadOptions;

      payloadOptions["visible"] = bMakeVisible;
      
      prequest->initialize_create(pappOnBehalfOf->m_strAppId, payloadFile, payloadOptions, puiParent, eflag, atom);

      request(prequest);

      return ::user::__document(prequest);

   }


   ::user::document* server::create_subdocument(::user::impact_data* pimpactdata, ::data::data * pdata)
   {

      //auto pdocument = open_document_file(
      //   pimpactdata->m_pplaceholder->get_app(),
      //   ::e_type_null,
      //   true,
      //   pimpactdata->m_pplaceholder);
      auto prequest = pimpactdata->m_pplaceholder->get_app()->__create_new< ::request>();

      ::payload payloadOptions;

      payloadOptions["visible"] = true;

      ::payload payloadFile;

      prequest->initialize_create(
         pimpactdata->m_pplaceholder->get_app()->m_strAppId,
         payloadFile, 
         payloadOptions, 
         pimpactdata->m_pplaceholder,
         e_window_flag(), 
         pimpactdata->m_atom);

      ::pointer<::user::system>pusersystem;
      
      pimpactdata->m_pplaceholder->get_app()->__construct_new(pusersystem);

      prequest->m_pmatterUserPayload = pusersystem;

      pusersystem->m_pimpactdata = pimpactdata;

      request(prequest);

      auto pdocument = ::user::__document(prequest);

      pimpactdata->m_pdocument = pdocument;

      return pdocument;

   }


} // namespace user



