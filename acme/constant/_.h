//
// Created by camilo on 04/12/2020. <3Tbs, Mummi and bilbo!!
//
#pragma once


#include "exception.h"

#include "_constant.h"

#include "_id.h"

#include "_message.h"

#include "heap.h"


enum enum_start_reference
{

   e_start_reference,

};


enum enum_array : ::i32
{

   e_array_none = 0,
   // e_array_zeroe_on_allocation = 1,
   // e_array_preallocated = 2,
   e_array_raw = 8,
   // e_array_carriage_return = 4,
   // e_array_disable_referencing_debugging = 1ll << 52,

};


enum enum_font_awesome : ::i32;


enum enum_character_set : ::i32;


enum enum_posix_shell : ::i32;


enum enum_integer_type : ::i32
{

   e_integer_type_char = 0,
   e_integer_type_unsigned_char = 1,
   e_integer_type_short = 2,
   e_integer_type_unsigned_short = 3,
   e_integer_type_int = 4,
   e_integer_type_unsigned_int = 5,
   e_integer_type_i64 = 6,
   e_integer_type_u64 = 7,

};

class eimpact;


enum enum_simple_command : ::i32;
namespace user
{
   enum enum_message : ::u32;
} // namespace user
enum enum_message : ::i32;
enum enum_impact : ::i64;
enum enum_id : ::uptr;
enum enum_check : ::i32;
enum enum_happening : ::i32;

enum enum_platform_level
{

   e_platform_level_acme,
   e_platform_level_apex,

   e_platform_level_aura,
   e_platform_level_axis,
   e_platform_level_base,
   e_platform_level_core,

};





enum enum_image_type
{

   e_image_type_complex,
   e_image_type_plain_color

};



//#include "_mathematics.h"


#include "_geometry.h"


//#include "geometry2d.h"


#include "code_page.h"


#include "cursor.h"


#include "flag.h"


#include "user_text.h"
#include "user.h"
#include "flag.h"


//#include "earth.h"


#include "data.h"


#include "error_code_type.h"


#include "application_capability.h"



enum enum_domain : ::i32
{

   e_domain_none = 0,
   e_domain_1024 = 1024,

};










enum enum_exit
{

   e_exit_close,
   e_exit_application,
   e_exit_session,
   e_exit_system,

};




namespace windowing
{


   enum enum_operating_ambient : ::i64;

   enum enum_toolkit : ::i64;

   enum enum_windowing : ::i64;

   enum enum_display_type : ::i64;

   enum enum_bias : ::i64;


} // namespace windowing



enum enum_dispatch
{

   e_dispatch_none,
   e_dispatch_send = 1,
   e_dispatch_post = 2,
   e_dispatch_fork = 4,
   e_dispatch_main_send = 0x10 | e_dispatch_send,
   e_dispatch_main_post = 0x10 | e_dispatch_post,
   e_dispatch_user_send = 0x100 | e_dispatch_send,
   e_dispatch_user_post = 0x100 | e_dispatch_post,


};




