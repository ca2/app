#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "base/user/menu/_menu.h"
#endif
#include "aqua/xml.h"


namespace user
{


   menu_central::menu_central() :
      m_fontMenu(e_create)
   {

      defer_create_mutex();

   }


   menu_central::~menu_central()
   {

   }


   bool menu_central::MenuV033AddImageMap(::layered * pobjectContext, ::xml::node * pnode)
   {

      defer_initialize();

      sync_lock sl(mutex());

      i32 iIndex;

      id id;

      for(i32 i = 0; i < pnode->children().get_count(); i++)
      {

         __pointer(::xml::node) pchild = pnode->child_at(i);

         string strId;

         pchild->find_attribute("id", strId);

         string strImage;

         pchild->find_attribute("img", strImage);

         iIndex = MenuV033GetImageList()->add_file(strImage);

         id = strId;

         m_mapCommandImage.set_at(id, iIndex);

         m_mapImageCommand.set_at(iIndex, id);

      }

      ::draw2d::graphics_pointer spgraphics(e_create);
      spgraphics->CreateCompatibleDC(nullptr);

      class imaging & imaging = System.imaging();

      imaging.change_hue(
      m_pilHue,
      MenuV033GetImageList(),
      rgb(192, 192, 180),
      0.50);

      imaging.color_blend(
      m_pilBlend,
      MenuV033GetImageList(),
      rgb(255, 255, 240),
      64);

      imaging.change_hue(
      m_pilHueLight,
      m_pil,
      rgb(220, 220, 215),
      0.5);

      return true;

   }


   ::draw2d::font * menu_central::MenuV033GetFont()
   {
      return GetMenuFont();
   }

   ::draw2d::font * menu_central::GetMenuFont()
   {

      return m_fontMenu;

   }


   int menu_central::command_image(id id)
   {

      int iImage;

      if(!m_mapCommandImage.lookup(id, iImage))
      {

         return -1;

      }

      return iImage;

   }


   id menu_central::image_command(int iImage)
   {

      id id;

      if(!m_mapImageCommand.lookup(iImage, id))
      {

         return ::id();

      }

      return id;

   }


   void menu_central::defer_initialize()
   {

      sync_lock sl(mutex());

      if (m_pil.is_set())
      {

         return;

      }

      m_pil = __new(image_list);
      m_pilHue = __new(image_list);
      m_pilBlend = __new(image_list);
      m_pilHueLight = __new(image_list);

      VERIFY(m_fontMenu->create_point_font(os_font_name(e_font_sans), 11));

#ifdef WINDOWS_DESKTOP
      if (!MenuV033GetImageList()->create(16, 16, ILC_COLOR24 | ILC_MASK, 0, 10))
      {
         __throw(::exception::exception("resource exception menu_central constructor"));
      }
#else
      if (!MenuV033GetImageList()->create(16, 16, 0, 0, 10))
      {
         __throw(::exception::exception("resource exception menu_central constructor"));
      }
#endif

   }


   __pointer(image_list) menu_central::MenuV033GetImageList()
   {

      defer_initialize();

      return m_pil;

   }


   __pointer(image_list) menu_central::MenuV033GetImageListHue()
   {

      return m_pilHue;

   }


   __pointer(image_list) menu_central::MenuV033GetImageListBlend()
   {

      return m_pilBlend;

   }


   __pointer(image_list) menu_central::MenuV033GetImageListHueLight()
   {

      return m_pilHueLight;

   }


} // namespace user



