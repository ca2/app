// Created by camilo on 2026-07-29 08:38 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
#pragma once


#include "acme/quality/self_test_item.h"


class CLASS_DECL_ACME self_test
{
public:

   
   class ::time m_timeStart;

   const char* m_pszName;

   self_test_item* m_pselftestitemLast;


   self_test(const char * pszName);
   ~self_test();


   void add(self_test_item* pselftestitem);


   void run();


}; 


CLASS_DECL_ACME self_test* main_self_test();


#define RUN_SELF_TEST(groupid) \
groupid ## _self_test()->run()