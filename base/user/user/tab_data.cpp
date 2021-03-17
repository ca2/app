// Created by Camilo 2021-01-08 <3TBS!!
#include "framework.h"
#include "base/user/user/_user.h"


namespace user
{


   tab_data::tab_data() :
      m_pen(e_create),
      //m_brushTextHover(e_create),
      //m_brushTextSel(e_create),
      //m_brushText(e_create),
      m_brushCloseHover(e_create),
      m_brushCloseSel(e_create),
      m_brushClose(e_create)
      //,
      //m_penBorder(e_create),
      //m_penBorderSel(e_create),
      //m_penBorderHover(e_create)
   {

      m_bNoClient = false;
      //m_brushTextHover->create_solid(argb(255, 0, 127, 255));
      //m_brushTextSel->create_solid(argb(255, 0, 0, 0));
      //m_brushText->create_solid(argb(163, 0, 0, 0));
      m_brushCloseHover->create_solid(argb(255, 255, 127, 0));
      m_brushCloseSel->create_solid(argb(255, 0, 0, 0));
      m_brushClose->create_solid(argb(163, 0, 0, 0));
      //m_penBorderHover->create_solid(1.0, argb(255, 0, 0, 0));
      //m_penBorderSel->create_solid(1.0, argb(255, 0, 0, 0));
      //m_penBorder->create_solid(1.0, argb(163, 90, 90, 80));

      m_bEnableCloseAll = false;
      m_rectTabClient.set(0, 0, 0, 0);

   }

   tab_data::~tab_data()
   {
   }


   tab_pane * tab_data::get_pane_by_id(id id)
   {

      return m_tabpanecompositea.get_by_id(id);

   }


   ::count tab_data::get_visible_tab_count()
   {

      return m_tabpanecompositea.get_visible_count();

   }



} // namespace base


