#include "framework.h"


namespace music
{


   namespace midi
   {


      namespace mmsystem
      {


         namespace player
         {


            window::window(::object * pobject) :
               ::object(pobject)
            {
               m_pcallback = nullptr;
            }

            window::~window()
            {
            }

            void window::install_message_routing(::channel * pchannel)
            {
               ::user::interaction::install_message_routing(pchannel);
               MESSAGE_LINK(MMSG_DONE, pchannel, this, &window::_001OnMmsgDone);
               MESSAGE_LINK(::music::midi::player::message_notify_event, pchannel, this, &window::_001OnNotifyEvent);
               MESSAGE_LINK(WM_USER, pchannel, this, &window::_001OnUserMessage);
               MESSAGE_LINK(WM_APP + 3388, pchannel, this, &window::_001OnApp3388Message);
            }

            void window::_001OnMmsgDone(::message::message * pmessage)
            {
               __pointer(::user::message) pusermessage(pmessage);
               if(get_callback() != nullptr)
               {
                  ::music::midi::sequence * pseq = (::music::midi::sequence *) pusermessage->m_wparam;
                  ::music::midi::LPMIDIDONEDATA lpmdd = (::music::midi::LPMIDIDONEDATA) pusermessage->m_lparam.m_lparam;


                  get_callback()->OnMmsgDone(pseq, lpmdd);
                  pusermessage->set_lresult(0);
               }
               else
               {
                  pusermessage->set_lresult(-1);
               }
            }

            void window::_001OnNotifyEvent(::message::message * pmessage)
            {
               __pointer(::user::message) pusermessage(pmessage);
               ::music::midi::player::notify_event * pdata = (::music::midi::player::notify_event *) pusermessage->m_lparam.m_lparam;
               if(get_callback() != nullptr)
               {
                  get_callback()->OnMidiPlayerNotifyEvent(pdata);
                  pusermessage->set_lresult(0);
               }
               else
               {
                  pusermessage->set_lresult(-1);
               }
               if(pdata != nullptr)
                  delete pdata;
            }


            ::music::midi::player::callback_interface * window::get_callback()
            {
               return m_pcallback;
            }

            void window::set_callback(::music::midi::player::callback_interface *pcallback)
            {
               m_pcallback = pcallback;
            }


            bool window::create()
            {
               if(!create_message_queue("::ca2::music::music::midiwindow"))
               {
                  return false;
               }
               return true;
            }

            void window::_001OnUserMessage(::message::message * pmessage)
            {
               __pointer(::user::message) pusermessage(pmessage);
               switch(pusermessage->m_wparam)
               {
               case 3388:
               {
                  // Lyric ::view Event
                  if(get_callback() != nullptr)
                  {
                     get_callback()->OnMidiLyricEvent((array<::ikaraoke::lyric_event_v1, ::ikaraoke::lyric_event_v1&> *) pusermessage->m_lparam.m_lparam);
                     delete (array<::ikaraoke::lyric_event_v1, ::ikaraoke::lyric_event_v1&> *) pusermessage->m_lparam.m_lparam;
                  }
               }
               break;
               }
               pusermessage->set_lresult(0);
            }

            void window::_001OnApp3388Message(::message::message * pmessage)
            {
               __throw(error_not_implemented);
               __pointer(::user::message) pusermessage(pmessage);
               /*            MSG msg;

               while(PeekMessage(
               &msg,
               get_handle(),
               WM_APP + 3388,
               WM_APP + 3388,
               PM_REMOVE))
               {
               if(pusermessage->m_wparam == 3388)
               {
               delete (array<::ikaraoke::lyric_event_v1, ::ikaraoke::lyric_event_v1&> * ) pusermessage->m_lparam.m_lparam;
               }

               pusermessage->m_wparam = msg.wParam;
               pusermessage->m_lparam = msg.lParam;
               }
               switch(pusermessage->m_wparam)
               {
               case 3388:
               {
               // Lyric ::view Event
               if(get_callback() != nullptr)
               {
               get_callback()->OnMidiLyricEvent((array<::ikaraoke::lyric_event_v1, ::ikaraoke::lyric_event_v1&> *) pusermessage->m_lparam.m_lparam);
               delete (array<::ikaraoke::lyric_event_v1, ::ikaraoke::lyric_event_v1&> *) pusermessage->m_lparam.m_lparam;
               }
               }
               break;
               }*/

               pusermessage->set_lresult(0);
            }


         } // namespace player


      } // namespace mmsystem


   } // namespace midi_mmsystem


} // namespace music









