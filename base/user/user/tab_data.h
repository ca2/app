// Created by Camilo 2021-01-08 <3TBS!!
#pragma once


namespace user
{


   class CLASS_DECL_BASE tab_data :
      virtual public ::data::data
   {
   public:


      ::size_i32                           m_sizeSep;
      i32                              m_iHeightAddUp;
      ::draw2d::pen_pointer                 m_pen;
      //::draw2d::brush_pointer               m_brushTextHover;
      //::draw2d::brush_pointer               m_brushTextSel;
      //::draw2d::brush_pointer               m_brushText;
      ::draw2d::brush_pointer               m_brushCloseHover;
      ::draw2d::brush_pointer               m_brushCloseSel;
      ::draw2d::brush_pointer               m_brushClose;
      //::draw2d::pen_pointer                 m_penBorder;
      //::draw2d::pen_pointer                 m_penBorderSel;
      //::draw2d::pen_pointer                 m_penBorderHover;
      bool                             m_bCreated;
      i32                              m_iTabHeight;
      i32                              m_iTabWidth;
      tab_pane_composite_array         m_tabpanecompositea;
      ::rectangle_i32                  m_rectTab;
      ::rectangle_i32                  m_rectTabClient;
      draw2d::graphics_extension       m_dcextension;
      id_array                         m_idaSel;
      ::rectangle_i32                  m_rectBorder;
      ::rectangle_i32                  m_rectMargin;
      ::rectangle_i32                  m_rectTextMargin;
      __pointer(::image_list)          m_pimagelist;
      tab_callback *                   m_pcallback;
      ::index                          m_iClickTab;
      bool                             m_bDrag;
      bool                             m_bVertical;
      ::match::any                     m_matchanyRestore;
      bool                             m_bEnableCloseAll;
      bool                             m_bNoClient;
      ::size_i32                           m_sizeTabTotal;


      tab_data();
      ~tab_data() override;

      virtual tab_pane * get_tab_by_id(id id);

      ::count get_visible_tab_count();

   };


} // namespace user



