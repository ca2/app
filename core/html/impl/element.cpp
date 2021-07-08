#include "framework.h"
#include "_impl.h"


namespace html
{


   namespace impl
   {


      element::element()
      {

         m_cxMax = -2;
         m_cxMin = -2;
         m_bHoverEvaluated = false;
         m_bHasHover = false;
         m_bHover = false;
         m_bHasChar = false;

      }


      element::~element()
      {

      }


      ::e_status element::initialize_html_impl_elemental(::html_data * pdata)
      {

         auto estatus = initialize(pdata);

         if (!estatus)
         {

            return estatus;

         }

         return estatus;

      }


      void element::delete_implementation(html_data * pdocument)
      {

         m_cxMax = -2;
         m_cxMin = -2;

      }


      bool element::hit_test(html_data * pdata, const ::point_f32 & point)
      {

         UNREFERENCED_PARAMETER(pdata);

//          e_tag etype = m_pelemental->m_etag;_001

         string strValue = m_pelemental->m_strBody;

         if (m_box.contains(point))
         {

            return true;

         }

         return false;

      }


      double element::bound_hit_test(html_data * pdata, const ::point_f32 & point)
      {

         UNREFERENCED_PARAMETER(pdata);

         float dx;

         float dy;

         if (point.x < m_box.left)
         {

            dx = m_box.left - point.x;

         }
         else if (point.x > m_box.right)
         {
            dx = point.x - m_box.right;
         }
         else
         {
            dx = 0;
         }

         if (point.y <m_box.top)
         {
            dy = m_box.top - point.y;
         }
         else if (point.y > m_box.bottom)
         {
            dy = point.y - m_box.bottom;
         }
         else
         {
            dy = 0;
         }

         return sqrt(dx * dx + dy * dy);
      }

      void element::OnLButtonDown(::message::message * pmessage)
      {
         
         __pointer(::html::message) phtml(pmessage);
         
         __pointer(::message::mouse) pmouse = phtml->m_pmessage;
         
         if (has_link())
         {
            
            pmouse->m_bRet = true;

            pmouse->m_lresult = 1;

         }

      }


      void element::OnMouseMove(::message::message * pmessage)
      {

         __pointer(::html::message) phtml(pmessage);

         __pointer(::message::mouse) pmouse = phtml->m_pmessage;

         if (!m_bHoverEvaluated)
         {

            bool bHasHover = true;

            if (bHasHover && !has_link())
            {

               bHasHover = false;

            }

            if (bHasHover)
            {

               e_tag etag = m_pelemental->m_etag;

               string strClass = m_pelemental->m_strClass;

               style * pstyle = phtml->m_phtmldata->m_pcoredata->m_stylesheeta.rfind(etag, strClass, "hover", "");

               if (pstyle == nullptr)
               {

                  bHasHover = false;

               }

            }

            m_bHasHover = bHasHover;

            m_bHoverEvaluated = true;

         }

         //::const ::point_f32 & point = pmouse->m_point;

         //phtml->m_puserinteraction->screen_to_client(&::point_f32);

         //bool bHover = hit_test(phtml->m_pdata, ::point_f32) != 0;

         //if (bHover != m_bHover)
         //{

         //   m_bHover = bHover;

         //   phtml->m_puserinteraction->set_need_redraw();

         //}

         if (has_link())
         {

            auto psession = get_session()->m_paurasession;

            auto puser = psession->user();

            auto pwindowing = puser->windowing();

            auto pcursor = pwindowing->get_cursor(e_cursor_hand);

            pmouse->m_pcursor = pcursor;

         }

      }


      void element::OnLButtonUp(::message::message * pmessage)
      {
         
         __pointer(::html::message) phtml(pmessage);

         if (has_link())
         {

            phtml->m_phtmldata->open_link(link());

         }

      }


      void element::implement_phase1(html_data * pdata, ::html::element * pelemental)
      {

         UNREFERENCED_PARAMETER(pdata);

         m_pelemental = pelemental;

         m_eposition = PositionRelative;

      }


