#pragma once


namespace user
{


   class CLASS_DECL_BASE margin_base:
      virtual public ::user::interaction
   {
   public:


      ::rect      m_rectMargin;


      margin_base();
      virtual ~margin_base();


      virtual void get_margin_rect(RECT * prectMargin) override;



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

      margin(::object * pobject):
         ::object(pobject)
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

//      void _001ScreenToClient(RECT * prect)

      //    {

      //     BASE::_001ScreenToClient(prect);


      /*prect->left   -= m_rectMargin.left;

      prect->right  -= m_rectMargin.left;

      prect->top    -= m_rectMargin.top;

      prect->bottom -= m_rectMargin.top;*/


      // }

      virtual ::point get_viewport_offset() override
      {

         auto pointOffset = BASE::get_viewport_offset();

         pointOffset.x += m_rectMargin.left;

         pointOffset.y += m_rectMargin.top;

         return pointOffset;

      }


      void set_viewport_offset(int x,int y) override
      {

         BASE::set_viewport_offset(x - m_rectMargin.left, y - m_rectMargin.top);

      }


      virtual ::sized get_total_size() override
      {

         auto s = BASE::get_total_size();

         return decltype(s)(s.cx + m_rectMargin.left + m_rectMargin.right,s.cy + m_rectMargin.top + m_rectMargin.bottom);

      }

   };

} // namespace user



