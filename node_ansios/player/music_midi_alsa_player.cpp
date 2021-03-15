#include "framework.h"


namespace music
{


   namespace midi
   {


      namespace alsa
      {


         player::player(::context_object * pcontextobject) :
            object(pobject),
            thread(pobject),
            ::music::midi::player(pobject)
         {

            m_psequencethread = __sp(new ::music::midi::alsa::sequence_thread(this));

            m_psequencethread->begin();

            m_puie = NULL;

         }


         player::~player()
         {

         }


         bool player::init_thread()
         {

            m_psequencethread->ResumeThread();

            TRACE("player::initialize_instance %X\n", get_os_int());

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
            //    if(m_pmidicallbackdata != NULL)
            //  {
            //    delete m_pmidicallbackdata;
            ///  m_pmidicallbackdata = NULL;
            //}
            music::midi::player::player::term_thread();

         }


         void player::install_message_routing(::message::sender * pinterface)
         {

            ::music::midi::player::install_message_routing(pinterface);
            //IGUI_WIN_MSG_LINK(MM_MOM_DONE, pinterface, this, &player::OnMultimediaMidiOutputMessageDone);
            //IGUI_WIN_MSG_LINK(MM_MOM_POSITIONCB, pinterface, this, &player::OnMultimediaMidiOutputMessagePositionCB);
         }


         bool player::Play(imedia_position tkStart, ::u32 dwEllapse)
         {

            auto pcommand = __sp(new ::music::midi::player_command(this));

            pcommand->m_ecommand = ::music::midi::command_play;
            pcommand->m_dwEllapse = dwEllapse;
            pcommand->m_flags.signalize(::music::midi::player_command::flag_ticks);
            pcommand->m_ticks = tkStart;

            m_psequencethread->ExecuteCommand(pcommand);

            bool bFinished = pcommand->wait_ready();

            return bFinished;

         }


         bool player::PlayRate(double dRate, ::u32 dwEllapse)
         {

            auto pcommand = __sp(new ::music::midi::player_command(this));

            pcommand->m_ecommand = ::music::midi::command_play;
            pcommand->m_dwEllapse = dwEllapse;
            pcommand->m_flags.signalize(::music::midi::player_command::flag_dRate);
            pcommand->m_dRate = dRate;

            m_psequencethread->ExecuteCommand(pcommand);

            bool bFinished = pcommand->wait_ready();

            return bFinished;

         }

         imedia_position player::RateToTicks(double dRate)
         {
            ASSERT(dRate >= 0.0);
            ASSERT(dRate <= 1.0);
            return (imedia_position) (int32_t) (get_sequence()->m_tkLength * dRate);
         }



         bool player::IsPlaying()
         {
            ASSERT(!get_sequence()->IsNull());
            return (bool) get_sequence()->IsPlaying();

         }

         bool player::ExecuteCommand(::music::midi::e_command ecommand, ::u32 dwEllapse)
         {

            auto pcommand = __sp(new ::music::midi::player_command(this));

            pcommand->m_ecommand = ecommand;
            pcommand->m_dwEllapse = dwEllapse;

            m_psequencethread->ExecuteCommand(pcommand);

            bool bFinished = pcommand->wait_ready();

            return bFinished;

         }


         void player::close_file()
         {

            ::e_status            mmrc;

            if(::failed(mmrc = get_sequence()->close_file()) &&
               mmrc != ::error_wrong_state)
            {

               __throw(new ::multimedia::exception(::multimedia::exception_music, mmrc));

            }
         }


         void player::pause()
         {

            if (get_sequence()->get_state() == ::music::midi::sequence::e_state_paused)
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
            if (::music::midi::sequence::e_state_playing != get_sequence()->get_state() &&
               ::music::midi::sequence::e_state_stopping != get_sequence()->get_state() &&
               ::music::midi::sequence::e_state_opened != get_sequence()->get_state())
               return;

            if(get_sequence()->IsPlaying())
            {

               ::music::midi::sequence::player_link & link = get_sequence()->GetPlayerLink();

               link() |= ::music::midi::sequence::e_flag_setting_position;

               link.m_tkRestart = RateToTicks(dRate);

               get_sequence()->Stop();

            }

         }

