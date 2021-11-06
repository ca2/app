//Created by camilo on 2021-03-26 00:10 BRT <3ThomasBS_
#pragma once
//
////class text;
////class text_data;
////
////class CLASS_DECL_ACME text_translator :
////   virtual public ::object
////{
////public:
////
////   address_array < text* >      m_textaddresa;
////
////
////   text_translator();
////   virtual ~text_translator();
////
////   void translate_text(text* ptext);
////   void translate();
////
////   text create_text(text * ptext);
////   void unregister_text(text* ptext);
////
////   text_data* clone_text_data(const text_data* ptextdata);
////
////};
//
//class CLASS_DECL_ACME text_data
//{
//public:
//
//   bool                 m_bNeedUpdate;
//   ::text_translator *  m_ptexttranslator;
//   ::id                 m_id;
//   string               m_str;
//
//
//   friend class text_translator;
//   text_data(text_translator * ptexttranslator)
//   {
//
//
//   }
//
//};
//
//class CLASS_DECL_ACME text
//{
//public:
//
//
//   ::text_data *           m_ptextdata;
//
//
//   text() { m_ptextdata = nullptr; }
//   text(text&& text) { m_ptextdata = text.m_ptextdata; text.m_ptextdata; }
//   text(const text & text) { m_ptextdata = text.clone(); }
//   ~text() { delete m_ptextdata; }
//
//   text_data* clone() const
//   {
//
//      if (!m_ptextdata)
//      {
//
//         return nullptr;
//
//      }
//
//      return m_ptextdata->m_ptexttranslator->clone_text_data(this);
//
//   }
//
//   void destroy()
//   {
//
//      if (m_ptextdata)
//      {
//
//         delete m_ptextdata;
//
//         m_ptextdata = nullptr;
//
//      }
//
//   }
//
//   text & operator=(const text& text)
//   {
//
//      destroy();
//
//      m_ptextdata = text.m_ptextdata;
//
//      return *this;
//
//   }
//
//};
//
//
//
