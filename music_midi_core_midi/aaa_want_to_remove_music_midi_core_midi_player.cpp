#include "framework.h"


namespace music
{
   
   
   namespace midi
   {
      
      
      namespace core_midi
      {
         


         player::player(::context_object * pcontextobject) :
            object(pobject),
            thread(pobject),
            ::music::midi::player::player(pobject)
         {

            m_psequencethread = __new(sequence_thread(this));
            
            
            m_psequencethread->begin();

            m_puie               = nullptr;

         }

         player::~player()
         {

         }


         bool player::init_thread()
         {

            m_psequencethread->ResumeThread();

            TRACE("player::init_instance %X\n", get_os_int());
            //SetMainWnd(nullptr);
            //ASSERT(GetMainWnd() == nullptr);

            set_thread_priority(::priority_normal);

            m_evInitialized.SetEvent();

            return true;

         }


         void player::term_thread()
         {
            // TODO:  perform any per-thread cleanup here
            //   if(!get_sequence()->IsNull())
            //   {
            //      delete get_sequence();
            //   }
            //    if(m_pmidicallbackdata != nullptr)
            //  {
            //    delete m_pmidicallbackdata;
            ///  m_pmidicallbackdata = nullptr;
            //}

            thread::term_thread();

         }


         void player::install_message_routing(::channel * pchannel)
         {
            ::music::midi::player::player::install_message_routing(pchannel);
            //MESSAGE_LINK(MM_MOM_DONE, pchannel, this, &player::OnMultimediaMidiOutputMessageDone);
            //MESSAGE_LINK(MM_MOM_POSITIONCB, pchannel, this, &player::OnMultimediaMidiOutputMessagePositionCB);
         }

//         bool player::Play(imedia_time tkStart, u32 dwEllapse)
//         {
//
//            auto pcommand = __new(player_command(this));
//
//            pcommand->m_ecommand = command_play;
//            pcommand->m_dwEllapse = dwEllapse;
//            pcommand->m_flags.add(player_command::flag_ticks);
//            pcommand->m_ticks = tkStart;
//
//            m_psequencethread->ExecuteCommand(pcommand);
//
//            bool bFinished = pcommand->wait_ready();
//
//            pcommand->release();
//
//            return bFinished;
//         }
//
//         bool player::PlayRate(double dRate, u32 dwEllapse)
//         {
//
//            auto pcommand = __new(player_command(this));
//
//            pcommand->m_ecommand = player_command::command_play;
//            pcommand->m_dwEllapse = dwEllapse;
//            pcommand->m_flags.add(::music::midi::player::command::flag_dRate);
//            pcommand->m_dRate = dRate;
//
//            m_psequencethread->ExecuteCommand(pcommand);
//
//            bool bFinished = pcommand->wait_ready();
//
//            pcommand->release();
//
//            return bFinished;
//
//         }
//
//         imedia_time player::RateToTicks(double dRate)
//         {
//            ASSERT(dRate >= 0.0);
//            ASSERT(dRate <= 1.0);
//            return (imedia_time) (i32) (get_sequence()->m_tkLength * dRate);
//         }



         bool player::IsPlaying()
         {
            ASSERT(!get_sequence()->IsNull());
            return (bool) get_sequence()->IsPlaying();

         }

//         bool player::ExecuteCommand(::music::midi::player::enum_command ecommand, u32 dwEllapse)
//         {
//
//            ::music::midi::player::command * pcommand = new ::music::midi::player::command(this);
//
//            pcommand->m_ecommand = ecommand;
//            pcommand->m_dwEllapse = dwEllapse;
//
//            m_psequencethread->ExecuteCommand(pcommand);
//
//            bool bFinished = pcommand->wait_ready();
//
//            pcommand->release();
//
//            return bFinished;
//         }


//         void player::close_file()
//         {
//            ::e_status                estatus;
//            if(::failed(estatus = get_sequence()->close_file()) &&
//                  estatus != ::error_unsupported_function)
//            {
//               __throw(::exception::exception(multimedia::exception_music, error_midi_player_close));
//            }
//         }

