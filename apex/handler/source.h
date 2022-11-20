// Created by camilo on day after ThomasBirthday2021 04:44 BRT
#pragma once


//#include "acme/primitive/primitive/object.h"


/// source is originator of subjects
class CLASS_DECL_APEX source :
   virtual public ::object
{
public:


   pointer < comparable_array < ::signal_handler > > m_psignalhandlera;


   source();
   ~source() override;


   inline bool has_handler() const
   {

      return m_psignalhandlera && m_psignalhandlera->has_element();

   }

   virtual void add_signal_handler(const ::signal_handler& signalhandler, bool bPriority = false);

   virtual void add_handler(::matter * pmatter, bool bPriority = false);

   void route(::topic * ptopic, ::context * pcontext = nullptr);

   //void signal(::topic * ptopic, ::context * pcontext) override;


};
