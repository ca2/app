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

         //virtual int get_image_foo(oswindow oswindow, const ::scoped_string & scopedstrExtension, e_file_attribute eattribute, e_icon eicon, color32_t crBk = 0) override;
         //virtual int get_file_extension_image(oswindow oswindow, const ::scoped_string & scopedstrExtension, e_file_attribute eattribute, e_icon eicon, color32_t crBk = 0) override;
         int get_image_by_file_extension(image_key & imagekey);
         //virtual int get_image(oswindow oswindow, const ::scoped_string & scopedstrPath, e_file_attribute eattribute, e_icon eicon, color32_t crBk = 0) override;


         virtual void on_update_sizes_interest() override;


         virtual int impl_get_file_image(const image_key & imagekey) override;


         virtual ::user::shell::e_folder get_folder_type(::particle * pparticle, const ::wide_character * lpcszPath) override;
         virtual ::user::shell::e_folder get_folder_type(::particle * pparticle, const char * lpcszPath) override;

         int add_icon_path(::file::path path, color32_t crBk);



//         int get_image(per_fork * pfork, oswindow oswindow, image_key key, const unichar * lpcszExtra, color32_t crBk);
//         int get_image_by_extension(per_fork * pfork, oswindow oswindow, image_key & key, color32_t crBk);
//         int get_foo_image(per_fork * pfork, oswindow oswindow, image_key key, color32_t crBk);



         //int shell_run();





      };


   //} // namespace linux


} // namespace filemanager


