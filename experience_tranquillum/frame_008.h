#pragma once


namespace experience
{


   namespace tranquillum
   {


      class CLASS_DECL_APP_EXPERIENCE_TRANQUILLUM frame_008 :
               public frame
            {
            public:


               frame_008();
               virtual ~frame_008();


               virtual string get_default_user_style() const override;
               virtual void _on_style_change(::draw2d::graphics_pointer & pgraphics) override;


               void on_draw_frame(::draw2d::graphics_pointer & pgraphics) override;
               void DrawBorder(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangleClient);

               void draw_border_side(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangleClient, enum_border eside);

               void GetBorderRect(const ::rectangle_i32 & rectangleClient, RECTANGLE_I32 * prectangle, enum_border eside);


               e_hittest _001HitTest(const ::point_i32 & point) override;
               //color32_t get_border_main_body_color() override;

               //virtual bool get_color(color32_t & color32, ::user::e_color ecolor, ::user::style_context * pcontext) override;


            };


         } // namespace tranquillum


   } // namespace experience



