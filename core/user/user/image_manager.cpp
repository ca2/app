#include "framework.h"
#include "image_manager.h"
#include "acme/exception/interface_only.h"
#include "aura/graphics/image/list_base.h"


namespace user
{

   image_manager::image_manager()
   {
      m_pimagelist            = nullptr;
      m_pimagelistDisable     = nullptr;
   }

   image_manager::~image_manager()
   {
   }


   bool image_manager::Initialize(::particle * pparticle, unsigned int uaMenuV003Map [][2])
   {
      __UNREFERENCED_PARAMETER(pparticle);
      __UNREFERENCED_PARAMETER(uaMenuV003Map);
      throw ::interface_only();

      return true;

   }

   ::image::image_list & image_manager::GetImageList()
   {
      return *m_pimagelist;
   }

   ::image::image_list & image_manager::GetImageListDisable()
   {
      return *m_pimagelistDisable;
   }


   /*void image_manager::LoadToolbar(toolbar & toolbar, unsigned int * pinteraction)
   {

      toolbar.GetToolBarCtrl().SetImageList(&GetImageList());
      TBBUTTON tbb;

      Carray < unsigned int, unsigned int > uia;
      while(*pinteraction != 0xffffffff)
      {
         tbb.idCommand = *pinteraction;
         uia.erase_all();
         m_rel.GetFromA(*pinteraction, uia);
         if(uia.get_size() > 0)
         {
            tbb.iBitmap = uia[0];
         }
         else
         {
            tbb.iBitmap = -1;
         }
         tbb.fsState = 0;
         if(*pinteraction == 0)
         {
            tbb.fsStyle = TBSTYLE_SEP;
         }
         else
         {
            tbb.fsStyle = TBSTYLE_BUTTON;
         }
         tbb.dwData = 0;
         tbb.iString = -1;
         toolbar.GetToolBarCtrl().AddButtons(1, &tbb);
         pinteraction++;
      }

   }*/

   /*
   void image_manager::LoadToolbar(simple_toolbar & toolbar, unsigned int * pinteraction)
   {

      toolbar._001SetImageList(&GetImageList());
      TBBUTTON tbb;
      memory_set(&tbb, 0, sizeof(tbb));

      unsigned int user;
      while(*pinteraction != 0xffffffff)
      {
         tbb.idCommand = *pinteraction;
         if(m_rel.lookup(*pinteraction, user))
         {
            tbb.iBitmap = user;
         }
         else
         {
            tbb.iBitmap = -1;
         }
         tbb.fsState = 0;
         if(*pinteraction == 0)
         {
            tbb.fsStyle = TBSTYLE_SEP;
         }
         else
         {
            tbb.fsStyle = TBSTYLE_BUTTON;
         }
         tbb.dwData = 0;
         tbb.iString = -1;
         toolbar.AddButton(&tbb);
         pinteraction++;
      }
      toolbar._001Layout();
   }
   */

} // namespace user
