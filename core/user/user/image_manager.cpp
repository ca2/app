#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/user/user/_user.h"
#endif


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


   bool image_manager::Initialize(::object * pobject, UINT uiaMenuV003Map [][2])
   {
      UNREFERENCED_PARAMETER(pobject);
      UNREFERENCED_PARAMETER(uiaMenuV003Map);
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


   /*void image_manager::LoadToolbar(toolbar & toolbar, UINT * pinteraction)
   {

      toolbar.GetToolBarCtrl().SetImageList(&GetImageList());
      TBBUTTON tbb;

      Carray < UINT, UINT > uia;
      while(*pinteraction != 0xffffffff)
      {
         tbb.idCommand = *pinteraction;
         uia.remove_all();
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
   void image_manager::LoadToolbar(simple_toolbar & toolbar, UINT * pinteraction)
   {

      toolbar._001SetImageList(&GetImageList());
      TBBUTTON tbb;
      __memset(&tbb, 0, sizeof(tbb));

      UINT user;
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
