#pragma once


#include "apex/user/shell.h"

namespace linux
{


   //namespace shell
   //{


      class CLASS_DECL_APEX shell :
         virtual public ::user::shell
      {
      public:



         shell();
         virtual ~shell();


         //virtual void initialize() override;

         //virtual void defer_start();

         //virtual i32 get_image_foo(oswindow oswindow, const string & strExtension, e_file_attribute eattribute, e_icon eicon, COLORREF crBk = 0) override;
         //virtual i32 get_file_extension_image(oswindow oswindow, const string & strExtension, e_file_attribute eattribute, e_icon eicon, COLORREF crBk = 0) override;
         i32 get_image_by_file_extension(image_key & imagekey);
         //virtual i32 get_image(oswindow oswindow, const string & strPath, e_file_attribute eattribute, e_icon eicon, COLORREF crBk = 0) override;


         virtual void on_update_sizes_interest() override;


         virtual i32 impl_get_file_image(const image_key & imagekey) override;


         virtual ::user::shell::e_folder get_folder_type(::object * pobject, const widechar * lpcszPath) override;
         virtual ::user::shell::e_folder get_folder_type(::object * pobject, const char * lpcszPath) override;

         int add_icon_path(::file::path path, COLORREF crBk);



//         i32 get_image(per_fork * pfork, oswindow oswindow, image_key key, const unichar * lpcszExtra, COLORREF crBk);
//         i32 get_image_by_extension(per_fork * pfork, oswindow oswindow, image_key & key, COLORREF crBk);
//         i32 get_foo_image(per_fork * pfork, oswindow oswindow, image_key key, COLORREF crBk);



         //int shell_run();





      };


   //} // namespace linux


} // namespace filemanager


