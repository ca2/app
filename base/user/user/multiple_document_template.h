#pragma once


namespace user
{


   // MDI support (zero or more documents)
   class CLASS_DECL_BASE multiple_document_template :
      virtual public ::user::impact_system
   {
   public:


      __pointer_array(::user::document) m_docptra;          // open documents of this type
      ::u32 m_nUntitledCount;   // start at 0, for "Document1" title


      multiple_document_template(const char * pszMatter, ::type pDocClass, ::type pFrameClass, ::type pViewClass);
      virtual ~multiple_document_template();


      virtual void load_template() override;
      virtual void add_document(::user::document * pDoc) override;
      virtual void erase_document(::user::document * pDoc) override;
      virtual ::count get_document_count() const override;
      virtual ::user::document * get_document(index index) const override;
      virtual void on_request(::create * pcreate) override;
      virtual void set_default_title(::user::document * pdocument) override;

      virtual void dump(dump_context &) const override;
      virtual void assert_valid() const override;

      //virtual i64 add_ref(OBJECT_REF_DEBUG_PARAMS) override
      //{
      //   return ::user::impact_system::add_ref(OBJECT_REF_DEBUG_ARGS);
      //}

      //virtual i64 dec_ref(OBJECT_REF_DEBUG_PARAMS) override
      //{
      //   return ::user::impact_system::dec_ref(OBJECT_REF_DEBUG_ARGS);
      //}

   };


} // namespace user






