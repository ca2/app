// Created by camilo on 2026-07-29 08:52 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
#include "platform.h"


self_test_item::self_test_item(self_test* pselftest, const char* pszName, PSELF_TEST_PROCEDURE pprocedure) :
m_pselftest(pselftest),
m_pszName(pszName),
m_estatusResult(error_not_run)
{

   pselftest->add(this);
   
}


self_test_item::~self_test_item()
{


}


void self_test_item::run_this_and_do_next()
{

   m_estatusResult = run_this();

   if (m_pselftestitemNext)
   {

      m_pselftestitemNext->run_this_and_do_next();

   }

}


::e_status self_test_item::run_this()
{

   m_timeStart.Now();

   ::e_status estatus = error_not_run;

   try
   {

      estatus = on_run_this();

      if (estatus.succeeded())
      {

         information("self test succeeed : \"{}\"", m_pszName);

      }
      else
      {

         information("self test FAILED!! : \"{}\"", m_pszName);

      }

   }
   catch (...)
   {

      information("self test produced exception : \"{}\"", m_pszName);

      estatus = ::error_exception;

   }

   ::information("self test \"{}\" took {} ms", m_pszName, m_timeStart.elapsed().floating_millisecond());

   return estatus;

}


::e_status self_test_item::on_run_this()
{

   if (m_pprocedure)
   {

      return m_pprocedure(this);

   }

   throw ::exception(error_wrong_state);

}
