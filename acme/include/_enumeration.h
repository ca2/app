// Created by camilo on 2022-11-01 23:14 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/primitive/primitive/enumeration.h"
#include "acme/filesystem/file/_constant.h"


enum enum_as_block
{

   e_as_block,

};


enum enum_as_little_endian_block
{

   e_as_little_endian_block,

};


enum enum_as_typed_block
{

   e_as_typed_block,

};


DECLARE_ENUMERATION(e_message_box, enum_message_box);
DECLARE_ENUMERATION(e_dock, enum_dock);
DECLARE_ENUMERATION(e_border, enum_border);
DECLARE_ENUMERATION(e_grip, enum_grip);






namespace user
{

   DECLARE_ENUMERATION(e_flag, enum_flag);

} // namespace user

DECLARE_ENUMERATION(e_command, enum_command);

namespace library
{

   DECLARE_ENUMERATION(e_state, enum_state);

} // namespace library



using eiostate = ::enumeration<::file::e_iostate>;

using ecommand = ::enumeration<enum_command>;

using echeck = ::enumeration<enum_check>;

