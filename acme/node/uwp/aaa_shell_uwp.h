#pragma once


#include "acme/user/shell.h"


namespace universal_windows
{


   class CLASS_DECL_ACME shell :
      virtual public ::user::shell
   {
   public:


      shell();
      virtual ~shell();


      virtual ::user::shell::e_folder get_folder_type(::matter * pobject, const unichar * lpcszPath) override;
      virtual ::user::shell::e_folder get_folder_type(::matter * pobject, const char * lpcszPath) override;


      virtual i32 impl_get_file_image(const image_key & imagekey) override;


      i32 get_image_by_extension(const image_key & key, color32_t crBk);


      virtual void do_initialize() override;


   };


} // namespace universal_windows



