#include "framework.h"

//
//namespace node_gnome
//{
//
//
//   factory_exchange::factory_exchange()
//   {
//
//      create_factory < node, ::acme::node > ();
//
//   }
//
//
//   factory_exchange::~factory_exchange()
//   {
//
//   }
//
//
//} // namespace music
//
//
//
//





extern "C"
void node_ansios_factory_exchange()
{

   create_factory < ::node_ansios::file_memory_map, ::file::memory_map > ();

}



