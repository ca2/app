#include "framework.h"


namespace music
{


   namespace midi
   {


      namespace mmsystem
      {


         ::e_status     MMRESULT mmr
         {

            if(mmr == MMSYSERR_NOERROR)
            {

               return ::success;

            }
            else
            {

               return error_failed;

            }

         }


      } // namespace mmsystem

   } // namespace midi_mmsystem


} // namespace music