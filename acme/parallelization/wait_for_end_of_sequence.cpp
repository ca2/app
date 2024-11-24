// Created by camilo on 2024-11-19 01:10 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "wait_for_end_of_sequence.h"
#include "manual_reset_happening.h"
#include "acme/handler/sequence.h"


wait_for_end_of_sequence::wait_for_end_of_sequence(::manual_reset_happening * pmanualresethappeningEndOfSequence, ::sequence * psequence) :
   single_lock(pmanualresethappeningEndOfSequence, false),
   m_psequence(psequence)
{

}


void wait_for_end_of_sequence::on_before_set(const class ::time & wait)
{

   if (m_psequence)
   {
    
      m_psequence->m_timeTimeout = wait;
      m_psequence->m_timeLocked.Now();

   }

}


::e_status wait_for_end_of_sequence::on_set_or_timeout(::e_status estatus)
{

   if (m_psequence)
   {

      m_psequence->m_estatusWait = estatus;

      m_psequence->m_timeSet.Now();

   }

   return estatus;

}


