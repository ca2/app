#pragma once


namespace simple_ui
{



   class CLASS_DECL_CORE password :
      virtual public edit_box
   {
   public:


      password();
      virtual ~password();


      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics);


   };






} // namespace simple_ui





