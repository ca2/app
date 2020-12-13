#pragma once





   namespace experience
   {


      


         namespace lite

         {


            class CLASS_DECL_APP_EXPERIENCE_LITE frame_005 :
               public frame
            {
            public:


               ::draw2d::brush_pointer                m_brushGrip;
               ::draw2d::brush_pointer                m_brushTextCaption;


               frame_005(::layered * pobjectContext);
               virtual ~frame_005();


               virtual void on_style_change();


               void on_draw_frame(::draw2d::graphics_pointer & pgraphics);
               void Draw3dRectSide(::draw2d::graphics_pointer & pgraphics, const ::rect & rect, enum_border eborder, color32_t crTopLeft, color32_t crBottomRight);
               void DrawBorder(::draw2d::graphics_pointer & pgraphics, const RECT32 & lpcrectClient);
               void draw_border_side(::draw2d::graphics_pointer & pgraphics, const RECT32 & lpcrectClient, enum_border eside);
               void GetBorderRect(const RECT32 & lpcrectClient, LPRECT32 lprect, enum_border eside);
               void DrawGripSet(::draw2d::graphics_pointer & pgraphics, const RECT32 & lpcrectClient);
               void DrawGrip(::draw2d::graphics_pointer & pgraphics, const RECT32 & lpcrectClient, enum_grip egrip);
               void DrawRectGrip(::draw2d::graphics_pointer & pgraphics, const ::rect & rect);

               virtual e_hittest _001HitTest(const ::point & point);


            };


         } // namespace lite



      


   } // namespace experience











