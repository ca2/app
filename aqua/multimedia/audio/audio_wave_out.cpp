#include "framework.h"


//namespace aura
//{
//
//
//   namespace audio
//   {
//
//
//      out::out(::particle * pparticle) :
//         ::object(pparticle)
//      {
//
//         defer_create_synchronization();
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
//         single_lock synchronouslock(this->synchronization());
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
//         single_lock synchronouslock(this->synchronization());
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
//CLASS_DECL_AURA bool out_push_packet(WAVE_OUT_PACKET * ppacket)
//{
//
//   return acmesystem()->m_spwaveout->out_push_packet(ppacket);
//
//}
//
//
//CLASS_DECL_AURA WAVE_OUT_PACKET * out_pop_packet(char chChannel)
//{
//
//   return acmesystem()->m_spwaveout->out_pop_packet(chChannel);
//
//}




//LPWAVEOUT waveout_open(int iChannel, LPAUDIOFORMAT pformat, LPWAVEOUT_CALLBACK pcallback)
//{
//
//   auto paudio = acmesystem()->audio();
//
//   return paudio->waveout_open(iChannel, pformat, pcallback);
//
//}


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



