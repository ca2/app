#pragma once


namespace multimedia
{


   namespace audio_mixer_mmsystem
   {


      class CLASS_DECL_AUDIO_MIXER_MMSYSTEM control :
         virtual public ::multimedia::audio_mixer::control
      {
      public:


         enum Styles
         {
            StyleV001 = 1
         };


         MIXERCONTROL                     m_mixercontrol;
         MIXERCONTROLDETAILS              m_mixercontroldetails;


         control(__pointer(base_application) papp);
         control(control & control);
         virtual ~control();

         using ::multimedia::audio_mixer::user::control_ptr_array::add;
         virtual iptr add(::multimedia::audio_mixer::user::control * pcontrol);

         bool control_type(::multimedia::audio_mixer::e_control econtrol) const;
         bool OnCommand(WPARAM wParam, LPARAM lParam);
         ::multimedia::audio_mixer::control_data * GetWindowDataByDlgCtrlID(u32 nID);
         ::multimedia::audio_mixer::user::control * GetControlByDlgCtrlID(u32 nID);
         //   bool OnNotify(u32 nID, LPNMHDR lpnmhdr);
         void OnVHScroll(u32 nSBCode, u32 nPos, __pointer(::user::interaction) pScrollBar);
         ::multimedia::audio_mixer::control_data * GetWindowData(i32 iType);
         void OnMixerControlChange();
         ::multimedia::audio_mixer::user::control * GetControl(i32 iType);
         ::multimedia::audio_mixer::user::control * GetControlByIndex(::index iIndex);
         void Prepare();
         bool CreateWindowsVolumeV001(__pointer(::user::interaction) pParent, u32 nStartID, u32 * nNextID);

         //  bool _001CreateMuteControl(__pointer(::user::interaction) pParent, CRuntimeClass * pruntimeclassMuteControl, u32 nStartID, u32 * nNextID);
         bool _001CreateMuteControl(__pointer(::user::interaction) pParent, u32 nStartID, u32 * nNextID);

         bool CreateWindows(__pointer(::user::interaction) pParent, i32 iStyle);

         control & operator =(const control & control);


         MIXERCONTROL & GetMixerControl();
         MIXERCONTROLDETAILS & GetMixerControlDetails();


      };


   } // namespace audio_mixer_mmsystem


} // namespace multimedia




