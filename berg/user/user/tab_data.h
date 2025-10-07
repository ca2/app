// Created by Camilo 2021-01-08 <3TBS!!
#pragma once


#include "acme/prototype/data/data.h"
#include "acme/prototype/collection/atom_array.h"
//#include "acme/prototype/geometry2d/_geometry2d.h"
#include "aura/graphics/draw2d/graphics_extension.h"
#include "aura/graphics/draw2d/holder.h"
#include "acme/prototype/prototype/match.h"
#include "tab_pane_array.h"


namespace user
{


   class CLASS_DECL_BERG tab_data :
      virtual public ::data::data,
      virtual public ::draw2d::holder
   {
   public:


      ::double_size                          m_sizeSep;
      int                                 m_iHeightAddUp;
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
      int                                 m_iTabHeight;
      int                                 m_iTabWidth;
      tab_pane_array                      m_tabpanea;
      ::int_rectangle                     m_rectangleTab;
      ::int_rectangle                     m_rectangleHosting;
      draw2d::graphics_extension          m_dcextension;
      atom_array                          m_idaSel;
      ::int_rectangle                     m_rectangleBorder;
      ::int_rectangle                     m_rectangleMargin;
      ::int_rectangle                     m_rectangleTextMargin;
      ::image::image_list_pointer              m_pimagelist;
      tab_callback *                      m_pcallback;
      ::collection::index                             m_iClickTab;
      bool                                m_bDrag;
      bool                                m_bVertical;
      ::match::any                        m_matchanyRestore;
      bool                                m_bEnableCloseAll;
      bool                                m_bNoClient;
      ::int_size                          m_sizeTabTotal;


      tab_data();
      ~tab_data() override;

      
      void initialize(::particle * pparticle) override;


      virtual tab_pane * get_tab_by_id(atom atom);

      ::collection::count get_visible_tab_count();

   };


} // namespace user



