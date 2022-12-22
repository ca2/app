//Created by camilo on 2021-03-26 00:10 BRT <3ThomasBS_
#include "framework.h"
#include "text.h"
#include "translator.h"
#include "acme/parallelization/synchronous_lock.h"


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


   ::string text::defer_update_text() const
   {

      if (::is_null(m_pdata))
      {

         return {};

      }

      if (m_pdata->m_bPendingUpdate)
      {

         m_pdata->m_bPendingUpdate = false;

         if(m_pdata->m_ptranslator)
         {

            synchronous_lock lock(m_pdata->m_ptranslator->synchronization());

            m_pdata->m_ptranslator->translate_text_data(m_pdata);

         }
         else
         {

            string strText = m_pdata->m_atom;

            auto find = strText.find_index("://");

            if(find < 0)
            {

               find = 0;

            }
            else
            {

               find += 3;

               auto find1 = strText(find).find_index("/");

               if(find1 > find)
               {

                  find = find1 + 1;

                  find1 = strText(find).find_index("/");

                  if(find1 > find)
                  {

                     find = find1 + 1;

                  }

               }

            }

            m_pdata->m_str = strText.substr(find);

         }

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




