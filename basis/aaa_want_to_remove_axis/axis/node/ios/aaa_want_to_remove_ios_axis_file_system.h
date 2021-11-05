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




         file_system(::object * pobject);

         virtual file_pointer get_file(::payload payloadFile,::u32 nOpenFlags,::extended::status * pfesp,::aura::application * papp);


      };


   } // namespace axis


} // namespace ios



