#include "framework.h"


namespace music
{


   namespace midi
   {


      namespace mmsystem
      {


         namespace player
         {


            player_interface::player_interface(::layered * pobjectContext) :
               ::object(pobject),
               callback(pobject),
               ::music::midi::player::player_interface(pobject)

            {
               m_psection = nullptr;
               m_pmidiplayer = nullptr;
            }

            player_interface::~player_interface()
            {

            }

            bool player_interface::Initialize(__pointer(::music::midi::midi) pcentral)
            {

               if(!initialize())
                  return false;

               m_psection = pcentral;

               return true;
            }


            bool player_interface::Finalize()
            {

               if(!finalize())
                  return false;

               return true;
            }


            bool player_interface::OpenMidiPlayer()
            {
               try
               {
                  m_pmidiplayer = dynamic_cast < ::music::midi::player::player * > (__begin_thread < player >(
                                  get_context_application(),
                                  ::aura::scheduling_priority_normal,
                                  0,
                                  CREATE_SUSPENDED));
               }
               catch(memory_exception *pe)
               {
                  System.message_box(nullptr, _T("No memory to perform this operation." ));
                  ::exception_pointer esp(pe);
                  return false;
               }

               m_pmidiplayer->SetMidiCentral(m_psection);

               m_pmidiplayer->SetCallbackWindow(&m_wnd);

               if(failed(m_pmidiplayer->Initialize(GetMidiPlayerCallbackThread())))
               {

                  return false;

               }



               if(!OnOpenMidiPlayer())
               {
                  return false;
               }
               m_pmidiplayer->ResumeThread();
               m_pmidiplayer->m_evInitialized.wait();
               return true;
            }

            bool player_interface::OnOpenMidiPlayer()
            {
               GetMidiPlayer()->SetInterface(this);
               m_wnd.set_callback(m_composite);
               return true;
            }


            // Event handling
            void player_interface::OnMidiPlayerNotifyEvent(::music::midi::player::notify_event * pdata)
            {
               callback::OnMidiPlayerNotifyEvent(pdata);
               switch(pdata->m_enotifyevent)
               {
               case music::midi::player::notify_event_set_sequence:
                  //      pdata->m_pplayer->get_sequence()->m_midicallbackdata.lpThreadV1 = GetMidiPlayerCallbackThread();
                  break;
               }

            }


         } // namespace player


      } // namespace mmsystem


   } // namespace midi_mmsystem


} // namespace music









