// Created by camilo on 2021-01-22 06:11 AM <3ThomasBorregaardSorensen
#pragma once


#include "acme/prototype/geometry2d/point.h"
#include "acme/prototype/geometry2d/size.h"
#include "acme/constant/element.h"
#include "acme/handler/item.h"


namespace user
{


   class drag_client;
   class mouse;


   class CLASS_DECL_ACME drag :
      virtual public ::particle
   {
   public:


      ::item_pointer                m_pitem;
      //::e_element                 m_eelement;
      //e_zorder                    m_ezorder;
      bool                          m_bLButtonDown;
      bool                          m_bLButtonDownUsed;
      ::int_point                   m_pointLButtonDown2;
      ::int_point                   m_pointInitial;
      //::int_size                  m_sizeLButtonDownOffset;
      //::pointer<::user::mouse>      m_pmouse;
      enum_cursor                   m_ecursor;

      bool                          m_bDrag;

      
      drag();
      ~drag() override;


      void drag_start(::user::mouse * pmouse, ::user::drag_client * pdragclient, ::item * pitem, const ::int_point & pointDrag);
      void drag_end();


      //::int_point point() const;


   };




} // namespace user



