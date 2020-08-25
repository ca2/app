#pragma once


#include "aura/user/user/shell.h"


namespace uwp
{


   class CLASS_DECL_AURA shell :
      virtual public ::user::shell
   {
   public:


      shell();
      virtual ~shell();


      virtual ::user::shell::e_folder get_folder_type(::object * pobject, const unichar * lpcszPath) override;
      virtual ::user::shell::e_folder get_folder_type(::object * pobject, const char * lpcszPath) override;


      virtual i32 impl_get_file_image(const image_key & imagekey) override;


      i32 get_image_by_extension(const image_key & key, COLORREF crBk);


      virtual void do_initialize() override;


   };


} // namespace uwp



