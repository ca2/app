//*****************************************************************************
//
//      Class:          manual_reset_happening
//      Author:         Kenny Kerr
//      Date created:   10 April 2004
//      Description:    Notifies one or more waiting threads that an happening has
//                      occurred.
//
//*****************************************************************************


#pragma once


#include "happening.h"


#define DECLARE_REUSABLE(TYPE) \
TYPE * m_pnext; \
::factory_item::reusable_factory_item < TYPE, TYPE > * m_pfactory; \
void delete_this() override { if(m_pfactory) m_pfactory->return_back(this); else delete this;}


class CLASS_DECL_ACME manual_reset_happening :
   public ::happening
{
public:


   //__creatable(manual_reset_happening);


   ::e_status m_estatus;
   // DECLARE_REUSABLE(manual_reset_happening);


   manual_reset_happening(char * sz = nullptr, bool bInitiallyOwn = false);
   ~manual_reset_happening() override;

   //void reuse() { reset_happening(); }

};


class CLASS_DECL_ACME notify_lock :
   virtual public ::particle
{
public:


   manual_reset_happening                 m_manualresethappening;


   ::pointer_array < ::subparticle >      m_synca;

   ~notify_lock() override
   {

      for (auto & psync : m_synca)
      {

         psync->end_notify_lock(this);

      }

   }

};