         void player::pause()
         {
            if (get_sequence()->get_state() == sequence::e_state_paused)
            {
               get_sequence()->Restart();
            }
            else
            {
               get_sequence()->Pause();
            }

         }

         void player::SetPosition(double dRate)
         {
            if (sequence::e_state_playing != get_sequence()->get_state() &&
                  sequence::e_state_stopping != get_sequence()->get_state() &&
                  sequence::e_state_opened != get_sequence()->get_state())
               return;

            if(get_sequence()->IsPlaying())
            {
               auto & link = get_sequence()->GetPlayerLink();
               link() |= sequence::e_flag_setting_position;
               link.m_tkRestart = RateToTicks(dRate);
               get_sequence()->Stop();
            }

         }

         void player::OnMmsgDone(::music::midi::sequence * pSeq)
         {
            ASSERT(false);
            ASSERT(false);
            ASSERT(false);
            ASSERT(false);
            ASSERT(false);
            ASSERT(false);
            ASSERT(false);
            ASSERT(false);
            ASSERT(pSeq == get_sequence());
            if(pSeq->IsSettingPosition())
            {
               get_sequence()->SetSettingPositionFlag(false);
               try
               {
                  //         PrerollAndWait(m_dNextPositionRate);
               }
               catch(const ::exception::exception & e)
               {
                  return;
               }
               get_sequence()->Start();
            }
            else
            {
            }

         }

         void player::pre_translate_message(::message::message * pmessage)
         {
            //__pointer(::user::message) pusermessage(pmessage);
            //ASSERT(GetMainWnd() == nullptr);
            //   if(pMsg->message == MM_MOM_DONE ||
            //      pMsg->message == MM_MOM_POSITIONCB ||
            //      pMsg->message == MM_MOM_OPEN ||
            //      pMsg->message == MM_MOM_OPEN)
            //   {
            //      OnMidiOutMessage(pMsg->message, pMsg->wParam, pMsg->lParam);
            //      return true;
            //   }
//            if(pusermessage->m_puserinteraction == nullptr)
//            {
//               switch(pusermessage->m_id)
//               {
//               case WM_USER + 100:
//               {
//                  LPDOUBLESTRUCT lpds = (LPDOUBLESTRUCT) pusermessage->m_wparam;
//                  SetPosition(lpds->d);
//                  delete lpds;
//               }
//               return;
//               }
//            }
//            if(pusermessage->m_id == MMSG_DONE)
//            {
//               OnMmsgDone((::music::midi::sequence *) pusermessage->m_wparam);
//               pusermessage->m_bRet = true;
//               return;
//            }
//            else if(pusermessage->m_id == WM_USER)
//            {
//               //      OnUserMessage(pMsg->wParam, pMsg->lParam);
//            }
            return thread::pre_translate_message(pmessage);
         }

//         void player::SaveFile(const char * lpszPathName)
//         {
//            ::e_status                estatus;
//            if(::music::failed(estatus = get_sequence()->SaveFile(lpszPathName)) )
//            {
//               __throw(multimedia::exception(multimedia::exception_music, ::music::error_midi_player_save));
//            }
//
//         }


         void player::OnUserMessage(::message::message * pmessage)
         {
            __pointer(::user::message) pusermessage(pmessage);
            if(pusermessage->m_wparam == 3377)
            {
               m_puie->send_message(WM_USER, pusermessage->m_wparam, pusermessage->m_lparam);
            }

         }


//         void player::PostGMReset()
//         {
//            m_psequencethread->PostGMReset();
//         }
//
//         void player::PostTempoChange()
//         {
//            m_psequencethread->PostTempoChange();
//         }
//
//         void player::SendTempoChange()
//         {
//            m_psequencethread->SendTempoChange();
//         }


         ::e_status     player::Initialize(thread * pthread)
         {
            UNREFERENCED_PARAMETER(pthread);
            return ::success;
         }

