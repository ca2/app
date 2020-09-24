#pragma once


namespace draw2d
{


   class CLASS_DECL_AURA font_list_item :
      virtual public context_object
   {
   public:


      index                               m_iItem;
      text_box                            m_box[3];
      string                              m_strName;
      string                              m_strFont;
      string                              m_strSample;
      ::char_set_array                    m_echarseta;


      font_list_item();
      virtual ~font_list_item();

   };


   class CLASS_DECL_AURA font_list_data :
      virtual public __pointer_array(font_list_item)
   {
   public:


      index          m_iSerial;
      index          m_iUpdateId;
      int            m_iBaseSize;
      int_array      m_iaSize;
      ::rect         m_rectClient;
      int            m_iUpdatedCount;
      bool           m_bLayoutStillIntersect;


   };



   class CLASS_DECL_AURA font_list :
      virtual public ::object
   {
   public:


      enum e_type
      {

         type_wide,
         type_single_column,

      };


      string                                          m_strFontFamily;
      index                                           m_iSequentialItemToLayout;
      __pointer(::draw2d::font_enumeration)           m_pfontenumeration;
      __pointer(::draw2d::font_enum_item_array)       m_pitema;

      __pointer(font_list_data)                       m_plistdata;


      u32_array                                       m_dwaBg;
      u32_array                                       m_dwaFg;
      ::user::interaction *                           m_puserinteraction;

      e_type                                          m_etype;
      point                                           m_point;
      ::size                                          m_size;
      string                                          m_strText;
      string                                          m_strTextLayout;

      ::rect                                          m_rectClient;
      ::rect                                          m_rectMargin;
      int                                             m_iBaseSizeLayout;
      tick                                            m_tickLastLayout;
      __pointer(::thread)                             m_pthreadLayout;
      bool                                            m_bLayoutWideStillIntersect;
      int_array                                       m_iaSize;

      int                                             m_iSelUpdateId;
      ::index                                         m_iSel;
      ::index                                         m_iHover;
      bool                                            m_bUpdating;


      font_list();
      virtual ~font_list();


      virtual void defer_update();
      virtual void update();

      virtual void defer_font_enumeration();
      virtual void update_font_enumeration();
      virtual void sync_font_enumeration();

      virtual void update_extents();
      virtual void update_extents(font_list_data * plistdata, font_list_item * pitem, ::draw2d::graphics_pointer & pgraphics, index iBox);
      
      virtual void set_need_layout();

      virtual void layout();
      virtual void layout_wide();
      virtual void layout_single_column();

      virtual bool is_updating() const;

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics);
      virtual void _001OnDrawWide(::draw2d::graphics_pointer & pgraphics);
      virtual void _001OnDrawSingleColumn(::draw2d::graphics_pointer & pgraphics);

      virtual index find_name(string str);

      virtual bool set_sel_by_name(string str);

      //virtual void ensure_sel_visible();


      virtual ::user::item hit_test(const ::point& point);
      virtual ::user::item hit_test_wide(const ::point& point);
      virtual ::user::item hit_test_single_column(const ::point& point);
      
      virtual bool get_box_rect(LPRECT lprect, ::index i);
      virtual bool get_box_rect_wide(LPRECT lprect, ::index i);
      virtual bool get_box_rect_single_column(LPRECT lprect, ::index i);


   };


} // namespace draw2d





