// Created by camilo on 2022-03-18 19:47 <3ThomasBorregaardSørensen!!
#pragma once


namespace appearance
{


   class CLASS_DECL_AURA appearance :
      virtual public object
   {
   public:


      bool                                   m_bUsePreferredSize;
      __pointer(::user::interaction)         m_puserinteraction;



      appearance();
      ~appearance() override;


      virtual ::size_i32 preferred_size(::draw2d::graphics_pointer & pointer);

      virtual void perform_layout(::draw2d::graphics_pointer & pointer);

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics);


   };


} // namespace appearance



