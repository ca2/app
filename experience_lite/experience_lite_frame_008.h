#pragma once





   namespace experience
   {


      


         namespace lite

         {


            class CLASS_DECL_APP_EXPERIENCE_LITE frame_008 :
               public frame
            {
            public:


               bool     m_bHollow;


               frame_008(::particle * pparticle);
               virtual ~frame_008();


               virtual void on_style_change() override;

               void on_draw_frame(::draw2d::graphics_pointer & pgraphics) override;
               void DrawBorder(::draw2d::graphics_pointer & pgraphics, const ::int_rectangle &lpcrectClient);
               void draw_border_side(::draw2d::graphics_pointer & pgraphics, const ::int_rectangle &lpcrectClient, enum_border eside);
               //void GetBorderRectangle(const ::int_rectangle &lpcrectClient, ::int_rectangle * lprect, enum_border eside);

               virtual e_hittest _001HitTest(const ::int_point & point) override;
               color32_t get_border_main_body_color() override;

               virtual bool get_color(color32_t & color32, ::user::e_color ecolor, ::user::style_context * pcontext) override;


            };


         } // namespace lite



      


   } // namespace experience









