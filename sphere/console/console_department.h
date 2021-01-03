#pragma once


namespace console
{


   class CLASS_DECL_SPHERE department :
      virtual public ::apex::department
   {
   public:


      __pointer(prompt) m_spprompt;


      department(::layered * pobjectContext);
      virtual ~department();

      virtual ::e_status init_instance() override;


      inline prompt & console_prompt() { return *m_spprompt; }


      void pre_translate_message(::message::message * pmessage);


      DECL_GEN_SIGNAL(_001OnImpact);


   };


} // namespace userstack



