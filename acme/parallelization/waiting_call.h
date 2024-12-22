// Created by camilo on 2024-12-17 20:46 <3ThomasBorregaardSorensen!!
#pragma once


#include "manual_reset_happening.h"


class CLASS_DECL_ACME waiting_call_base :
   virtual public ::particle
{
public:

   bool m_bStarted = false;
   ::task * m_ptask = nullptr;
   class ::time m_timeStart;


   waiting_call_base();
   ~waiting_call_base() override;

   //void set_happening();

   void on_start_call();
   void on_end_or_timeout_call(::e_status estatus);


};


template < typename CALLING >
class waiting_call :
   virtual public ::waiting_call_base
{
public:

   
   CALLING     m_calling;


   waiting_call(const CALLING & calling) :
      m_calling(calling)
   {

   }

   ~waiting_call() override
   {

   }

};



template < typename CALLING >
inline auto as_waiting_call(const CALLING & calling)
{

   auto pwaitingcall = __allocate::waiting_call<CALLING>(calling);

   return ::transfer(pwaitingcall);

}
