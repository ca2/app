#pragma once



namespace prompt
{


   class CLASS_DECL_SPHERE department :
      public ::acme::department
   {
   public:


      ::pointer<::user::single_document_template>   m_ptemplateCommandMain;


      department(::object * pobject);
      virtual ~department();


      void construct();


      virtual void init_instance() override;
      virtual void term_instance() override;


      void OnFileManagerOpenFile(::filemanager::data * pdata, ::file::item_array & itema);

   };

} // namespace prompt
