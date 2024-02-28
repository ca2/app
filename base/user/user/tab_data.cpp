// Created by Camilo 2021-01-08 <3TBS!!
#include "framework.h"
#include "tab_data.h"
#include "acme/primitive/data/listener.h"
#include "aura/graphics/draw2d/brush.h"
#include "aura/graphics/draw2d/pen.h"


namespace user
{


   tab_data::tab_data()
   {

      m_bVertical = false;
      m_bNoClient = false;
      m_bEnableCloseAll = false;
      //m_rectangleHosting.set(0, 0, 0, 0);

   }


   tab_data::~tab_data()
   {


   }


   void tab_data::initialize(::particle * pparticle)
   {

      //auto estatus = 
      
      ::data::data::initialize(pparticle);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      __construct(m_ppen);
      __construct(m_pbrushCloseHover);
      __construct(m_pbrushCloseSel);
      __construct(m_pbrushClose);
         //m_pbrushTextHover(e_create),
         //m_pbrushTextSel(e_create),
         //m_pbrushText(e_create),
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


      //return estatus;

   }


   tab_pane * tab_data::get_tab_by_id(atom atom)
   {

      return m_tabpanea.get_by_id(atom);

   }


   ::count tab_data::get_visible_tab_count()
   {

      return m_tabpanea.get_visible_count();

   }


} // namespace base



