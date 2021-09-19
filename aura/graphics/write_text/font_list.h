#pragma once


namespace write_text
{




   class CLASS_DECL_AURA font_list :
      virtual public ::manager
   {
   public:


      enum enum_type
      {

         type_wide,
         type_single_column,

      };


   protected:


      ::rectangle_i32                           m_rectangleClient;
      enum_type                                 m_etype;


   public:


      bool                                      m_bUpdatingFontList : 1;
      string                                    m_strFontFamily;
      ::i32                                     m_iLayoutSerial;
      __pointer(font_enumeration)               m_pfontenumeration;
      __pointer(font_enumeration_item_array)    m_pfontenumerationitema;
      __pointer(font_list_data)                 m_pfontlistdata;


      ::color::color                            m_uaBackgroundColor[2][3];
      ::color::color                            m_uaForegroundColor[2][3];
      __pointer(::user::interaction)            m_puserinteraction;


      point_i32                                 m_point;
      ::size_i32                                m_size;
      string                                    m_strText;
      string                                    m_strTextLayout;

      ::rectangle_i32                           m_rectMargin;
      int                                       m_iBaseSizeLayout;
      millis                                    m_millisLastLayout;
      ::task_pointer                            m_pthreadLayout;
      bool                                      m_bLayoutWideStillIntersect;
      int_array                                 m_iaSize;

      int                                       m_iSelUpdateId;
      ::index                                   m_iSel;
      ::index                                   m_iHover;
      bool                                      m_bDarkMode;


      font_list();
      ~font_list() override;


      virtual ::e_status initialize_font_list(::user::interaction * puserinteraction);

      //virtual void on_subject(::subject * psubject) override;

      virtual void handle(::subject * psubject, ::context * pcontext) override;

      //virtual void defer_enumerate_fonts(::subject * psubject);
      //virtual void enumerate_fonts(::subject * psubject);
      //virtual void sync_enumerate_fonts(::subject * psubject);

      virtual void update_extents();
      virtual void update_extents(font_list_data * plistdata, font_list_item * pitem, ::draw2d::graphics_pointer & pgraphics, index iBox);
      
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


      virtual ::item hit_test(const ::point_i32& point);
      virtual ::item hit_test_wide(const ::point_i32& point);
      virtual ::item hit_test_single_column(const ::point_i32& point);
      
      virtual bool get_box_rect(RECTANGLE_I32 * lprect, ::index i);
      virtual bool get_box_rect_wide(RECTANGLE_I32 * lprect, ::index i);
      virtual bool get_box_rect_single_column(RECTANGLE_I32 * lprect, ::index i);


      virtual void set_client_rectangle(const RECTANGLE_I32 * lpcrectangle);

      virtual void set_font_list_type(enum_type etype);
      virtual enum_type get_font_list_type() const;


   };


} // namespace write_text