         //void player::SetView(CXfplayerView *pview)
         //{
         //    m_pView = pview;
         //}

//         ::e_status     player::SetInterface(player_interface * pinterface)
//         {
//            m_pinterface = pinterface;
//            get_sequence()->m_pthread   = m_psequencethread;
//            m_psequencethread->m_psequence = get_sequence();
//            m_psequencethread->m_pplayer = this;
//            PostNotifyEvent(notify_event_set_sequence);
//            return ::success;
//         }
//
//
//


//         ::e_status     player::set_client(player_client * pclient)
//         {
//
//            m_pclient = pclient;
//
//            get_sequence()->m_pthread   = m_psequencethread;
//
//            m_psequencethread->m_psequence = get_sequence();
//
//            m_psequencethread->m_pplayer = this;
//
//            PostNotifyEvent(notify_event_set_sequence);
//
//            return ::success;
//
//         }
//
//
//
//         bool player::SetMidiOutDevice(u32 uiDevice)
//         {
//            UNREFERENCED_PARAMETER(uiDevice);
//            OnMidiOutDeviceChange();
//            return true;
//         }
//


         bool player::SetTempoShift(i32 iTempoShift)
         {
            //   if(IsPlaying())
            {
               /*
                get_sequence()->SetTempoChangeFlag();
                sequence::PlayerLink & link = get_sequence()->GetPlayerLink();
                link.ModifyFlag(
                sequence::e_flag_tempo_change,
                sequence::e_flag_null);
                imedia_time tk = get_sequence()->GetPositionTicks();
                get_sequence()->m_evMmsgDone.ResetEvent();
                link.m_tkRestart = tk + get_sequence()->m_tkBase;
                //m_bChangingTempo = true;
                get_sequence()->Stop();
                //get_sequence()->m_evMmsgDone.lock();
                */

               bool bPlay = IsPlaying();

               imedia_time ticks = 0;

               if(bPlay)
               {

                  ticks = get_sequence()->get_position_ticks();

                  get_sequence()->Stop();

               }

               if(!get_sequence()->SetTempoShift(iTempoShift))
               {

                  return false;

               }

               if(bPlay)
               {
                  get_sequence()->m_pthread->PrerollAndWait(ticks);
                  get_sequence()->Start();
               }

            }
            return true;
         }


//         void player::PostNotifyEvent(::music::midi::player::e_notify_event eevent)
//         {
//            if(m_puie != nullptr)
//            {
//               __pointer(::music::midi::player::notify_event) pdata(__new(::music::midi::player::notify_event));
//               pdata->m_pplayer = this;
//               pdata->m_enotifyevent = eevent;
//               m_puie->post_object(::music::midi::player::message_notify_event, 0, pdata);
//            }
//         }

//         void player::SendMmsgDone(::music::midi::sequence *pSeq, ::music::midi::LPMIDIDONEDATA lpmdd)
//         {
//            if(m_puie != nullptr)
//            {
//               m_puie->post_message(MMSG_DONE, (WPARAM) pSeq, (LPARAM) lpmdd);
//            }
//
//         }

//         u32 player::GetMidiOutDevice()
//         {
//
//            return papplication->midi()->GetMidiOutDevice();
//         }


         void player::on_attribute_change(::message::message * pmessage)
         {
            __pointer(::music::midi::attribute_message) pchange(pmessage);

            switch(pchange->m_eattribute)
            {
            case ::music::midi::attribute_midi_out_device:
               OnMidiOutDeviceChange();
               break;
            }

         }


         void player::OnMidiOutDeviceChange()
         {

            ::music::midi::player::OnMidiOutDeviceChange();

            if(get_sequence()->IsPlaying())
            {

               imedia_time tkPosition = 0;

               get_sequence()->get_position(tkPosition);

               auto & link = get_sequence()->GetPlayerLink();

               link() |= sequence::e_flag_tempo_change;

               link.m_tkRestart = tkPosition;

               get_sequence()->Stop();

            }

         }


