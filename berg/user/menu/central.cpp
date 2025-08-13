#include "framework.h"
#include "central.h"
////#include "acme/exception/exception.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/definition.h"
#include "aqua/xml/document.h"
#include "acme/platform/debug.h"
#include "aura/platform/node.h"
#include "aura/graphics/write_text/font.h"
#include "aura/graphics/image/context.h"
#include "aura/graphics/image/drawing.h"
#include "aura/graphics/image/list.h"
#include "aura/graphics/image/imaging.h"
#include "berg/platform/system.h"


namespace user
{


   menu_central::menu_central()
   {

      defer_create_synchronization();

   }


   menu_central::~menu_central()
   {

   }


   bool menu_central::MenuV033AddImageMap(::particle * pparticle, ::xml::node * pnode)
   {

      defer_initialize();

      synchronous_lock synchronouslock(this->synchronization());

      int iIndex;

      atom atom;

      for(int i = 0; i < pnode->children().get_count(); i++)
      {

         ::pointer<::xml::node>pchild = pnode->child_at(i);

         string strId;

         strId = pchild->attribute("id");

         string strImage;

         strImage = pchild->attribute("img");

         //auto pimagecontext = image();

         auto pimage = image()->get_image(strImage);

         ::image::image_source imagesource(pimage);

         ::image::image_drawing_options imagedrawingoptions;

         ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

         iIndex = MenuV033GetImageList()->add(imagedrawing);

         atom = strId;

         m_mapCommandImage.set_at(atom, iIndex);

         m_mapImageCommand.set_at(iIndex, atom);

      }

      ::draw2d::graphics_pointer spgraphics(e_create, this);

      spgraphics->CreateCompatibleDC(nullptr);

      imaging()->change_hue(
      m_pimagelistHue,
      MenuV033GetImageList(),
      rgb(192, 192, 180),
      0.50);

      m_pimagelistBlend->color_blend(
      MenuV033GetImageList(),
      rgb(255, 255, 240),
      64);

      imaging()->change_hue(
      m_pimagelistHueLight,
      m_pimagelist,
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

      if(!m_mapCommandImage.find(atom, iImage))
      {

         return -1;

      }

      return iImage;

   }


   atom menu_central::image_command(int iImage)
   {

      atom atom;

      if(!m_mapImageCommand.find(iImage, atom))
      {

         return ::atom();

      }

      return atom;

   }


   void menu_central::defer_initialize()
   {

      synchronous_lock synchronouslock(this->synchronization());

      if (m_pimagelist)
      {

         return;

      }

      __øconstruct(m_pfontMenu);

      __construct_new(m_pimagelist);
      __construct_new(m_pimagelistHue);
      __construct_new(m_pimagelistBlend);
      __construct_new(m_pimagelistHueLight);

      VERIFY(m_pfontMenu->create_font(e_font_sans, 11_pt));

//#ifdef WINDOWS_DESKTOP
//      if (!MenuV033GetImageList()->create(16, 16, ILC_COLOR24 | ILC_MASK, 0, 10))
//      {
//         throw ::exception(::exception("resource exception menu_central constructor"));
//      }
//#else
      if (!MenuV033GetImageList()->create(16, 16, 0, 0, 10))
      {
         
         throw ::exception(::error_failed, "resource exception menu_central constructor");

      }
//#endif

   }


   ::image::image_list_pointer menu_central::MenuV033GetImageList()
   {

      defer_initialize();

      return m_pimagelist;

   }


   ::image::image_list_pointer menu_central::MenuV033GetImageListHue()
   {

      return m_pimagelistHue;

   }


   ::image::image_list_pointer menu_central::MenuV033GetImageListBlend()
   {

      return m_pimagelistBlend;

   }


   ::image::image_list_pointer menu_central::MenuV033GetImageListHueLight()
   {

      return m_pimagelistHueLight;

   }


} // namespace user



