//
// Created by camilo on 2025-07-10 00:52 <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "driver.h"


namespace acme
{

    
    ::pointer<driver> g_pandroiddriver;


    driver::driver()
    {


    }


    driver::~driver()
    {


    }

    driver *driver::get()
    {

       return g_pandroiddriver;

    }


    void driver::set(driver *pdriver)
    {

       g_pandroiddriver = pdriver;

    }


    void driver::exchange1()
    {


    }


    void driver::after_exchange()
    {


    }


    void
    driver::queue_message_box(::message_box *pmessagebox)
    {

       //synchronous_lock synchronouslock(m_pparticleMutexMessageBoxSequencer);

       synchronous_lock synchronouslock(this->synchronization());

       m_messageboxa.add(pmessagebox);

    }


    ::pointer<::message_box> driver::pick_message_box()
    {

       //synchronous_lock synchronouslock(m_pparticleMutexMessageBoxSequencer);

       synchronous_lock synchronouslock(this->synchronization());

       if (m_messageboxa.is_empty()) {

          return nullptr;

       }

       auto psequencer = m_messageboxa.pop_first();

       return psequencer;

    }

    
    void driver::open_url(const ::scoped_string & scopedstrOpenUrl)
    {

       synchronous_lock lock(this->synchronization());

       m_straOpenUrl.add(scopedstrOpenUrl);

    }



   void driver::list_file_enumerate(const ::scoped_string & scopedstrListFileEnumerate)
   {

   //synchronous_lock lock(m_pparticleMutexListFileEnumerate);
   synchronous_lock lock(this->synchronization());

   m_straListFileEnumerate.add(scopedstrListFileEnumerate);

   }


} // namespace acme



