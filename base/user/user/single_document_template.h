#pragma once


namespace user
{


   class CLASS_DECL_BASE single_document_template :
      virtual public ::user::impact_system
   {
   public:


      __pointer(::user::document) m_pdocument;


      single_document_template(const ::string & pszMatter, ::type pDocClass, ::type pFrameClass, ::type pImpactClass);
      virtual ~single_document_template();

      virtual void add_document(::user::document * pDoc) override;
      virtual void erase_document(::user::document * pDoc) override;
      virtual ::count get_document_count() const override;
      virtual ::user::document * get_document(index index = 0) const override;
      virtual void on_request(::create * pcreate) override;
      virtual void set_default_title(::user::document * pdocument) override;

      virtual void dump(dump_context &) const override;
      void assert_ok() const override;


   };



} // namespace user






