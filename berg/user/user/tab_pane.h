// Created by Camilo 2021-01-08 <3TBS!!
#pragma once


#include "aura/graphics/draw2d/holder.h"
#include "acme/prototype/geometry2d/_collection.h"
//#include "acme/prototype/prototype/property_object.h"
#include "acme/prototype/text/text.h"
#include "acme/handler/item.h"


namespace user
{


   class CLASS_DECL_BERG tab_pane :
      virtual public ::item,
      virtual public ::property_object,
      virtual public ::draw2d::holder
   {
   public:

      ::text::text   m_textTitle;


   public:

      tab *                               m_ptab;

      ::collection::index                             m_iIndex;
      ::draw2d::brush_pointer             m_pbrushFill;
      ::draw2d::brush_pointer             m_pbrushFillSel;
      ::draw2d::brush_pointer             m_pbrushFillHover;
      atom                                m_atomTabPane;
      ::image::image_pointer                     m_pimage;
      ::pointer<place_holder>            m_pplaceholder;
      ::pointer<impact_data>             m_pimpactdata;
      bool                                m_bTabPaneVisible;
      bool                                m_bPermanent;
      int_size                            m_size;
      string_array_base                        m_straTitle;
      ::double_size_array                    m_sizeaText;
      int_point                           m_point;
      e_flag                              m_eflag;
      bool                                m_bNeedLayout;
      ::item_pointer                      m_pitemClose;


      tab_pane();
      tab_pane(const tab_pane & tab_pane);
      ~tab_pane() override;


      virtual void initialize_tab_pane(tab* ptab);


      tab_pane & operator = (const tab_pane & tab_pane);




      string get_title();
      void set_title(const ::scoped_string & scopedstrTitle);


      virtual void do_split_layout(::draw2d::graphics_extension * pdc, ::draw2d::graphics_pointer & pgraphics);


   };


} // namespace user



