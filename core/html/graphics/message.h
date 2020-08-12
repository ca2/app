#pragma once


class form_document;


namespace html
{


   class message :
      public ::message::message
   {
   public:


      ::html_data *                 m_pdata;
      ::message::message *          m_psignal;
      __pointer(::user::interaction)       m_puserinteraction;


      message();


   };


} // namespace html






