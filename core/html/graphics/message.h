#pragma once


class form_document;


namespace html
{


   class message :
      public ::message::message
   {
   public:


      __pointer(::html_data)              m_phtmldata;
      __pointer(::message::message)       m_pmessage;
      __pointer(::user::interaction)      m_puserinteraction;


      message();


   };


} // namespace html






