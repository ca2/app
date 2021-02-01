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
      ::rectangle_i32         m_rectClient;
      int            m_iUpdatedCount;
      bool           m_bLayoutStillIntersect;


   };



   class CLASS_DECL_AURA font_list :
      virtual public ::object
   {
   public:


      enum enum_type
      {

         type_wide,
         type_single_column,

      };


   protected:


      ::rectangle_i32                                          m_rectClient;
      enum_type                                          m_etype;


   public:


      string                                          m_strFontFamily;
      ::i32                                           m_iLayoutSerial;
      __pointer(::draw2d::font_enumeration)           m_pfontenumeration;
      __pointer(::draw2d::font_enum_item_array)       m_pitema;

      __pointer(font_list_data)                       m_plistdata;


      u32_array                                       m_dwaBg;
      u32_array                                       m_dwaFg;
      ::user::interaction *                           m_puserinteraction;

      point_i32                                           m_point;
      ::size_i32                                          m_size;
      string                                          m_strText;
      string                                          m_strTextLayout;

      ::rectangle_i32                                          m_rectMargin;
      int                                             m_iBaseSizeLayout;
      millis                                            m_millisLastLayout;
      __pointer(::thread)                             m_pthreadLayout;
      bool                                            m_bLayoutWideStillIntersect;
      int_array                                       m_iaSize;

      int                                             m_iSelUpdateId;
      ::index                                         m_iSel;
      ::index                                         m_iHover;
      bool                                            m_bUpdating;
      bool                                            m_bUpdatesHooked;


      font_list();
      virtual ~font_list();


      virtual ::e_status initialize(::layered* pobjectContext) override;


      virtual void on_subject(::promise::subject * psubject) override;

      virtual void on_subject(::promise::subject * psubject, ::promise::context * pcontext) override;


      //virtual void defer_update();
      //virtual void update();

      virtual void defer_font_enumeration(::promise::subject * psubject);
      virtual void update_font_enumeration(::promise::subject * psubject);
      virtual void sync_font_enumeration(::promise::subject * psubject);

      virtual void update_extents();
      virtual void update_extents(font_list_data * plistdata, font_list_item * pitem, ::draw2d::graphics_pointer & pgraphics, index iBox);
      
      virtual void set_need_layout();

      virtual void set_need_redraw();

      virtual void layout();
      virtual ::size_i32 layout_wide();
      virtual ::size_i32 layout_single_column();

      virtual bool is_updating() const;

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics);
      virtual void _001OnDrawWide(::draw2d::graphics_pointer & pgraphics);
      virtual void _001OnDrawSingleColumn(::draw2d::graphics_pointer & pgraphics);

      virtual index find_name(string str);

      virtual bool set_sel_by_name(string str);

      //virtual void ensure_sel_visible();


      virtual ::user::item hit_test(const ::point_i32& point);
      virtual ::user::item hit_test_wide(const ::point_i32& point);
      virtual ::user::item hit_test_single_column(const ::point_i32& point);
      
      virtual bool get_box_rect(RECTANGLE_I32 * lprect, ::index i);
      virtual bool get_box_rect_wide(RECTANGLE_I32 * lprect, ::index i);
      virtual bool get_box_rect_single_column(RECTANGLE_I32 * lprect, ::index i);


      virtual void set_client_rect(const RECTANGLE_I32 * lpcrect);

      virtual void set_font_list_type(enum_type etype);
      virtual enum_type get_font_list_type() const;


   };


} // namespace draw2d





