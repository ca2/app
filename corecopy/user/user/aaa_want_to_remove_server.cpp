#include "framework.h" 


namespace user
{


   server::server()
   {

   }


   server::~server()
   {

   }


   ::user::document * server::open_new_document(::aura::application * pappOnBehalfOf)
   {

      return open_document_file(pappOnBehalfOf);

   }


   void server::on_request(::create * pcreate)
   {

      __pointer(::create) cc(__new(::create(this, Application.m_strAppId, ::type_empty, true)));

      if (pcreate == nullptr)
      {

         pcreate = cc;

      }

      do_request(pcreate);

//      return pcreate->m_pcommandline->m_varQuery["document"].cast < ::user::document >();

   }


   ::user::document * server::open_document_file(::aura::application * pappOnBehalfOf, var varFile, bool bMakeVisible, ::user::interaction * puiParent, ewindowflag eflag, ::id id)
   {

      auto pcreate = __new(::create(pappOnBehalfOf, pappOnBehalfOf->m_strAppId, varFile, bMakeVisible, puiParent, eflag, id));

      do_request(pcreate);

      return ::user::__document(pcreate);

   }


   ::user::document * server::create_subdocument(::user::impact_data * pimpactdata)
   {

      auto pdocument = open_document_file(
                                    pimpactdata->m_pplaceholder->get_context_application(),
                                    ::type_null,
                                    true,
                                    pimpactdata->m_pplaceholder);

      pimpactdata->m_pdocument = pdocument;

      return pdocument;

   }


} // namespace user



