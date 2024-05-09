#pragma once


#include "impact_system.h"


namespace user
{


   class CLASS_DECL_BASE single_document_template :
      virtual public ::user::impact_system
   {
   public:


      ::pointer<::user::document>m_pdocument;


      single_document_template(const ::string & pszMatter, const ::type_atom & typeatomDocument, const ::type_atom & typeatomFrame, const ::type_atom & pImpactClass, const ::type_atom & typeatomData = {});
      ~single_document_template() override;


      void destroy() override;


      virtual void add_document(::user::document * pDoc) override;
      virtual void erase_document(::user::document * pDoc) override;
      virtual ::collection::count get_document_count() const override;
      virtual ::user::document * get_document(::collection::index index = 0) const override;
      virtual void on_request(::request * prequest) override;
      //void on_request_continuation(::user::document * pdocument, ::user::frame_window * pframewindow, ::request * prequest) override;
      virtual void set_default_title(::user::document * pdocument) override;

      // virtual void dump(dump_context &) const override;
      // void assert_ok() const override;


   };



} // namespace user






