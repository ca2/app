#include "framework.h"


namespace music
{
   
   
   namespace midi
   {
      
      
      namespace core_midi
      {
         
   
         sequence_thread::sequence_thread(::context_object * pcontextobject) :
            object(pobject),
            thread(pobject),
            ::music::midi::sequence_thread(pobject)
         {
            
         }
         

         sequence_thread::~sequence_thread()
         {
            
         }


         bool sequence_thread::init_thread()
         {

            set_thread_priority(::priority_highest);

            return true;

         }


         void sequence_thread::term_thread()
         {

            thread::term_thread();

         }


         void sequence_thread::install_message_routing(::channel * psender)
         {
            
            ::music::midi::sequence_thread::install_message_routing(psender);
   //         MESSAGE_LINK(e_message_player_command, pchannel, this, &sequence_thread::OnCommand);
            MESSAGE_LINK(e_message_midi_sequence_event, psender, this, &sequence_thread::OnMidiSequenceEvent);
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


         bool sequence_thread::PostMidiSequenceEvent(::music::midi::sequence * pseq, sequence::e_event eevent)
         {

            return post_object(message_event,  (WPARAM) pseq, pseq->create_new_event(eevent));

         }


         bool sequence_thread::PostMidiSequenceEvent(::music::midi::sequence * psequenceParam, sequence::e_event eevent, LPMIDIHDR lpmh)
         {
            
            __pointer(sequence) psequence = psequenceParam;

            return post_object(message_event,  (WPARAM) psequenceParam, psequence->create_new_event(eevent, lpmh));

         }


         void sequence_thread::OnMidiSequenceEvent(::message::message * pmessage)
         {

            __pointer(::user::message) pusermessage(pmessage);

            __pointer(sequence::event) pevent(pusermessage->m_lparam);

            auto pseq = pevent->m_psequence;

            pseq->OnEvent(pevent);

            switch(pevent->m_eevent)
            {
            case sequence::e_event_midi_playback_end:
            {
               auto & link = get_sequence()->GetPlayerLink();
               if(link() & sequence::e_flag_tempo_change)
               {
                  PrerollAndWait(link.m_tkRestart);
                  get_sequence()->SetTempoChangeFlag(false);
                  get_sequence()->Start();
                  link() -= sequence::e_flag_tempo_change;
               }
               else if(link() & sequence::e_flag_setting_position)
               {
                  link() -= sequence::e_flag_setting_position;
                  try
                  {
                     PrerollAndWait(link.m_tkRestart);
                  }
                  catch(const ::exception::exception & e)
                  {
                     return;
                  }
                  get_sequence()->Start();
                  PostNotifyEvent(notify_event_position_set);
               }
               else if(link() & sequence::e_flag_midi_out_device_change)
               {
                  link() -= sequence::e_flag_midi_out_device_change;
                  try
                  {
                     PrerollAndWait(link.m_tkRestart);
                  }
                  catch(const ::exception::exception & e)
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
               else if(link() & sequence::e_flag_midi_out_and_restart)
               {
                  link() -= sequence::e_flag_midi_out_and_restart;
                  try
                  {
                     PrerollAndWait(link.m_tkRestart);
                  }
                  catch(const ::exception::exception & e)
                  {
                     return;
                  }
                  get_sequence()->Start();
                  //PostNotifyEvent(player::notify_event_position_set);
               }
               else
               {

   //                  if(link.TestFlag(sequence::e_flag_stop))
                  {
                     link() -= sequence::e_flag_stop;
                     link.OnFinishCommand(command_stop);
                     PostNotifyEvent(notify_event_playback_end);

                  }

               }

            }
            break;
                  
            case sequence::e_event_operation:
            {
               PostNotifyEvent(notify_event_generic_mmsg_done);
            }
            break;
            
            case sequence::e_event_midi_playback_start:
            {

               //pseq->seq_start();

               pseq->m_psequencer = pseq->create_sequencer();

               pseq->m_psequencer->begin();

   //            post_message(::music::midi_core_midi::sequence::message_run);

               PostNotifyEvent(notify_event_playback_start);

            }
            break;
            case sequence::e_event_midi_playback_out:
            {
               PostNotifyEvent(notify_event_midi_stream_out);
            }
            break;

            }


         }

   //      void sequence_thread::PostNotifyEvent(e_notify_event eevent)
   //      {
   //         if(m_pplayer != nullptr)
   //         {
   //            auto pdata(__new(notify_event));
   //            pdata->m_enotifyevent = eevent;
   //            m_pplayer->post_object(::music::midi::player::message_notify_event, 0, pdata);
   //         }
   //      }

         void sequence_thread::Play(imedia_time tkStart)
         {
            ASSERT(get_sequence() != nullptr);
            ASSERT(get_sequence()->get_state() == sequence::e_state_opened);

            PrerollAndWait(tkStart);
            get_sequence()->Start();
         }

         void sequence_thread::PlayRate(double dRate)
         {
            ASSERT(get_sequence() != nullptr);
            ASSERT(get_sequence()->get_state() == sequence::e_state_opened);

            PrerollAndWait(dRate);
            get_sequence()->Start();
         }


         void sequence_thread::PrerollAndWait(imedia_time tkStart)
         {

            ::music::midi::PREROLL                 preroll;

            preroll.tkBase = tkStart;
            
            preroll.tkEnd  = get_sequence()->m_tkLength;

            get_sequence()->set_midi_out_device(m_pplayer->get_midi_out_device());

            try
            {
               
               get_sequence()->Preroll(this, &preroll, true);
               
            }
            catch (::exception_pointer e)
            {
               
               __rethrow(::move(e));
               
            }

         }


         void sequence_thread::PrerollRateAndWait(double dRate)
         {
            ::music::midi::PREROLL                 preroll;

            ::math::math::MaxClip(&dRate, 1.0);
            ::math::math::MinClip(&dRate,  0.0);

            preroll.tkBase = (imedia_time) (i32) ((double) get_sequence()->m_tkLength * dRate);
            preroll.tkEnd  = get_sequence()->m_tkLength;

            get_sequence()->set_midi_out_device(m_pplayer->get_midi_out_device());

            try
            {
               get_sequence()->Preroll(this, &preroll, true);
            }
            catch (::exception_pointer e)
            {
               __throw(error_not_implemented);
               /*string str;
                str.load_string(IDS_PREROLLUSERERROR001);
                pme->SetUserText(str);*/
               //__throw(pme);
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


      } // namespace core_midi


   } // namespace midi


} // namespace music


