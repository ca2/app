#pragma once


#include "acme/platform/department.h"
#include "acme/prototype/collection/int_map.h"


namespace user
{


   class CLASS_DECL_BASE menu_central :
      virtual public ::acme::department
   {
   public:


      atom_map < int >          m_mapCommandImage;
      ::i32_map < atom >        m_mapImageCommand;

      ::image::image_list_pointer      m_pimagelist;
      ::image::image_list_pointer      m_pimagelistHue;
      ::image::image_list_pointer      m_pimagelistBlend;
      ::image::image_list_pointer      m_pimagelistHueLight;
      ::write_text::font_pointer       m_pfontMenu;


      menu_central();
      virtual ~menu_central();


      virtual void defer_initialize();


      ::image::image_list_pointer  MenuV033GetImageList();
      ::image::image_list_pointer  MenuV033GetImageListHue();
      ::image::image_list_pointer  MenuV033GetImageListBlend();
      ::image::image_list_pointer  MenuV033GetImageListHueLight();


      bool MenuV033AddImageMap(::particle * pparticle, ::xml::node * pnode);
      

      int command_image(atom atom);
      atom image_command(int iImage);


      ::write_text::font * MenuV033GetFont();
      ::write_text::font * GetMenuFont();


   };


} // namespace user



