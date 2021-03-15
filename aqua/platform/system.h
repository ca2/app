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


      void aqua_construct();


      void common_construct();


      virtual ::e_status initialize(::context_object * pcontextobject) override;


      //virtual ::e_status initialize_rich_text();

      virtual ::xml::xml* _xml();


      virtual ::e_status create_audio();

      virtual ::aqua::audio* defer_get_audio();

      virtual void defer_multimedia();

      virtual ::aqua::multimedia* defer_get_multimedia();


      inline ::aqua::audio * audio() { return m_paudio; }

      inline ::aqua::multimedia * multimedia() { return m_pmultimedia; }



   };


} // namespace aqua




