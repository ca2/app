#include "framework.h"


namespace music
{


   namespace midi
   {


      namespace mmsystem
      {


         namespace player
         {


            callback::callback(::layered * pobjectContext) :
               m_wnd(pobject)
            {
            }

            callback::~callback()
            {
            }

            bool callback::initialize()
            {
               if(!m_wnd.create())
                  return false;
               m_wnd.set_callback(this);
               return true;
            }

            bool callback::finalize()
            {
               if(!m_wnd.is_window())
                  return true;
               m_wnd.DestroyWindow();
               return true;
            }


            void callback::OnMmsgDone(::music::midi::sequence *pSeq, ::music::midi::LPMIDIDONEDATA lpmdd)
            {
               UNREFERENCED_PARAMETER(pSeq);
               UNREFERENCED_PARAMETER(lpmdd);
            }

            void callback::OnMidiPlayerNotifyEvent(::music::midi::player::notify_event * pdata)
            {
               switch(pdata->m_enotifyevent)
               {
               case music::midi::player::notify_event_set_sequence:
                  //      pdata->m_pplayer->get_sequence()->m_midicallbackdata.oswindow = m_wnd.GetSafeoswindow_();
                  break;
               }
            }

            void callback::OnMidiLyricEvent(array<::ikaraoke::lyric_event_v1, ::ikaraoke::lyric_event_v1&> * pevents)
            {
               UNREFERENCED_PARAMETER(pevents);
            }


         } // namespace player


      } // namespace mmsystem


   } // namespace midi_mmsystem


} // namespace music









