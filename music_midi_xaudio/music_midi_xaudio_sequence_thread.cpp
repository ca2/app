#include "framework.h"


namespace music
{


   namespace midi
   {


      namespace mmsystem
      {


         sequence_thread::sequence_thread(::layered * pobjectContext) :
            ::object(pobject),
            thread(pobject),
            ::music::midi::sequence_thread(pobject)
         {
         }

         sequence_thread::~sequence_thread()
         {
         }

         bool sequence_thread::initialize_thread()
         {
            set_thread_priority(::aura::scheduling_priority_highest);
            return true;
         }

         i32 sequence_thread::exit_thread()
         {
            return thread::exit_thread();
         }

         void sequence_thread::install_message_routing(::channel * pchannel)
         {
            MESSAGE_LINK(::music::midi::player::message_command, pchannel, this, &sequence_thread::OnCommand);
            MESSAGE_LINK(e_message_midi_sequence_event, pchannel, this, &sequence_thread::OnMidiSequenceEvent);
         }

         void sequence_thread::Stop(imedia_time msEllapse)
         {
            get_sequence()->Stop();
            m_eventStop.wait(millis(msEllapse));
         }

         ::music::midi::sequence * sequence_thread::get_sequence()
         {
            return m_psequence;
         }


         bool sequence_thread::PostMidiSequenceEvent(::music::midi::sequence * pseq, ::music::midi::sequence::e_event eevent)
         {

            return post_thread_message(::music::midi::sequenceEVENT_MESSAGE,  (WPARAM) pseq, (LPARAM) pseq->create_new_event(eevent));

         }


         bool sequence_thread::PostMidiSequenceEvent(::music::midi::sequence * pseq, ::music::midi::sequence::e_event eevent, LPMIDIHDR lpmh)
         {

            __pointer(sequence) seq = pseq;

            return post_thread_message(::music::midi::sequenceEVENT_MESSAGE,  (WPARAM) pseq, (LPARAM) seq->create_new_event(eevent, lpmh));

         }

         void sequence_thread::OnMidiSequenceEvent(::message::message * pmessage)
         {

            SCAST_PTR(::message::base, pbase, pmessage);

            ::music::midi::sequence::event * pevent = (::music::midi::sequence::event *) pbase->m_lparam.m_lparam;
            ::music::midi::sequence * pseq = (::music::midi::sequence *) pevent->m_psequence;

            pseq->OnEvent(pevent);

            switch(pevent->m_eevent)
            {
            case ::music::midi::sequence::EventStopped:
            {
               ::music::midi::sequence::PlayerLink & link = get_sequence()->GetPlayerLink();
               if(link.TestFlag(::music::midi::sequence::FlagStop))
               {
                  link.ModifyFlag(::music::midi::sequence::FlagNull, ::music::midi::sequence::FlagStop);
                  link.OnFinishCommand(::music::midi::player::command_stop);
                  PostNotifyEvent(::music::midi::player::notify_event_playback_stop);

               }
               else if(link.TestFlag(::music::midi::sequence::FlagTempoChange))
               {
                  PrerollAndWait(link.m_tkRestart);
                  get_sequence()->SetTempoChangeFlag(false);
                  get_sequence()->Start();
                  link.ModifyFlag(::music::midi::sequence::FlagNull, ::music::midi::sequence::FlagTempoChange);
               }
               else if(link.TestFlag(::music::midi::sequence::FlagSettingPos))
               {
                  link.ModifyFlag(::music::midi::sequence::FlagNull, ::music::midi::sequence::FlagSettingPos);
                  try
                  {
                     PrerollAndWait(link.m_tkRestart);
                  }
                  catch(::exception_pointer e)
                  {
                     return;
                  }
                  get_sequence()->Start();
                  PostNotifyEvent(::music::midi::player::notify_event_position_set);
               }
               else if(link.TestFlag(
                       ::music::midi::sequence::FlagMidiOutDeviceChange))
               {
                  link.ModifyFlag(::music::midi::sequence::FlagNull, ::music::midi::sequence::FlagMidiOutDeviceChange);
                  try
                  {
                     PrerollAndWait(link.m_tkRestart);
                  }
                  catch(::exception_pointer e)
                  {
                     return;
                  }
                  get_sequence()->Start();
                  /*CNotifyEventData data;
                  data.m_pplayer = this;
                  data.m_enotifyevent = player::notify_event_position_set;
                  SendMessage(
                  m_oswindow_,
                  MIDIPLAYERMESSAGE_NOTIFYEVENT,
                  (WPARAM) &data,
                  0);      */

               }
               else if(link.TestFlag(::music::midi::sequence::FlagStopAndRestart))
               {
                  link.ModifyFlag(::music::midi::sequence::FlagNull, ::music::midi::sequence::FlagStopAndRestart);
                  try
                  {
                     PrerollAndWait(link.m_tkRestart);
                  }
                  catch(::exception_pointer e)
                  {
                     return;
                  }
                  get_sequence()->Start();
                  //PostNotifyEvent(player::notify_event_position_set);
               }

            }
            break;
            case ::music::midi::sequence::EventSpecialModeV001End:
            {
               PostNotifyEvent(::music::midi::player::notify_event_generic_mmsg_done);
            }
            break;
            case ::music::midi::sequence::EventMidiPlaybackStart:
            {
               PostNotifyEvent(::music::midi::player::notify_event_playback_start);
            }
            break;
            case ::music::midi::sequence::EventMidiStreamOut:
            {
               PostNotifyEvent(::music::midi::player::notify_event_midi_stream_out);
            }
            break;
            case ::music::midi::sequence::EventMidiPlaybackEnd:
            {
               PostNotifyEvent(::music::midi::player::notify_event_playback_end);
            }
            break;

            }

            delete pevent;


         }

