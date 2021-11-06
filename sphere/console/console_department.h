#pragma once


namespace console
{


   class CLASS_DECL_SPHERE department :
      virtual public ::acme::department
   {
   public:


      __pointer(prompt) m_spprompt;


      department(::object * pobject);
      virtual ~department();

      virtual ::e_status init_instance() override;


      inline prompt & console_prompt() { return *m_spprompt; }


      void pre_translate_message(::message::message * pmessage);


      DECLARE_MESSAGE_HANDLER(_001OnImpact);


   };


} // namespace userstack



