// Created by camilo on day after ThomasBirthday2021 04:44 BRT
#pragma once


////#include "acme/primitive/primitive/object.h"


/// source is originator of subjects
class CLASS_DECL_ACME source :
   virtual public ::object
{
public:


   pointer_array < ::particle >     m_particlea;


   source();
   ~source() override;


   inline bool has_handler() const
   {

      return m_particlea.has_element();

   }

//   virtual void add_signal_handler(const ::signal_handler& signalhandler, bool bPriority = false);

   virtual void add_handler(::particle * pmatter, bool bPriority = false);

   void route(::topic * ptopic, ::context * pcontext = nullptr);

   void on_topic(const ::atom & atom, ::particle * pparticle = nullptr, ::context * pcontext = nullptr);

   void notify_topic(const ::atom & atom, ::particle * pparticle = nullptr, ::context * pcontext = nullptr);

   //void signal(::topic * ptopic, ::context * pcontext) override;


};
