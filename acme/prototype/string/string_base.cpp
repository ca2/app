// Created by camilo on 2022-10-27 18:42 <3ThomasBorregaardSorensen!!
#include "framework.h"

//
//CLASS_DECL_ACME void copy(::string_base < ::ansi_character > * ptarget, const ::payload * psource)
//{
//
//   *ptarget = psource->get_string();
//
//}
//
//
//CLASS_DECL_ACME void copy(::string_base < ::wd16_character > * ptarget, const ::payload * psource);
//{
//
//   *ptarget = psource->get_string();
//
//}
//
//
//CLASS_DECL_ACME void copy(::string_base < ::wd32_character > * ptarget, const ::payload * psource);
//{
//
//   *ptarget = psource->get_string();
//
//}
//
//
//CLASS_DECL_ACME void copy(::string_base < ::ansi_character > * ptarget, const ::property * psource);
//{
//
//   *ptarget = psource->get_string();
//
//}
//
//
//CLASS_DECL_ACME void copy(::string_base < ::wd16_character > * ptarget, const ::property * psource);
//{
//
//   *ptarget = psource->get_string();
//
//}
//
//
//CLASS_DECL_ACME void copy(::string_base < ::wd32_character > * ptarget, const ::property * psource);
//{
//
//   *ptarget = psource->get_string();
//
//}
//
//
//CLASS_DECL_ACME void copy(::string_base < ::ansi_character > * ptarget, const ::atom * psource);
//{
//
//   *ptarget = psource->get_string();
//
//}
//
//
//CLASS_DECL_ACME void copy(::string_base < ::wd16_character > * ptarget, const ::atom * psource);
//{
//
//   *ptarget = psource->get_string();
//
//}
//
//
//CLASS_DECL_ACME void copy(::string_base < ::wd32_character > * ptarget, const ::atom * psource);
//{
//
//   *ptarget = psource->get_string();
//
//}
//
//
//
//CLASS_DECL_ACME void append(::string_base < ::ansi_character > * ptarget, const ::payload * psource)
//{
//
//   *ptarget += psource->get_string();
//
//}
//
//
//CLASS_DECL_ACME void append(::string_base < ::wd16_character > * ptarget, const ::payload * psource);
//{
//
//   *ptarget += psource->get_string();
//
//}
//
//
//CLASS_DECL_ACME void append(::string_base < ::wd32_character > * ptarget, const ::payload * psource);
//{
//
//   *ptarget += psource->get_string();
//
//}
//
//
//CLASS_DECL_ACME void append(::string_base < ::ansi_character > * ptarget, const ::property * psource);
//{
//
//   *ptarget += psource->get_string();
//
//}
//
//
//CLASS_DECL_ACME void append(::string_base < ::wd16_character > * ptarget, const ::property * psource);
//{
//
//   *ptarget += psource->get_string();
//
//}
//
//
//CLASS_DECL_ACME void append(::string_base < ::wd32_character > * ptarget, const ::property * psource);
//{
//
//   *ptarget += psource->get_string();
//
//}
//
//
//CLASS_DECL_ACME void append(::string_base < ::ansi_character > * ptarget, const ::atom * psource);
//{
//
//   *ptarget += psource->get_string();
//
//}
//
//
//CLASS_DECL_ACME void append(::string_base < ::wd16_character > * ptarget, const ::atom * psource);
//{
//
//   *ptarget += psource->get_string();
//
//}
//
//
//CLASS_DECL_ACME void append(::string_base < ::wd32_character > * ptarget, const ::atom * psource);
//{
//
//   *ptarget += psource->get_string();
//
//}
//
//



CLASS_DECL_ACME string format_arguments(const scoped_string & scopedstrFormat, std::format_args args)
{

   ::std::string_view str1(scopedstrFormat.begin(), scopedstrFormat.end());

   auto stdstr = std::vformat(str1, args);

   ::string str(stdstr.c_str(), stdstr.length());

   return str;

}


CLASS_DECL_ACME wstring wformat_arguments(const scoped_wstring & scopedstrFormat, std::wformat_args args)
{

   ::std::wstring_view str1(scopedstrFormat.begin(), scopedstrFormat.end());

   auto stdwstr = std::vformat(str1, args);

   ::wstring wstr(stdwstr.c_str(), stdwstr.length());

   return wstr;

}



