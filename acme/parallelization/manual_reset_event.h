//*****************************************************************************
//
//      Class:          manual_reset_event
//      Author:         Kenny Kerr
//      Date created:   10 April 2004
//      Description:    Notifies one or more waiting threads that an event has
//                      occurred.
//
//*****************************************************************************


#pragma once


#define DECLARE_REUSABLE(TYPE) \
TYPE * m_pnext; \
::factory::reusable_factory < TYPE, TYPE > * m_pfactory; \
void delete_this() override { if(m_pfactory) m_pfactory->return_back(this); else delete this;}


class CLASS_DECL_ACME manual_reset_event :
   public ::event
{
public:


   ::e_status m_estatus;
   // DECLARE_REUSABLE(manual_reset_event);


   manual_reset_event(char * sz = nullptr, bool bInitiallyOwn = false);
   ~manual_reset_event() override;

   void reuse() { ResetEvent(); }

};
