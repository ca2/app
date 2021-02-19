// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-02-01 20:16
#pragma once


namespace windowing
{


   class CLASS_DECL_AURA cursor :
      virtual public ::layered
   {
   public:


      enum_cursor                   m_ecursor;
      ::size_i32                    m_szHotspotOffset;
      __pointer(::draw2d::cursor)   m_pcursor;


      cursor();
      virtual ~cursor();

      virtual ::e_status initialize_system_default();

      virtual ::e_status create_from_image(const ::image * pimage, ::i32 xHotspot, ::i16 yHotspot);

      virtual ::e_status load_default_cursor(enum_cursor ecursor);

      virtual ::file::path get_file_path() const;


   };



} // namespace windowing





