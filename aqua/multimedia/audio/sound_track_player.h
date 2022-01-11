#pragma once


namespace aura
{


   class CLASS_DECL_AQUA sound_track_player :
      virtual public ::object
   {
   public:


      sound_track_player();
      ~sound_track_player() override;


      virtual void defer_start(::wave::e_purpose epurpose);

      virtual __pointer(::object) sound_plugin(const ::string &, bool bForceCreate = false, bool bLoop = false);

      virtual file_pointer sound_file(const ::string &);

      virtual string sound_path(const ::string &);

      virtual void mix(const ::string &);

      virtual void mix(::audio::plugin* pplugin);

      virtual ::wave::player* get_wave_player();

   };


} // namespace aura



