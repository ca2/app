// Created by camilo on 2021-08-09 14:40 BRT <3ThomasBorregaardS�rensen!!
#pragma once


enum enum_seek
{

   e_seek_set = 0x0,
   e_seek_current = 0x1,
   e_seek_from_end = 0x2,

};


enum enum_path
{

   e_path_none,
   e_path_file,
   e_path_url,
   e_path_data

};






namespace file
{

   enum enum_open
   {
      e_open_read = (i32)0x000001,
      e_open_write = (i32)0x000002,
      e_open_read_write = (i32)0x000003,
      e_open_share_compat = (i32)0x000000,
      e_open_share_exclusive = (i32)0x000010,
      e_open_share_deny_write = (i32)0x000020,
      e_open_share_deny_read = (i32)0x000030,
      e_open_share_deny_none = (i32)0x000040,
      e_open_share_mask = e_open_share_deny_none | e_open_share_deny_read | e_open_share_deny_write | e_open_share_exclusive,
      e_open_no_inherit = (i32)0x000080,
      e_open_create = (i32)0x001000,
      e_open_no_truncate = (i32)0x002000,
      e_open_text = (i32)0x004000, // type_text and type_binary are used in
      e_open_binary = (i32)0x008000, // derived classes only
      e_open_defer_create_directory = (i32)0x010000,
      e_open_update_unknown_length_supported = (i32)0x020000,
      e_open_truncate = (i32)0x040000,
      e_open_no_callstack = (i32)0x080000,
      e_open_no_cache = (i32)0x100000,
      e_open_no_share_violation_wait = (i32)0x200000,
      e_open_no_exception_on_open = (i32)0x10000000,
      //binary = type_binary,
      //out = mode_write,
      //in = mode_read,
      //trunc = mode_truncate
   };


   enum enum_state
   {

      e_state_read_line_truncated = 1,

   };




} // namespace file



