// Created by Camilo 2021-01-08 <3TBS!!
#pragma once


#include "aura/graphics/draw2d/holder.h"
#include "acme/primitive/geometry2d/_collection_basic.h"


namespace user
{


   class CLASS_DECL_BASE tab_pane :
      virtual public ::property_object,
      virtual public ::draw2d::holder
   {
   public:

      ::text::text   m_textTitle;


   public:

      tab *                               m_ptab;

      ::index                             m_iIndex;
      ::draw2d::brush_pointer             m_pbrushFill;
      ::draw2d::brush_pointer             m_pbrushFillSel;
      ::draw2d::brush_pointer             m_pbrushFillHover;
      atom                                m_atom;
      ::image_pointer                     m_pimage;
      ::pointer<place_holder>            m_pplaceholder;
      ::pointer<impact_data>             m_pimpactdata;
      bool                                m_bTabPaneVisible;
      bool                                m_bPermanent;
      size_i32                            m_size;
      string_array                        m_straTitle;
      ::size_array                        m_sizeaText;
      point_i32                           m_point;
      e_flag                              m_eflag;
      bool                                m_bNeedLayout;


      tab_pane();
      tab_pane(const tab_pane & tab_pane);
      ~tab_pane() override;


      virtual void initialize_tab_pane(tab* ptab);


      tab_pane & operator = (const tab_pane & tab_pane);




      string get_title();
      void set_title(const ::string & pszTitle);


      virtual void do_split_layout(::draw2d::graphics_extension * pdc, ::draw2d::graphics_pointer & pgraphics);


   };


} // namespace user



