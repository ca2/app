#pragma once


enum e_source : u64
{

   source_none = 0,

   source_clear = 1 << 0,
   source_load= 1 << 1,
   source_assign= 1 << 2,
   source_cast= 1 << 3,
   source_submit= 1 << 4,
   source_undo= 1 << 5,
   source_redo= 1 << 6,
   source_copy= 1 << 7,
   source_cut= 1 << 8,
   source_paste= 1 << 9,
   source_sync= 1 << 10,
   source_selection= 1 << 11,
   source_drop= 1 << 12,
   source_initialize= 1 << 13,
   source_refresh= 1 << 14,

   source_operator= 1 << 15,
   source_system= 1 << 16,
   source_default= 1 << 17,
   source_data= 1 << 18,
   source_database= 1 << 19,
   source_user= 1 << 20,

   source_user_test= 1 << 21,
   source_alarm= 1 << 22,
   source_timer= 1 << 23,
   source_command_line= 1 << 24,
   source_internal= 1 << 25,

};


__discrete_cflag(CLASS_DECL_CORE, esource, e_source);



