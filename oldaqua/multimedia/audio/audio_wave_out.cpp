#include "framework.h"


//namespace aura
//{
//
//
//   namespace audio
//   {
//
//
//      out::out(::object * pobject) :
//         ::object(pobject)
//      {
//
//         defer_create_mutex();
//
//      }
//
//
//      out::~out()
//      {
//
//
//      }
//
//
//      bool out::out_push_packet(WAVE_OUT_PACKET * ppacket)
//      {
//
//         single_lock sl(mutex());
//
//         auto & a = m_mapPacket[ppacket->m_chChannel];
//
//         a.insert_at(0, ppacket);
//
//         return;
//
//      }
//
//
//
//      WAVE_OUT_PACKET * out::out_pop_packet(char chChannel)
//      {
//
//         single_lock sl(mutex());
//
//         auto & a = m_mapPacket[chChannel];
//
//         if(a.is_empty())
//         {
//
//            return nullptr;
//
//         }
//
//         return a.pop();
//
//      }
//
//
//   } // namespace audio
//
//
//} // namespace aura
//
//
//
//
//
//CLASS_DECL_AQUA bool out_push_packet(WAVE_OUT_PACKET * ppacket)
//{
//
//   return ::get_context_system()->m_spwaveout->out_push_packet(ppacket);
//
//}
//
//
//CLASS_DECL_AQUA WAVE_OUT_PACKET * out_pop_packet(char chChannel)
//{
//
//   return ::get_context_system()->m_spwaveout->out_pop_packet(chChannel);
//
//}




LPWAVEOUT waveout_open(int iChannel, LPAUDIOFORMAT pformat, LPWAVEOUT_CALLBACK pcallback)
{

   return ::get_context_system()->waveout_open(iChannel, pformat, pcallback);

}


CLASS_DECL_AQUA int waveout_start(LPWAVEOUT pwaveout)
{

   return (*pwaveout->waveout_start)(pwaveout->waveoutcontext);

}

CLASS_DECL_AQUA int waveout_write(LPWAVEOUT pwaveout, const void * pdata, unsigned int s)
{

   return (*pwaveout->waveout_write)(pwaveout->waveoutcontext, pdata, s);

}

CLASS_DECL_AQUA int waveout_stop(LPWAVEOUT pwaveout)
{

   return (*pwaveout->waveout_stop)(pwaveout->waveoutcontext);

}

CLASS_DECL_AQUA int waveout_close(LPWAVEOUT pwaveout)
{

   return (*pwaveout->waveout_close)(pwaveout->waveoutcontext);

}




