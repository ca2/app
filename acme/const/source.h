#pragma once


enum enum_source : u64
{

   e_source_none = 0,

   e_source_clear = 1 << 0,
   e_source_load= 1 << 1,
   e_source_assign= 1 << 2,
   e_source_cast= 1 << 3,
   e_source_submit= 1 << 4,
   e_source_undo= 1 << 5,
   e_source_redo= 1 << 6,
   e_source_copy= 1 << 7,
   e_source_cut= 1 << 8,
   e_source_paste= 1 << 9,
   e_source_sync= 1 << 10,
   e_source_selection= 1 << 11,
   e_source_drop= 1 << 12,
   e_source_initialize= 1 << 13,
   e_source_refresh= 1 << 14,

   e_source_operator= 1 << 15,
   e_source_system= 1 << 16,
   e_source_default= 1 << 17,
   e_source_data= 1 << 18,
   e_source_database= 1 << 19,
   e_source_user= 1 << 20,

   e_source_user_test= 1 << 21,
   e_source_alarm= 1 << 22,
   e_source_timer= 1 << 23,
   e_source_command_line= 1 << 24,
   e_source_internal= 1 << 25,

};


DECLARE_C_FLAG(e_source, enum_source);



