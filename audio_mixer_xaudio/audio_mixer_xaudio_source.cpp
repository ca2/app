#include "framework.h"


namespace multimedia
{


   namespace audio_mixer_mmsystem
   {


      source::source(__pointer(base_application) papp) :
         ::object(pobject),
         ::multimedia::audio_mixer::source(pobject)
      {
         m_mixercontrola.set_app(pobject);
         m_pdestination = nullptr;
         m_mixerlinecontrols.pamxctrl = nullptr;
      }

      source::source(source & source) :
         ::matter(source.get_context_application()),
         ::multimedia::audio_mixer::source(source.get_context_application())
      {
         operator =(source);
      }

      source::~source()
      {

      }

      ::estatus     source::GetLineControls()
      {
         ::estatus     mmrc;
         m_bHasV001Controls = false;
         i32 iControlCount = m_mixerline.cControls;
         if (0 == iControlCount)
         {
            //        System.message_box(nullptr, e_message_box_ok | e_message_box_icon_exclamation,
            //"There are no controls associated with the selected line.");
            //        EndDialog(oswindow, FALSE);
            return ::success;
         }

         m_mixercontrola.set_size_create(iControlCount);

         if(m_mixerlinecontrols.pamxctrl != nullptr)
            delete[] (MIXERCONTROL *) m_mixerlinecontrols.pamxctrl;
         m_mixerlinecontrols.cbStruct       = sizeof(MIXERLINECONTROLS);
         m_mixerlinecontrols.dwLineID       = m_mixerline.dwLineID;
         ////////////mxlc.dwControlID    = 0;
         ////////////mxlc.dwControlType  = 0;
         m_mixerlinecontrols.cControls      = iControlCount;
         m_mixerlinecontrols.cbmxctrl       = sizeof(*m_mixerlinecontrols.pamxctrl);
         m_mixerlinecontrols.pamxctrl       = new MIXERCONTROL[m_mixerline.cControls];

         for (i32 i = 0; i < iControlCount; i++)
         {
            m_mixerlinecontrols.pamxctrl[i].cbStruct = sizeof(MIXERCONTROL);
         }

         __pointer(::multimedia::audio_mixer_mmsystem::device) device = get_device();

         mmrc = mmsystem::translate(mixerGetLineControls((HMIXEROBJ) device->m_hMixer, &m_mixerlinecontrols, MIXER_GETLINECONTROLSF_ALL));

         if (::success != mmrc)
         {
            System.message_box(nullptr, e_message_box_ok | e_message_box_icon_exclamation,
                                      "mixerGetLineControls(ctrlid=%.08lXh) failed on hmx=%.04Xh, mmr=%u!",
                                      m_mixerline.dwLineID, device->m_hMixer, mmrc);
         }
         else
         {
            //        char       ach[128];
            //      char       szControlType[64];
            //        u32        u;
            //    i32         nIndex;
            PMIXERCONTROL       pamxctrl;
            //        LPMIXERCONTROLDETAILS lpmcd;
            __pointer(::multimedia::audio_mixer_mmsystem::control)     lpMixerControl;

            //        if (0 != (APP_OPTF_DEBUGLOG & gfuAppOptions))
            //          MixAppDebugLog(nullptr);

            for (i32 i = 0; (u32) i < m_mixerlinecontrols.cControls; i++)
            {
               lpMixerControl = m_mixercontrola(i);
               lpMixerControl->m_pmixersource = this;
               pamxctrl = &lpMixerControl->GetMixerControl();
               //m_mixerlinecontrols.pamxctrl = pamxctrl;
               //*m_mixerlinecontrols.pamxctrl = m_mixerlinecontrols.pamxctrl[i];
               *pamxctrl = m_mixerlinecontrols.pamxctrl[i];
               lpMixerControl->Prepare();
               //            ::multimedia::audio_mixer::audio_mixer::get_control_type_name(pamxctrl, lpMixerControl->m_strTypeName);

               switch (pamxctrl->dwControlType)
               {
               //            case MIXERCONTROL_CONTROLTYPE_FADER:
               case MIXERCONTROL_CONTROLTYPE_VOLUME:
               //          case MIXERCONTROL_CONTROLTYPE_BASS:
               //        case MIXERCONTROL_CONTROLTYPE_TREBLE:
               //      case MIXERCONTROL_CONTROLTYPE_EQUALIZER:

               //    case MIXERCONTROL_CONTROLTYPE_BOOLEAN:
               //  case MIXERCONTROL_CONTROLTYPE_ONOFF:
               case MIXERCONTROL_CONTROLTYPE_MUTE:
                  //            case MIXERCONTROL_CONTROLTYPE_MONO:
                  //          case MIXERCONTROL_CONTROLTYPE_LOUDNESS:
                  //        case MIXERCONTROL_CONTROLTYPE_STEREOENH:
                  m_bHasV001Controls = true;
                  break;

               default:;
               }
               //
               //
               //
               //            wsprintf(ach, gszLineControlsFormatList,
               //                  u,
               //                (char *)szControlType,
               //              pamxctrl[u].dwControlID,
               //            pamxctrl[u].fdwControl,
               //          pamxctrl[u].cMultipleItems,
               //        (char *)pamxctrl[u].szName);

               //            if (0 != (APP_OPTF_DEBUGLOG & gfuAppOptions))
               //          {
               //            MixAppDebugLog(ach);
               //          MixAppDebugLog(gszCRLF);
               //    }

               //            nIndex = ListBox_AddString(ptlb->hlb, ach);
               //          ListBox_SetItemData(ptlb->hlb, nIndex, pamxctrl[u].dwControlID);
            }

            //    ListBox_SetCurSel(ptlb->hlb, 0);
            //  EnableWindow(get_child_by_id(oswindow, IDD_LINECONTROLS_BTN_INFO), TRUE);
            //EnableWindow(get_child_by_id(oswindow, IDD_LINECONTROLS_BTN_SETTINGS), TRUE);
         }

         //    SetWindowRedraw(ptlb->hlb, TRUE);
         //  LocalFree((HLOCAL)pamxctrl);
         return mmrc;

      }

