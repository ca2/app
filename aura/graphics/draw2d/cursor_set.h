#pragma once


namespace draw2d
{


   // help/chatting LilCold_ (Dunno, Duck)

   class CLASS_DECL_AURA cursor_set :
      virtual public ::matter
   {
   public:



      isomap < e_cursor, __pointer(cursor) >   m_cursormap;


      cursor_set();
      virtual ~cursor_set();

      void load_hotspot(const ::file::path& pszDir);

      string cursor_name(e_cursor ecursor);
      e_cursor cursor_enum(string strCursor);

      void parse_hotspot_text(string strText);
      __pointer(cursor) set_system_default_cursor(e_cursor ecursor);

      __pointer(cursor) get_cursor(e_cursor ecursor);
      __pointer(cursor) set_cursor_file(e_cursor ecursor, const ::file::path& path, bool bFromCache);
      ::count set_cursor_set_from_matter(const ::file::path& pszMatter);
      ::count set_cursor_set_from_dir(const ::file::path& pszDir, bool bFromCache = true);
      ::count set_cursor_set_system_default();


      virtual void finalize() override;


   };



} // namespace draw2d




