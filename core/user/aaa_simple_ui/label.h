#pragma once


namespace simple_ui
{


   class CLASS_DECL_CORE label :
      virtual public ::user::interaction
   {
   public:


      label();
      virtual ~label();


      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics);



   };


} // namespace simple_ui




