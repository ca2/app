#pragma once




   namespace experience
   {



         namespace core
         {


            class CLASS_DECL_APP_EXPERIENCE_CORE frame_Minimal001 :
               public frame
            {
            public:

               
               frame_Minimal001();
               virtual ~frame_Minimal001();


               virtual string get_default_user_style() const override;
               virtual void on_style_change();

               void on_draw_frame(::draw2d::graphics_pointer & pgraphics);
               void DrawBorder(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectClient);
               void draw_border_side(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectClient, enum_border eside);
               void GetBorderRect(const ::rectangle_i32 & rectClient, LPRECT32 lprect, enum_border eside);
               void DrawGripSet(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectClient);
               void DrawGrip(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectClient, enum_grip egrip);
               void DrawRectGrip(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangle);

               virtual e_hittest _001HitTest(const ::point_i32 & point);


            };



         } // namespace core


   } // namespace experience



