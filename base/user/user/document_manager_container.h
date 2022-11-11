#pragma once


namespace user
{


   class CLASS_DECL_BASE document_manager_container :
      virtual public ::object
   {
   public:



      // Pointer to ::user::document_manager used to manage document templates
   // for this application instance.
      ::pointer<::user::document_manager>          m_pdocmanager;


      document_manager_container();
      virtual ~document_manager_container();


      ::user::document_manager* document_manager();



      virtual void initialize(::particle * pparticle) override;

      virtual void add_document_template(::user::impact_system* ptemplate);



   };



} // namespace user




