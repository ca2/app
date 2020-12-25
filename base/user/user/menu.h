#pragma once


namespace user
{


   class menu_item;


   class CLASS_DECL_BASE menu :
      virtual public ::user::interaction
   {
   public:



      

      ::size                                 m_sizeMinimum;
      __pointer(menu)                        m_pmenuParent;
      __pointer(menu_item)                   m_pmenuitem;
      __pointer(::user::interaction)   m_puserinteractionParent;
      __pointer(::user::interaction)   m_puiMenuNotify;
#ifdef WINDOWS_DESKTOP
      HMENU                                  m_hmenu;
#endif
      bool                                   m_bOwnItem;
      ::size                                 m_size;
      double                                 m_dCheckBoxSize;
      bool                                   m_bAutoDelete;
      double                                 m_dHeaderHeight;
      __pointer(::user::menu_item)           m_pitemClose;
      id                                     m_idSubMenu;
      i32                                    m_iHoverSubMenu;
      u32                                    m_dwOut;
      __pointer(menu)                        m_psubmenu;
      id                                     m_idTimerMenu;
      point                                  m_pointTrack;
      point                                  m_pointPositionHint;
      int                                    m_iFlags;
      bool                                   m_bPositionHint;
      bool                                   m_bInline;
      bool                                   m_bMenuOk;
      __pointer(menu_item)                   m_pmenuitemSub;
      int_array                              m_iaColumnWidth;
      int_array                              m_iaColumnHeight;
      bool                                   m_bCloseButton;



      menu();
      menu(::user::menu_item * pitem);
      virtual ~menu();

      //virtual void nextstyle(::user::style_context * pcontext) override;
      virtual ::size get_window_minimum_size() override;

      //virtual i64 add_ref(OBJ_REF_DBG_PARAMS) override
      //{

      //   return ::object::add_ref(OBJ_REF_DBG_ARGS);

      //}

      //virtual i64 dec_ref(OBJ_REF_DBG_PARAMS) override
      //{

      //   return ::object::dec_ref(OBJ_REF_DBG_ARGS);

      //}

      virtual ::user::interaction * get_target_window();

      ::user::menu_item * GetSubMenu(i32 i);

      virtual void layout_menu(::draw2d::graphics_pointer& pgraphics, const ::point & point);

      virtual bool contains_menu_item(menu_item * pitem, bool bRecursive = true) const;

      virtual void update_flags(int iFlags);
      virtual void update_position(const ::point & point);
      virtual void hints(int iFlags, const ::point & point);

      virtual bool create_menu(::user::interaction * puiNotify = nullptr, ::user::interaction * puiParent = nullptr);
      virtual bool create_inline_menu(::user::interaction * puiNotify = nullptr, ::user::interaction * puiParent = nullptr);
      virtual bool track_popup_menu(::user::interaction * puiNotify = nullptr, ::user::interaction * puiParent = nullptr);

      void _001OnTimer(::timer * ptimer) override;

      void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      DECL_GEN_SIGNAL(_001OnLButtonDown);
      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnDestroy);
      DECL_GEN_SIGNAL(_001OnNcActivate);
      DECL_GEN_SIGNAL(_001OnNcCalcSize);
      DECL_GEN_SIGNAL(_001OnEnable);
      DECL_GEN_SIGNAL(_001OnShowWindow);
      DECL_GEN_SIGNAL(_001OnClose);
      DECL_GEN_SIGNAL(_001OnMouseActivate);
      DECL_GEN_SIGNAL(_001OnActivate);
      DECL_GEN_SIGNAL(_001OnNcCreate);


      virtual void on_control_event(::user::control_event * pevent) override;

      bool pre_create_window(::user::create_struct * pcreatestruct) override;

      virtual void install_message_routing(::channel * pchannel) override;

      __pointer(::user::menu_item) get_menu_item();

      //__pointer(::user::menu_item) get_menu_item(::user::interaction * pinteraction);

      virtual bool has_pending_graphical_update() override;

      virtual bool create_menu(const string_array & straCommand, const string_array & straCommandTitle);

      virtual void destroy_menu();

      virtual bool add_menu(::xml::node * pnode);

      virtual bool load_xml_menu(const payload & varXml);

      //virtual bool add_xml_menu(const payload & varXml);

      virtual void update_command(menu_item * pitemParent);

      void calc_size(menu_item * pitem, ::draw2d::graphics_pointer & pgraphics, i32 & iMaxWidth, i32 & iMaxHeight);
      void layout_buttons(menu_item * pitem, i32 iMaxWidth, RECT32 * prect, const ::rect & lpcrectBound);



      virtual void defer_close();

      virtual __pointer(::user::menu_interaction) create_menu_button(::draw2d::graphics_pointer & pgraphics, ::user::menu_item * pitem);


   };


} // namespace user



