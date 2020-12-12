#pragma once


namespace user
{


   class CLASS_DECL_BASE static_control :
      virtual public ::user::interaction
   {
   public:


      enum enum_type
      {
         type_text,
         type_icon,
         type_bitmap,
         type_cursor,
      };


      union
      {
         ::draw2d::bitmap *             m_pbitmap;
         ::draw2d::icon *           m_picon;
         ::draw2d::cursor *         m_pcursor;
      };


      enum_type                              m_etype;

      bool                                m_bLButtonDown;
      bool                                m_bHover;


      static_control();
      virtual ~static_control();


      virtual void install_message_routing(::channel * pchannel) override;


      virtual bool create_window(::user::interaction * puiParent,id id);


      virtual ::draw2d::font_pointer get_font(style* pstyle, enum_element eelement = element_none, estate estate = e_state_none) const override;

#ifdef WINDOWS_DESKTOP
      HENHMETAFILE SetEnhMetaFile(HENHMETAFILE hMetaFile);
      HENHMETAFILE GetEnhMetaFile();
#endif
      void static_set_icon(::draw2d::icon * picon);
      ::draw2d::icon * static_get_icon();
      void static_set_bitmap(::draw2d::bitmap * pbitmap);
      ::draw2d::bitmap * static_get_bitmap();
      void static_set_cursor(::draw2d::cursor * pcursor);
      ::draw2d::cursor * static_get_cursor();


      enum_type get_type();


      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;


      virtual bool OnChildNotify(::message::base * pbase) override;

      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnLButtonDown);
      DECL_GEN_SIGNAL(_001OnLButtonUp);
      DECL_GEN_SIGNAL(_001OnMouseMove);
      DECL_GEN_SIGNAL(_001OnMouseLeave);


   };


} // namespace user