      void element::implement_phase2(html_data * pdata)
      {

         UNREFERENCED_PARAMETER(pdata);

      }


      void element::layout_phase0(html_data * pdata)
      {

         m_box.left = 0;
         m_box.top = 0;
         m_box.right = 0;
         m_box.bottom = 0;
         m_bound.left = 0;
         m_bound.top = 0;
         m_bound.right = 0;
         m_bound.bottom = 0;
         UNREFERENCED_PARAMETER(pdata);

      }


      void element::container_raw_max_width(html_data * pdata)
      {

         if (m_pelemental->m_elementalptra.is_empty())
         {

            return;

         }

//         e_tag etag = m_pelemental->m_etag;

         float cxMax = 0.f;

         float cxMaxMax = 0.f;

         float cxMin = 0.f;

         float cxMinMax = 0.f;

         for (index i = 0; i < m_pelemental->m_elementalptra.get_count(); i++)
         {

            element * pelemental = m_pelemental->m_elementalptra[i]->m_pimpl;

            if (pelemental == nullptr)
               continue;

            if (pelemental == pelemental->get_first_sibling())
            {

               cxMaxMax = maximum(cxMax, cxMaxMax);

               cxMax = pelemental->m_cxMax;

               cxMinMax = maximum(cxMin, cxMinMax);

               cxMin = pelemental->m_cxMin;

            }
            else
            {

               cxMax += pelemental->m_cxMax;

               cxMin += pelemental->m_cxMin;

            }

         }

         cxMaxMax = maximum(cxMax, cxMaxMax);

         cxMinMax = maximum(cxMin, cxMinMax);

         m_cxMin = cxMinMax;

         m_cxMax = cxMaxMax;

      }


      void element::layout_phase0_end(html_data * pdata)
      {

         if (m_pelemental->m_elementalptra.is_empty())
         {

            return;

         }

         container_raw_max_width(pdata);

      }


      index element::find(element * pelemental)
      {

         for (index i = 0; i < m_pelemental->m_pparent->m_elementalptra.get_count(); i++)
         {

            if (m_pelemental->m_pparent->m_elementalptra[i]->m_pimpl == pelemental)
            {

               return i;

            }

         }

         return -1;

      }

      element * element::get_sibling(index i)
      {

         if (i < 0)
            return nullptr;

         if (i >= m_pelemental->m_pparent->m_elementalptra.get_count())
            return nullptr;

         return m_pelemental->m_pparent->m_elementalptra[i]->m_pimpl;

      }


      element * element::get_next_sibling()
      {

         if (m_pelemental->m_pstyle->m_edisplay == display_block)
         {

            return nullptr;

         }

         if (m_pelemental->m_pstyle->m_edisplay == display_table)
         {

            return nullptr;

         }

         element * pelemental = get_sibling(find(this) + 1);

         if (pelemental == nullptr)
         {

            return nullptr;

         }

         if (pelemental->m_pelemental->m_pstyle->m_edisplay == display_block)
         {

            return nullptr;

         }

         if (pelemental->m_pelemental->m_pstyle->m_edisplay == display_table)
         {

            return nullptr;

         }

         if (pelemental->m_pelemental->m_etag == tag_br)
         {

            return nullptr;

         }

         return pelemental;

      }


      element * element::get_first_sibling()
      {

         element * pelemental = this;

         element * pelementalPrevious = this;

         while (true)
         {

            e_tag etag = pelemental->m_pelemental->m_etag;

            if (pelemental->m_pelemental->m_pstyle->m_edisplay == display_block)
            {

               return pelementalPrevious;

            }

            if (pelemental->m_pelemental->m_pstyle->m_edisplay == display_table)
            {

               return pelementalPrevious;

            }

            if (etag == tag_br)
            {

               return pelementalPrevious;

            }

            if (etag == tag_head)
            {

               return pelementalPrevious;

            }

            if (etag == tag_title)
               return pelementalPrevious;

            if (etag == tag_meta)
               return pelementalPrevious;

            if (etag == tag_script)
               return pelementalPrevious;

            if (etag == tag_style)
               return pelementalPrevious;

            if (etag == tag_link)
               return pelementalPrevious;

            pelementalPrevious = pelemental;

            pelemental = pelemental->get_previous_sibling();

            if (pelemental == nullptr)
               return pelementalPrevious;

         }

      }

