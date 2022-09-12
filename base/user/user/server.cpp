#include "framework.h"
#include "server.h"
#include "aura/user/user/interaction.h"
#include "impact_data.h"
#include "place_holder.h"
#include "document.h"
#include "aura/platform/application.h"


namespace user
{


   server::server()
   {

   }


   server::~server()
   {

   }


   ::user::document* server::open_new_document(::app* pappOnBehalfOf, bool bMakeVisible, ::user::interaction* puiParent, ewindowflag eflag, ::atom atom)
   {

      return open_document_file(pappOnBehalfOf, nullptr, bMakeVisible, puiParent, eflag, atom);

   }


   void server::on_request(::create* pcreateParam)
   {

      __pointer(::create) pcreate(pcreateParam);
      
      if (pcreate == nullptr)
      {

         //auto estatus = 
         
         __construct_new(pcreate);

         //if (!estatus)
         //{

         //   throw ::exception(estatus);

         //}

         auto papp = get_app();

         pcreate->initialize_create(papp->m_strAppId, ::e_type_empty, true);

         //if (!estatus)
         //{

         //   throw ::exception(estatus);

         //}

      }

      do_request(pcreate);

      //      return pcreate->payload("document").cast < ::user::document >();

   }


   ::user::document* server::open_document_file(::app * pappOnBehalfOf, ::payload payloadFile, bool bMakeVisible, ::user::interaction* puiParent, ewindowflag eflag, ::atom atom)
   {

      auto pcreate = pappOnBehalfOf->__create_new< ::create>();
      
      pcreate->initialize_create(pappOnBehalfOf->m_strAppId, payloadFile, bMakeVisible, puiParent, eflag, atom);

      do_request(pcreate);

      return ::user::__document(pcreate);

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



