// Created by camilo on 2024-11-19 01:10 <3ThomasBorregaardSorensen!!
#pragma once


#include "single_lock.h"


class CLASS_DECL_ACME wait_for_end_of_sequence :
   public single_lock
{
public:


   ::sequence *               m_psequence;
   ::waiting_call_base *      m_pwaitingcallbase;


   explicit wait_for_end_of_sequence(manual_reset_happening * phappeningEndOfSequence, ::sequence * psequence, ::waiting_call_base * pwaitingcallbase);

   void on_before_set(const class ::time & wait = ::time::infinity());
   ::e_status on_set_or_timeout(::e_status estatus);
   void _wait() { on_before_set(); single_lock::_wait(); on_set_or_timeout(::success); }
   bool _wait(const class ::time & wait) { on_before_set(wait); return on_set_or_timeout(::single_lock::_wait(wait) ? ::success : ::error_wait_timeout); }
   ::e_status wait() { on_before_set(); return on_set_or_timeout(single_lock::wait()); }
   ::e_status wait(const class ::time & wait = ::time::infinity()) { on_before_set(wait); return on_set_or_timeout(single_lock::wait(wait)); }
   void _lock() { on_before_set(); single_lock::_lock(); on_set_or_timeout(::success); }
   bool lock(const class ::time & wait = ::time::infinity()) { on_before_set(wait); return on_set_or_timeout(::single_lock::lock(wait) ? ::success : ::error_wait_timeout); }


};




