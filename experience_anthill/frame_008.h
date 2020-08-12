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


               virtual void on_style_change() override;

               void on_draw_frame(::draw2d::graphics_pointer & pgraphics) override;
               void DrawBorder(::draw2d::graphics_pointer & pgraphics, const ::rect & rectClient);
               void draw_border_side(::draw2d::graphics_pointer & pgraphics, const ::rect & rectClient, e_border eside);
               void GetBorderRect(const ::rect & rectClient, LPRECT lprect, e_border eside);

               virtual e_hittest _001HitTest(const ::point & point) override;
               COLORREF get_border_main_body_color() override;

//               virtual bool get_color(COLORREF & cr, ::user::e_color ecolor, ::user::style_context * pcontext) override;


            };



   } // namespace anthill


} // namespace experience




