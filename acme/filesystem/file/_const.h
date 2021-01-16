#pragma once


namespace file
{


   enum enum_state
   {

      e_state_read_line_truncated = 1,

   };



   enum enum_flag :
      i64
   {

      e_flag_none = 0,
      e_flag_required = 1 << 0,
      e_flag_bypass_cache = 1 << 1,
      e_flag_dont_resolve_alias = 1 << 2,
      e_flag_resolve_alias = 1 << 3,
      e_flag_get_local_path = 1 << 4,
      e_flag_in_zip = 1 << 5,
      e_flag_folder = 1 << 6,
      e_flag_folder_ex001 = 1 << 7,
      e_flag_folder_ex001_calc = 1 << 8,
      e_flag_has_subfolder = 1 << 9,
      e_flag_has_subfolder_unknown = 1 << 10

   };

   class set_width
   {
   public:

      set_width(filesize n = 0) { m_width = n; }

      filesize m_width;

   };


   enum e_iostate
   {
      goodbit = 0x00,
      eofbit = 0x01,
      failbit = 0x02,
      badbit = 0x04,
      _Hardfail = 0x10
   };


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
      //binary = type_binary,
      //out = mode_write,
      //in = mode_read,
      //trunc = mode_truncate
   };


   enum fmtflags
   {
      nofmtflags = 0,
      boolalpha = 0x00000001,
      showbase = 0x00000002,
      showpoint = 0x00000004,
      showpos = 0x00000008,
      skipws = 0x00000010,
      unitbuf = 0x00000020,
      uppercase = 0x00000040,
      dec = 0x00000080,
      hex = 0x00000100,
      oct = 0x00000200,
      fixed = 0x00000400,
      scientific = 0x00000800,
      internal = 0x00001000,
      left = 0x00002000,
      right = 0x00004000,
      adjustfield = left | right | internal,
      basefield = dec | oct | hex,
      floatfield = scientific | fixed
   };


} // namespace file




enum e_str_flag
{

   str_flag_ifnumberspace = 1,
   str_flag_ifnumberparenthesize = 2,
   str_flag_ifnumberparenthesizeandspace = 3,

};






