#include "framework.h"


namespace multimedia
{


   namespace audio_mixer_mmsystem
   {


      device::device(__pointer(base_application) papp) :
         ::object(pobject),
         ::multimedia::audio_mixer::device(pobject)
         //m_mixerdestinationa(pobject)
      {

         //m_mixerdestinationa.set_app(this);

         m_pmixer = nullptr;

         m_hMixer = nullptr;

      }


      device::~device()
      {

         close();

      }

      bool device::initialize(::multimedia::audio_mixer::audio_mixer * pmixer)
      {

         m_pmixer = pmixer;

         return true;

      }

      ::e_status     device::open(u32 uiMixerId, u32 dwCallback, u32 dwInstance, u32 fdwOpen)
      {

         ::e_status                mmrc;
         HMIXER              hmx;
         MIXERCAPS           mxcaps;


         if (m_hMixer != nullptr)
         {

            ::e_status     mmrct = close();

            if(::success != mmrct)
            {

               psystem->message_box(nullptr, e_message_box_ok | e_message_box_icon_exclamation, "mixerClose() failed on hmx=%.04Xh, mmr=%u!", m_hMixer, mmrct);

            }

         }

         mmrc = mmsystem::translate(mixerGetDevCaps(uiMixerId, &mxcaps, sizeof(mxcaps)));

         if(::success != mmrc)
         {

            psystem->message_box(nullptr, e_message_box_ok | e_message_box_icon_exclamation, "mixerGetDevCaps() failed on uMxId=%u, mmr=%u!", uiMixerId, mmrc);

            return mmrc;

         }

         mmrc = mmsystem::translate(mixerOpen(&hmx, uiMixerId, dwCallback, dwInstance, fdwOpen));

         if(::success != mmrc)
         {

            psystem->message_box(nullptr, e_message_box_ok | e_message_box_icon_exclamation, "mixerOpen() failed on uMxId=%u, mmr=%u!", uiMixerId, mmrc);

            return mmrc;

         }



         m_hMixer = hmx;

         m_uiMixerID = uiMixerId;

         //    Appset_window_text(oswindow, "::multimedia::audio_mixer::audio_mixer Device: %s", (char *)mxcaps.szPname);

         return mmrc;

      }


      ::e_status     device::initialize_capabilities()
      {

         ::e_status     mmrc;

         mmrc = mmsystem::translate(mixerGetDevCaps((u32) m_hMixer, &m_mixercaps, sizeof(MIXERCAPS)));

         if(::success != mmrc)
         {

            psystem->message_box(nullptr, e_message_box_ok | e_message_box_icon_exclamation, "mixerGetDevCaps() failed on uMxId=%u, mmr=%u!", m_uiMixerID, mmrc);

            return mmrc;

         }

         return mmrc;

      }


      ::e_status     device::initialize_destinations()
      {

         __pointer(::multimedia::audio_mixer_mmsystem::destination)    lpDestination;

         m_mixerdestinationa.set_size_create(m_mixercaps.cDestinations);

         for (i32 i = 0; (u32) i < m_mixercaps.cDestinations; i++)
         {
            lpDestination = m_mixerdestinationa(i);
            lpDestination->set_device(this);
            lpDestination->mixerGetLineInfo(0, i, MIXER_GETLINEINFOF_DESTINATION);
            //        ::multimedia::audio_mixer::audio_mixer::get_component_name(lpmxl, lpDestination->m_strComponent);

            //        //
            //      //
            //    //
            //  wsprintf(ach, gszLineFormatList,
            //         (char *)szLineTypeDst,
            //       (MIXERLINE_LINEF_ACTIVE & mxl.fdwLine) ? '*' : ' ',
            //     (char *)szComponent,
            //   mxl.dwLineID,
            //   mxl.fdwLine,
            // mxl.cControls,
            // mxl.cConnections,
            //(char *)mxl.szName);

            //        if (0 != (APP_OPTF_DEBUGLOG & gfuAppOptions))
            //      {
            //        MixAppDebugLog(ach);
            //      MixAppDebugLog(gszCRLF);
            //  }

            //        nIndex = ListBox_AddString(ptlb->hlb, ach);
            //      ListBox_SetItemData(ptlb->hlb, nIndex, mxl.dwLineID);

         }


         //
         //
         //
         //    SetWindowRedraw(ptlb->hlb, true);
         return ::success;

      }

      ::e_status     device::get_destination(::multimedia::audio_mixer::e_destination edestination, ::multimedia::audio_mixer::destination **ppDestination)
      {

         u32 dwComponentType;

         switch(edestination)
         {
         case ::multimedia::audio_mixer::destination_speakers:
            dwComponentType = MIXERLINE_COMPONENTTYPE_DST_SPEAKERS;
            break;

         default:
            return error_failed;
         };


         if(m_mixerdestinationa.get_size() <= 0)
            initialize_destinations();

         if(m_mixerdestinationa.get_size() <= 0)
            return error_failed;

         for(i32 i = 0; i < m_mixerdestinationa.get_size(); i++)
         {

            __pointer(::multimedia::audio_mixer_mmsystem::destination) destination = m_mixerdestinationa(i);

            u32 dw = destination->m_mixerline.dwComponentType;

            if(dw == dwComponentType)
            {

               *ppDestination = m_mixerdestinationa(i);

               return ::success;

            }

         }

         return error_failed;

      }

