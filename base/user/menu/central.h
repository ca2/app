#pragma once


namespace user
{


   class CLASS_DECL_BASE menu_central :
      virtual public ::acme::department
   {
   public:


      id_map < int >          m_mapCommandImage;
      ::i32_map < atom >        m_mapImageCommand;

      __pointer(::image_list)      m_pimagelist;
      __pointer(::image_list)      m_pimagelistHue;
      __pointer(::image_list)      m_pimagelistBlend;
      __pointer(::image_list)      m_pimagelistHueLight;
      ::write_text::font_pointer       m_pfontMenu;


      menu_central();
      virtual ~menu_central();


      virtual void defer_initialize();


      __pointer(::image_list) MenuV033GetImageList();
      __pointer(::image_list) MenuV033GetImageListHue();
      __pointer(::image_list) MenuV033GetImageListBlend();
      __pointer(::image_list) MenuV033GetImageListHueLight();


      bool MenuV033AddImageMap(::object * pobject, ::xml::node * pnode);
      

      int command_image(atom atom);
      atom image_command(int iImage);


      ::write_text::font * MenuV033GetFont();
      ::write_text::font * GetMenuFont();


   };


} // namespace user



