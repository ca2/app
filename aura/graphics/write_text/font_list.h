#pragma once


#include "font_enumeration.h"
#include "font_list_data.h"
#include "acme/exception/status.h"


namespace write_text
{



   class CLASS_DECL_AURA font_list :
      virtual public ::manager
   {
   public:




   protected:


      ::rectangle_i32                           m_rectangleX;
      enum_font_list                            m_efontlist;


   public:


      bool                                      m_bUpdatingFontList : 1;
      string                                    m_strFontFamily;
      string                                    m_strFontBranch;
      int                                     m_iLayoutSerial;
      ::pointer<font_enumeration>               m_pfontenumeration;
      ::pointer<font_enumeration>               m_pfontenumerationAddRedrawHandler;
      ::pointer<font_enumeration_item_array>    m_pfontenumerationitema;
      ::pointer<font_list_data>                 m_pfontlistdata;


      ::color::color                            m_uaBackgroundColor[2][3];
      ::color::color                            m_uaForegroundColor[2][3];
      ::pointer<::user::interaction>            m_puserinteraction;
      ::pointer<::user::interaction>            m_puserinteractionGraphicsContext;


      point_i32                                 m_point;
      ::size_i32                                m_size;
      string                                    m_strText;
      string                                    m_strTextLayout;

      ::rectangle_i32                           m_rectangleMargin;
      int                                       m_iBaseSizeLayout;
      class ::time                                    m_timeLastLayout;
      ::task_pointer                            m_pthreadLayout;
      bool                                      m_bLayoutWideStillIntersect;
      ::int_array                                 m_iaSize;

      int                                       m_iSelUpdateId;
      //::collection::index                                   m_iSel;
      //::collection::index                                   m_iHover;
      bool                                      m_bDarkMode;


      font_list();
      ~font_list() override;


      void initialize(::particle * pparticle) override;

      //virtual void on_subject(::topic * ptopic) override;

      void handle(::topic * ptopic, ::context * pcontext) override;

      //virtual void defer_enumerate_fonts(::topic * ptopic);
      //virtual void enumerate_fonts(::topic * ptopic);
      //virtual void sync_enumerate_fonts(::topic * ptopic);

      virtual void update_extents();
      virtual void update_extents(font_list_data * plistdata, font_list_item * pitem, ::draw2d::graphics_pointer & pgraphics, ::collection::index iBox);
      
      virtual void layout();
      virtual ::size_i32 layout_wide();
      virtual ::size_i32 layout_single_column();

      virtual bool is_updating() const;

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics, ::user::interaction * puserinteraction);
      virtual void _001OnDrawWide(::draw2d::graphics_pointer & pgraphics);
      virtual void _001OnDrawSingleColumn(::draw2d::graphics_pointer & pgraphics, ::user::interaction * puserinteraction);

      virtual ::collection::index find_name(string str);

      virtual bool set_sel_by_name(string str);

      //virtual void ensure_sel_visible();


      virtual ::item_pointer hit_test(const ::point_i32 & point, ::user::e_zorder ezorder);
      virtual ::item_pointer hit_test_wide(const ::point_i32& point);
      virtual ::item_pointer hit_test_single_column(const ::point_i32& point);
      

      virtual ::status < rectangle_i32 > item_rectangle(::item * pitem);


      virtual bool get_box_rect(::rectangle_i32 * lprect, ::collection::index i);
      virtual bool get_box_rect_wide(::rectangle_i32 * lprect, ::collection::index i);
      virtual bool get_box_rect_single_column(::rectangle_i32 * lprect, ::collection::index i);


      virtual void set_client_rectangle(const ::rectangle_i32 &rectangle);

      virtual void set_font_list_type(enum_font_list efontlist);
      virtual enum_font_list get_font_list_type() const;

      virtual void set_font_branch(const ::scoped_string & scopedstrFontBranch);
      virtual void on_update_font_branch();


   };


} // namespace write_text





