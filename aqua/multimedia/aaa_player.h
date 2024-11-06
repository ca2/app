#pragma once


namespace wave
{


   class CLASS_DECL_APP_CORE_AUDIO player :
      virtual public ::object
   {
   public:


      friend class out;





      pointer_array < player_listener >                    m_listenera;

      enum_device_state                            m_edevicestate;
      enum_decoder_state                           m_epluginstate;
      enum_player_state                            m_eplayerstate;
      int                                          m_iBufferId;
      enum_purpose                                 m_epurpose;
      ::pointer<::iaudio::wave_stream_effect>     m_pstreameffectOut;


      player();
      ~player() override;


      virtual void prepare_wave_player(enum_purpose epurpose);

      virtual bool DecoderOpen(player_command* pcommand);

      virtual bool DecoderIsActive();
      virtual void audio_initialize(::pointer<::file::file>pfile);
      virtual void audio_close();
      virtual void DecoderRun();




      virtual bool player_command_procedure(player_command* pcommand);

      virtual void FadeOutAndStop() = 0;
      virtual void set_player_state(enum_player_state eplayerstate);
      virtual enum_player_state get_player_state();
      virtual bool ExecuteIsPaused();
      virtual bool GetStopEnable();
      virtual bool GetPlayEnable();
      //virtual out* get_out();
      virtual bool IsPlaying();
      virtual enum_device_state get_device_state();
      virtual enum_decoder_state get_decoder_state();
      virtual void set_device_state(enum_device_state estate);
      virtual void set_decoder_state(enum_decoder_state estate);

      virtual void post_event(enum_player_event event, player_command* pcommand = nullptr);
      virtual void OnEvent(enum_player_event event, player_command* pcommand = nullptr);
      virtual bool DeviceIsOpened();
      virtual bool DecoderIsOpened();


      static string get_device_state_string(enum_device_state edevicestate);
      static string get_decoder_state_string(enum_decoder_state edecoderstate);
      static string get_player_state_string(enum_player_state eplayerstate);


      virtual void post_command(player_command* pcommand);


      virtual void _Stop();
      virtual void ExecuteStop();


      virtual void add_listener(player_listener* plistener);
      virtual void erase_listener(player_listener* plistener);
      virtual void erase_all_listeners();


      virtual class ::time player_get_position_for_synch();
      virtual class ::time player_get_position();

      virtual ::audio::plugin* plugin();

      virtual void player_set_volume(double dVolume);
      virtual double player_get_volume();

      virtual class ::time player_get_prebuffer_time();
      virtual u64 player_get_frame_byte_count();


      virtual out * wave_out();


   };


   CLASS_DECL_APP_CORE_AUDIO void compose_player(::pointer<player>& pplayer, player_listener * plistener);


} // namespace multimedia



