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
      unsigned int m_nUntitledCount;   // start at 0, for "Document1" title


      multiple_document_template(const ::scoped_string & scopedstrMatter, const ::type_atom & typeatomDocument, const ::type_atom & typeatomFrame, const ::type_atom & typeatomImpact, const ::type_atom & typeatomData = {});
      ~multiple_document_template() override;


      void destroy() override;


      void load_impact_system() override;
      void add_document(::user::document * pDoc) override;
      void erase_document(::user::document * pDoc) override;
      ::collection::count get_document_count() const override;
      ::user::document * get_document(::collection::index index) const override;
      void on_request(::request * prequest) override;
      void set_default_title(::user::document * pdocument) override;

      // virtual void dump(dump_context &) const override;
      // void assert_ok() const override;

      //virtual long long increment_reference_count() override
      //{
      //   return ::user::impact_system::increment_reference_count();
      //}

      //virtual long long decrement_reference_count() override
      //{
      //   return ::user::impact_system::decrement_reference_count();
      //}

   };


} // namespace user






