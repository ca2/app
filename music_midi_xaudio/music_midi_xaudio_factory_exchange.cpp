#include "framework.h"


namespace music
{


   namespace midi
   {


      namespace mmsystem
      {


         factory_exchange::factory_exchange()
         {

            create_factory < sequence                    >  (__type(::music::midi::sequence));
            create_factory < buffer                      >  (__type(::music::midi::file::buffer));
            create_factory < sequence_thread             >  (__type(::music::midi::sequence_thread));
            create_factory < player::player              >  (__type(::music::midi::player::player));
            create_factory < player:: player_interface   >  (__type(::music::midi::player::player_interface));

         }


         factory_exchange::~factory_exchange()
         {

         }


      } // namespace mmsystem


   } // namespace midi_mmsystem


} // namespace music


void factory_exchange()
{

   ::music::midi::mmsystem::factory_exchange factoryexchange();

}









