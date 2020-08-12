#include "framework.h"


//namespace music
//{
//   
//   
//   namespace midi
//   {
//      
//      
//      namespace core_midi
//      {
//         
//
//         factory_exchange::factory_exchange()
//         {
//
//            //create_factory < sequence        , ::music::midi::sequence >();
//            create_factory < file            , ::music::midi::file>();
//            //create_factory < sequence_thread , ::music::midi::sequence_thread>();
//            create_factory < player          , ::music::midi::player>();
//            create_factory < midi            , ::music::midi::midi> ();
//
//         }
//
//
//         factory_exchange::~factory_exchange()
//         {
//         }
//
//         
//      } // namespace core_midi
//
//      
//   } // namespace midi
//
//
//} // namespace music
//

extern "C" void music_midi_core_midi_factory_exchange()
{

   //::music::midi::core_midi::factory_exchange factoryexchange();
   //create_factory < sequence        , ::music::midi::sequence >();
//   create_factory < ::music::midi::core_midi::buffer            , ::music::midi::file>();
//   //create_factory < sequence_thread , ::music::midi::sequence_thread>();
//   create_factory < ::music::midi::core_midi::player          , ::music::midi::player>();
   create_factory < ::music::midi::core_midi::midi            , ::music::midi::midi> ();
}









