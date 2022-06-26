//Created by camilo on 2021-03-26 00:10 BRT <3ThomasBS_
#pragma once


#include "data.h"


namespace text
{


   class CLASS_DECL_ACME text
   {
   public:


      data * m_pdata;


      text();
      text(text&& text);
      text(const text& text);
      text(data * ptextdata);
      ~text(); 

      inline string get_text() const { return ::is_set(m_pdata) ? ((m_pdata->m_bPendingUpdate) ? defer_update_text() : m_pdata->m_str) : ::string(); }

      inline string defer_update_text() const;

      void destroy();

      text& operator = (const text& text);

   protected:

      data * clone_text_data() const;


   };


} // namespace text



