#pragma once


namespace filehandler
{


   class CLASS_DECL_SPHERE impact :
      public ::user::form_impact
   {
   public:


      

      class list;


      class CLASS_DECL_SPHERE item :
         virtual public ::object
      {
      public:


         string         m_strApp;
         ::index        m_iIndex;

         ::rectangle_i32         m_rectangleItem;
         ::rectangle_i32         m_rectangleStatusImage;
         ::rectangle_i32         m_rectangleName;

         item(::particle * pparticle);

         void parse(const ::string & pszApp);

         void draw(::pointer<impact>pimpact, ::draw2d::graphics_pointer & pgraphics, list * plist);

      };

      class CLASS_DECL_SPHERE list :
         virtual public pointer_array < item >
      {
      public:

         i32 m_iItemHeight;

         list(::particle * pparticle);


         void parse(::filehandler::handler * phandler, const ::string & pszTopic);

         void on_layout(const RECTANGLE_I32 * lpcrect);
         void draw(::pointer<impact>pimpact, ::draw2d::graphics_pointer & pgraphics);

      };


      ::xml::document *         m_pxmldoc;
      ::pointer<list>               m_plistWorking;
      ::pointer<list>               m_plist;

      ::write_text::font_pointer       m_pfont;


      impact(::particle * pparticle);
      virtual ~impact();


      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics);

      void install_message_routing(::channel * pchannel) override;

      virtual void refresh();

      DECLARE_MESSAGE_HANDLER(on_message_create);
      void _001OnTimer(::timer * ptimer);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_up);

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics);


      void on_hit_test(::item & item);


      void layout_list(list * plist);

      virtual bool get_font(::write_text::font_pointer & font);

   };


} // namespace filehandler



