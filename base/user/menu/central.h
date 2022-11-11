#pragma once


#include "acme/platform/department.h"
#include "acme/primitive/collection/int_map.h"


namespace user
{


   class CLASS_DECL_BASE menu_central :
      virtual public ::acme::department
   {
   public:


      atom_map < int >          m_mapCommandImage;
      ::i32_map < atom >        m_mapImageCommand;

      ::pointer<::image_list>     m_pimagelist;
      ::pointer<::image_list>     m_pimagelistHue;
      ::pointer<::image_list>     m_pimagelistBlend;
      ::pointer<::image_list>     m_pimagelistHueLight;
      ::write_text::font_pointer       m_pfontMenu;


      menu_central();
      virtual ~menu_central();


      virtual void defer_initialize();


      ::pointer<::image_list>MenuV033GetImageList();
      ::pointer<::image_list>MenuV033GetImageListHue();
      ::pointer<::image_list>MenuV033GetImageListBlend();
      ::pointer<::image_list>MenuV033GetImageListHueLight();


      bool MenuV033AddImageMap(::particle * pparticle, ::xml::node * pnode);
      

      int command_image(atom atom);
      atom image_command(int iImage);


      ::write_text::font * MenuV033GetFont();
      ::write_text::font * GetMenuFont();


   };


} // namespace user



