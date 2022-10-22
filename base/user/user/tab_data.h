// Created by Camilo 2021-01-08 <3TBS!!
#pragma once


#include "aura/graphics/draw2d/graphics_extension.h"
#include "aura/graphics/draw2d/holder.h"
#include "acme/primitive/primitive/match.h"
#include "tab_pane_array.h"


namespace user
{


   class CLASS_DECL_BASE tab_data :
      virtual public ::data::data,
      virtual public ::draw2d::holder
   {
   public:


      ::size_i32                          m_sizeSep;
      i32                                 m_iHeightAddUp;
      ::draw2d::pen_pointer               m_ppen;
      ::draw2d::brush_pointer             m_pbrushTextHover;
      ::draw2d::brush_pointer             m_pbrushTextSel;
      ::draw2d::brush_pointer             m_pbrushText;
      ::draw2d::brush_pointer             m_pbrushCloseHover;
      ::draw2d::brush_pointer             m_pbrushCloseSel;
      ::draw2d::brush_pointer             m_pbrushClose;
      ::draw2d::pen_pointer               m_ppenBorder;
      ::draw2d::pen_pointer               m_ppenBorderSel;
      ::draw2d::pen_pointer               m_ppenBorderHover;
      bool                                m_bCreated;
      i32                                 m_iTabHeight;
      i32                                 m_iTabWidth;
      tab_pane_composite_array            m_tabpanecompositea;
      ::rectangle_i32                     m_rectangleTab;
      ::rectangle_i32                     m_rectangleTabClient;
      draw2d::graphics_extension          m_dcextension;
      atom_array                            m_idaSel;
      ::rectangle_i32                     m_rectangleBorder;
      ::rectangle_i32                     m_rectangleMargin;
      ::rectangle_i32                     m_rectangleTextMargin;
      ::pointer<::image_list>            m_pimagelist;
      tab_callback *                      m_pcallback;
      ::index                             m_iClickTab;
      bool                                m_bDrag;
      bool                                m_bVertical;
      ::match::any                        m_matchanyRestore;
      bool                                m_bEnableCloseAll;
      bool                                m_bNoClient;
      ::size_i32                          m_sizeTabTotal;


      tab_data();
      ~tab_data() override;

      
      void initialize(::object * pobject) override;


      virtual tab_pane * get_tab_by_id(atom atom);

      ::count get_visible_tab_count();

   };


} // namespace user