         void player::OnMultimediaMidiOutputMessageDone(::message::message * pmessage)
         {

            UNREFERENCED_PARAMETER(pmessage);
//            __pointer(::user::message) pusermessage(pmessage);

            /*seq_context_t * pseq = (seq_context_t *) pusermessage->m_wparam;

             LPMIDIHDR lpmidihdr = (LPMIDIHDR) pusermessage->m_lparam.m_lparam;

             __pointer(sequence) sequence = get_sequence();

             ASSERT(sequence->m_pseq == pseq);

             sequence->OnDone(pseq, lpmidihdr);*/

         }

//         void player::OnMultimediaMidiOutputMessagePositionCB(::message::message * pmessage)
//         {
//            UNREFERENCED_PARAMETER(pmessage);
////            __pointer(::user::message) pusermessage(pmessage);
//            /*            LPMIDIHDR lpmidihdr = (LPMIDIHDR) pusermessage->m_wparam;
//             //          get_sequence()->OnPositionCB(lpmidihdr);
//
//             __pointer(sequence) sequence = get_sequence();
//
//             //            ASSERT(sequence->m_hstream == hmidistream);
//
//             sequence->OnPositionCB(lpmidihdr);*/
//         }
//
//
//

//         void player::OnNotifyEvent(::message::message * pmessage)
//         {
//            __pointer(::user::message) pusermessage(pmessage);
//            __pointer(::music::midi::player::notify_event) pdata(pusermessage->m_lparam);
//            pdata->m_pplayer = this;
//            if(m_puie != nullptr)
//            {
//               m_puie->post_object(::music::midi::player::message_notify_event, 0, pdata);
//            }
//         }




//         void player::SendReset()
//         {
//            /*            HMIDIOUT hmidiout = nullptr;
//             ::e_status     estatus;
//             u32 uDeviceID = 0;
//             estatus = midiOutOpen(&hmidiout, uDeviceID,  0, 0, CALLBACK_NULL);
//             if(estatus != ::success)
//             return;
//             sleep(300_ms);
//             const uchar gmModeOn[] = {
//             //        0x00, 0x00, 0x00, 0x00,
//             //        0x00, 0x00, 0x00, 0x00,
//             //        0x1b, 0x8a, 0x06, MEVT_TEMPO,
//             0x00, 0x00, 0x00, 0x00,
//             0x00, 0x00, 0x00, 0x00,
//             0x06, 0x00, 0x00, MEVT_LONGMSG,
//             0xf0, 0x7e, 0x7f, 0x09,
//             0x01, 0xf7, 0x00, 0x00};
//             //        0x70, 0x01, 0x00, 0x00,
//             //      0x00, 0x00, 0x00, 0x00 };
//             //      0x09, 0x00, 0x00, MEVT_LONGMSG,
//             //      0x43, 0x10, 0x4c,
//             //    0x00, 0x00, 0x7e, 0x00,
//             //  0xf7, 0x00, 0x00, 0x00,};
//             MIDIHDR mh;
//             LPMIDIHDR lpmh = &mh;
//             lpmh->lpData = (char *) gmModeOn;
//             lpmh->dwBufferLength = sizeof(gmModeOn);
//             lpmh->dwBytesRecorded = 0;
//             lpmh->dwFlags = 0;
//             estatus = midiOutPrepareHeader( hmidiout, lpmh, sizeof(MIDIHDR));
//             if(estatus != ::success)
//             goto End;
//             lpmh->dwBytesRecorded = sizeof(gmModeOn);
//             if(estatus != ::success)
//             goto End;
//             estatus = midiOutLongMsg( hmidiout, lpmh, sizeof(MIDIHDR));
//             sleep(300_ms);
//             estatus = midiOutUnprepareHeader( hmidiout, lpmh, sizeof(MIDIHDR));
//             if(estatus != ::success)
//             goto End;
//             End:
//             midiOutClose( hmidiout);
//             */
//         }


      } // namespace player


   } // namespace midi_core_midi


} // namespace music









