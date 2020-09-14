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
               void Draw3dRectSide(::draw2d::graphics_pointer & pgraphics, const ::rect & rect, e_border eborder, COLORREF crTopLeft, COLORREF crBottomRight);
               void DrawBorder(::draw2d::graphics_pointer & pgraphics, const RECT & lpcrectClient);
               void draw_border_side(::draw2d::graphics_pointer & pgraphics, const RECT & lpcrectClient, e_border eside);
               void GetBorderRect(const RECT & lpcrectClient, LPRECT lprect, e_border eside);
               void DrawGripSet(::draw2d::graphics_pointer & pgraphics, const RECT & lpcrectClient);
               void DrawGrip(::draw2d::graphics_pointer & pgraphics, const RECT & lpcrectClient, e_grip egrip);
               void DrawRectGrip(::draw2d::graphics_pointer & pgraphics, const ::rect & rect);

               virtual e_hittest _001HitTest(const ::point & point);


            };


         } // namespace lite



      


   } // namespace experience











