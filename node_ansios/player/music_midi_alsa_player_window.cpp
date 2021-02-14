#include "framework.h"


namespace music
{


   namespace midi_alsa
   {


      namespace player
      {


         window::window(sp(::base::application) papp) :
            element(papp)
         {
            m_pcallback = NULL;
         }

         window::~window()
         {
         }

         void window::install_message_handling(::message::dispatch * pinterface)
         {
            ::user::interaction::install_message_handling(pinterface);
            IGUI_WIN_MSG_LINK(MMSG_DONE                        , pinterface, this, &window::_001OnMmsgDone);
            IGUI_WIN_MSG_LINK(::music::midi::player::message_notify_event   , pinterface, this, &window::_001OnNotifyEvent);
            IGUI_WIN_MSG_LINK(WM_USER                          , pinterface, this, &window::_001OnUserMessage);
            IGUI_WIN_MSG_LINK(WM_APP + 3388                    , pinterface, this, &window::_001OnApp3388Message);
         }

         void window::_001OnMmsgDone(::signal_details * pobj)
         {
            SCAST_PTR(::message::base, pbase, pobj);
            if(get_callback() != NULL)
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

         void window::_001OnNotifyEvent(::signal_details * pobj)
         {
            SCAST_PTR(::message::base, pbase, pobj);
            ::music::midi::player::notify_event * pdata = (::music::midi::player::notify_event *) pbase->m_lparam.m_lparam;
            if(get_callback() != NULL)
            {
               get_callback()->OnMidiPlayerNotifyEvent(pdata);
               pbase->set_lresult(0);
            }
            else
            {
               pbase->set_lresult(-1);
            }
            if(pdata != NULL)
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

         void window::_001OnUserMessage(::signal_details * pobj)
         {
            SCAST_PTR(::message::base, pbase, pobj);
            switch(pbase->m_wparam)
            {
            case 3388:
               {
                  // Lyric ::view Event
                  if(get_callback() != NULL)
                  {
                     get_callback()->OnMidiLyricEvent((array<::ikaraoke::lyric_event_v1, ::ikaraoke::lyric_event_v1&> *) pbase->m_lparam.m_lparam);
                     delete (array<::ikaraoke::lyric_event_v1, ::ikaraoke::lyric_event_v1&> *) pbase->m_lparam.m_lparam;
                  }
               }
               break;
            }
            pbase->set_lresult(0);
         }

         void window::_001OnApp3388Message(::signal_details * pobj)
         {
            throw not_implemented(get_app());
            SCAST_PTR(::message::base, pbase, pobj);
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
                  if(get_callback() != NULL)
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


   } // namespace midi_alsa


} // namespace music









