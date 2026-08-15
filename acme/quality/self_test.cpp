// Created by camilo on 2026-07-29 08:48 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
#include "platform.h"


CLASS_DECL_ACME self_test* main_self_test()
{
   
   static self_test s_selftestMain("main_self_test");

   return &s_selftestMain;

}


self_test::self_test(const char * pszName) :
   m_pszName(pszName),
   m_pselftestitemLast(nullptr)
{


}

self_test::~self_test()
{


}


void self_test::add(self_test_item* pselftestitem)
{

   pselftestitem->m_pselftestitemNext = m_pselftestitemLast;

   m_pselftestitemLast = pselftestitem;

}


void self_test::run()
{

   m_timeStart.Now();

   if (m_pselftestitemLast)
   {

      m_pselftestitemLast->run_this_and_do_next();

   }

   ::information("test group \"{}\" took {} ms", m_pszName, m_timeStart.elapsed().floating_millisecond());

}


