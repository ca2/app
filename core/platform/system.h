#pragma once


namespace core
{


   class CLASS_DECL_CORE system :
      virtual public ::bred::system
   {
   public:


      system();
      virtual ~system();

      void common_construct();


      virtual ::e_status initialize(::object * pobject) override;


      virtual void on_add_session(::apex::session * papexsession) override;

      virtual ::e_status initialize_rich_text();

      virtual void InsertTime(::ftp::file_status& ftpFileStatus);
     
   };


} // namespace core




