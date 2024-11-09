// Created by camilo on day after ThomasBirthday2021 04:44 BRT
#pragma once


class CLASS_DECL_APEX event_source :
   virtual public ::object
{
public:


   pointer< pointer_array < ::event_handler > >    m_phappeninghandlera;


   inline bool has_event_handler() const
   {

      return m_phappeninghandlera && m_phappeninghandlera->has_element();

   }

   virtual void add_event_handler(::event_handler * phandler, bool bPriority = false);

   virtual void route_event(::happening * pevent);


};
