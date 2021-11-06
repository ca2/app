#pragma once


namespace user
{


   class CLASS_DECL_BASE menu_central :
      virtual public ::acme::department
   {
   public:


      id_map < int >          m_mapCommandImage;
      ::i32_map < id >        m_mapImageCommand;

      __pointer(::image_list)      m_pil;
      __pointer(::image_list)      m_pilHue;
      __pointer(::image_list)      m_pilBlend;
      __pointer(::image_list)      m_pilHueLight;
      ::write_text::font_pointer       m_pfontMenu;


      menu_central();
      virtual ~menu_central();


      virtual void defer_initialize();


      __pointer(::image_list) MenuV033GetImageList();
      __pointer(::image_list) MenuV033GetImageListHue();
      __pointer(::image_list) MenuV033GetImageListBlend();
      __pointer(::image_list) MenuV033GetImageListHueLight();


      bool MenuV033AddImageMap(::object * pobject, ::xml::node * pnode);
      

      int command_image(id id);
      id image_command(int iImage);


      ::write_text::font * MenuV033GetFont();
      ::write_text::font * GetMenuFont();


   };


} // namespace user



