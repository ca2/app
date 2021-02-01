#pragma once



   namespace experience
   {


         namespace core
         {


            class CLASS_DECL_APP_EXPERIENCE_CORE frame_005 :
               public frame
            {
            public:


               ::draw2d::brush_pointer                m_brushGrip;
               ::draw2d::brush_pointer                m_brushTextCaption;


               frame_005();
               virtual ~frame_005();


               virtual void on_initialize_experience_frame() override;


               virtual string get_default_user_style() const;
               virtual void on_style_change() override;


               void on_draw_frame(::draw2d::graphics_pointer & pgraphics) override;
               void Draw3dRectSide(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangle, enum_border eborder, color32_t crTopLeft, color32_t crBottomRight) override;
               void DrawBorder(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectClient);
               void draw_border_side(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectClient, enum_border eside);
               void GetBorderRect(const ::rectangle_i32 & rectClient, LPRECT32 lprect, enum_border eside);
               void DrawGripSet(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectClient);
               void DrawGrip(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectClient, enum_grip egrip);
               void DrawRectGrip(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangle);

               virtual e_hittest _001HitTest(const ::point_i32 & point) override;


            };



         } // namespace core


   } // namespace experience