      element * element::get_previous_sibling()
      {

         return get_sibling(find(this) - 1);

      }


      bool element::layout_phase1(html_data * pdata)
      {

         if (m_pelemental == nullptr)
            return false;

         if (m_pelemental->m_pparent == nullptr)
            return false;

         e_tag etag = m_pelemental->m_etag;

         if (etag == tag_html
               || etag == tag_head
               || etag == tag_style
               || etag == tag_link
               || etag == tag_script
               || etag == tag_title
               || etag == tag_meta
               || etag == tag_body)
            return false;

         bool bBlock = m_pelemental->m_pstyle->m_edisplay == display_block
                       || m_pelemental->m_pstyle->m_edisplay == display_table;

         string str = m_pelemental->m_strBody;

         if (m_pelemental->m_elementalptra.is_empty())
         {

            if (!bBlock)
            {

               auto cx = minimum(m_pelemental->m_pparent->m_pimpl->m_bound.width(), m_cxMax);

               m_box.set_width(cx);

               m_bound.set_width(cx);

               return true;

            }
            else if (!m_bHasChar)
            {

               m_box.set_size(0, 0);

               m_bound.set_size(0, 0);

               return false;

            }

         }


         float fTotalMax = 0;

         float fTotalMin = 0;

         element * pelemental = get_first_sibling();

         int iCount = 0;

         while (pelemental != nullptr)
         {

            iCount++;

            fTotalMax += pelemental->m_cxMax;

            fTotalMin += pelemental->m_cxMin;

            pelemental = pelemental->get_next_sibling();

         }

         if (fTotalMax < m_pelemental->m_pparent->m_pimpl->m_bound.width())
         {

            m_box.set_width(m_cxMax + (m_pelemental->m_pparent->m_pimpl->m_bound.width() - fTotalMax) / iCount);

         }
         else if (fTotalMin < m_pelemental->m_pparent->m_pimpl->m_bound.width())
         {

            m_box.set_width(m_cxMin + (m_pelemental->m_pparent->m_pimpl->m_bound.width() - fTotalMin) / iCount);

         }
         else
         {

            m_box.set_width(m_cxMin);

         }

         m_bound.set_width(m_box.width());

         return true;

      }


      void element::layout_phase1_end(html_data * pdata)
      {

         if (m_pelemental == nullptr)
            return;

         if (m_pelemental->m_pparent == nullptr)
            return;

         e_tag etag = m_pelemental->m_etag;

         if (etag == tag_html
               || etag == tag_head
               || etag == tag_style
               || etag == tag_link
               || etag == tag_script
               || etag == tag_title
               || etag == tag_meta)
            return;

         if (m_pelemental->m_elementalptra.is_empty() || etag == tag_select)
         {

            return;

         }

         if (etag == tag_tbody)
         {

            m_box.set_size(0, 0);

            return;

         }

         float cxMax = pdata->m_pcoredata->m_layoutstate1.m_cxMax.last() + get_extra_content_width();

         float cxTotal = pdata->m_pcoredata->m_layoutstate1.m_cxa.last() + get_extra_content_width();

         cxMax = maximum(cxMax, cxTotal);

         pdata->m_pcoredata->m_layoutstate1.m_cxMax.last() = cxMax;

         m_box.set_height(pdata->m_pcoredata->m_layoutstate1.m_cya.last());

         pdata->m_pcoredata->m_layoutstate1.m_cy = pdata->m_pcoredata->m_layoutstate1.m_cya.last() + get_extra_content_height();

         pdata->m_pcoredata->m_layoutstate1.m_cya.last() = pdata->m_pcoredata->m_layoutstate1.m_cy;

         m_box.set_width(pdata->m_pcoredata->m_layoutstate1.m_cxMax.last());

      }


