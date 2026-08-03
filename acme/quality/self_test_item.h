// Created by camilo on 2026-07-29 08:36 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
#pragma once


#define SELF_TEST(groupid, name) \
class self_test_item_ ## name :                               \
   public self_test_item                               \
{                               \
public:                                 \
   using self_test_item:: self_test_item;                 \
   ::e_status on_run_this() override;              \
};              \
self_test_item_ ## name g_selftestitem ## name(groupid ## _self_test(), #name);      \
::e_status self_test_item_ ## name::on_run_this()


class self_test;
class self_test_item;


typedef ::e_status SELF_TEST_PROCEDURE(self_test_item * pselftestitem);
using PSELF_TEST_PROCEDURE = SELF_TEST_PROCEDURE *;


class self_test_item
{
public:


   class ::time m_timeStart;
   PSELF_TEST_PROCEDURE m_pprocedure;
   self_test_item* m_pselftestitemNext;
   self_test* m_pselftest;
   const char* m_pszName;
   ::e_status m_estatusResult;


   self_test_item(self_test* pselftest, const char* pszName, PSELF_TEST_PROCEDURE pprocedure = nullptr);
   ~self_test_item();


   virtual void run_this_and_do_next();

   virtual ::e_status run_this();

   virtual ::e_status on_run_this();


};



