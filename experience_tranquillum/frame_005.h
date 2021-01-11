#pragma once


namespace experience
{


   namespace tranquillum
   {


      class CLASS_DECL_APP_EXPERIENCE_TRANQUILLUM frame_005 :
               public frame
            {
            public:


               ::draw2d::brush_pointer                m_brushGrip;
               ::draw2d::brush_pointer                m_brushTextCaption;


               frame_005();
               virtual ~frame_005();


               virtual string get_default_user_style() const override;
               virtual void on_style_change();

               virtual void on_initialize_experience_frame();


               void on_draw_frame(::draw2d::graphics_pointer & pgraphics);
               void Draw3dRectSide(::draw2d::graphics_pointer & pgraphics, const ::rect & rect, enum_border eborder, color32_t crTopLeft, color32_t crBottomRight);
               void DrawBorder(::draw2d::graphics_pointer & pgraphics, const ::rect & rectClient);

               void draw_border_side(::draw2d::graphics_pointer & pgraphics, const ::rect & rectClient, enum_border eside);

               void GetBorderRect(const ::rect & rectClient, RECT32 * prect, enum_border eside);

               void DrawGripSet(::draw2d::graphics_pointer & pgraphics, const ::rect & rectClient);

               void DrawGrip(::draw2d::graphics_pointer & pgraphics, const ::rect & rectClient, enum_grip egrip);

               void DrawRectGrip(::draw2d::graphics_pointer & pgraphics, const ::rect & rect);

               virtual e_hittest _001HitTest(const ::point & point);


            };


         } // namespace tranquillum


   } // namespace experience



