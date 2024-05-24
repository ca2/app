//
// Created by camilo on 2022-10-28 23:33 <3ThomasBorregaardSorensen!!
//
#pragma once


CLASS_DECL_ACID string consume_command_line_parameter(const ::scoped_string & scopedstrCommandLine, const char ** pszEndPtr);
CLASS_DECL_ACID bool is_command_line_parameter_true(string & strValue, const ::scoped_string & scopedstrCommandLine, const ::scoped_string & scopedstrParam, bool bDefault = false);
CLASS_DECL_ACID bool get_command_line_parameter(string & strValue, const ::scoped_string & scopedstrCommandLine, const ::scoped_string & scopedstrParam);
CLASS_DECL_ACID bool get_command_line_parameter(string & strValue, const ::scoped_string & scopedstrCommandLine, const ::scoped_string & scopedstrParam, const ::scoped_string & scopedstrDefault);
CLASS_DECL_ACID string get_command_line_parameter(const ::scoped_string & scopedstrCommandLine, const ::scoped_string & scopedstrParam);


CLASS_DECL_ACID string_array command_arguments_from_command_line(const ::string & strCommandLine);
//CLASS_DECL_ACID string executable_title_from_appid(string str);



CLASS_DECL_ACID void prepare_argc_argv(int & argc, char ** argv, char * cmd_line);


CLASS_DECL_ACID string transform_to_c_arg(const ::scoped_string & scopedstr);
CLASS_DECL_ACID string_array get_c_args_from_string(const ::scoped_string & scopedstr);
CLASS_DECL_ACID string_array no_escape_get_c_args_from_string(const ::scoped_string & scopedstr);
CLASS_DECL_ACID string_array get_c_args_from_c(const ::scoped_string & scopedstr);
CLASS_DECL_ACID string_array get_c_args_for_c(const ::scoped_string & scopedstr);
CLASS_DECL_ACID string_array get_c_args(int argc, char ** argv);



