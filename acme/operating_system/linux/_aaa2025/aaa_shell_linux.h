#pragma once


#include "acme/user/user/shell.h"

namespace linux
{


   //namespace shell
   //{


      class CLASS_DECL_ACME shell :
         virtual public ::user::shell
      {
      public:



         shell();
         virtual ~shell();


         //virtual void initialize() override;

         //virtual void defer_start();

         //virtual ::i32 get_image_foo(::acme::windowing::window * pacmewindowingwindow, const ::scoped_string & scopedstrExtension, e_file_attribute eattribute, e_icon eicon, color32_t crBk = 0) override;
         //virtual ::i32 get_file_extension_image(::acme::windowing::window * pacmewindowingwindow, const ::scoped_string & scopedstrExtension, e_file_attribute eattribute, e_icon eicon, color32_t crBk = 0) override;
         ::i32 get_image_by_file_extension(image_key & imagekey);
         //virtual ::i32 get_image(::acme::windowing::window * pacmewindowingwindow, const ::scoped_string & scopedstrPath, e_file_attribute eattribute, e_icon eicon, color32_t crBk = 0) override;


         virtual void on_update_sizes_interest() override;


         virtual ::i32 impl_get_file_image(const image_key & imagekey) override;


         virtual ::user::shell::e_folder get_folder_type(::particle * pparticle, const ::wide_character * lpcszPath) override;
         virtual ::user::shell::e_folder get_folder_type(::particle * pparticle, const_char_pointer lpcszPath) override;

         ::i32 add_icon_path(::file::path path, color32_t crBk);



//         ::i32 get_image(per_fork * pfork, ::acme::windowing::window * pacmewindowingwindow, image_key key, const wide_character * lpcszExtra, color32_t crBk);
//         ::i32 get_image_by_extension(per_fork * pfork, ::acme::windowing::window * pacmewindowingwindow, image_key & key, color32_t crBk);
//         ::i32 get_foo_image(per_fork * pfork, ::acme::windowing::window * pacmewindowingwindow, image_key key, color32_t crBk);



         //::i32 shell_run();





      };


   //} // namespace linux


} // namespace filemanager


