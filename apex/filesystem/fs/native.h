#pragma once


#include "data.h"


namespace fs
{


// fs::interface - file system interface


   class CLASS_DECL_APEX native :
      virtual public ::fs::data
   {
   public:


      native();
      ~native() override;


      //bool _enumerates(::file::listing & listing) override;
      bool enumerate(::file::listing & listing) override;
      // virtual ::file::listing & ls_relative_name(::file::listing & listing) override;


      bool is_link(const ::file::path & path) override;

      // optional if ls_dir is implemented
      bool has_subdir(const ::file::path & path) override;


      bool fast_has_subdir(const ::file::path & path) override;

      int is_dir(const ::file::path & path) override;
      ::file::listing & root_ones(::file::listing & listing) override;

      bool file_exists(const ::file::path & path) override;

      bool file_move(const ::file::path & pathTarget,const ::file::path & pathSource) override;

      file_pointer get_file(const ::payload & payloadFile, ::file::e_open eopen, ::pointer < ::file::exception >* ppfileexception = nullptr) override;


   };


} // namespace fs