      void element::layout_phase2(html_data * pdata)
      {

         UNREFERENCED_PARAMETER(pdata);

      }


      void element::layout_phase3(html_data * pdata)
      {

         move_to(pdata);

//         bool bParent = false;

         e_tag etag = m_pelemental->m_etag;

         if (m_pelemental->m_elementalptra.has_elements() && etag != tag_select)
            return;

         if (etag == tag_html
               || etag == tag_head
               || etag == tag_style
               || etag == tag_script
               || etag == tag_table
               || etag == tag_tbody)
         {
            return;
         }


         if (etag == tag_br)
         {

            pdata->m_pcoredata->m_layoutstate3.m_y += height();

            //pdata->m_pcoredata->m_layoutstate3.m_y += pdata->m_pcoredata->m_layoutstate3.m_cya.last();

            pdata->m_pcoredata->m_layoutstate3.m_x = pdata->m_pcoredata->m_layoutstate3.m_xParent.last();

            pdata->m_pcoredata->m_layoutstate3.m_cya.last() = 0;


            return;

         }


         ::html::impl::cell * pcell = dynamic_cast < ::html::impl::cell * > (this);
         float iTableBorder = 0;
         if (pcell != nullptr)
         {
            if (pcell->get_table()->m_iBorder > 0)
            {
               iTableBorder = pcell->get_table()->m_iBorder + 1;
            }
         }

         string str = m_pelemental->m_strBody;

         float cx = m_box.width();

         float cy = m_box.height();

         m_box.set_width(cx);

         m_box.set_height(cy);

         pdata->m_pcoredata->m_layoutstate3.m_x = left() + width() + m_margin.right;

         pdata->m_pcoredata->m_layoutstate3.m_y = top();

         pdata->m_pcoredata->m_layoutstate3.m_cx = width();

         pdata->m_pcoredata->m_layoutstate3.m_cya.last() = maximum(pdata->m_pcoredata->m_layoutstate3.m_cya.last(), height());


      }


      void element::move_to(html_data * pdata)
      {

         move_to(pdata, (float)pdata->m_pcoredata->m_layoutstate3.m_x, (float)pdata->m_pcoredata->m_layoutstate3.m_y);

      }


