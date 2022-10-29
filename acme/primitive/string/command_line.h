//
// Created by camilo on 2022-10-28 23:33 <3ThomasBorregaardSorensen!!
//
#pragma once


CLASS_DECL_ACME string consume_command_line_parameter(const char * pszCommandLine, const char ** pszEndPtr);
CLASS_DECL_ACME bool is_command_line_parameter_true(string & strValue, const char * pszCommandLine, const char * pszParam, bool bDefault = false);
CLASS_DECL_ACME bool get_command_line_parameter(string & strValue, const char * pszCommandLine, const char * pszParam);
CLASS_DECL_ACME bool get_command_line_parameter(string & strValue, const char * pszCommandLine, const char * pszParam, const char * pszDefault);
CLASS_DECL_ACME string get_command_line_parameter(const char * pszCommandLine, const char * pszParam);


CLASS_DECL_ACME string_array command_arguments_from_command_line(const ::string & strCommandLine);
CLASS_DECL_ACME string executable_title_from_appid(string str);



CLASS_DECL_ACME void prepare_argc_argv(int & argc, char ** argv, char * cmd_line);


CLASS_DECL_ACME string transform_to_c_arg(const char * psz);
CLASS_DECL_ACME string_array get_c_args_from_string(const char * psz);
CLASS_DECL_ACME string_array no_escape_get_c_args_from_string(const char * psz);
CLASS_DECL_ACME string_array get_c_args_from_c(const char * psz);
CLASS_DECL_ACME string_array get_c_args_for_c(const char * psz);
CLASS_DECL_ACME string_array get_c_args(int argc, char ** argv);



