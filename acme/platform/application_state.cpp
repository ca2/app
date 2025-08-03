//
// Created by camilo on 2025-07-10 00:52 <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "application_state.h"


namespace platform
{

    
    ::pointer<application_state> g_papplicationstate;


   application_state::application_state()
    {


    }


   application_state::~application_state()
    {


    }

   application_state *application_state::get()
    {

       return g_papplicationstate;

    }


    void application_state::set(application_state *papplicationstate)
    {

       g_papplicationstate = papplicationstate;

    }


    void application_state::exchange1()
    {


    }


    void application_state::after_exchange()
    {


    }


    void
    application_state::queue_message_box(::message_box *pmessagebox)
    {

       //synchronous_lock synchronouslock(m_pparticleMutexMessageBoxSequencer);

       synchronous_lock synchronouslock(this->synchronization());

       m_messageboxa.add(pmessagebox);

    }


    ::pointer<::message_box> application_state::pick_message_box()
    {

       //synchronous_lock synchronouslock(m_pparticleMutexMessageBoxSequencer);

       synchronous_lock synchronouslock(this->synchronization());

       if (m_messageboxa.is_empty()) {

          return nullptr;

       }

       auto psequencer = m_messageboxa.pop_first();

       return psequencer;

    }

    
    void application_state::open_url(const ::scoped_string & scopedstrOpenUrl)
    {

       synchronous_lock lock(this->synchronization());

       m_straOpenUrl.add(scopedstrOpenUrl);

    }



   void application_state::list_file_enumerate(const ::scoped_string & scopedstrListFileEnumerate)
   {

   //synchronous_lock lock(m_pparticleMutexListFileEnumerate);
   synchronous_lock lock(this->synchronization());

   m_straListFileEnumerate.add(scopedstrListFileEnumerate);

   }


} // namespace platform



