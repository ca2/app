#pragma once


namespace aura
{


   class CLASS_DECL_AURA sound_track_player :
      virtual public ::object
   {
   public:


      sound_track_player();
      virtual ~sound_track_player();


      virtual ::estatus defer_start(::wave::e_purpose epurpose);

      virtual __pointer(::object) sound_plugin(const char*, bool bForceCreate = false);

      virtual file_pointer sound_file(const char*);

      virtual string sound_path(const char*);

      virtual void mix(const char*);

      virtual void mix(::audio::plugin* pplugin);

      virtual ::wave::player* get_wave_player();

   };


} // namespace aura



