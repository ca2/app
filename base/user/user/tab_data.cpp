// Created by Camilo 2021-01-08 <3TBS!!
#include "framework.h"
#include "base/user/user/_user.h"


namespace user
{


   tab_data::tab_data()
   {

      m_bVertical = false;
      m_bNoClient = false;
      m_bEnableCloseAll = false;
      m_rectangleTabClient.set(0, 0, 0, 0);

   }


   tab_data::~tab_data()
   {


   }


   ::e_status tab_data::initialize(::object * pobject)
   {

      auto estatus = ::data::data::initialize(pobject);

      if (!estatus)
      {

         return estatus;

      }

      m_ppen.create(this);
         //m_pbrushTextHover(e_create),
         //m_pbrushTextSel(e_create),
         //m_pbrushText(e_create),
         m_pbrushCloseHover.create(this);
         m_pbrushCloseSel.create(this);
         m_pbrushClose.create(this);
         //,
         //m_ppenBorder(e_create),
         //m_ppenBorderSel(e_create),
         //m_ppenBorderHover(e_create)
         //m_pbrushTextHover->create_solid(argb(255, 0, 127, 255));
      //m_pbrushTextSel->create_solid(argb(255, 0, 0, 0));
      //m_pbrushText->create_solid(argb(163, 0, 0, 0));
         m_pbrushCloseHover->create_solid(argb(255, 255, 127, 0));
      m_pbrushCloseSel->create_solid(argb(255, 0, 0, 0));
      m_pbrushClose->create_solid(argb(163, 0, 0, 0));
      //m_ppenBorderHover->create_solid(1.0, argb(255, 0, 0, 0));
      //m_ppenBorderSel->create_solid(1.0, argb(255, 0, 0, 0));
      //m_ppenBorder->create_solid(1.0, argb(163, 90, 90, 80));


      return estatus;

   }


   tab_pane * tab_data::get_tab_by_id(id id)
   {

      return m_tabpanecompositea.get_by_id(id);

   }


   ::count tab_data::get_visible_tab_count()
   {

      return m_tabpanecompositea.get_visible_count();

   }


} // namespace base



