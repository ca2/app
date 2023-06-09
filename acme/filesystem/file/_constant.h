#pragma once



enum enum_depth : ::i32
{

   e_depth_none = 0,
   e_depth_recursively = INT_MAX,

};


namespace file
{


   enum enum_flag :
      i64
   {

      e_flag_none = 0,
      e_flag_file = 1,
      e_flag_folder = 2,
      e_flag_file_or_folder = 3,
      e_flag_folder_ex001 = 1 << 2,
      e_flag_folder_ex001_calc = 1 << 3,
      e_flag_required = 1 << 4,
      e_flag_bypass_cache = 1 << 5,
      e_flag_dont_resolve_alias = 1 << 6,
      e_flag_resolve_alias = 1 << 7,
      e_flag_get_local_path = 1 << 8,
      e_flag_in_zip = 1 << 9,
      e_flag_has_subfolder = 1 << 10,
      e_flag_has_subfolder_unknown = 1 << 11,
      e_flag_final_path = 1 << 12

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




   enum fmtflags : ::u32
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
      network_payload = 0x00008000,
      separated = 0x00010000,
      adjustfield = left | right | internal,
      basefield = dec | oct | hex,
      floatfield = scientific | fixed
   };


   DECLARE_ENUMERATION(e_flag, enum_flag);

} // namespace file





inline ::file::e_flag & fix_file_listing_flag(::file::e_flag & eflag)
{

   if ((eflag & ::file::e_flag_file_or_folder) == 0)
   {

      eflag |= ::file::e_flag_file_or_folder;

   }

   return eflag;

}



enum e_str_flag
{

   str_flag_ifnumberspace = 1,
   str_flag_ifnumberparenthesize = 2,
   str_flag_ifnumberparenthesizeandspace = 3,

};






