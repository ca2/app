//
// Created by camilo on 2024-06-21 17-43 <3ThomasBorregaardSorensen!!.
//
#include "framework.h"
#include <stdio.h>
#include <cstdarg>

void fprint_line(FILE * pfile, const ::scoped_string & scopedstr);
void fprint_out(FILE * pfile, const ::scoped_string & scopedstr);
void fprintf_line(FILE * pfile, const ::ansi_character * pszFormat, ...);
void fprintf_out(FILE * pfile, const ::ansi_character * pszFormat, ...);
void fprintf_line_arguments(FILE * pfile, const ::ansi_character * pszFormat, va_list arguments);
void fprintf_out_arguments(FILE * pfile, const ::ansi_character * pszFormat, va_list arguments);


void fprint_line(FILE * pfile, const ::scoped_string & scopedstr)
{

   ::string str(scopedstr);

   str += "\n";

   fprint_out(pfile, str);

}


void fprint_out(FILE * pfile, const ::scoped_string & scopedstr)
{

   fwrite(scopedstr.begin(), 1, scopedstr.size(), pfile);

   fflush(pfile);

}


void fprintf_line(FILE * pfile, const ::ansi_character * pszFormat, ...)
{

   va_list arguments;

   va_start (arguments, pszFormat);

   ::string str;

   str.formatf_arguments(pszFormat, arguments);

   fprint_line(pfile, str);

   va_end (arguments);

}


void printf_out(FILE * pfile, const ::ansi_character * pszFormat, ...)
{

   va_list arguments;

   va_start (arguments, pszFormat);

   ::string str;

   str.formatf_arguments(pszFormat, arguments);

   fprint_out(pfile, str);

   va_end (arguments);

}


void printf_line_arguments(const ::ansi_character * pszFormat, va_list arguments)
{

   fprintf_line_arguments(stdout, pszFormat, arguments);

}


void printf_out_arguments(const ::ansi_character * pszFormat, va_list arguments)
{

   fprintf_out_arguments(stdout, pszFormat, arguments);

}


void errf_line_arguments(const ::ansi_character * pszFormat, va_list arguments)
{

   fprintf_line_arguments(stderr, pszFormat, arguments);

}


void errf_out_arguments(const ::ansi_character * pszFormat, va_list arguments)
{

   fprintf_out_arguments(stderr, pszFormat, arguments);

}


void print_line(const ::scoped_string & scopedstr)
{

   fprint_line(stdout, scopedstr);

}


void print_out(const ::scoped_string & scopedstr)
{

   fprint_out(stdout, scopedstr);

}


void printf_line(const ::ansi_character * pszFormat, ...)
{

   va_list arguments;

   va_start (arguments, pszFormat);

   fprintf_line_arguments(stdout, pszFormat, arguments);

   va_end (arguments);

}


void printf_out(const ::ansi_character * pszFormat, ...)
{

   va_list arguments;

   va_start (arguments, pszFormat);

   fprintf_out_arguments(stdout, pszFormat, arguments);

   va_end (arguments);

}


void err_line(const ::scoped_string & scopedstr)
{

   fprint_line(stderr, scopedstr);

}


void err_out(const ::scoped_string & scopedstr)
{

   fprint_out(stderr, scopedstr);

}



void errf_line(const ::ansi_character * pszFormat, ...)
{

   va_list arguments;

   va_start (arguments, pszFormat);

   fprintf_line_arguments(stderr, pszFormat, arguments);

   va_end (arguments);

}


void errf_out(const ::ansi_character * pszFormat, ...)
{

   va_list arguments;

   va_start (arguments, pszFormat);

   fprintf_out_arguments(stderr, pszFormat, arguments);

   va_end (arguments);

}

