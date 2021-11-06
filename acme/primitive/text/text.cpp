//Created by camilo on 2021-03-26 00:10 BRT <3ThomasBS_
#include "framework.h"
#include "_.h"


namespace text
{


   text::text()
   {

      m_pdata = nullptr;

   }


   text::text(text&& text)
   {

      m_pdata = text.m_pdata;

      text.m_pdata = nullptr;

   }


   text::text(const text& text)
   {

      m_pdata = text.clone_text_data();

   }


   text::~text()
   {

      destroy();

   }


   text::text(data* pdata) :
      m_pdata(pdata)
   {


   }


   data* text::clone_text_data() const
   {

      auto pdata = m_pdata;

      if (::is_null(pdata))
      {

         return nullptr;

      }

      auto ptranslator = pdata->m_ptranslator;

      return ptranslator->clone_text_data(pdata);

   }


   string text::get_text() const
   {

      if (::is_null(m_pdata))
      {

         return "";

      }

      synchronous_lock lock(m_pdata->m_ptranslator->mutex());

      if (m_pdata->m_bPendingUpdate)
      {

         m_pdata->m_bPendingUpdate = false;

         m_pdata->m_ptranslator->translate_text_data(m_pdata);

      }

      return m_pdata->m_str;

   }


   void text::destroy()
   {

      if (::is_set(m_pdata))
      {

         m_pdata->m_ptranslator->destroy_text_data(m_pdata);

         m_pdata = nullptr;

      }

   }


   text& text::operator = (const text& text)
   {

      if (m_pdata != text.m_pdata)
      {

         destroy();

         m_pdata = text.clone_text_data();

      }

      return *this;

   }


} // namespace text




