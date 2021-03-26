#pragma once


namespace filehandler
{


   class CLASS_DECL_SPHERE view :
      public ::user::form_view
   {
   public:


      

      class list;


      class CLASS_DECL_SPHERE item :
         virtual public ::object
      {
      public:


         string         m_strApp;
         ::index        m_iIndex;

         ::rectangle_i32         m_rectItem;
         ::rectangle_i32         m_rectStatusImage;
         ::rectangle_i32         m_rectName;

         item(::object * pobject);

         void parse(const char * pszApp);

         void draw(__pointer(view) pview, ::draw2d::graphics_pointer & pgraphics, list * plist);

      };

      class CLASS_DECL_SPHERE list :
         virtual public __pointer_array(item)
      {
      public:

         i32 m_iItemHeight;

         list(::object * pobject);


         void parse(::filehandler::handler * phandler, const char * pszTopic);

         void on_layout(const RECTANGLE_I32 * lpcrect);
         void draw(__pointer(view) pview, ::draw2d::graphics_pointer & pgraphics);

      };


      ::xml::document *         m_pxmldoc;
      __pointer(list)                m_plistWorking;
      __pointer(list)                m_plist;

      ::write_text::font_pointer       m_pfont;


      view(::object * pobject);
      virtual ~view();


      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics);

      virtual void install_message_routing(::channel * pchannel);

      virtual void refresh();

      DECL_GEN_SIGNAL(on_message_create);
      void _001OnTimer(::timer * ptimer);
      DECL_GEN_SIGNAL(on_message_left_button_up);

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics);


      void on_hit_test(::user::item & item);


      void layout_list(list * plist);

      virtual bool get_font(::write_text::font_pointer & font);

   };


} // namespace filehandler



