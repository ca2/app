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


   enum enum_open : ::uptr
   {

      e_open_none = 0ull,
      e_open_read = 0x000001ull,
      e_open_write = 0x000002ull,
      e_open_read_write = 0x000003ull,
      e_open_share_compat = 0x000000ull,
      e_open_share_exclusive = 0x000010ull,
      e_open_share_deny_write = 0x000020ull,
      e_open_share_deny_read = 0x000030ull,
      e_open_share_deny_none = 0x000040ull,
      e_open_share_mask = e_open_share_deny_none | e_open_share_deny_read | e_open_share_deny_write | e_open_share_exclusive,
      e_open_no_inherit = 0x000080ull,
      e_open_create = 0x001000ull,
      e_open_no_truncate = 0x002000ull,
      e_open_text = 0x004000ull, // type_text and type_binary are used in
      e_open_binary = 0x008000ull, // derived classes only
      e_open_defer_create_directory = 0x010000ull,
      e_open_update_unknown_length_supported = 0x020000ull,
      e_open_truncate = 0x040000ull,
      e_open_no_callstack = 0x080000ull,
      e_open_no_cache = 0x100000ull,
      e_open_no_share_violation_wait = 0x200000ull,
      e_open_no_follow_uniform_resource_locator = 0x400000ull,
      e_open_no_exception_on_open = 0x10000000ull,
      e_open_file = 0x20000000ull,
      e_open_no_exception_if_not_found = 0x40000000ull,
      _e_open_delete = 0x80000000ull,
      _e_open_stat = 0x100000000ull,
      _e_open_set_stat = 0x200000000ull,
      _e_open_create_directory = 0x400000000ull,
      _e_open_set_current_directory = 0x800000000ull,


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

