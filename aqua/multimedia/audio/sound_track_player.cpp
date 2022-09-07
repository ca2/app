#include "framework.h"
#include "sound_track_player.h"


namespace aqua
{


   sound_track_player::sound_track_player()
   {

   }


   sound_track_player::~sound_track_player()
   {

   }


   void sound_track_player::defer_start(::wave::enum_purpose epurpose)
   {


      //return ::success;

   }


   string sound_track_player::sound_path(const ::string & str)
   {

      return "";

   }


   file_pointer sound_track_player::sound_file(const ::string & psz)
   {


      return nullptr;

   }


   __pointer(::object) sound_track_player::sound_plugin(const ::string & psz, bool bForceCreate, bool bLoop)
   {

      return nullptr;

   }


   void sound_track_player::mix(::audio::plugin* ppluginParam)
   {


   }


   void sound_track_player::mix(const ::string & psz)
   {


   }


   ::wave::player* sound_track_player::get_wave_player()
   {

      return nullptr;

   }


} // namespace aqua



