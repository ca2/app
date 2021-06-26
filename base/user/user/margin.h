#pragma once


namespace user
{


   class CLASS_DECL_BASE margin_base:
      virtual public ::user::interaction
   {
   public:


      ::rectangle_i32      m_rectMargin;


      margin_base();
      virtual ~margin_base();


      virtual void get_margin_rect(RECTANGLE_I32 * prectMargin) override;



   };


   template < class BASE >
   class margin:
      virtual public margin_base,
      virtual public BASE
   {
   public:

      margin()
      {
      }

      virtual ~margin()
      {
      }

      virtual void install_message_routing(::channel * pchannel) override
      {

         ::user::margin_base::install_message_routing(pchannel);
         BASE::install_message_routing(pchannel);

      }

//      void screen_to_client(RECTANGLE_I32 * prectangle)

      //    {

      //     BASE::screen_to_client(prectangle);


      /*prectangle->left   -= m_rectMargin.left;

      prectangle->right  -= m_rectMargin.left;

      prectangle->top    -= m_rectMargin.top;

      prectangle->bottom -= m_rectMargin.top;*/


      // }

      virtual ::point_i32 get_viewport_offset() override
      {

         auto pointOffset = BASE::get_viewport_offset();

         pointOffset.x += m_rectMargin.left;

         pointOffset.y += m_rectMargin.top;

         return pointOffset;

      }


      void set_viewport_offset(::draw2d::graphics_pointer & pgraphics, int x,int y) override
      {

         BASE::set_viewport_offset(pgraphics, x - m_rectMargin.left, y - m_rectMargin.top);

      }


      virtual ::size_f64 get_total_size() override
      {

         auto s = BASE::get_total_size();

         return decltype(s)(s.cx + m_rectMargin.left + m_rectMargin.right,s.cy + m_rectMargin.top + m_rectMargin.bottom);

      }

   };

} // namespace user



