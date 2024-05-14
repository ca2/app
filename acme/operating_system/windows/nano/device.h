//
// Created by camilo on 31/01/2022 14:35 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/user/nano/device.h"
#undef USUAL_OPERATING_SYSTEM_SUPPRESSIONS
#include "acme/_operating_system.h"


namespace windows
{


   class CLASS_DECL_ACME ::nano::user::device :
      virtual public ::nano::user::device
   {
   public:


      //CreatableFromBase(::nano::user::device, ::nano::user::device);


      HDC         m_hdc;
      bool        m_bDelete;


      ::nano::user::device();
      ::nano::user::device(HDC hdc);
      ~::nano::user::device() override;


      void _draw_text(const ::string & str, const ::rectangle_i32 & rectangleText, const ::e_align & ealign, const ::e_draw_text & edrawtext, ::nano::user::brush * pnanobrushBack, ::nano::user::brush * pnanobrushText, ::nano::user::font * pnanofont) override;
      ::size_i32 get_text_extents(const ::string & str, ::nano::user::font * pnanofont) override;
      void rectangle(const ::rectangle_i32 & rectangle, ::nano::user::brush * pnanobrush, ::nano::user::pen * pnanopen) override;


   };


} // namespace windows



