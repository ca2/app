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


      multiple_document_template(const ::string & pszMatter, ::type pDocClass, ::type pFrameClass, ::type pImpactClass);
      virtual ~multiple_document_template();


      virtual void load_template() override;
      virtual void add_document(::user::document * pDoc) override;
      virtual void erase_document(::user::document * pDoc) override;
      virtual ::count get_document_count() const override;
      virtual ::user::document * get_document(index index) const override;
      virtual void on_request(::create * pcreate) override;
      virtual void set_default_title(::user::document * pdocument) override;

      // virtual void dump(dump_context &) const override;
      // void assert_ok() const override;

      //virtual i64 increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override
      //{
      //   return ::user::impact_system::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);
      //}

      //virtual i64 decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override
      //{
      //   return ::user::impact_system::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);
      //}

   };


} // namespace user






