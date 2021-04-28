#include "framework.h"
#include "core/user/user/_user.h"


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


   bool image_manager::Initialize(::object * pobject, ::u32 uaMenuV003Map [][2])
   {
      UNREFERENCED_PARAMETER(pobject);
      UNREFERENCED_PARAMETER(uaMenuV003Map);
      ::exception::throw_not_implemented();

      return true;

   }

   ::image_list & image_manager::GetImageList()
   {
      return *m_pimagelist;
   }

   ::image_list & image_manager::GetImageListDisable()
   {
      return *m_pimagelistDisable;
   }


   /*void image_manager::LoadToolbar(toolbar & toolbar, ::u32 * pinteraction)
   {

      toolbar.GetToolBarCtrl().SetImageList(&GetImageList());
      TBBUTTON tbb;

      Carray < ::u32, ::u32 > uia;
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
   void image_manager::LoadToolbar(simple_toolbar & toolbar, ::u32 * pinteraction)
   {

      toolbar._001SetImageList(&GetImageList());
      TBBUTTON tbb;
      __memset(&tbb, 0, sizeof(tbb));

      ::u32 user;
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
