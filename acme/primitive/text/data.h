//Created by camilo on 2021-03-26 00:35 BRT <3ThomasBS_
#pragma once


namespace text
{


   class CLASS_DECL_ACME data
   {
   protected:


      bool                       m_bPendingUpdate;
      translator *               m_ptranslator;
      ::id                       m_id;
      string                     m_str;


      friend class translator;
      friend class text;
      friend class ::acme::context;


      data(translator * ptranslator);
      ~data();


   };


} // namespace text



