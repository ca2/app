// created by Camilo AS DRAW2D::icon
// created by Camilo 2021-02-04 08:42 BRT CamiloSasuke<3ThomasBorregaardSoerensen
// Changing to windowing by Camilo on 2021-02-08 <3TBS_!!
#pragma once


namespace windowing
{


   // help/chatting LilCold_ (Dunno, Duck)
   // with him in Chat again, now at windowing component...

   class CLASS_DECL_AURA cursor_manager :
      virtual public ::object
   {
   public:


      map < enum_cursor, __pointer(cursor) >   m_cursormap;


      cursor_manager();
      virtual ~cursor_manager();


      inline ::aura::application* get_application() const;
      inline ::aura::session* get_session() const;
      inline ::aura::system* get_system() const;


      void load_hotspot(const ::file::path & pszDir);

      string cursor_name(enum_cursor ecursor);
      enum_cursor cursor_enum(string strCursor);

      void parse_hotspot_text(string strText);
      __pointer(cursor) set_system_default_cursor(enum_cursor ecursor);

      __pointer(cursor) get_cursor(enum_cursor ecursor);
      __pointer(cursor) set_cursor_file(enum_cursor ecursor, const ::file::path & path, bool bFromCache);
      ::e_status set_cursor_set_from_matter(const ::file::path & pszMatter);
      ::e_status set_cursor_set_from_dir(const ::file::path & pszDir, bool bFromCache = true);
      ::e_status set_cursor_set_system_default();


      virtual ::e_status destroy() override;


   };



} // namespace draw2d




//
//#pragma once
//
//
//namespace windowing
//{
//
//
//   // help/chatting LilCold_ (Dunno, Duck)
//
//   class CLASS_DECL_AURA cursor_set :
//      virtual public ::matter
//   {
//   public:
//
//
//
//      map < enum_cursor, __pointer(cursor) >   m_cursormap;
//
//
//      cursor_set();
//      virtual ~cursor_set();
//
//      void load_hotspot(const ::file::path & pszDir);
//
//      string cursor_name(enum_cursor ecursor);
//      enum_cursor cursor_enum(string strCursor);
//
//      void parse_hotspot_text(string strText);
//      __pointer(cursor) set_system_default_cursor(enum_cursor ecursor);
//
//      __pointer(cursor) get_cursor(enum_cursor ecursor);
//      __pointer(cursor) set_cursor_file(enum_cursor ecursor, const ::file::path & path, bool bFromCache);
//      ::count set_cursor_set_from_matter(const ::file::path & pszMatter);
//      ::count set_cursor_set_from_dir(const ::file::path & pszDir, bool bFromCache = true);
//      ::count set_cursor_set_system_default();
//
//
//      virtual ::e_status destroy() override;
//
//
//   };
//
//
//
//} // namespace windowing
//
//
//
//
