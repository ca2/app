//
//  user_key_enum.h
//  base
//
//  moved from aura on 16 de Novembro de 2013
//
#pragma once


#include "acme/constant/user.h"
#include "acme/prototype/prototype/enumeration.h"


DECLARE_ENUMERATION(e_system_command, enum_system_command);


namespace user
{

   DECLARE_ENUMERATION(e_mouse, enum_mouse);
   DECLARE_ENUMERATION(e_key, enum_key);
   DECLARE_ENUMERATION(e_zorder, enum_zorder);


   DECLARE_ENUMERATION(e_interaction, enum_interaction);

} // namespace user


DECLARE_ENUMERATION(e_tool_item_state, enum_tool_item_state);
DECLARE_ENUMERATION(e_tool_item_style, enum_tool_item_style);



