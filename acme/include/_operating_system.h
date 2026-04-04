// Created by speccylad(Twitch) 
// From https://github.com/deetonn/stud/blob/master/stud/forward.hpp
// by camilo on 2023-10-20 00:37 <3ThomasBorregaardSorensen!!
// Merged acme/constant/_constant.h:enum_operating_system on 2023-10-20 00:50 by camilo
#pragma once


//#ifndef _STUD_FORWARD_HPP

//#define _STUD_API_BEGIN namespace stud {
//#define _STUD_UNSTABLE_API_BEGIN namespace stud::unsafe {
//#define _STUD_DETAIL_API namespace stud::__detail {
//#define _STUD_API_END }

//#define _STUD_API_BEGIN 
//#define _STUD_UNSTABLE_API_BEGIN 
////#define _STUD_DETAIL_API 
//#define _STUD_API_END 

#define _STUD_API inline constexpr

#define _STUD_NODISCARD [[nodiscard]]

#define _STUD_NOEXCEPT(expr) noexcept(noexcept(expr))

//#define DISCARD(expr) ((void)expr)
//#define NOOP() DISCARD(0)

//#define _STUD ::stud::
//#define _DETAIL ::stud::__detail::

#define _NODISCARD [[nodiscard]]

//_STUD_DETAIL_API


enum enum_operating_system
{


   e_operating_system_unknown = -1,
   e_operating_system_none = 0,
   e_operating_system_current,
   e_operating_system_windows,
   e_operating_system_macos,
   e_operating_system_ios,
   e_operating_system_linux,
   e_operating_system_android,
   e_operating_system_unix,
   e_operating_system_freebsd,


};
