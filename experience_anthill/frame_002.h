#pragma once



namespace experience
{


   namespace anthill
   {


            class CLASS_DECL_APP_EXPERIENCE_ANTHILL frame_002 :
               public frame
            {
            public:


               frame_002();
               virtual ~frame_002();

               
               virtual string get_default_user_style() const;
               virtual void on_style_change();


               void on_draw_frame(::draw2d::graphics_pointer & pgraphics);
               void DrawBorder(::draw2d::graphics_pointer & pgraphics, const ::rect & rectClient);
               void draw_border_side(::draw2d::graphics_pointer & pgraphics, const ::rect & rectClient, enum_border eside);
               void GetBorderRect(const ::rect & rectClient, LPRECT32 lprect, enum_border eside);
               void DrawGripSet(::draw2d::graphics_pointer & pgraphics, const ::rect & rectClient);
               void DrawGrip(::draw2d::graphics_pointer & pgraphics, const ::rect & rectClient, enum_grip egrip);
               void DrawRectGrip(::draw2d::graphics_pointer & pgraphics, const ::rect & rect);

               virtual e_hittest _001HitTest(const ::point & point);

               color32_t get_border_main_body_color();


            };




   } // namespace anthill


} // namespace experience




