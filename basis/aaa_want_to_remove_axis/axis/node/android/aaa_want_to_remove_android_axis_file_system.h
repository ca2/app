#pragma once


namespace android
{


   namespace axis
   {


      class CLASS_DECL_AXIS file_system :
         virtual public ::android::file_system,
         virtual public ::file::axis::system
      {
      public:


         file_system(::context_object * pcontextobject);

         virtual file_pointer get_file(::payload varFile, ::u32 nOpenFlags, ::extended::status * pfesp, ::aura::application * papp);

      };


   } // namespace axis


} // namespace android





