// Created by camilo on day after ThomasBirthday2021 04:44 BRT
#pragma once


/// source is originator of subjects
class CLASS_DECL_APEX source :
   virtual public ::object
{
public:


   __pointer(__pointer_array(::matter))    m_phandlera;


   inline bool has_handler() const
   {

      return m_phandlera && m_phandlera->has_element();

   }

   virtual void add_handler(::matter * pmatter, bool bPriority = false);

   void route(::topic * ptopic, ::context * pcontext = nullptr);

   //void signal(::topic * ptopic, ::context * pcontext) override;


};
