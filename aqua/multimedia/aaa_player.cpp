#include "framework.h"
#include "player.h"
#include "player_command.h"
#include "effect_crescendo.h"
#include "out.h"
#include "acme/exception/interface_only.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/node.h"
#include "aqua/platform/system.h"
#include "audio/audio/audio.h"
#include "audio/audio/wave/wave.h"
#include "audio/audio/decode/decoder_plugin_set.h"
#include "audio/audio/decode/decoder_plugin.h"
#include "audio/audio/decode/decoder.h"


namespace wave
{


   player::player()
   {

      //m_bMessageThread = true;

      m_eplayerstate = e_player_state_initial;
      m_epurpose = e_purpose_default;

   }


   player::~player()
   {

   }


   void player::prepare_wave_player(enum_purpose epurpose)
   {

      synchronous_lock synchronouslock(this->synchronization());

      //if (thread_active())
      //{

      //   return ::success_none;

      //}

      //if (!allocate_player())
      //{

         // return false;

      //}

      //if (m_pwaveplayerForListener->thread_active())
      //{

         // return true;

      //}

      m_epurpose = epurpose;

      synchronouslock.unlock();

      //if (!begin_synch())
      //{

      //   return ::error_failed;

      //}

      //return ::success;

   }


   bool player::DecoderOpen(player_command  * pcommand)
   {

      if (DecoderIsActive())
      {

         audio_close();

      }

      string strDecoder;

      ::pointer<::audio::plugin>pplugin;

      auto paudio = system()->m_paquasystem->audio()->m_paudio;

      if (pcommand->GetCommand() == command_open_plugin)
      {

         pplugin = pcommand->m_ppluginOpen;

      }
      else if (pcommand->GetCommand() == command_open_file)
      {

         if (pcommand->m_bSeekable)
         {

            pplugin = paudio->audiowave()->m_pdecoderset->GetNewDecoder(pcommand->get_open_file(), pcommand->m_bSeekable);

         }
         else
         {

            pplugin = paudio->audiowave()->m_pdecoderset->GetNewDecoder(pcommand->get_open_file(), pcommand->m_bSeekable, 1024);

         }

      }
      else
      {

         switch (pcommand->GetCommand())
         {
         case command_open_file_aiff:
            //m_pplugin = __new _vmsaiffdec::plugin ();
            return false;
            break;
         case command_open_file_cda:
         {
            strDecoder = node()->library_file_name("audio_cd");
         }
         break;
         case command_open_file_mp3:
         case command_open_file_rtp:
         {
            strDecoder = node()->library_file_name("audio_libmpg123");
         }
         break;
         case command_open_file_vqf:
            //m_pplugin = __new _vmstwinvqdec::plugin ();
            return false;
            break;
         case command_open_file_wm:
         {
            strDecoder = node()->library_file_name("audio_window_media");
         }
         break;
         case command_open_file_wav:
         {
            strDecoder = node()->library_file_name("audio_wave");
         }
         break;
         default:
            return false;
            break;
         }

         auto pdecoderplugin = paudio->audiowave()->m_pdecoderset->LoadPlugin(strDecoder);

         if(!pdecoderplugin)
         {

            return false;

         }

         ::pointer<::audio::decoder>pdecoder = pdecoderplugin->NewDecoder();

         if (pdecoder.is_null())
         {

            return false;

         }

         if (pcommand->GetCommand() == command_open_file_rtp)
         {

            if (pdecoder->audio_set_seekable(false))
            {

               return false;

            }

            if (!pdecoder->audio_set_real_time())
            {

               return false;

            }

            if (pdecoder->audio_set_read_block_size(1024) != 1024)
            {

               return false;

            }

         }

         pdecoder->multimedia_open(pcommand->get_open_file());

         //if (!pdecoder->multimedia_open(pcommand->get_open_file()))
         //{

         //   return false;

         //}

         pplugin = pdecoder;

      }

      if (pplugin.is_set())
      {

         auto pwaveout = wave_out();

         //pplugin->__refer(pplugin->m_pwaveout, pwaveout);

         pplugin->m_pwaveout = pwaveout;

         pplugin->audio_initialize();

      }

      OnEvent(e_player_event_open_decoder, pcommand);

      return pplugin.is_set();

   }


   void player::audio_initialize(::pointer<::file::file> payloadFile)
   {

      //__UNREFERENCED_PARAMETER(payloadFile);

   }


   bool player::DecoderIsActive()
   {

      throw ::interface_only();

      return false;

   }


   out * player::wave_out()
   {

      return nullptr;

   }


   void player::audio_close()
   {

      try
      {

         //m_pwaveout->out_set_plugin(nullptr);

      }
      catch (...)
      {


      }

   }


   void player::DecoderRun()
   {

   }


