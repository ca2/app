#pragma once


#include "font_enumeration.h"
#include "font_list_data.h"
#include "acme/exception/status.h"


#include <atomic>
#include <chrono>


namespace write_text
{



   class CLASS_DECL_AURA font_list :
      virtual public ::manager
   {
   public:




   protected:


      ::i32_rectangle                           m_rectangleX;
      enum_font_list                            m_efontlist;


   public:


      bool                                      m_bUpdatingFontList : 1;
      string                                    m_strFontFamily;
      string                                    m_strFontBranch;
      ::i32                                     m_iLayoutSerial;
      ::pointer<font_enumeration>               m_pfontenumeration;
      ::pointer<font_enumeration>               m_pfontenumerationAddRedrawHandler;
      ::pointer<font_enumeration_item_array>    m_pfontenumerationitema;
      ::pointer<font_list_data>                 m_pfontlistdata;


      ::color::color                            m_uaBackgroundColor[2][3];
      ::color::color                            m_uaForegroundColor[2][3];
      ::pointer<::user::interaction>            m_puserinteraction;
      ::pointer<::user::interaction>            m_puserinteractionGraphicsContext;


      i32_point                                 m_point;
      ::i32_size                                m_size;
      string                                    m_strText;
      string                                    m_strTextLayout;

      ::i32_rectangle                           m_rectangleMargin;
      ::i32                                       m_iBaseSizeLayout;
      class ::time                                    m_timeLastLayout;
      ::task_pointer                            m_pthreadLayout;
      bool                                      m_bLayoutWideStillIntersect;
      ::i32_array_base                                 m_iaSize;

      ::i32                                       m_iSelUpdateId;
      //::collection::index                                   m_iSel;
      //::collection::index                                   m_iHover;
      bool                                      m_bDarkMode;
      ::std::atomic_bool                        m_bPerformanceDiagnosticsEnabledLast{false};
      ::std::atomic<::u64>                      m_uPerformanceDiagnosticsGenerationLast{0};
      ::std::atomic<::u64>                      m_uPerformanceDrawPasses{0};
      ::std::atomic<::u64>                      m_uPerformanceItemsExamined{0};
      ::std::atomic<::u64>                      m_uPerformanceVisibleItems{0};
      ::std::atomic<::u64>                      m_uPerformancePreviewUpdates{0};
      ::std::atomic<::u64>                      m_uPerformanceCachedDraws{0};
      ::std::atomic<::u64>                      m_uPerformancePreviewUpdateMicroseconds{0};
      ::std::atomic<::u64>                      m_uPerformanceCachedDrawMicroseconds{0};
      ::std::atomic<::i64>                      m_iPerformanceNextReportNanoseconds{0};


      font_list();
      ~font_list() override;


      void initialize(::particle * pparticle) override;

      //virtual void on_subject(::topic * ptopic) override;

      void handle(::topic * ptopic, ::handler_context * phandlercontext) override;

      //virtual void defer_enumerate_fonts(::topic * ptopic);
      //virtual void enumerate_fonts(::topic * ptopic);
      //virtual void sync_enumerate_fonts(::topic * ptopic);

      virtual void update_extents();
      virtual void update_extents(font_list_data * plistdata, font_list_item * pitem, ::draw2d::graphics * pgraphics, ::collection::index iBox);
      
      virtual void layout();
      virtual ::i32_size layout_wide();
      virtual ::i32_size layout_single_column();

      virtual bool is_updating() const;

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics, ::user::interaction * puserinteraction);
      virtual void _001OnDrawWide(::draw2d::graphics_pointer & pgraphics);
      virtual void _001OnDrawSingleColumn(::draw2d::graphics_pointer & pgraphics, ::user::interaction * puserinteraction);

      bool begin_font_list_performance_diagnostics();
      void record_font_item_examined();
      void record_visible_font_item();
      void record_font_preview_update(::u64 uMicroseconds);
      void record_cached_font_preview_draw(::u64 uMicroseconds);
      void report_font_list_performance_diagnostics_if_due();
      void reset_font_list_performance_diagnostics();

      virtual ::collection::index find_name(const ::scoped_string & scopedstr);

      virtual bool set_sel_by_name(const ::scoped_string & scopedstr);

      //virtual void ensure_sel_visible();


      virtual ::item_pointer hit_test(const ::i32_point & point, ::user::e_zorder ezorder);
      virtual ::item_pointer hit_test_wide(const ::i32_point& point);
      virtual ::item_pointer hit_test_single_column(const ::i32_point& point);
      

      virtual ::status < i32_rectangle > item_rectangle(::item * pitem);


      virtual bool get_box_rect(::i32_rectangle * lprect, ::collection::index i);
      virtual bool get_box_rect_wide(::i32_rectangle * lprect, ::collection::index i);
      virtual bool get_box_rect_single_column(::i32_rectangle * lprect, ::collection::index i);


      virtual void set_client_rectangle(const ::i32_rectangle &rectangle);

      virtual void set_font_list_type(enum_font_list efontlist);
      virtual enum_font_list get_font_list_type() const;

      virtual void set_font_branch(const ::scoped_string & scopedstrFontBranch);
      virtual void on_update_font_branch();


   };


} // namespace write_text





