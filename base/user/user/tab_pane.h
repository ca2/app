// Created by Camilo 2021-01-08 <3TBS!!
#pragma once


namespace user
{


   class CLASS_DECL_BASE tab_pane :
      virtual public ::property_object
   {
   public:

      ::text::text   m_textTitle;


   public:

      tab *                               m_ptab;

      ::index                             m_iIndex;
      ::draw2d::brush_pointer             m_pbrushFill;
      ::draw2d::brush_pointer             m_pbrushFillSel;
      ::draw2d::brush_pointer             m_pbrushFillHover;
      id                                  m_id;
      ::image_pointer                     m_pimage;
      __pointer(place_holder)             m_pplaceholder;
      __pointer(impact_data)              m_pimpactdata;
      bool                                m_bTabPaneVisible;
      bool                                m_bPermanent;
      size_i32                            m_size;
      string_array                        m_straTitle;
      ::size_array                        m_sizeaText;
      point_i32                           m_point;
      eflag                               m_eflag;


      tab_pane();
      tab_pane(const tab_pane & tab_pane);
      ~tab_pane() override;


      virtual void initialize_tab_pane(tab* ptab);


      tab_pane & operator = (const tab_pane & tab_pane);




      string get_title();
      void set_title(const ::string & pszTitle);


      virtual void do_split_layout(::draw2d::graphics_extension & dc, ::draw2d::graphics_pointer & pgraphics);


   };


} // namespace user