         void player::OnMmsgDone(::music::midi::sequence * pSeq)
         {
            ASSERT(FALSE);
            ASSERT(FALSE);
            ASSERT(FALSE);
            ASSERT(FALSE);
            ASSERT(FALSE);
            ASSERT(FALSE);
            ASSERT(FALSE);
            ASSERT(FALSE);
            ASSERT(pSeq == get_sequence());
            if(pSeq->IsSettingPosition())
            {
               get_sequence()->SetSettingPositionFlag(FALSE);
               try
               {
                  //         PrerollAndWait(m_dNextPositionRate);
               }
               catch(exception_sp e)
               {

                  //pe->Delete();

                  return;

               }

               get_sequence()->Start();

            }
            else
            {

            }

         }


         void player::pre_translate_message(::message::message * pobj)
         {

            SCAST_PTR(::message::base, pbase, pobj);

            //ASSERT(GetMainWnd() == NULL);
            //   if(pMsg->message == MM_MOM_DONE ||
            //      pMsg->message == MM_MOM_POSITIONCB ||
            //      pMsg->message == MM_MOM_OPEN ||
            //      pMsg->message == MM_MOM_OPEN)
            //   {
            //      OnMidiOutMessage(pMsg->message, pMsg->wParam, pMsg->lParam);
            //      return TRUE;
            //   }
            if(pbase->m_puserinteraction == NULL)
            {
               switch(pbase->m_id)
               {
               case WM_USER + 100:
                  {
                     //LPDOUBLESTRUCT lpds = (LPDOUBLESTRUCT) pbase->m_wparam;
                     //SetPosition(lpds->d);
                     //delete lpds;
                     throw 123;
                  }
                  return;
               }
            }
            if(pbase->m_id == MMSG_DONE)
            {
               //OnMmsgDone((::music::midi::sequence *) pbase->m_wparam);
               throw 1234;
               pbase->m_bRet = true;
               return;
            }
            else if(pbase->m_id == WM_USER)
            {
               //      OnUserMessage(pMsg->wParam, pMsg->lParam);
            }
            return thread::pre_translate_message(pobj);
         }

//         void player::SaveFile(const char * lpszPathName)
//         {
//            ::e_status            mmrc;
//            if(::failed(mmrc = get_sequence()->SaveFile(lpszPathName)) )
//            {
//               __throw(new ::multimedia::exception(::multimedia::exception_midi, mmrc));
//            }
//
//         }


         void player::OnUserMessage(::message::message * pobj)
         {
            SCAST_PTR(::message::base, pbase, pobj);
            if(pbase->m_wparam == 3377)
            {
               m_puie->send_message(WM_USER, pbase->m_wparam, pbase->m_lparam);
            }

         }


         void player::PostGMReset()
         {
            m_psequencethread->PostGMReset();
         }

         void player::PostTempoChange()
         {
            m_psequencethread->PostTempoChange();
         }

         void player::SendTempoChange()
         {
            m_psequencethread->SendTempoChange();
         }


         ::e_status player::Initialize(thread * pthread)
         {
            UNREFERENCED_PARAMETER(pthread);
            return ::success;
         }

         //void player::SetView(CXfplayerView *pview)
         //{
         //    m_pView = pview;
         //}

         ::e_status player::SetInterface(player * pinterface)
         {
            get_sequence()->m_pthread   = m_psequencethread;
            m_psequencethread->m_psequence = get_sequence();
            m_psequencethread->m_pplayer = this;
            PostNotifyEvent(::music::midi::notify_event_set_sequence);
            return ::success;
         }


         bool player::SetMidiOutDevice(::u32 uiDevice)
         {
            UNREFERENCED_PARAMETER(uiDevice);
            OnMidiOutDeviceChange();
            return true;
         }



