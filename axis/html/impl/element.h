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
         ::f32_rectangle                 m_box;
         ::f32_rectangle                 m_bound;
         ::f32_rectangle                 m_padding;
         border                  m_border;
         ::f32_rectangle                 m_margin;
         ::i32                        m_iLayoutChildLineStartIndex;
         ::i32                        m_iLayoutChildIndex;

         enum_position              m_eposition;
         flags < enum_flag >        m_flags;
         ::f32                   m_cxMax;
         ::f32                   m_cxMin;
         string_map_base < ::i32 >      m_mapFont;
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

         bool hit_test(html_data * pdata, const ::f32_point & point);
         ::f64 bound_hit_test(html_data * pdata, const ::f32_point & point);


         virtual ::f32 left();
         virtual ::f32 top();
         virtual ::f32 right();
         virtual ::f32 bottom();
         virtual ::f32 width();
         virtual ::f32 height();

         virtual ::f32_point top_left();
         virtual ::f32_size size();


         virtual ::f32_size get_content_size();
         virtual ::f32_point get_content_top_left();

         virtual ::f32 get_table_border();
         virtual ::f32 get_cell_spacing();
         virtual ::f32 get_cell_padding();

         virtual ::f32 get_first_line_height();
         virtual ::f32 get_last_line_height();
         virtual ::f32_size get_bound_size();
         virtual void set_bound_size(html_data * pdocument, const ::f32_size & size);
         virtual ::f32_point get_bound_top_left();
         virtual void move_bound_to(html_data * pdocument, const ::f32_point & point);
         virtual void move_left_to(html_data * pdocument, ::f32 l);
         virtual void move_top_to(html_data * pdocument, ::f32 t);
         virtual void set_width(html_data * pdocument, ::f32 w);
         virtual void set_height(html_data * pdocument, ::f32 h);
         virtual void move_to(html_data * pdocument, ::f32 l, ::f32 t);
         virtual void set_size(html_data * pdocument, ::f32 w, ::f32 h);
         virtual void set_dim(html_data * pdocument, ::f32 l, ::f32 t, ::f32 w, ::f32 h);

         virtual void _001OnDraw(html_data * pdocument);


         virtual ::f32 get_extra_content_width();
         virtual ::f32 get_extra_content_height();


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

         virtual ::f32 calc_width();
         virtual bool use_in_final_layout(::html::impl::element * pimplChild);

         virtual bool is_tag();
         virtual bool is_value();


         DECLARE_MESSAGE_HANDLER(OnLButtonDown);
         DECLARE_MESSAGE_HANDLER(OnMouseMove);
         DECLARE_MESSAGE_HANDLER(OnLButtonUp);


      };


   } // namespace impl


} // namespace html





