#include "framework.h"


critical_section * g_pcriticalsectionSequence = nullptr;


critical_section * get_sequence_critical_section()
{


   return g_pcriticalsectionSequence;

}


void initialize_sequence_critical_section()
{

   if (!g_pcriticalsectionSequence)
   {

      g_pcriticalsectionSequence = memory_new critical_section();

   }

}


void finalize_sequence_critical_section()
{

   if (g_pcriticalsectionSequence)
   {

      delete g_pcriticalsectionSequence;

      g_pcriticalsectionSequence = nullptr;

   }

}