      /*::estatus     source::GetControl(u32 dwControlType, u32 dwControlFlags,  ::multimedia::audio_mixer::control ** ppControl)
      {
      ::multimedia::audio_mixer::control_array & controla = m_mixercontrola;
      if(controla.get_size() <= 0)
      GetLineControls();
      if(controla.get_size() <= 0)
      return MMSYSERR_ERROR;
      for(i32 i = 0; i < controla.get_size(); i++)
      {
      if((dwControlType != 0 && controla[i].GetControlType() == dwControlType)
      || (dwControlType == 0 && ((controla[i].GetControlType() & dwControlFlags) != 0)))
      {
      *ppControl = controla(i);
      return MMSYSERR_NOERROR;
      }
      }
      return MMSYSERR_ERROR;
      }*/

      /*void source::OnArrayReallocation(void *pNewPointer)
      {
      m_pmixerdestination = (::multimedia::audio_mixer::destination *) pNewPointer;
      }*/

      void source::OnMixerLineChange()
      {

      }



      void source::update_all_controls()
      {
         ::multimedia::audio_mixer::control_array & controla = get_control_array();
         for(i32 i = 0; i < controla.get_size(); i++)
         {
            controla[i].OnMixerControlChange();
         }
      }

      source & source::operator = (const source & source)
      {
         m_bHasV001Controls = source.m_bHasV001Controls;
         m_pdestination = source.m_pdestination;
         return *this;
      }

      
      string source::get_name()
      {

         return m_mixerline.szName;

      }


      u32 source::GetLineID()
      {
         return m_mixerline.dwLineID;
      }


      ::multimedia::audio_mixer::device * source::get_device()
      {
         return m_pdestination->get_device();
      }

      void source::SetDestination(::multimedia::audio_mixer::destination * pdestination)
      {
         m_pdestination = pdestination;
      }


      ::estatus     source::mixerGetLineInfo(u32 dwSource, u32 dwDestination, u32 fdwInfo)
      {

         m_mixerline.cbStruct       = sizeof(MIXERLINE);
         m_mixerline.dwDestination  = dwDestination;
         m_mixerline.dwSource       = dwSource;


         __pointer(::multimedia::audio_mixer_mmsystem::device) device = get_device();

         ::estatus     mmrc = mmsystem::translate(::mixerGetLineInfo((HMIXEROBJ)device->m_hMixer, &m_mixerline, fdwInfo));

         if (::success != mmrc)
         {
            System.message_box(nullptr, e_message_box_ok | e_message_box_icon_exclamation,
                                      "mixerGetLineInfo(src=%u) failed on hmx=%.04Xh, mmr=%u!",
                                      dwSource, device->m_hMixer, mmrc);
         }

         return mmrc;


      }

      ::estatus     source::mixerGetLineInfo(u32 dwSource, ::multimedia::audio_mixer::destination * pdestination)
      {

         __pointer(::multimedia::audio_mixer_mmsystem::destination) destination = pdestination;

         ::estatus     mmrc = mixerGetLineInfo(dwSource, destination->m_mixerline.dwDestination, MIXER_GETLINEINFOF_SOURCE);
         SetDestination(pdestination);
         return mmrc;

      }

      ::multimedia::audio_mixer::destination * source::get_destination()
      {
         return m_pdestination;
      }

      bool source::HasV001Controls()
      {
         return m_bHasV001Controls;
      }

      ::multimedia::audio_mixer::control_array & source::get_control_array()
      {
         return m_mixercontrola;
      }

      MIXERLINE & source::get_mixer_line()
      {
         return m_mixerline;
      }

      MIXERLINECONTROLS & source::get_mixer_line_controls()
      {
         return m_mixerlinecontrols;
      }


   } // namespace audio_mixer_mmsystem


} // namespace multimedia




