#pragma once


#include "acme/platform/flags.h"
#include "acme/prototype/collection/string_map.h"
////#include "acme/prototype/prototype/object.h"
#include "axis/html/graphics/border.h"


namespace html
{

   
   class element;


   namespace impl
   {


      class CLASS_DECL_AXIS element :
         virtual public object
      {
      public:


         ::html::element *     m_pelemental;
         ::float_rectangle                 m_box;
         ::float_rectangle                 m_bound;
         ::float_rectangle                 m_padding;
         border                  m_border;
         ::float_rectangle                 m_margin;
         int                        m_iLayoutChildLineStartIndex;
         int                        m_iLayoutChildIndex;

         enum_position              m_eposition;
         flags < enum_flag >        m_flags;
         float                   m_cxMax;
         float                   m_cxMin;
         string_map < int >      m_mapFont;
         bool                    m_bHoverEvaluated;
         bool                    m_bHasHover;
         bool                    m_bHover;

         bool                    m_bHasChar;



         element();
         virtual ~element();


         virtual void initialize_html_impl_elemental(::html_data * pdata);


         virtual void delete_implementation(html_data * pdocument);


         virtual bool get_color(::color::color & color32);

         virtual bool has_link();
         virtual string link();

         virtual ::collection::index find(element * pelemental);

         virtual element * get_sibling(::collection::index i);

         virtual element * get_next_sibling();
         virtual element * get_first_sibling();
         virtual element * get_previous_sibling();

         bool hit_test(html_data * pdata, const ::float_point & point);
         double bound_hit_test(html_data * pdata, const ::float_point & point);


         virtual float left();
         virtual float top();
         virtual float right();
         virtual float bottom();
         virtual float width();
         virtual float height();

         virtual ::float_point top_left();
         virtual ::float_size size();


         virtual ::float_size get_content_size();
         virtual ::float_point get_content_top_left();

         virtual float get_table_border();
         virtual float get_cell_spacing();
         virtual float get_cell_padding();

         virtual float get_first_line_height();
         virtual float get_last_line_height();
         virtual ::float_size get_bound_size();
         virtual void set_bound_size(html_data * pdocument, const ::float_size & size);
         virtual ::float_point get_bound_top_left();
         virtual void move_bound_to(html_data * pdocument, const ::float_point & point);
         virtual void move_left_to(html_data * pdocument, float l);
         virtual void move_top_to(html_data * pdocument, float t);
         virtual void set_width(html_data * pdocument, float w);
         virtual void set_height(html_data * pdocument, float h);
         virtual void move_to(html_data * pdocument, float l, float t);
         virtual void set_size(html_data * pdocument, float w, float h);
         virtual void set_dim(html_data * pdocument, float l, float t, float w, float h);

         virtual void _001OnDraw(html_data * pdocument);


         virtual float get_extra_content_width();
         virtual float get_extra_content_height();


         virtual void implement_phase1(html_data * pdocument, ::html::element * pelemental);
         virtual void implement_phase2(html_data * pdocument);


         virtual void container_raw_max_width(html_data * pdata);


         virtual void layout_phase0(html_data * pdata); // cx minimum/maximum calculation
         // return true if function performed layout
         // if it returns false, layout must be ignored
         virtual bool layout_phase1(html_data * pdata); // cx calculation or cxy calculation at final nodes
         virtual void layout_phase2(html_data * pdata); // adjust
         virtual void layout_phase3(html_data * pdata); // final on_layout


         virtual void layout_phase0_end(html_data * pdata); // cxMax calculation for containers
         virtual void layout_phase1_end(html_data * pdata); // cy calculation
         virtual void layout_phase3_end(html_data * pdata); // final on_layout

         virtual void move_to(html_data * pdocument);

         virtual void on_change_layout(html_data * pdocument);

         virtual float calc_width();
         virtual bool use_in_final_layout(::html::impl::element * pimplChild);

         virtual bool is_tag();
         virtual bool is_value();


         DECLARE_MESSAGE_HANDLER(OnLButtonDown);
         DECLARE_MESSAGE_HANDLER(OnMouseMove);
         DECLARE_MESSAGE_HANDLER(OnLButtonUp);


      };


   } // namespace impl


} // namespace html