   //void player::init_thread()
   //{

   //   if (!::thread::init_thread())
   //   {

   //      return false;

   //   }

   //   auto estatus = __construct(m_pwaveout);

   //   if (!estatus)
   //   {

   //      return estatus;

   //   }

   //   set_thread_priority(::e_priority_highest);

   //   m_pwaveout->m_pplayer = this;

   //   if (!m_pwaveout->thread_active())
   //   {

   //      if (!m_pwaveout->begin_synch(::e_priority_highest))
   //      {

   //         return false;

   //      }

   //   }

   //   return true;

   //}


   //void player::term_thread()
   //{

   //   try
   //   {

   //      for (auto & plistener : m_listenera)
   //      {

   //         try
   //         {

   //            plistener->OnWavePlayerEvent(this, e_player_event_destroy);

   //         }
   //         catch (...)
   //         {


   //         }

   //      }

   //   }
   //   catch (...)
   //   {


   //   }

   //   erase_all_listeners();

   //   thread::term_thread();

   //}



   void player::post_command(player_command * pcommand)
   {

//      post_object(e_message_player_command, 0, pcommand);

   }


   //void player::on_player_command(::message::message * pmessage)
   //{

   //   ::pointer<::user::message>pusermessage(pmessage);

   //   ::pointer<player_command>pcommand(pusermessage->m_lparam);

   //   player_command_procedure(pcommand);

   //   if (pcommand->m_pbResult != nullptr)
   //   {

   //      *pcommand->m_pbResult = pcommand->m_bResult;

   //   }

   //   pmessage->m_bRet = true;

   //}


   bool player::player_command_procedure(player_command * pcommand)
   {

      pcommand->m_bResult = true;

      enum_command ecommand = pcommand->GetCommand();

      switch (ecommand)
      {
      case command_open_plugin:
      case command_open_file_cda:
      case command_open_file_mp3:
      case command_open_file_rtp:
      case command_open_file_aiff:
      case command_open_file_vqf:
      case command_open_file_wm:
      case command_open_file_wav:
      case command_open_file:
      {

         if (IsPlaying())
         {
            return true;
         }

         if (DecoderIsActive())
         {

            audio_close();

         }

         if (!DecoderOpen(pcommand))
         {

            pcommand->m_bResult = false;

            OnEvent(e_player_event_open_decoder_failed);

            break;

         }

         if (!DecoderIsActive())
         {

            pcommand->m_bResult = false;

            OnEvent(e_player_event_open_decoder_failed);

            break;

         }

         OnEvent(e_player_event_open_decoder, pcommand);

      }
      break;
      case command_execute_play:
      {

         informationf("audio_player command_execute_play");

         if (IsPlaying())
         {

            informationf("Error : Wrong State : audio_player audio already playing");

            pcommand->m_bResult = false;

            break;

         }

         //if (m_pwaveout->out_plugin() == nullptr)
         //{

         //   informationf("audio_player plugin isn't set : NOT going to play");

         //   pcommand->m_bResult = false;

         //   break;

         //}

         //m_pwaveout->post_object(e_message_player_start, 0, pcommand);

      }
      break;
      case command_execute_stop:
      {

         FadeOutAndStop();

      }
      break;
      case command_execute_pause:
      {

         //m_pwaveout->out_pause();

      }
      break;
      case command_execute_restart:
      {

         //m_pwaveout->out_restart();

      }
      break;
      case command_close_device:
      {

         //if(m_pwaveout != nullptr)
         //{

         //   m_pwaveout->out_close();

         //}

         OnEvent(e_player_event_close_device);

      }
      break;
      default:
         ASSERT(false);
         break;
      }

      pcommand->SetEvents();

      return pcommand->m_bResult;

   }



   void player::ExecuteStop()
   {

      //m_pwaveout->out_stop();

   }


   bool player::DeviceIsOpened()
   {

      return get_device_state() == e_device_state_opened;

   }


   bool player::DecoderIsOpened()
   {

      return get_decoder_state() == e_decoder_state_opened;

   }


   bool player::IsPlaying()
   {

      //return m_pwaveout != nullptr && (get_device_state() == e_device_state_playing
      //                                 || get_device_state() == e_device_state_stopping
      //                                 || m_eplayerstate == e_player_state_fading_out_to_stop);

      return false;

   }


   bool player::GetPlayEnable()
   {

      return get_decoder_state() == e_decoder_state_opened
               && !IsPlaying();

   }


   bool player::GetStopEnable()
   {

      return IsPlaying();

   }


   void player::post_event(enum_player_event eevent, player_command * pcommand)
   {

      //::pointer<player_command>spcommand(pcommand);

      //post_message(e_message_player_event, (WPARAM)eevent, spcommand);
      OnEvent(eevent, pcommand);

   }


