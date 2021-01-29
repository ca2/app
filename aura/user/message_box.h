//
// Created by camilo on 29/01/2021.  02:05 BRT <3ThomasBS_!!
//


namespace user
{


   class CLASS_DECL_AURA message_box :
      virtual public ::matter
   {
   public:


      string                  m_strText;
      string                  m_strTitle;
      ::e_message_box         m_emessagebox;


      message_box(const string &strText, const string &strTitle, const ::e_message_box &emessagebox);
      virtual ~message_box();


      virtual ::payload realize() override;


   };


} // namespace user


//CLASS_DECL_AURA ::e_status os_message_box(const char * pszMessage, const char * pszTitle = nullptr, const ::e_message_box & emessagebox = e_message_box_ok, const promise::process & process = ::promise::process());



