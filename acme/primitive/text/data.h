//Created by camilo on 2021-03-26 00:35 BRT <3ThomasBS_
#pragma once


class CLASS_DECL_ACME text_data
{
protected:


   bool                       m_bPendingUpdate;
   text_translator *          m_ptexttranslator;
   ::id                       m_id;
   string                     m_str;

   friend class text_translator;
   friend class text;
   friend class ::acme::context;

   text_data(text_translator* ptexttranslator);
   ~text_data();


};