      void device::map_controls()
      {

         m_mapIDToControl.remove_all();

         for(i32 i = 0; i < m_mixerdestinationa.get_size(); i++)
         {

            __pointer(::multimedia::audio_mixer_mmsystem::destination) destination = m_mixerdestinationa(i);

            MapLineControls(destination);

            ::multimedia::audio_mixer::source_array & sourcea = destination->get_source_info();

            for(i32 j = 0; j < sourcea.get_size(); j++)
            {

               __pointer(::multimedia::audio_mixer::source) source = sourcea(j);

               MapLineControls(source);

            }

         }

      }


      void device::map_lines()
      {

         m_mapIDToLine.remove_all();

         for(i32 i = 0; i < m_mixerdestinationa.get_size(); i++)
         {

            __pointer(::multimedia::audio_mixer_mmsystem::destination) destination = m_mixerdestinationa(i);

            m_mapIDToLine.set_at(destination->get_mixer_line().dwLineID, destination);

            ::multimedia::audio_mixer::source_array & sourcea = destination->get_source_info();

            for(i32 j = 0; j < sourcea.get_size(); j++)
            {

               __pointer(::multimedia::audio_mixer_mmsystem::source) source = sourcea(j);

               m_mapIDToLine.set_at(source->m_mixerline.dwLineID, source);

            }

         }

      }

      void device::OnMixerLineChange(u32 dwLineID)
      {
         ::multimedia::audio_mixer::source * pSource;
         if(m_mapIDToLine.lookup(dwLineID, pSource))
         {
            pSource->OnMixerLineChange();
         }
      }

      void device::OnMixerControlChange(u32 dwControlID)
      {
         ::multimedia::audio_mixer::control * pControl;
         if(m_mapIDToControl.lookup(dwControlID, pControl))
         {
            pControl->OnMixerControlChange();
         }
      }

      void device::MapLineControls(::multimedia::audio_mixer::source * psource)
      {
         ::multimedia::audio_mixer::control_array & controla = psource->get_control_array();
         for(i32 k = 0; k < controla.get_size(); k++)
         {
            __pointer(::multimedia::audio_mixer_mmsystem::control) control = controla(k);
            m_mapIDToControl.set_at(control->GetMixerControl().dwControlID, control);
            for(i32 l = 0; l < control->get_size(); l++)
            {
               __pointer(::multimedia::audio_mixer::user::control) pinteraction = control->operator ()(l);
               m_mapDlgItemIDToControl.set_at(pinteraction->_GetDlgCtrlID(), control);
            }
         }
      }

      void device::MapDlgCtrlIDToControls()
      {
         m_mapDlgItemIDToControl.remove_all();

         ::multimedia::audio_mixer::destination_array & destinationa = m_mixerdestinationa;
         for(i32 i = 0; i < destinationa.get_size(); i++)
         {
            __pointer(::multimedia::audio_mixer_mmsystem::destination) destination = destinationa(i);
            MapDlgCtrlIDToLineControls(destination);
            ::multimedia::audio_mixer::source_array & sourcea = destination->get_source_info();
            for(i32 j = 0; j < sourcea.get_size(); j++)
            {
               ::multimedia::audio_mixer::source & source = sourcea[j];
               MapDlgCtrlIDToLineControls(&source);
            }
         }

      }

      void device::MapDlgCtrlIDToLineControls(::multimedia::audio_mixer::source * psource)
      {
         ::multimedia::audio_mixer::control_array & controla = psource->get_control_array();
         for(i32 k = 0; k < controla.get_size(); k++)
         {
            __pointer(::multimedia::audio_mixer::control) control = controla(k);
            for(i32 l = 0; l < control->get_size(); l++)
            {
               __pointer(::multimedia::audio_mixer::user::control) pinteraction = control->operator()(l);
               m_mapDlgItemIDToControl.set_at(pinteraction->_GetDlgCtrlID(), control);
            }
         }
      }


      ::e_status     device::close()
      {

         ::e_status     mmrc = ::success;

         if(m_hMixer != nullptr)
         {

            mmrc = mmsystem::translate(mixerClose(m_hMixer));

            m_mixerdestinationa.remove_all();

            m_mapIDToControl.remove_all();

            m_mapDlgItemIDToControl.remove_all();

            m_mapIDToLine.remove_all();

            m_hMixer = nullptr;

         }

         return mmrc;

      }

      bool device::OnCommand(wparam wparam, lparam lparam)
      {

         u32 uiID = LOWORD(wparam);

         ::multimedia::audio_mixer::control * pinteraction;

         if(m_mapDlgItemIDToControl.lookup(uiID, pinteraction)
               && pinteraction->OnCommand(wparam, lparam))
            return true;

         return false;

      }


      string device::get_product_name()
      {

         return m_mixercaps.szPname;

      }


      ::multimedia::audio_mixer::audio_mixer * device::get_mixer()
      {
         return m_pmixer;
      }


   } // namespace audio_mixer_mmsystem


} // namespace multimedia