         bool player::SetTempoShift(int32_t iTempoShift)
         {
            //   if(IsPlaying())
            {/*
             get_sequence()->SetTempoChangeFlag();
             ::music::midi::sequence::PlayerLink & link = get_sequence()->GetPlayerLink();
             link.ModifyFlag(
             ::music::midi::sequence::e_flag_tempo_change,
             ::music::midi::sequence::e_flag_null);
             imedia::position tk = get_sequence()->GetPositionTicks();
             get_sequence()->m_evMmsgDone.ResetEvent();
             link.m_tkRestart = tk + get_sequence()->m_tkBase;
             //m_bChangingTempo = true;
             get_sequence()->Stop();
             //get_sequence()->m_evMmsgDone.lock();
             */
               bool bPlay = IsPlaying();
               imedia_position ticks = 0;
               if(bPlay)
               {
                  ticks = get_sequence()->get_position_ticks();
                  get_sequence()->Stop();
               }
               if(!get_sequence()->SetTempoShift(iTempoShift))
                  return false;
               if(bPlay)
               {
                  get_sequence()->m_pthread->PrerollAndWait(ticks);
                  get_sequence()->Start();
               }

            }
            return true;
         }


//         void player::PostNotifyEvent(::music::midi::e_notify_event eevent)
//         {
//
//            if(m_puie != NULL)
//            {
//
//               auto pdata = __sp(new ::music::midi::notify_event));
//
//               pdata->m_pplayer = this;
//
//               pdata->m_enotifyevent = eevent;
//
//               m_puie->post_object(::music::midi::message_notify_event, 0, pdata);
//
//            }
//
//         }


//         void player::SendMmsgDone(::music::midi::sequence *pSeq, ::music::midi::LPMIDIDONEDATA lpmdd)
//         {
//
//            if(m_puie != NULL)
//            {
//
//               m_puie->post_message(MMSG_DONE, (WPARAM) pSeq, (LPARAM) lpmdd);
//
//            }
//
//         }

//
//         ::u32 player::GetMidiOutDevice()
//         {
//
//            return papplication->midi()->GetMidiOutDevice();
//         }

//         void player::SetCallbackWindow(sp(::user::interaction) puie)
//         {
//            m_puie = puie;
//         }


         void player::on_attribute_change(::message::message * pobj)
         {

            SCAST_PTR(::music::midi::attribute_message, pchange, pobj);

            switch(pchange->m_eattribute)
            {
            case ::music::midi::attribute_midi_out_device:
               OnMidiOutDeviceChange();
               break;
            }

         }


         void player::OnMidiOutDeviceChange()
         {

            get_sequence()->set_midi_out_device(papplication->midi()->get_midi_out_device());

            if(get_sequence()->IsPlaying())
            {
               imedia_position tkPosition = 0;
               get_sequence()->get_position(tkPosition);
               ::music::midi::sequence::player_link & link = get_sequence()->GetPlayerLink();
               link() |= ::music::midi::sequence::e_flag_tempo_change;
               link.m_tkRestart = tkPosition;
               get_sequence()->Stop();
            }

         }


         void player::OnMultimediaMidiOutputMessageDone(::message::message * pobj)
         {

            SCAST_PTR(::message::base, pbase, pobj);

            /*seq_context_t * pseq = (seq_context_t *) pbase->m_wparam;

            LPMIDIHDR lpmidihdr = (LPMIDIHDR) pbase->m_lparam.m_lparam;

            sp(sequence) sequence = get_sequence();

            ASSERT(sequence->m_pseq == pseq);

            sequence->OnDone(pseq, lpmidihdr);*/

         }

         void player::OnMultimediaMidiOutputMessagePositionCB(::message::message * pobj)
         {
            SCAST_PTR(::message::base, pbase, pobj);
/*            LPMIDIHDR lpmidihdr = (LPMIDIHDR) pbase->m_wparam;
  //          get_sequence()->OnPositionCB(lpmidihdr);

            sp(sequence) sequence = get_sequence();

//            ASSERT(sequence->m_hstream == hmidistream);

            sequence->OnPositionCB(lpmidihdr);*/
         }




         void player::OnNotifyEvent(::message::message * pobj)
         {

            SCAST_PTR(::message::base, pbase, pobj);

            sp(::music::midi::notify_event) pdata(pbase->m_lparam);

            pdata->m_pplayer = this;

            if(m_puie != NULL)
            {

               m_puie->post_object(message_player_notify_event, 0, pdata);

            }

         }




