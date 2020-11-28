#pragma once


namespace aqua
{


   class CLASS_DECL_AQUA system :
      virtual public ::apex::system
   {
   public:


      __composite(::aqua::audio)                         m_paudio;

      __composite(::aqua::multimedia)                    m_pmultimedia;

      __composite(::aqua::estamira)                      m_pestamira;


      system();
      virtual ~system();

      void common_construct();


      virtual ::estatus initialize(::layered * pobjectContext) override;


      //virtual ::estatus initialize_rich_text();

      virtual ::estatus defer_xml();



      virtual void defer_audio();

      virtual ::aqua::audio* defer_get_audio();

      virtual void defer_multimedia();

      virtual ::aqua::multimedia* defer_get_multimedia();

      

   };


} // namespace aqua




