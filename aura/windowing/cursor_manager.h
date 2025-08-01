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


      ::pointer < ::windowing::windowing >      m_pwindowing;
      map < enum_cursor, ::pointer<cursor >>    m_cursormap;


      cursor_manager();
      ~cursor_manager() override;


      long long increment_reference_count() override;
      long long decrement_reference_count() override;


      //inline ::aura::application* get_app();
      //inline ::aura::session* get_session();
      //inline ::aura::system* system();


      void load_hotspot(const ::file::path & pathFolder);

      string cursor_name(enum_cursor ecursor);
      enum_cursor cursor_enum(string strCursor);

      void parse_hotspot_text(string strText);
      ::pointer<cursor>set_system_default_cursor(enum_cursor ecursor);

      ::pointer<cursor>get_cursor(enum_cursor ecursor);
      ::pointer<cursor>set_cursor_file(enum_cursor ecursor, const ::file::path & path, bool bFromCache);
      void set_cursor_set_from_matter(::object * pobjectContext, const ::file::path & pathMatter);
      void set_cursor_set_from_dir(::object * pobjectContext, const ::file::path & pathFolder, bool bFromCache = true);
      void set_cursor_set_system_default();


      virtual void destroy() override;


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
//      map < enum_cursor, ::pointer<cursor >>  m_cursormap;
//
//
//      cursor_set();
//      virtual ~cursor_set();
//
//      void load_hotspot(const ::file::path & pathFolder);
//
//      string cursor_name(enum_cursor ecursor);
//      enum_cursor cursor_enum(string strCursor);
//
//      void parse_hotspot_text(string strText);
//      ::pointer<cursor>set_system_default_cursor(enum_cursor ecursor);
//
//      ::pointer<cursor>get_cursor(enum_cursor ecursor);
//      ::pointer<cursor>set_cursor_file(enum_cursor ecursor, const ::file::path & path, bool bFromCache);
//      ::collection::count set_cursor_set_from_matter(const ::file::path & pathMatter);
//      ::collection::count set_cursor_set_from_dir(const ::file::path & pathFolder, bool bFromCache = true);
//      ::collection::count set_cursor_set_system_default();
//
//
//      virtual void destroy() override;
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
