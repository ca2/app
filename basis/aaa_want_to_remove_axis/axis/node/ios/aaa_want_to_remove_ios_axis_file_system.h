#pragma once


namespace ios
{


   namespace axis
   {


      class CLASS_DECL_AXIS file_system :
         virtual public ::file::axis::system,
         virtual public ::ios::file_system
      {
      public:




         file_system(::layered * pobjectContext);

         virtual file_pointer get_file(payload varFile,::u32 nOpenFlags,::status::result * pfesp,::aura::application * papp);


      };


   } // namespace axis


} // namespace ios



