#pragma once





class CLASS_DECL_ACME trace_category :
   virtual public particle
{
public:


   enum_trace_category        m_etracecategory;
   string                     m_strTopicText;
   bool                       m_bEnable;


   static pointer_array < trace_category > * s_ptracecategorya;

   

   trace_category(enum_trace_category etracecategory, const ::scoped_string & scopedstrTopicText) :
      m_etracecategory(etracecategory),
      m_strTopicText(scopedstrTopicText)
   {

   }


};

