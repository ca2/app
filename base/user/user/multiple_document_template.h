#pragma once


#include "impact_system.h"


namespace user
{


   // MDI support (zero or more documents)
   class CLASS_DECL_BASE multiple_document_template :
      virtual public ::user::impact_system
   {
   public:


      pointer_array < ::user::document > m_docptra;          // open documents of this type
      ::u32 m_nUntitledCount;   // start at 0, for "Document1" title


      multiple_document_template(const ::string & pszMatter, const ::type_atom & typeatomDocument, const ::type_atom & typeatomFrame, const ::type_atom & typeatomImpact, const ::type_atom & typeatomData = {});
      ~multiple_document_template() override;


      void load_template() override;
      void add_document(::user::document * pDoc) override;
      void erase_document(::user::document * pDoc) override;
      ::count get_document_count() const override;
      ::user::document * get_document(index index) const override;
      void on_request(::request * prequest) override;
      void set_default_title(::user::document * pdocument) override;

      // virtual void dump(dump_context &) const override;
      // void assert_ok() const override;

      //virtual i64 increment_reference_count(REFERENCING_DEBUGGING_PARAMETERS) override
      //{
      //   return ::user::impact_system::increment_reference_count(REFERENCING_DEBUGGING_ARGS);
      //}

      //virtual i64 decrement_reference_count(REFERENCING_DEBUGGING_PARAMETERS) override
      //{
      //   return ::user::impact_system::decrement_reference_count(REFERENCING_DEBUGGING_ARGS);
      //}

   };


} // namespace user






