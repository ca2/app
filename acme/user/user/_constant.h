//
//  user_key_enum.h
//  base
//
//  moved from aura on 16 de Novembro de 2013
//
#pragma once


//#include "acme/constant/button_state.h"
#include "acme/constant/key_state.h"
#include "acme/constant/user.h"
#include "acme/prototype/prototype/enumeration.h"


DECLARE_C_FLAG(e_system_command, enum_system_command);


namespace user
{

   //DECLARE_C_FLAG(e_mouse, enum_mouse);
   //DECLARE_C_FLAG(e_button_state, enum_button_state);
   DECLARE_C_FLAG(e_key_state, enum_key_state);
   DECLARE_ENUMERATION(e_key, enum_key);
   DECLARE_C_FLAG(e_zorder, enum_zorder);


   DECLARE_C_FLAG(e_interaction, enum_interaction);

} // namespace user


DECLARE_C_FLAG(e_tool_item_state, enum_tool_item_state);
DECLARE_C_FLAG(e_tool_item_style, enum_tool_item_style);



