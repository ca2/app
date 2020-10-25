#include "framework.h"


namespace music
{


   namespace midi
   {


      namespace mmsystem
      {


         namespace player
         {


            window::window(::layered * pobjectContext) :
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
               SCAST_PTR(::message::base, pbase, pmessage);
               if(get_callback() != nullptr)
               {
                  ::music::midi::sequence * pseq = (::music::midi::sequence *) pbase->m_wparam;
                  ::music::midi::LPMIDIDONEDATA lpmdd = (::music::midi::LPMIDIDONEDATA) pbase->m_lparam.m_lparam;


                  get_callback()->OnMmsgDone(pseq, lpmdd);
                  pbase->set_lresult(0);
               }
               else
               {
                  pbase->set_lresult(-1);
               }
            }

            void window::_001OnNotifyEvent(::message::message * pmessage)
            {
               SCAST_PTR(::message::base, pbase, pmessage);
               ::music::midi::player::notify_event * pdata = (::music::midi::player::notify_event *) pbase->m_lparam.m_lparam;
               if(get_callback() != nullptr)
               {
                  get_callback()->OnMidiPlayerNotifyEvent(pdata);
                  pbase->set_lresult(0);
               }
               else
               {
                  pbase->set_lresult(-1);
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
               SCAST_PTR(::message::base, pbase, pmessage);
               switch(pbase->m_wparam)
               {
               case 3388:
               {
                  // Lyric ::view Event
                  if(get_callback() != nullptr)
                  {
                     get_callback()->OnMidiLyricEvent((array<::ikaraoke::lyric_event_v1, ::ikaraoke::lyric_event_v1&> *) pbase->m_lparam.m_lparam);
                     delete (array<::ikaraoke::lyric_event_v1, ::ikaraoke::lyric_event_v1&> *) pbase->m_lparam.m_lparam;
                  }
               }
               break;
               }
               pbase->set_lresult(0);
            }

            void window::_001OnApp3388Message(::message::message * pmessage)
            {
               __throw(not_implemented());
               SCAST_PTR(::message::base, pbase, pmessage);
               /*            MSG msg;

               while(PeekMessage(
               &msg,
               get_handle(),
               WM_APP + 3388,
               WM_APP + 3388,
               PM_REMOVE))
               {
               if(pbase->m_wparam == 3388)
               {
               delete (array<::ikaraoke::lyric_event_v1, ::ikaraoke::lyric_event_v1&> * ) pbase->m_lparam.m_lparam;
               }

               pbase->m_wparam = msg.wParam;
               pbase->m_lparam = msg.lParam;
               }
               switch(pbase->m_wparam)
               {
               case 3388:
               {
               // Lyric ::view Event
               if(get_callback() != nullptr)
               {
               get_callback()->OnMidiLyricEvent((array<::ikaraoke::lyric_event_v1, ::ikaraoke::lyric_event_v1&> *) pbase->m_lparam.m_lparam);
               delete (array<::ikaraoke::lyric_event_v1, ::ikaraoke::lyric_event_v1&> *) pbase->m_lparam.m_lparam;
               }
               }
               break;
               }*/

               pbase->set_lresult(0);
            }


         } // namespace player


      } // namespace mmsystem


   } // namespace midi_mmsystem


} // namespace music









