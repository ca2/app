#include "framework.h"
#include "base/user/user/_user.h"


namespace user
{


   server::server()
   {

   }


   server::~server()
   {

   }


   ::user::document* server::open_new_document(::application* pappOnBehalfOf, bool bMakeVisible, ::user::interaction* puiParent, ewindowflag eflag, ::id id)
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

            __throw(estatus);

         }

         auto papplication = get_application();

         pcreate->initialize_create(papplication->m_strAppId, ::e_type_empty, true);

         if (!estatus)
         {

            __throw(estatus);

         }

      }

      do_request(pcreate);

      //      return pcreate->m_pcommandline->m_varQuery["document"].cast < ::user::document >();

   }


   ::user::document* server::open_document_file(::application* pappOnBehalfOf, ::payload varFile, bool bMakeVisible, ::user::interaction* puiParent, ewindowflag eflag, ::id id)
   {

      auto pcreate = pappOnBehalfOf->__create_new< ::create>();
      
      pcreate->initialize_create(pappOnBehalfOf->m_strAppId, varFile, bMakeVisible, puiParent, eflag, id);

      do_request(pcreate);

      return ::user::__document(pcreate);

   }


   ::user::document* server::create_subdocument(::user::impact_data* pimpactdata)
   {

      auto pdocument = open_document_file(
         pimpactdata->m_pplaceholder->get_application(),
         ::e_type_null,
         true,
         pimpactdata->m_pplaceholder);

      pimpactdata->m_pdocument = pdocument;

      return pdocument;

   }


} // namespace user



