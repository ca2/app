#include "framework.h"


namespace music
{


   namespace midi_alsa
   {


      namespace player
      {


         player_interface::player_interface(sp(::base::application) papp) :
            element(papp),
            callback(papp),
            ::music::midi::player::player_interface(papp)

         {
            m_psection = NULL;
            m_pmidiplayer = NULL;
         }

         player_interface::~player_interface()
         {

         }


      } // namespace player


   } // namespace midi_alsa


} // namespace music









