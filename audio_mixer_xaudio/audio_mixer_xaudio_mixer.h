#pragma once


namespace multimedia
{


   namespace audio_mixer_mmsystem
   {


      class CLASS_DECL_AUDIO_MIXER_MMSYSTEM audio_mixer :
         virtual public ::multimedia::audio_mixer::audio_mixer
      {
      public:


         ::multimedia::audio_mixer_mmsystem::window            m_window;


         audio_mixer(__pointer(base_application) papp);
         virtual ~audio_mixer();



         ::multimedia::audio_mixer::callback * get_callback();
         void set_callback(::multimedia::audio_mixer::callback * pcallback);


         ::estatus     set_new_device(u32 uiMixerId);


         bool OnCommand(WPARAM wparam, LPARAM lparam);
         void OnMixerControlChange(HMIXER hMixer, u32 dwControlID);
         void OnMixerLineChange(HMIXER hMixer, u32 dwLineID);


         static bool get_component_name(LPMIXERLINE pmxl, string & strComponent);
         static bool get_control_type_name(LPMIXERCONTROL pmxctrl, string & strTypeName);



      };


   } // namespace audio_mixer_mmsystem


} // namespace multimedia







