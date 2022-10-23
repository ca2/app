#pragma once


#include "acme/primitive/primitive/matter.h"


class CLASS_DECL_ACME trace_category :
   virtual public matter
{
public:


   enum_trace_category        m_etracecategory;
   string                     m_strTopicText;
   bool                       m_bEnable;


   static pointer_array < trace_category > * s_ptracecategorya;

   

   trace_category(enum_trace_category etracecategory, const char * pszTopicText) :
      m_etracecategory(etracecategory),
      m_strTopicText(pszTopicText)
   {

   }


};

