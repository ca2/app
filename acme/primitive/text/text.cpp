//Created by camilo on 2021-03-26 00:10 BRT <3ThomasBS_
#include "framework.h"
#include "_.h"


text::text()
{
   
   m_ptextdata = nullptr;

}


text::text(text&& text)
{

   m_ptextdata = text.m_ptextdata;
   
   text.m_ptextdata = nullptr;

}


text::text(const text& text)
{
   
   m_ptextdata = text.clone_text_data();

}


text::~text()
{

   destroy();

}


text::text(text_data* ptextdata) :
   m_ptextdata(ptextdata)
{


}


text_data * text::clone_text_data() const
{

   auto ptextdata = m_ptextdata;

   if (::is_null(ptextdata))
   {

      return nullptr;

   }

   auto ptexttranslator = ptextdata->m_ptexttranslator;

   return ptexttranslator->clone_text_data(ptextdata);

}


string text::get_text() const
{

   if (::is_null(m_ptextdata))
   {

      return "";

   }

   synchronous_lock lock(m_ptextdata->m_ptexttranslator->mutex());

   if (m_ptextdata->m_bPendingUpdate)
   {

      m_ptextdata->m_bPendingUpdate = false;

      m_ptextdata->m_ptexttranslator->translate_text_data(m_ptextdata);

   }

   return m_ptextdata->m_str;

}


void text::destroy()
{

   if (::is_set(m_ptextdata))
   {

      m_ptextdata->m_ptexttranslator->destroy_text_data(m_ptextdata);

      m_ptextdata = nullptr;

   }

}


text& text::operator = (const text& text)
{

   if (m_ptextdata != text.m_ptextdata)
   {

      destroy();

      m_ptextdata = text.clone_text_data();

   }

   return *this;

}

