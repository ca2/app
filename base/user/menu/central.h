#pragma once


namespace user
{


   class CLASS_DECL_BASE menu_central :
      virtual public ::aura::department
   {
   public:


      id_map < int >          m_mapCommandImage;
      ::int_map < id >        m_mapImageCommand;

      __pointer(image_list)          m_pil;
      __pointer(image_list)          m_pilHue;
      __pointer(image_list)          m_pilBlend;
      __pointer(image_list)          m_pilHueLight;
      ::draw2d::font_pointer       m_fontMenu;


      menu_central();
      virtual ~menu_central();


      void defer_initialize();


      __pointer(image_list) MenuV033GetImageList();
      __pointer(image_list) MenuV033GetImageListHue();
      __pointer(image_list) MenuV033GetImageListBlend();
      __pointer(image_list) MenuV033GetImageListHueLight();


      bool MenuV033AddImageMap(::object * pobjectContext, ::xml::node * pnode);
      

      int command_image(id id);
      id image_command(int iImage);


      ::draw2d::font * MenuV033GetFont();
      ::draw2d::font * GetMenuFont();


   };


} // namespace user



