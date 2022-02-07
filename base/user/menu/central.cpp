#include "framework.h"
#include "base/user/menu/_menu.h"
#include "aqua/xml.h"
#include "aura/graphics/draw2d/context_image.h"
#include "aura/graphics/draw2d/image_drawing.h"
#include "aura/graphics/draw2d/image_list.h"
#include "aura/graphics/draw2d/imaging.h"


namespace user
{


   menu_central::menu_central()
   {

      defer_create_mutex();

   }


   menu_central::~menu_central()
   {

   }


   bool menu_central::MenuV033AddImageMap(::object * pobject, ::xml::node * pnode)
   {

      defer_initialize();

      synchronous_lock synchronouslock(mutex());

      i32 iIndex;

      atom atom;

      for(i32 i = 0; i < pnode->children().get_count(); i++)
      {

         __pointer(::xml::node) pchild = pnode->child_at(i);

         string strId;

         pchild->find_attribute("atom", strId);

         string strImage;

         pchild->find_attribute("img", strImage);

         auto pcontextimage = m_pcontext->context_image();

         auto pimage = pcontextimage->get_image(strImage);

         image_source imagesource(pimage);

         image_drawing_options imagedrawingoptions;

         image_drawing imagedrawing(imagedrawingoptions, imagesource);

         iIndex = MenuV033GetImageList()->add(imagedrawing);

         atom = strId;

         m_mapCommandImage.set_at(atom, iIndex);

         m_mapImageCommand.set_at(iIndex, atom);

      }

      ::draw2d::graphics_pointer spgraphics(e_create, this);

      spgraphics->CreateCompatibleDC(nullptr);

      auto psystem = get_system()->m_pbasesystem;

      class imaging & imaging = psystem->imaging();

      imaging.change_hue(
      m_pilHue,
      MenuV033GetImageList(),
      rgb(192, 192, 180),
      0.50);

      m_pilBlend->color_blend(
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


   ::write_text::font * menu_central::MenuV033GetFont()
   {
      
      return GetMenuFont();

   }


   ::write_text::font * menu_central::GetMenuFont()
   {

      return m_pfontMenu;

   }


   int menu_central::command_image(atom atom)
   {

      int iImage;

      if(!m_mapCommandImage.lookup(atom, iImage))
      {

         return -1;

      }

      return iImage;

   }


   atom menu_central::image_command(int iImage)
   {

      atom atom;

      if(!m_mapImageCommand.lookup(iImage, atom))
      {

         return ::atom();

      }

      return atom;

   }


   void menu_central::defer_initialize()
   {

      synchronous_lock synchronouslock(mutex());

      if (m_pil)
      {

         return;

      }

      m_pfontMenu.create(this);

      __construct_new(m_pil);
      __construct_new(m_pilHue);
      __construct_new(m_pilBlend);
      __construct_new(m_pilHueLight);

      auto psystem = m_psystem->m_pbasesystem;

      auto pnode = psystem->node();

      VERIFY(m_pfontMenu->create_point_font(pnode->font_name(e_font_sans), 11));

//#ifdef WINDOWS_DESKTOP
//      if (!MenuV033GetImageList()->create(16, 16, ILC_COLOR24 | ILC_MASK, 0, 10))
//      {
//         throw ::exception(::exception("resource exception menu_central constructor"));
//      }
//#else
      if (!MenuV033GetImageList()->create(16, 16, 0, 0, 10))
      {
         
         throw ::exception("resource exception menu_central constructor");

      }
//#endif

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