      void element::_001OnDraw(html_data * pdata)
      {

         ::draw2d::graphics_pointer pgraphics = pdata->m_pcoredata->m_pgraphics;

         e_tag etag = m_pelemental->m_etag;

         if (etag == tag_body)
         {

            ::rectangle_i32 rectangle;

            if (!pdata->m_pcoredata->m_bDrawFirstBody)
            {

               pdata->m_pcoredata->m_bDrawFirstBody = true;

               rectangle = pdata->m_pcoredata->m_pform->get_client_rect();

            }
            else
            {

               __copy(rectangle, m_box);

            }


            //::color32_t color32;

            pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

            //if (m_pelemental->m_pstyle->get_alpha("", pdata, m_pelemental, d))
            //{

            //   if (m_pelemental->get_color(color32, ::user::color_background, pdata->m_pcoredata->m_pform))
            //   {

            //      App(pdata->get_application()).imaging().color_blend(pgraphics, rectangle, color32, maximum(0, minimum(255, (byte)(d * 255))));

            //   }

            //}
            //else
//            {
//
//               //::user::style_context style(m_pelemental);
//
////               auto pstyle
//
//               if(m_pelemental->get_color(color32,::user::color_background, &style))
//               {
//
//                  pgraphics->fill_rectangle(rectangle, color32);
//
//               }
//
//            }

         }

         ::rectangle_f32 bIn;

         ::rectangle_f32 bOut;

         if (m_border.left > 0.f || m_border.top > 0.f || m_border.right > 0.f || m_border.bottom > 0.f)
         {
            ::point_f32 pIn = get_content_top_left();
            ::size_f32 szIn = get_content_size();
            bIn.move_to(pIn);
            bIn.set_size(szIn);
            bIn.left -= m_padding.left;
            bIn.top -= m_padding.top;
            bIn.right += m_padding.right;
            bIn.bottom += m_padding.bottom;
            bOut = bIn;
            bOut.left -= m_border.left;
            bOut.top -= m_border.top;
            bOut.right += m_border.right;
            bOut.bottom += m_border.bottom;
         }


         if (m_border.left > 0.f)
         {
            if (m_border.left < 2.f)
            {
               ::point_f32 point1(m_box.left + m_margin.left + m_border.left / 2.f, m_box.top + m_margin.top + m_border.top / 2.f);
               ::point_f32 point2(m_box.left + m_margin.left + m_border.left / 2.f, m_box.bottom - m_margin.bottom - m_border.bottom / 2.f);
               ::draw2d::pen_pointer pen(e_create_new, pdata);
               pen->create_solid(m_border.left, m_border.crLeft);
               pgraphics->set(pen);
               pgraphics->draw_line(point1.x, point1.y, point2.x, point2.y);
            }
            else
            {
               ::point_f64 pa[4];
               pa[0] = ::point_f64(bOut.left, bOut.top);
               pa[1] = ::point_f64(bIn.left, bIn.top);
               pa[2] = ::point_f64(bIn.left, bIn.bottom);
               pa[3] = ::point_f64(bOut.left, bOut.bottom);
               ::draw2d::brush_pointer brush(e_create_new, pdata);
               brush->create_solid(m_border.crLeft);
               pgraphics->set(brush);
               pgraphics->fill_polygon(pa, 4);
            }
         }
         if (m_border.top > 0.f)
         {
            if (m_border.top < 2.f)
            {
               ::point_f32 point1(m_box.left + m_margin.left + m_border.left / 2.f, m_box.top + m_margin.top + m_border.top / 2.f);
               ::point_f32 point2(m_box.right - m_margin.right - m_border.right / 2.f, m_box.top + m_margin.top + m_border.top / 2.f);
               ::draw2d::pen_pointer pen(e_create_new, pdata);
               pen->create_solid(m_border.top, m_border.crTop);
               pgraphics->set(pen);
               pgraphics->draw_line(point1.x, point1.y, point2.x, point2.y);
            }
            else
            {
               ::point_f64 pa[4];
               pa[0] = ::point_f64(bOut.left, bOut.top);
               pa[1] = ::point_f64(bOut.right, bOut.top);
               pa[2] = ::point_f64(bIn.right, bIn.top);
               pa[3] = ::point_f64(bIn.left, bIn.top);
               ::draw2d::brush_pointer brush(e_create_new, pdata);
               brush->create_solid(m_border.crTop);
               pgraphics->set(brush);
               pgraphics->fill_polygon(pa, 4);
            }
         }
         if (m_border.right > 0.f)
         {
            if (m_border.right < 2.f)
            {
               ::point_f32 point1(m_box.right - m_margin.right - m_border.right / 2.f, m_box.top + m_margin.top + m_border.top / 2.f);
               ::point_f32 point2(m_box.right - m_margin.right - m_border.right / 2.f, m_box.bottom - m_margin.bottom - m_border.bottom / 2.f);
               ::draw2d::pen_pointer pen(e_create_new, pdata);
               pen->create_solid(m_border.right, m_border.crRight);
               pgraphics->set(pen);
               pgraphics->draw_line(point1.x, point1.y, point2.x, point2.y);
            }
            else
            {
               ::point_f64 pa[4];
               pa[0] = ::point_f64(bOut.right, bOut.top);
               pa[1] = ::point_f64(bOut.right, bOut.bottom);
               pa[2] = ::point_f64(bIn.right, bIn.bottom);
               pa[3] = ::point_f64(bIn.right, bIn.top);
               ::draw2d::brush_pointer brush(e_create_new, pdata);
               brush->create_solid(m_border.crRight);
               pgraphics->set(brush);
               pgraphics->fill_polygon(pa, 4);
            }
         }
         if (m_border.bottom > 0.f)
         {
            if (m_border.bottom < 2.f)
            {
               ::point_f32 point1(m_box.left + m_margin.left + m_border.left / 2.f, m_box.bottom - m_margin.bottom - m_border.bottom / 2.f);
               ::point_f32 point2(m_box.right - m_margin.right - m_border.right / 2.f, m_box.bottom - m_margin.bottom - m_border.bottom / 2.f);
               ::draw2d::pen_pointer pen(e_create_new, pdata);
               pen->create_solid(m_border.bottom, m_border.crBottom);
               pgraphics->set(pen);
               pgraphics->draw_line(point1.x, point1.y, point2.x, point2.y);
            }
            else
            {
               ::point_f64 pa[4];
               pa[0] = ::point_f64(bIn.left, bIn.bottom);
               pa[1] = ::point_f64(bIn.right, bIn.bottom);
               pa[2] = ::point_f64(bOut.right, bOut.bottom);
               pa[3] = ::point_f64(bOut.left, bOut.bottom);
               ::draw2d::brush_pointer brush(e_create_new, pdata);
               brush->create_solid(m_border.crBottom);
               pgraphics->set(brush);
               pgraphics->fill_polygon(pa, 4);

            }

         }

      }


