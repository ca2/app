#pragma once


namespace multimedia
{


   namespace audio_mixer_mmsystem
   {


      class CLASS_DECL_AUDIO_MIXER_MMSYSTEM device :
         virtual public ::multimedia::audio_mixer::device
      {
      public:


         HMIXER                        m_hMixer;
         MIXERCAPS                     m_mixercaps;


         device(__pointer(base_application) papp);
         virtual ~device();

         virtual bool initialize(::multimedia::audio_mixer::audio_mixer * pmixer);

         ::multimedia::audio_mixer::audio_mixer * get_mixer();
         virtual string get_product_name();
         bool OnCommand(WPARAM wparam, LPARAM lparam);
         ::estatus     close();
         void MapDlgCtrlIDToLineControls(::multimedia::audio_mixer::source * pSource);
         void MapDlgCtrlIDToControls();
         void MapLineControls(::multimedia::audio_mixer::source * pSource);
         void OnMixerControlChange(u32 dwControlID);
         void OnMixerLineChange(u32 dwLineID);
         void map_lines();
         void map_controls();
         ::estatus     get_destination(::multimedia::audio_mixer::e_destination edestination, ::multimedia::audio_mixer::destination ** ppDestination);
         ::estatus     initialize_destinations();
         ::estatus     initialize_capabilities();
         ::estatus     open(u32 uiMixerId, u32 dwCallback, u32 dwInstance, u32 fdwOpen);


      };


   } // namespace audio_mixer_mmsystem


} // namespace multimedia





