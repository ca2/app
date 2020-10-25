#include "framework.h"


namespace multimedia
{


   namespace audio_mixer_mmsystem
   {


      window::window(__pointer(base_application) papp) :
         ::object(pobject)
      {
         create_message_queue("");
      }

      window::~window()
      {
      }

      void window::install_message_routing(::channel * pchannel)
      {
         ::user::interaction::install_message_routing(pchannel);
         MESSAGE_LINK(MM_MIXM_CONTROL_CHANGE, pchannel, this, &window::_001OnMixerControlChange);
         MESSAGE_LINK(MM_MIXM_LINE_CHANGE, pchannel, this, &window::_001OnMixerLineChange);
      }

      void window::_001OnMixerControlChange(::message::message * pmessage)
      {
         IGUI_WIN_CST(base);
         (dynamic_cast < ::multimedia::audio_mixer_mmsystem::audio_mixer * > (m_pmixer))->OnMixerControlChange((HMIXER) pbase->m_wparam, (u32) pbase->m_lparam);
         pbase->set_lresult(0);
      }

      void window::_001OnMixerLineChange(::message::message * pmessage)
      {
         IGUI_WIN_CST(base);
         (dynamic_cast < ::multimedia::audio_mixer_mmsystem::audio_mixer * > (m_pmixer))->OnMixerLineChange((HMIXER) pbase->m_wparam, (u32) pbase->m_lparam);
         pbase->set_lresult(0);
      }


   } // namespace audio_mixer_mmsystem


} // namespace multimedia