   //void player::on_event(::message::message * pmessage)
   //{

   //   ::pointer<::user::message>pusermessage(pmessage);

   //   ::pointer<player_command>pcommand(pusermessage->m_lparam);

   //   OnEvent((e_event) pusermessage->m_wparam.m_number, pcommand);

   //}


   void player::OnEvent(enum_player_event eevent, player_command * pcommand)
   {

      switch (eevent)
      {
      case e_player_event_open_device:
         informationf("player OnEvent e_player_event_open_device");
         set_device_state(e_device_state_opened);
         break;
      case e_player_event_open_device_failed:
         informationf("player OnEvent e_player_event_open_device_failed");
         set_device_state(e_device_state_initial);
         break;
      case e_player_event_open_decoder:
         informationf("player OnEvent e_player_event_open_decoder");
         set_decoder_state(e_decoder_state_opened);
         break;
      case e_player_event_start_device_failed:
      {

         informationf("player OnEvent e_player_event_start_device_failed");

         set_device_state(e_device_state_opened);
         set_player_state(e_player_state_initial);

      }
      break;
      case e_player_event_play:
      {

         informationf("player OnEvent e_player_event_play");

         set_device_state(e_device_state_playing);
         set_player_state(e_player_state_playing);

      }
      break;
      case e_player_event_stop:
      {

         informationf("player OnEvent e_player_event_stop");

         set_device_state(e_device_state_stopping);
         set_player_state(e_player_state_initial);
      }
      break;
      case e_player_event_fade_out_and_stop:
      {

         informationf("player OnEvent e_player_event_fade_out_and_stop");

         set_player_state(e_player_state_fading_out_to_stop);

      }
      break;
      case e_player_event_execute_pause:
      {

         informationf("player OnEvent EventDeviceOpen");

         set_device_state(e_device_state_paused);
         set_player_state(e_player_state_paused);

      }
      break;
      case e_player_event_execute_restart:
      {

         informationf("player OnEvent e_player_event_execute_restart");

         set_device_state(e_device_state_playing);


         set_player_state(e_player_state_playing);

      }
      break;
      case e_player_event_eof:
      {

         informationf("player OnEvent e_player_event_eof");

      }
      break;
      case e_player_event_playback_end:
      {

         informationf("player e_player_event_playback_end");

         //m_pwaveout->out_close();

         set_device_state(e_device_state_initial);

         //if (m_pwaveout->out_plugin() != nullptr)
         //{

         //   m_pwaveout->out_plugin()->audio_stop();

            set_decoder_state(e_decoder_state_opened);

            //m_pwaveout->out_plugin()->audio_seek_begin();

         //}

         set_player_state(e_player_state_initial);

         m_eplayerstate = e_player_state_initial;

      }
      break;
      case e_player_event_stopped:
      {

         informationf("player e_player_event_stopped");

         //m_pwaveout->out_close();

         //if (m_pwaveout->out_plugin() != nullptr)
         //{

         //   m_pwaveout->out_plugin()->audio_stop();

            set_decoder_state(e_decoder_state_opened);

      /*      m_pwaveout->out_plugin()->audio_seek_begin();

         }*/

         set_player_state(e_player_state_initial);

         set_device_state(e_device_state_initial);

      }
      break;
      case e_player_event_close_device:
      {
         informationf("player OnEvent e_player_event_close_device");
         set_device_state(e_device_state_initial);
      }
      break;
      case e_player_event_close_decoder:
      {
         informationf("player OnEvent e_player_event_close_decoder");
         set_decoder_state(e_decoder_state_initial);
      }
      break;
      case e_player_event_open_decoder_failed:
      {
         informationf("player OnEvent e_player_event_open_decoder_failed");
         set_decoder_state(e_decoder_state_initial);
      }
      break;
      case e_player_event_destroy:
      {
         informationf("player OnEvent e_player_event_destroy");
         set_device_state(e_device_state_initial);
      }
      break;
      }

      for (auto plistener : m_listenera)
      {

         plistener->OnWavePlayerEvent(this, eevent, pcommand);

      }

   }


   void player::set_device_state(enum_device_state estate)
   {

      m_edevicestate = estate;

   }


   void player::set_decoder_state(enum_decoder_state estate)
   {
      
      m_epluginstate = estate;

   }


   void player::set_player_state(enum_player_state estate)
   {

      m_eplayerstate = estate;

   }


   enum_player_state player::get_player_state()
   {

      return m_eplayerstate;

   }


   enum_device_state player::get_device_state()
   {

      if (m_edevicestate == e_device_state_playing
            || m_edevicestate == e_device_state_stopping)
      {

         //if (m_pwaveout->out_get_state() != out::e_player_state_playing
         //      && m_pwaveout->out_get_state() != out::e_player_state_stopping)
         //{

            m_edevicestate = e_device_state_opened;

         //}

      }

      return m_edevicestate;

   }


