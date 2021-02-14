#include "framework.h"


namespace music
{


   namespace midi_alsa
   {


      namespace player
      {


         callback::callback(sp(::base::application) papp) :
            m_wnd(papp)
         {
         }

         callback::~callback()
         {
         }


      } // namespace player


   } // namespace midi_alsa


} // namespace music









