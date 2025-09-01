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


enum enum_font_awesome : int;


enum enum_character_set : int;


enum enum_posix_shell : int;


enum enum_integer_type : int
{

   e_integer_type_char = 0,
   e_integer_type_unsigned_char = 1,
   e_integer_type_short = 2,
   e_integer_type_unsigned_short = 3,
   e_integer_type_int = 4,
   e_integer_type_unsigned_int = 5,
   e_integer_type_long_long = 6,
   e_integer_type_unsigned_long_long = 7,

};

class eimpact;


enum enum_simple_command : int;
namespace user
{
   enum enum_message : unsigned int;
} // namespace user
namespace message
{
   enum enum_message : int;
} // namespace message
enum enum_impact : long long;
enum enum_id : ::uptr;
enum enum_check : int;
enum enum_happening : int;

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



enum enum_domain : int
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