      bool element::get_color(::color::color & color32)
      {

         color32 = argb(255, 0, 0, 0);

         return true;

      }


      bool element::has_link()
      {

         if (m_pelemental->m_pparent != nullptr && m_pelemental->m_pparent->m_pimpl != nullptr)
         {

            return m_pelemental->m_pparent->m_pimpl->has_link();

         }
         else
         {

            return false;

         }

      }


      string element::link()
      {
         if (m_pelemental->m_pparent != nullptr)
         {
            return m_pelemental->m_pparent->m_pimpl->link();
         }
         else
         {
            return "";
         }
      }

      void element::on_change_layout(html_data * pdata)
      {
         UNREFERENCED_PARAMETER(pdata);
      }


      float element::left()
      {

         return m_box.left;

      }


      float element::top()
      {

         return m_box.top;

      }


      float element::right()
      {

         return m_box.right;

      }


      float element::bottom()
      {

         return m_box.bottom;

      }


      float element::height()
      {

         return m_box.height();

      }


      float element::get_first_line_height()
      {

         return m_box.height();

      }


      float element::get_last_line_height()
      {

         return m_box.height();

      }


      float element::width()
      {

         return m_box.width();

      }


      ::point_f32 element::top_left()
      {

         return m_box.top_left();

      }


      ::size_f32 element::size()
      {

         return m_box.size();

      }


      ::size_f32 element::get_bound_size()
      {

         return m_bound.size();

      }


      void element::set_bound_size(html_data * pdata, const ::size_f32 & size)
      {

         m_bound.set_size(size);

         on_change_layout(pdata);

      }


      ::point_f32 element::get_bound_top_left()
      {

         return m_bound.top_left();

      }


      void element::move_bound_to(html_data * pdata, const ::point_f32 & point)
      {

         m_bound.move_to(point);

         m_bound.constrain(m_box);

         //m_box.constrain_to(m_bound);

         /*         if(m_point.x < m_pointBound.x)
         m_point.x = m_pointBound.x;
         else if(m_point.x > (m_pointBound.x + m_sizeBound.cx))
         m_point.x = m_pointBound.x + m_sizeBound.cx;
         if(m_point.y < m_pointBound.y)
         m_point.y = m_pointBound.y;
         else if(m_point.y > (m_pointBound.y + m_sizeBound.cy))
         m_point.y = m_pointBound.y + m_sizeBound.cy;*/
         on_change_layout(pdata);
      }


      void element::move_left_to(html_data * pdata, float x)
      {

         m_box.move_left_to(x);

         on_change_layout(pdata);

      }


      void element::move_top_to(html_data * pdata, float y)
      {

         m_box.move_top_to(y);

         on_change_layout(pdata);

      }


      void element::set_width(html_data * pdata, float cx)
      {

         m_box.set_width(cx);

         on_change_layout(pdata);

      }


