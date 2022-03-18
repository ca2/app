#pragma once


namespace experience
{


   namespace anthill
   {


      class CLASS_DECL_APP_EXPERIENCE_ANTHILL frame_008 :
         public frame
      {
      public:


         bool     m_bHollow;


         frame_008();
         virtual ~frame_008();


         
         virtual void _on_style_change(::draw2d::graphics_pointer& pgraphics) override;

         void on_draw_frame(::draw2d::graphics_pointer & pgraphics) override;
         void DrawBorder(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangleClient);
         void draw_border_side(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangleClient, enum_border eside);
         void GetBorderRect(const ::rectangle_i32 & rectangleClient, RECTANGLE_I32 * lprect, enum_border eside);

         virtual e_hittest _001HitTest(const ::point_i32 & point) override;
         //color32_t get_border_main_body_color() override;


//               virtual bool get_color(color32_t & color32, ::user::e_color ecolor, ::user::style_context * pcontext) override;


      };


   } // namespace anthill


} // namespace experience



