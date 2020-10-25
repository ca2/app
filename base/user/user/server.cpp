#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "base/user/user/_user.h"
#endif


namespace user
{


   server::server()
   {

   }


   server::~server()
   {

   }


   ::user::document* server::open_new_document(::apex::application* pappOnBehalfOf, bool bMakeVisible, ::user::interaction* puiParent, ewindowflag eflag, ::id id)
   {

      return open_document_file(pappOnBehalfOf, nullptr, bMakeVisible, puiParent, eflag, id);

   }


   void server::on_request(::create* pcreateParam)
   {

      __pointer(::create) pcreate(pcreateParam);
      
      if (pcreate == nullptr)
      {

         auto estatus = __construct_new(pcreate);

         if (!estatus)
         {

            __throw(exception::exception(estatus));

         }

         pcreate->initialize_create(Application.m_strAppId, ::type_empty, true);

         if (!estatus)
         {

            __throw(exception::exception(estatus));

         }

      }

      do_request(pcreate);

      //      return pcreate->m_pcommandline->m_varQuery["document"].cast < ::user::document >();

   }


   ::user::document* server::open_document_file(::apex::application* pappOnBehalfOf, var varFile, bool bMakeVisible, ::user::interaction* puiParent, ewindowflag eflag, ::id id)
   {

      auto pcreate = pappOnBehalfOf->__create_new< ::create>();
      
      pcreate->initialize_create(pappOnBehalfOf->m_strAppId, varFile, bMakeVisible, puiParent, eflag, id);

      do_request(pcreate);

      return ::user::__document(pcreate);

   }


   ::user::document* server::create_subdocument(::user::impact_data* pimpactdata)
   {

      auto pdocument = open_document_file(
         pimpactdata->m_pplaceholder->get_context_application(),
         ::e_type_null,
         true,
         pimpactdata->m_pplaceholder);

      pimpactdata->m_pdocument = pdocument;

      return pdocument;

   }


} // namespace user