      void element::set_height(html_data * pdata, float cy)
      {

         m_box.set_height(cy);

         on_change_layout(pdata);

      }


      void element::move_to(html_data * pdata, float x, float y)
      {

         m_box.move_to(x, y);

         on_change_layout(pdata);

      }


      void element::set_size(html_data * pdata, float cx, float cy)
      {

         m_box.set_size(cx, cy);

         on_change_layout(pdata);

      }


      void element::set_dim(html_data * pdata, float l, float t, float w, float h)
      {

         m_box.set_dim(l, t, w, h);

         on_change_layout(pdata);

      }


      bool element::use_in_final_layout(::html::impl::element * pimplChild)
      {

         ::html::impl::cell * pcell = dynamic_cast < ::html::impl::cell * > (pimplChild);

         if (pcell != nullptr)
         {
            if (pcell->m_iColBeg >= 0
                  || pcell->m_iColEnd >= 0
                  || pcell->m_iRowBeg >= 0
                  || pcell->m_iRowEnd >= 0)
            {

               return false;

            }
         }

         //UNREFERENCED_PARAMETER(pimplChild);

         return true;

      }

      void element::layout_phase3_end(html_data * pdata)
      {

         e_tag etag = m_pelemental->m_etag;

         if (m_pelemental->m_elementalptra.is_empty()
               || etag == tag_select)
            return;

         float x = 3e33f;

         float y = 3e33f;

         float cx = -3e33f;

         float cy = -3e33f;

         bool bOk = false;

         for (i32 i = 0; i < m_pelemental->m_elementalptra.get_size(); i++)
         {

            element * pelemental = m_pelemental->m_elementalptra[i]->m_pimpl;

            if (pelemental == nullptr)
               continue;

            if (!use_in_final_layout(pelemental))
               continue;



            if (pelemental->left() < x)
               x = pelemental->left();
            if (pelemental->top() < y)
               y = pelemental->top();
            if (pelemental->right() > x + cx)
               cx = pelemental->right() - x;
            if (pelemental->bottom() > y + cy)
               cy = pelemental->bottom() - y;

            bOk = true;

         }

         if (bOk)
         {

            set_dim(pdata, x, y, cx, cy);

         }

      }


      float element::calc_width()
      {

         if (m_pelemental != nullptr && m_pelemental->m_pparent != nullptr)
         {

            return m_pelemental->m_pparent->m_pimpl->calc_width();

         }
         else
         {

            return get_bound_size().cx;

         }

      }


      bool element::is_tag()
      {

         return m_pelemental->m_pbase->get_type() == ::html::base::type_tag;

      }


      bool element::is_value()
      {

         return m_pelemental->m_pbase->get_type() == ::html::base::type_value;

      }





      ::size_f32 element::get_content_size()
      {

         auto size = m_box.size();

         size.cx = maximum(0.f, size.cx - m_padding.left - m_padding.right - m_border.left - m_border.right - m_margin.left - m_margin.right);
         size.cy = maximum(0.f, size.cy - m_padding.top - m_padding.bottom - m_border.top - m_border.bottom - m_margin.top - m_margin.bottom);

         return size;

      }


      ::point_f32 element::get_content_top_left()
      {

         auto point = m_box.top_left();

         point.x = point.x + m_padding.left + m_border.left + m_margin.left;
         point.y = point.y + m_padding.top + m_border.top + m_margin.top;

         return point;

      }


      float element::get_table_border()
      {

         return 0.f;

      }


      float element::get_cell_spacing()
      {

         return 0.f;

      }


      float element::get_cell_padding()
      {

         return 0.f;

      }


      float element::get_extra_content_width()
      {

         return m_margin.left
                + m_border.left
                + m_padding.left
                + m_padding.right
                + m_border.right
                + m_margin.right;

      }


      float element::get_extra_content_height()
      {

         return m_margin.top
                + m_border.top
                + m_padding.top
                + m_padding.bottom
                + m_border.bottom
                + m_margin.bottom;

      }


   } // namespace impl


} // namespace html




