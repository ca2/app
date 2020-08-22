#pragma once


namespace net
{


   class CLASS_DECL_AURA email :
      virtual public ::object
   {
   public:


      string            m_strSenderName;
      email_address     m_addressSender;
      string            m_strRecipientName;
      email_address     m_addressRecipient;
      string            m_strSubject;
      string            m_strHeaders;
      string            m_strBody;


      email();
      virtual ~email();


      virtual ::estatus initialize(::object * pobjectContext) override;


      void prepare_headers();


   };


} // namespace net



