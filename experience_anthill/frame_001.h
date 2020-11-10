#pragma once



namespace experience
{


   namespace anthill
   {


            class CLASS_DECL_APP_EXPERIENCE_ANTHILL frame_001 :
               public frame
            {
            public:


               frame_001();
               virtual ~frame_001();

               virtual void on_style_change();

               void on_draw_frame(::draw2d::graphics_pointer & pgraphics);
               void DrawBorder(::draw2d::graphics_pointer & pgraphics, const ::rect & rectClient);
               void draw_border_side(::draw2d::graphics_pointer & pgraphics, const ::rect & rectClient, e_border eside);
               void GetBorderRect(const ::rect & rectClient, LPRECT32 lprect, e_border eside);
               void DrawGripSet(::draw2d::graphics_pointer & pgraphics, const ::rect & rectClient);
               void DrawGrip(::draw2d::graphics_pointer & pgraphics, const ::rect & rectClient, e_grip egrip);
               void DrawRectGrip(::draw2d::graphics_pointer & pgraphics, const ::rect & rect);

               virtual e_hittest _001HitTest(const ::point & point);


            };


   } // namespace anthill


} // namespace experience




