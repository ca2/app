// From acme/platform/error.h by camilo on 2023-07-06 08:41 <3ThomasBorregaardSorense!!


#pragma once


CLASS_DECL_ACME::e_status get_last_status();
CLASS_DECL_ACME void set_last_status(const ::e_status & estatus);


struct c_error_number_t {};


/// Class with static functions to get information about an error.
class CLASS_DECL_ACME c_error_number
{
public:


   ::i32          m_iErrorNumber;


   c_error_number();
   c_error_number(c_error_number_t, ::i32 iErrorNumber);
   c_error_number(const c_error_number & cerrornumber);


   ::string get_error_description();


   ::e_status as_status();


   ::e_status set_last_errno_status();

   static c_error_number s_errno();

   static string s_get_error_description(c_error_number cerrornumber = s_errno());

   static void s_throw_exception(c_error_number cerrornumber);


};