         void sequence_thread::PostNotifyEvent(::music::midi::player::e_notify_event eevent)
         {
            if(m_pplayer != nullptr)
            {
               __pointer(::music::midi::player::notify_event) pdata(__new(::music::midi::player::notify_event));
               pdata->m_enotifyevent = eevent;
               m_pplayer->post_object(::music::midi::player::message_notify_event, 0,pdata);
            }
         }

         void sequence_thread::Play(imedia_time tkStart)
         {
            ASSERT(get_sequence() != nullptr);
            ASSERT(get_sequence()->GetState() == ::music::midi::sequence::state_opened);

            PrerollAndWait(tkStart);
            get_sequence()->Start();
         }

         void sequence_thread::Play(double dRate)
         {
            ASSERT(get_sequence() != nullptr);
            ASSERT(get_sequence()->GetState() == ::music::midi::sequence::state_opened);

            PrerollAndWait(dRate);
            get_sequence()->Start();
         }


         void sequence_thread::PrerollAndWait(imedia_time tkStart)
         {

            ::music::midi::PREROLL                 preroll;

            preroll.tkBase = tkStart;
            preroll.tkEnd  = get_sequence()->m_tkLength;

            get_sequence()->SetMidiOutDevice(m_pplayer->GetMidiOutDevice());

            try
            {
               get_sequence()->Preroll(this, &preroll, true);
            }
            catch (::exception_pointer e)
            {
               string str;
               ASSERT(FALSE);

               /* super merge module      CVmsMusDll::load_string(str, IDS_PREROLLUSERERROR001);
               pme->SetUserText(str);*/
               __throw(pme);
            }

         }


         void sequence_thread::PrerollAndWait(double dRate)
         {
            ::music::midi::PREROLL                 preroll;

            ::math::math::MaxClip(&dRate, 1.0);
            ::math::math::MinClip(&dRate,  0.0);

            preroll.tkBase = (imedia_time) (i32) ((double) get_sequence()->m_tkLength * dRate);
            preroll.tkEnd  = get_sequence()->m_tkLength;

            get_sequence()->SetMidiOutDevice(m_pplayer->GetMidiOutDevice());

            try
            {
               get_sequence()->Preroll(this, &preroll, true);
            }
            catch (::exception_pointer e)
            {
               __throw(not_implemented());
               /*string str;
               str.load_string(IDS_PREROLLUSERERROR001);
               pme->SetUserText(str);*/
               __throw(pme);
            }

            //    if(!get_sequence()->IsInSpecialModeV001())
            //  {
            //    SendMessage(m_oswindow_, WM_USER, 33, preroll.tkBase);
            //}
         }


