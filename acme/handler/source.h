// Created by camilo on day after ThomasBirthday2021 04:44 BRT
#pragma once


////#include "acme/prototype/prototype/object.h"


/// source is originator of subjects
class CLASS_DECL_ACME source :
   virtual public ::particle
{
public:


   pointer_array < ::particle >     m_particlea;


   source();
   ~source() override;


   void destroy() override;

   inline bool has_handler() const
   {

      return m_particlea.has_element();

   }

//   virtual void add_signal_handler(const ::signal_handler& signalhandler, bool bPriority = false);

   virtual void add_handler(::particle * pmatter, bool bPriority = false);

   virtual void route(::topic * ptopic, ::handler_context * phandlercontext = nullptr);

   virtual void on_topic(const ::atom & atom, ::particle * pparticle = nullptr, ::handler_context * pcontext = nullptr);

   virtual void notify_topic(const ::atom & atom, ::particle * pparticle = nullptr, ::handler_context * pcontext = nullptr);

   //void signal(::topic * ptopic, ::handler_context * phandlercontext) override;


};
