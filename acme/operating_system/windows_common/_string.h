// Created by camilo on 2022-11-08 00:24 <3ThomasBorregaardSorensen!!
#pragma once





namespace windows
{


   CLASS_DECL_ACME wstring get_file_path_root(const wstring & wstrPath);
   CLASS_DECL_ACME string last_error_message();
   CLASS_DECL_ACME string last_error_message(const last_error & lasterror);
   CLASS_DECL_ACME string last_error_message(const ::scoped_string & scopedstrErrorMessage, const last_error & lasterror);



} // namespace windows


