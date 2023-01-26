#pragma once


namespace youtube
{


   class CLASS_DECL_APP_CORE_YOUTUBE application :
      virtual public ::resident::application
   {
   public:



      //::file::path m_strIrcFolder;

      application(::particle * pparticle);
      ~application() override;

      bool initialize_application();
      virtual i32 exit_application() override;
      void on_request(::request * prequest) override;

      void construct();

      virtual ::pointer<comm>create_youtube_comm(::object * pdata);


   };


} // namespace youtube



