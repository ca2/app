// Created by camilo on 2021-08-09 14:40 BRT <3ThomasBorregaardSorensen!!
#pragma once


enum enum_seek
{

   e_seek_set = 0x0,
   e_seek_current = 0x1,
   e_seek_from_end = 0x2,

};


namespace file
{


   enum enum_open
   {

      e_open_none = 0,
      e_open_read = (int)0x000001,
      e_open_write = (int)0x000002,
      e_open_read_write = (int)0x000003,
      e_open_share_compat = (int)0x000000,
      e_open_share_exclusive = (int)0x000010,
      e_open_share_deny_write = (int)0x000020,
      e_open_share_deny_read = (int)0x000030,
      e_open_share_deny_none = (int)0x000040,
      e_open_share_mask = e_open_share_deny_none | e_open_share_deny_read | e_open_share_deny_write | e_open_share_exclusive,
      e_open_no_inherit = (int)0x000080,
      e_open_create = (int)0x001000,
      e_open_no_truncate = (int)0x002000,
      e_open_text = (int)0x004000, // type_text and type_binary are used in
      e_open_binary = (int)0x008000, // derived classes only
      e_open_defer_create_directory = (int)0x010000,
      e_open_update_unknown_length_supported = (int)0x020000,
      e_open_truncate = (int)0x040000,
      e_open_no_callstack = (int)0x080000,
      e_open_no_cache = (int)0x100000,
      e_open_no_share_violation_wait = (int)0x200000,
      e_open_no_follow_uniform_resource_locator = (int)0x400000,
      e_open_no_exception_on_open = (int)0x10000000,
      e_open_file = (int)0x20000000,
      e_open_no_exception_if_not_found = (int)0x40000000,


   };


   enum enum_state
   {

      e_state_none = 0,
      e_state_end_of_file = 1,
      e_state_read_line_truncated = 2,

   };


   DECLARE_ENUMERATION(e_open, enum_open);
   DECLARE_ENUMERATION(e_state, enum_state);


} // namespace file

