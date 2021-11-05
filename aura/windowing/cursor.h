// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-02-01 20:16
#pragma once


namespace windowing
{


   class CLASS_DECL_AURA cursor :
      virtual public ::matter,
      virtual public ::osdata_array
   {
   public:


      enum_cursor                         m_ecursor;
      ::size_i32                          m_szHotspotOffset;
      __pointer(::draw2d::cursor)    m_pcursor;
      image_pointer                       m_pimage;
      ::file::path                        m_path;
      //bool                                m_bLoadSystemDefaultCursorHint;


      cursor();
      ~cursor() override;


      virtual ::e_status set_cursor(enum_cursor ecursor);

//      virtual ::e_status load_system_default_cursor_hint();

      virtual ::e_status set_image(const ::image * pimage, ::i32 xHotspot, ::i32 yHotspot);

      virtual ::e_status set_file_path(const ::file::path & path);

      virtual ::file::path get_file_path() const;

      virtual ::e_status _create_os_cursor();
      
      //virtual ::e_status set_cursor_file(const ::file::path& pathParam, bool bFromCache);


   };



} // namespace windowing





