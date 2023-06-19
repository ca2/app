// Created by camilo on 2021-01-22 06:11 AM <3ThomasBorregaardSorensen
#pragma once


#include "acme/primitive/geometry2d/point.h"
#include "acme/primitive/geometry2d/size.h"
#include "acme/constant/element.h"


namespace user
{


   class drag_client;
   class mouse;


   class CLASS_DECL_ACME drag :
      virtual public ::particle
   {
   public:



      ::e_element                m_eelement;
      e_zorder                   m_ezorder;
      bool                       m_bLButtonDown;
      ::point_i32                m_pointLButtonDown;
      ::point_i32                m_pointInitial;
      ::size_i32                 m_sizeLButtonDownOffset;
      ::pointer<::user::mouse>   m_pmouse;
      enum_cursor                m_ecursor;

      bool                       m_bDrag;

      
      drag();
      ~drag() override;


      void start(::user::mouse * pmouse, const ::point_i32 & pointDrag);
      void end();


      ::point_i32 point() const;


   };




} // namespace user