         void player::SendReset()
         {
/*            HMIDIOUT hmidiout = NULL;
            ::e_status mmrc;
            ::u32 uDeviceID = 0;
            mmrc = midiOutOpen(&hmidiout, uDeviceID,  0, 0, CALLBACK_NULL);
            if(mmrc != ::success)
               return;
            Sleep(284);
            const uchar gmModeOn[] = {
               //        0x00, 0x00, 0x00, 0x00,
               //        0x00, 0x00, 0x00, 0x00,
               //        0x1b, 0x8a, 0x06, MEVT_TEMPO,
               0x00, 0x00, 0x00, 0x00,
               0x00, 0x00, 0x00, 0x00,
               0x06, 0x00, 0x00, MEVT_LONGMSG,
               0xf0, 0x7e, 0x7f, 0x09,
               0x01, 0xf7, 0x00, 0x00};
            //        0x70, 0x01, 0x00, 0x00,
            //      0x00, 0x00, 0x00, 0x00 };
            //      0x09, 0x00, 0x00, MEVT_LONGMSG,
            //      0x43, 0x10, 0x4c,
            //    0x00, 0x00, 0x7e, 0x00,
            //  0xf7, 0x00, 0x00, 0x00,};
            MIDIHDR mh;
            LPMIDIHDR lpmh = &mh;
            lpmh->lpData = (char *) gmModeOn;
            lpmh->dwBufferLength = sizeof(gmModeOn);
            lpmh->dwBytesRecorded = 0;
            lpmh->dwFlags = 0;
            mmrc = midiOutPrepareHeader( hmidiout, lpmh, sizeof(MIDIHDR));
            if(mmrc != ::success)
               goto End;
            lpmh->dwBytesRecorded = sizeof(gmModeOn);
            if(mmrc != ::success)
               goto End;
            mmrc = midiOutLongMsg( hmidiout, lpmh, sizeof(MIDIHDR));
            Sleep(284);
            mmrc = midiOutUnprepareHeader( hmidiout, lpmh, sizeof(MIDIHDR));
            if(mmrc != ::success)
               goto End;
End:
            midiOutClose( hmidiout);
            */
         }


         void player::OnMmsgDone(::music::midi::sequence *pSeq, ::music::midi::LPMIDIDONEDATA lpmdd)
         {
            UNREFERENCED_PARAMETER(pSeq);
            UNREFERENCED_PARAMETER(lpmdd);
         }

//         void player::OnMidiPlayerNotifyEvent(::music::midi::notify_event * pdata)
//         {
//            switch(pdata->m_enotifyevent)
//            {
//            case music::midi::player::notify_event_set_sequence:
//               //      pdata->m_pplayer->get_sequence()->m_midicallbackdata.oswindow = m_wnd.GetSafeoswindow_();
//               break;
//            }
//         }

         void player::OnMidiLyricEvent(array<::ikaraoke::lyric_event_v1, ::ikaraoke::lyric_event_v1&> * pevents)
         {
            UNREFERENCED_PARAMETER(pevents);
         }
         bool player::Initialize(sp(::music::midi::midi) pcentral)
         {

//            if(!initialize())
  //             return false;

            // = pcentral;

            return true;
         }


         bool player::Finalize()
         {

            //if(!finalize())
              // return false;

            return true;
         }


         bool player::OpenMidiPlayer()
         {

            SetMidiCentral(papplication->midi());

//            m_pmidiplayer->SetCallbackWindow(&m_wnd);
            if(::failed(Initialize(this)))
            {
               return false;
            }



            if(!OnOpenMidiPlayer())
            {
               return false;
            }
            ResumeThread();
            m_evInitialized.wait();
            return true;
         }

         bool player::OnOpenMidiPlayer()
         {
            SetInterface(this);
//            m_wnd.set_callback(m_composite);
            return true;
         }


         // Event handling
         void player::OnMidiPlayerNotifyEvent(::music::midi::notify_event * pdata)
         {
//            callback::OnMidiPlayerNotifyEvent(pdata);
//            switch(pdata->m_enotifyevent)
//            {
//            case music::midi::player::notify_event_set_sequence:
//               //      pdata->m_pplayer->get_sequence()->m_midicallbackdata.lpThreadV1 = GetMidiPlayerCallbackThread();
//               break;
//            }

         }


      } // namespace alsa


   } // namespace midi


} // namespace music