         void sequence_thread::PostGMReset()
         {
            ASSERT(!get_sequence()->IsPlaying());
            get_sequence()->set_operation(::music::midi::operation_general_midi_reset);
            PrerollAndWait(0.0);
            get_sequence()->Start();

         }

         void sequence_thread::PostTempoChange()
         {
            ASSERT(!get_sequence()->IsPlaying());
            get_sequence()->set_operation(::music::midi::operation_tempo_change);
            PrerollAndWait(0.0);
            get_sequence()->Start();
         }

         void sequence_thread::SendTempoChange()
         {
            ASSERT(!get_sequence()->IsPlaying());
            get_sequence()->m_evMmsgDone.ResetEvent();
            PostTempoChange();
            get_sequence()->m_evMmsgDone.wait();
         }


         void sequence_thread::ExecuteCommand(pointer < ::music::midi::player::command > spcommand)
         {
            spcommand->add_ref(OBJ_REF_DBG_ARGS);
            post_thread_message(
            ::music::midi::player::message_command,
            0,
            (LPARAM) (::music::midi::player::command *) spcommand);
         }


         void sequence_thread::OnCommand(::message::message * pmessage)
         {
            SCAST_PTR(::message::base, pbase, pmessage);
            pointer < ::music::midi::player::command > spcommand;
            spcommand = (::music::midi::player::command *) pbase->m_lparam.m_lparam;
            try
            {
               _ExecuteCommand(spcommand);
            }
            catch(exception * pe)
            {
               ::exception_pointer esp(pe);
            }
            catch(...)
            {
            }
         }


         void sequence_thread::_ExecuteCommand(pointer < ::music::midi::player::command > spcommand)
         {
            switch(spcommand->GetCommand())
            {
            case ::music::midi::player::command_play:
            {
               if(spcommand->m_flags.has(::music::midi::player::command::flag_dRate))
               {
                  Play(spcommand->m_dRate);
               }
               else if(spcommand->m_flags.has(::music::midi::player::command::flag_ticks))
               {
                  Play(spcommand->m_ticks);
               }
               else
               {
                  Play();
               }
               spcommand->OnFinish();
            }
            break;
            case ::music::midi::player::command_close_device:
            {
               if(get_sequence() != nullptr)
               {
                  get_sequence()->CloseFile();
               }
               spcommand->OnFinish();
            }
            break;
            case ::music::midi::player::command_stop:
            {
               m_eventStop.ResetEvent();
               ::estatus                estatus;
               ::music::midi::sequence::PlayerLink & link = get_sequence()->GetPlayerLink();
               link.SetCommand(spcommand);
               link.ModifyFlag(::music::midi::sequence::FlagStop, ::music::midi::sequence::FlagNull);
               if(MMSYSERR_NOERROR != (estatus = get_sequence()->Stop()))
               {
                  __throw(multimedia::exception(multimedia::exception_midi, EMidiPlayerStop));
               }
            }
            break;
            case ::music::midi::player::command_stop_and_restart:
            {
               ::estatus                estatus;
               ::music::midi::sequence::PlayerLink & link = get_sequence()->GetPlayerLink();
               link.SetCommand(spcommand);
               link.ModifyFlag(
               ::music::midi::sequence::FlagStopAndRestart,
               ::music::midi::sequence::FlagNull);
               link.m_tkRestart = get_sequence()->GetPositionTicks();
               if(::success != (estatus = get_sequence()->Stop()))
               {
                  __throw(multimedia::exception(multimedia::exception_midi, EMidiPlayerStop));
               }
            }
            break;
            }
         }


      } // namespace mmsystem


   } // namespace midi


} // namespace music









