#include "framework.h"


namespace music
{


   namespace midi
   {


      namespace mmsystem
      {


         out::out(::layered * pobjectContext) :
            ::object(pobject),
            ::music::midi::out(pobject)
         {

            m_hmidiout = nullptr;

         }


         out::~out()
         {

            close();

         }


         ::e_status     out::open()
         {

            MMRESULT estatus;

            u32 uDeviceID = 0;

            m_hmidiout = nullptr;

            estatus = midiOutOpen(&m_hmidiout, uDeviceID,  0, 0, CALLBACK_NULL);

            if(estatus != MMSYSERR_NOERROR)
               return error_failed;


            return ::success;

         }

         ::e_status     out::close()
         {

            if(m_hmidiout != nullptr)
            {

               midiOutClose(m_hmidiout);

            }

            return ::success;

         }

         ::e_status     out::send_short_message(::music::midi::enum_type etype, int iChannel, int iData1, int iData2)
         {

            return midiOutShortMsg(m_hmidiout, MIDIMSG(((int) etype) >> 4, iChannel, iData1, iData2));

         }


      } //


   } // namespace midi_mmsystem


} // namespace music




