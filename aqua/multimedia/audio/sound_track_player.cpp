#include "framework.h"


namespace aura
{


   sound_track_player::sound_track_player()
   {

   }


   sound_track_player::~sound_track_player()
   {

   }


   ::e_status sound_track_player::defer_start(::wave::e_purpose epurpose)
   {


      return ::success;

   }


   string sound_track_player::sound_path(const char* psz)
   {

      return "";

   }


   file_pointer sound_track_player::sound_file(const char* psz)
   {


      return nullptr;

   }


   __pointer(::object) sound_track_player::sound_plugin(const char* psz, bool bForceCreate, bool bLoop)
   {

      return nullptr;

   }


   void sound_track_player::mix(::audio::plugin* ppluginParam)
   {


   }


   void sound_track_player::mix(const char* psz)
   {


   }


   ::wave::player* sound_track_player::get_wave_player()
   {

      return nullptr;

   }


} // namespace aura



