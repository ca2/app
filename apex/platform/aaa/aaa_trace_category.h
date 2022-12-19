#pragma once


class CLASS_DECL_APEX trace_category :
   virtual public matter
{
public:


   e_trace_category     m_ecategory;
   string               m_strTopicText;
   bool                 m_bEnable;


   static pointer_array < trace_category > * s_ptracecategorya;

   

   trace_category(e_trace_category etracecategory, const scoped_string & strTopicText) :
      m_ecategory(etracecategory),
      m_strTopicText(pszTopicText)
   {

   }


};

