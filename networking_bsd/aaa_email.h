#pragma once


namespace net
{


   class CLASS_DECL_APEX email :
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


      virtual void initialize(::particle * pparticle) override;


      void prepare_headers();


   };


} // namespace net