   enum_decoder_state player::get_decoder_state()
   {

      return m_epluginstate;

   }


   //out * player::get_out()
   //{

   //   return m_pwaveout;

   //}


   bool player::ExecuteIsPaused()
   {

      return m_eplayerstate == e_player_state_paused;

   }


   void player::_Stop()
   {

      if (IsPlaying())
      {

         //m_pwaveout->post_message(e_message_player_stop);

      }

   }


   void player::FadeOutAndStop()
   {

      if (m_eplayerstate != e_player_state_playing)
      {

         return;

      }

      OnEvent(e_player_event_fade_out_and_stop);

      effect_diminuendo * pdiminuendo = __new effect_diminuendo();

      pdiminuendo->m_bEnd = true;
      pdiminuendo->m_bSustain = true;
      pdiminuendo->m_bTriggerEnd = true;
      //pdiminuendo->SetLengthMillis(5000, m_pwaveout->out_get_buffer()->m_waveformatOut.nSamplesPerSec);
      pdiminuendo->Initialize();

      //m_pwaveout->out_set_stream_out_effect(pdiminuendo);

   }


   

   void player::add_listener(player_listener * plistener)
   {

      try
      {

         synchronous_lock synchronouslock(this->synchronization());

         //plistener->assert_ok();

         //try
         //{


         //   if (plistener->m_pwaveplayerForListener != this)
         //   {

         //      if (plistener->m_pwaveplayerForListener.is_set())
         //      {

         //         plistener->m_pwaveplayerForListener->erase_listener(plistener);

         //      }

         //      plistener->m_pwaveplayerForListener = this;

         //   }

         //}
         //catch (...)
         //{


         //}

         try
         {

            m_listenera.add_unique(plistener);

         }
         catch (...)
         {

         }

      }
      catch (...)
      {

      }

   }


   void player::erase_listener(player_listener * plistener)
   {

      try
      {

         synchronous_lock synchronouslock(this->synchronization());

         //try
         //{

         //   if (plistener->m_pwaveplayerForListener == this)
         //   {

         //      plistener->m_pwaveplayerForListener.release();

         //   }

         //}
         //catch (...)
         //{


         //}

         try
         {

            m_listenera.erase(plistener);

         }
         catch (...)
         {

         }

      }
      catch (...)
      {

      }

   }


   void player::erase_all_listeners()
   {

      try
      {

         synchronous_lock synchronouslock(this->synchronization());

         while (m_listenera.get_count() > 0)
         {

            erase_listener(m_listenera[0]);

         }

      }
      catch (...)
      {

      }

   }


   string player::get_device_state_string(enum_device_state edevicestate)
   {

      switch(edevicestate)
      {
      case e_device_state_initial:
         return "e_device_state_initial";
      case e_device_state_opened:
         return "e_device_state_opened";
      case e_device_state_playing:
         return "e_device_state_playing";
      case e_device_state_stopping:
         return "e_device_state_stopping";
      case e_device_state_paused:
         return "e_device_state_paused";
      default:
         return "unknown device state";
      }

   }


   string player::get_decoder_state_string(enum_decoder_state edecoderstate)
   {

      switch(edecoderstate)
      {
      case e_decoder_state_initial:
         return "e_decoder_state_initial";
      case e_decoder_state_opened:
         return "e_decoder_state_opened";
      default:
         return "unknown decoder state";
      }

   }


   string player::get_player_state_string(enum_player_state eplayerstate)
   {

      switch(eplayerstate)
      {
      case e_player_state_initial:
         return "e_player_state_initial";
      case e_player_state_playing:
         return "e_player_state_playing";
      case e_player_state_paused:
         return "e_player_state_paused";
      case e_player_state_fading_out_to_stop:
         return "e_player_state_fading_out_to_stop";
      default:
         return "unknown state";
      }

   }

   void player::player_set_volume(double dVolume)
   {


   }


   double player::player_get_volume()
   {

      return 1.0;
   }


   class ::time player::player_get_position_for_synch()
   {

      return 0_s;

   }


   class ::time player::player_get_position()
   {

      return 0_s;

   }


   //::time player::player_get_time_for_synch()
   //{

   //   return 0;

   //}

   u64 player::player_get_frame_byte_count()
   {

      return 0;

   }

   
   class ::time player::player_get_prebuffer_time()
   {
   
      return 0_s;

   }


   ::audio::plugin * player::plugin()
   {

      //if (m_pwaveout.is_null())
      //{

      //   return nullptr;

      //}

      //return m_pwaveout->out_plugin();

      return nullptr;

   }


} // namespace wave



