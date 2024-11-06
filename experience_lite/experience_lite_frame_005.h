#pragma once





   namespace experience
   {


      


         namespace lite

         {


            class CLASS_DECL_APP_EXPERIENCE_LITE frame_005 :
               public frame
            {
            public:


               ::draw2d::brush_pointer                m_pbrushGrip;
               ::draw2d::brush_pointer                m_pbrushTextCaption;


               frame_005(::particle * pparticle);
               virtual ~frame_005();


               virtual void _on_style_change(::draw2d::graphics_pointer & pgraphics) override;


               void on_draw_frame(::draw2d::graphics_pointer & pgraphics);
               void Draw3dRectSide(::draw2d::graphics_pointer & pgraphics, const ::int_rectangle & rectangle, enum_border eborder, color32_t crTopLeft, color32_t crBottomRight);
               void DrawBorder(::draw2d::graphics_pointer & pgraphics, const ::int_rectangle &lpcrectClient);
               void draw_border_side(::draw2d::graphics_pointer & pgraphics, const ::int_rectangle &lpcrectClient, enum_border eside);
               //void GetBorderRectangle(const ::int_rectangle &lpcrectClient, ::int_rectangle * lprect, enum_border eside);
               void DrawGripSet(::draw2d::graphics_pointer & pgraphics, const ::int_rectangle &lpcrectClient);
               void DrawGrip(::draw2d::graphics_pointer & pgraphics, const ::int_rectangle &lpcrectClient, enum_grip egrip);
               void DrawRectGrip(::draw2d::graphics_pointer & pgraphics, const ::int_rectangle & rectangle);

               virtual e_hittest _001HitTest(const ::int_point & point);


            };


         } // namespace lite



      


   } // namespace experience











