#pragma once


namespace multimedia
{


   namespace audio_mixer_mmsystem
   {


      class CLASS_DECL_AUDIO_MIXER_MMSYSTEM destination :
         virtual public ::multimedia::audio_mixer_mmsystem::source,
         virtual public ::multimedia::audio_mixer::destination
      {
      public:


         destination(__pointer(base_application) papp);
         destination(const destination & destination);
         virtual ~destination();


         u32 get_component_type();
         void update_all_controls();
         ::estatus     initialize_all_controls();
         ::estatus     initialize_source_info();

         ::multimedia::audio_mixer::source_array & get_source_info();
         void operator delete(void *);

         destination & operator = (const destination & device);

         ::multimedia::audio_mixer::device * get_device();
         void set_device(::multimedia::audio_mixer::device * pdevice);


         virtual u32 get_mixer_line_id();

      };


   } // namespace audio_mixer_mmsystem



} // namespace multimedia




