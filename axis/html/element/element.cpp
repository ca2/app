#include "framework.h"
#include "element.h"
#include "acme/exception/parsing.h"
#include "acme/prototype/prototype/url.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/prototype/geometry2d/_collection.h"
#include "acme/prototype/string/str.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "axis/html/html/data.h"
#include "axis/html/html/core_data.h"
#include "axis/html/graphics/base.h"
#include "axis/html/graphics/tag.h"
#include "axis/platform/session.h"
#include "axis/user/user/user.h"
#include "axis/html/graphics/style.h"
#include "axis/html/impl/element.h"
#include "axis/html/impl/text.h"
#include "axis/html/impl/input_text.h"
#include "axis/html/impl/input_button.h"
#include "axis/html/impl/input_checkbox.h"
#include "axis/html/impl/select.h"
#include "axis/html/impl/image.h"
#include "axis/html/impl/table.h"
#include "axis/html/impl/table_row.h"
#include "axis/html/graphics/value.h"
#include "axis/html/user/form.h"
#include "axis/html/graphics/font.h"
#include "axis/html/html/html.h"
#include "aura/platform/system.h"


void trim001(string & str);


namespace html
{


   element::element()
   {

   }


   element::~element()
   {

      try
      {

         if (m_pdata != nullptr)
         {

            if (m_pdata->m_pcoredata->m_pform != nullptr)
            {

               //if (m_pdata->m_pcoredata->m_pform != nullptr)

               //   if (m_pdata->m_pcoredata->m_pform->m_pelementalHover == this)
               //   {

               //      m_pdata->m_pcoredata->m_pform->m_pelementalHover = nullptr;

               //   }

               //   if (m_pdata->m_pcoredata->m_pform->m_pelementalLButtonDown == this)
               //   {

               //      m_pdata->m_pcoredata->m_pform->m_pelementalLButtonDown = nullptr;

               //   }

            }

         }


      }
      catch (...)
      {


      }

   }


   void element::implement(html_data * phtmldata)
   {

      m_pdata = phtmldata;

      synchronous_lock lock(phtmldata->synchronization());

      implement_phase1(phtmldata);

      implement_phase2(phtmldata);

   }


   tag * element::get_tag()
   {

      if (m_phtmlbase == nullptr)
      {
         
         return nullptr;

      }
      else if (m_phtmlbase->get_type() == ::html::base::type_tag)
      {
         
         return dynamic_cast < ::html::tag * > (m_phtmlbase);

      }
      else
      {
         
         return nullptr;

      }

   }


   void element::initialize_html_element(html_data * phtmldata)
   {

      if (m_pparent != nullptr && m_atomTagName.is_empty())
      {

         m_bParent = true;

      }
      else
      {
         m_bParent = false;

      }

      auto psession = phtmldata->session();

      auto puser = user();

      m_etag = puser->m_phtml->tag_name_to_id(m_atomTagName);

      if (m_etag == tag_initial)
      {

         m_etag = tag_unknown;

         m_bTagVisible = false;

      }
      else
      {

         m_bTagVisible = ::html::html::tag_visible(m_etag);

      }

      m_pstyle->initialize_style(m_etag);

      if (m_phtmlbase->get_type() == ::html::base::type_value)
      {

         m_strClass = m_pparent->get_tag()->get_attr_value("html_class");

         m_strInlineStyle = m_pparent->get_tag()->get_attr_value("style");

      }
      else
      {

         m_strClass = get_tag()->get_attr_value("html_class");

         m_strInlineStyle = get_tag()->get_attr_value("style");

      }

      //return ::success;

   }


   void element::implement_phase1(html_data * phtmldata)
   {

      if (m_phtmlbase == nullptr)
      {

         return;

      }
      
      ::e_status estatus = ::success;

      if (m_etag == tag_initial)
      {

         //estatus =
         
         initialize_html_element(phtmldata);

         //if (!estatus)
         //{

         //   return;

         //}

      }

      tag * ptag = get_tag();

      if (ptag != nullptr)
      {
         string str = ptag->get_attr_value("style");

         if (!str.is_empty())
         {

            auto range = str();

            m_pstyle->parse(phtmldata, range);

         }

         if (m_etag == tag_font)
         {

            string str = ptag->get_attr_value("face");

            if (str.has_character())
            {

               m_pstyle->m_propertyset["font-family"] = str;

            }

            str = ptag->get_attr_value("color");

            if (str.has_character())
            {

               m_pstyle->m_propertyset["color"] = str;

            }

         }

      }

      if (m_pimpl == nullptr)
      {

         if (m_etag == tag_html || m_etag == tag_body || m_etag == tag_head || m_etag == tag_style)
         {

            if (m_etag == tag_head || m_etag == tag_html)
            {

               m_pimpl = __allocate ::html::impl::element();

            }
            else if (m_etag == tag_body)
            {

               m_pimpl = __allocate ::html::impl::text();

            }
            else
            {

               m_pimpl = __allocate ::html::impl::element();

            }

         }
         else if (m_etag == tag_title)
         {

            if (m_phtmlbase->get_type() == ::html::base::type_value)
            {

               phtmldata->m_pcoredata->m_strTitle = m_phtmlbase->get_value()->get_value();

               m_pimpl = __allocate ::html::impl::element();

            }
            else
            {

               m_pimpl = __allocate ::html::impl::element();

            }

         }
         else if (m_etag == tag_input)
         {

            string strType;

            if (!m_propertyset.is_new_or_null("type"))
            {

               strType = m_propertyset["type"];

            }

            trim001(strType);

            if (strType == "text")
            {

               m_pimpl = __allocate ::html::impl::input_text();

            }
            else if(strType == "calculator")
            {

               m_pimpl = __allocate ::html::impl::input_text("calculator", m_propertyset["unit"]);

            }
            else if (strType == "password")
            {

               m_pimpl = __allocate ::html::impl::input_text();

            }
            else if (strType == "button")
            {

               m_pimpl = __allocate ::html::impl::input_button();

            }
            else if (strType == "checkbox")
            {

               m_pimpl = __allocate ::html::impl::input_checkbox();

            }
            else
            {

               m_pimpl = __allocate ::html::impl::text();

            }

         }
         else if (m_etag == tag_select)
         {

            m_pimpl = __allocate ::html::impl::select();

         }
         else if (m_etag == tag_option)
         {

            m_pimpl = nullptr;

         }
         else if (m_etag == tag_img)
         {

            m_pimpl = __allocate ::html::impl::image();

         }
         else if (m_etag == tag_table && m_elementalptra.has_elements())
         {

            m_pimpl = __allocate ::html::impl::table();

         }
         else if (m_etag == tag_tr && m_elementalptra.has_elements())
         {

            m_pimpl = __allocate ::html::impl::table_row();

         }
         else if (m_etag == tag_td && m_elementalptra.has_elements())
         {

            m_pimpl = __allocate ::html::impl::cell();

         }
         else
         {

            m_pimpl = __allocate ::html::impl::text();

         }

         if (m_pimpl != nullptr)
         {

            m_pimpl->initialize_html_impl_elemental(phtmldata);

         }

      }

      if (m_pimpl != nullptr)
      {

         //if (m_elementalptra.has_elements())
         {

            if (m_strClass.has_character() || m_strInlineStyle.has_character())
            {
               if (m_strClass == "field")
               {

                  informationf("field");

               }
               m_pstyle->get_surround_box("html_padding", "", phtmldata, this, m_pimpl->m_padding);

               m_pstyle->get_border_box("html_border", "", phtmldata, this, m_pimpl->m_border);

               m_pstyle->get_border_color("html_border", "", phtmldata, this, m_pimpl->m_border);

               m_pstyle->get_surround_box("html_margin", "", phtmldata, this, m_pimpl->m_margin);

            }

            if (m_pimpl->m_margin.left() > 1.0f)
            {

               informationf("margin-left greater than 1.0f");

            }

         }

         m_pimpl->implement_phase1(phtmldata, this);

         for (int i = 0; i < m_elementalptra.get_size(); i++)
         {

            m_elementalptra[i]->implement_phase1(phtmldata);

         }

         if (m_elementalptra.is_empty())
         {

            if (m_pstyle->m_edisplay == display_block || m_pimpl == nullptr)
            {

               phtmldata->m_pcoredata->m_bHasChar = false;

            }
            else
            {

               phtmldata->m_pcoredata->m_bHasChar = m_pimpl->m_bHasChar;

            }

         }

      }

   }


   void element::implement_phase2(html_data * phtmldata)
   {

      __UNREFERENCED_PARAMETER(phtmldata);

   }


   void element::on_layout(html_data * phtmldata)
   {

      phtmldata->m_pcoredata->m_bHasChar = false;

      layout_phase0(phtmldata);

      layout_phase1(phtmldata);

      layout_phase2(phtmldata);

      layout_phase3(phtmldata);

   }


   void element::layout_phase0(html_data * phtmldata)
   {

      if (m_pimpl == nullptr)
         return;

      e_tag etag = m_etag;

      m_pimpl->layout_phase0(phtmldata);

      if (m_elementalptra.has_elements()
            && etag != tag_table
            && etag != tag_tbody
            && etag != tag_tr)
      {

         for (int i = 0; i < m_elementalptra.get_size(); i++)
         {

            m_elementalptra[i]->layout_phase0(phtmldata);

         }

      }

      m_pimpl->layout_phase0_end(phtmldata);

   }


   void element::layout_phase1(html_data * phtmldata)
   {

      if (m_pimpl == nullptr)
         return;

      if (m_etag == tag_html || m_etag == tag_body || m_etag == tag_head || m_pparent == nullptr)
      {

         m_pimpl->move_bound_to(phtmldata, {});

         m_pimpl->set_bound_size(phtmldata, phtmldata->m_pcoredata->m_box.size());

      }

      float xMax;

      float x;

      float fLastX;

      float fLastY;

      bool bLayout = m_pimpl->layout_phase1(phtmldata);

      if (m_elementalptra.has_elements() &&
            m_etag != tag_select)
      {

         phtmldata->m_pcoredata->m_layoutstate1.m_cya.add(0.f);
         phtmldata->m_pcoredata->m_layoutstate1.m_cxa.add(0.f);
         phtmldata->m_pcoredata->m_layoutstate1.m_cxMax.add(0.f);

         phtmldata->m_pcoredata->m_layoutstate1.m_cy = 0.f;

         for (int i = 0; i < m_elementalptra.get_size(); i++)
         {

            m_elementalptra[i]->layout_phase1(phtmldata);

         }

         phtmldata->m_pcoredata->m_layoutstate1.m_cya.last() += m_pimpl->get_extra_content_height();

         m_pimpl->layout_phase1_end(phtmldata);

         if (m_etag != tag_tr)
         {

            if (m_pstyle->m_edisplay == display_block || m_pstyle->m_edisplay == display_table)
            {

               fLastY = phtmldata->m_pcoredata->m_layoutstate1.m_cya.pop();

               phtmldata->m_pcoredata->m_layoutstate1.m_cya.last() += fLastY;

            }
            else
            {

               phtmldata->m_pcoredata->m_layoutstate1.m_cya.pop_max();

            }


            {

               xMax = phtmldata->m_pcoredata->m_layoutstate1.m_cxMax.pop();

               x = phtmldata->m_pcoredata->m_layoutstate1.m_cxa.pop();

               fLastX = maximum(xMax, x);

               phtmldata->m_pcoredata->m_layoutstate1.m_cxMax.last() = fLastX;

            }

         }

      }
      else if (bLayout)
      {

         m_pimpl->layout_phase1_end(phtmldata);

         phtmldata->m_pcoredata->m_layoutstate1.m_cy = m_pimpl->m_box.height();

         int iExtraCy;

         iExtraCy = (int) (m_pimpl->get_extra_content_height());

         if (iExtraCy > 0)
         {

            informationf("extra_cy > 0");

         }

         phtmldata->m_pcoredata->m_layoutstate1.m_cy += iExtraCy;

         if (m_etag == tag_br)
         {

            //phtmldata->m_pcoredata->m_layoutstate1.m_cya.last() += m_pimpl->m_box.get_cy();
            phtmldata->m_pcoredata->m_layoutstate1.m_cya.last() = maximum(phtmldata->m_pcoredata->m_layoutstate1.m_cya.last(), phtmldata->m_pcoredata->m_layoutstate1.m_cy);

         }
         else
         {

            auto newLastCy = maximum(phtmldata->m_pcoredata->m_layoutstate1.m_cya.last(), phtmldata->m_pcoredata->m_layoutstate1.m_cy);

            auto addLastCx = m_pimpl->m_box.width() + m_pimpl->get_extra_content_width();

            phtmldata->m_pcoredata->m_layoutstate1.m_cya.last() = newLastCy;

            phtmldata->m_pcoredata->m_layoutstate1.m_cxa.last() += addLastCx;

         }

         xMax = phtmldata->m_pcoredata->m_layoutstate1.m_cxMax.last();

         x = phtmldata->m_pcoredata->m_layoutstate1.m_cxa.last();

         fLastX = maximum(xMax, x);

         phtmldata->m_pcoredata->m_layoutstate1.m_cxMax.last() = fLastX;

      }


      if (m_elementalptra.is_empty())
      {

         if (m_pstyle->m_edisplay == display_block)
         {

            phtmldata->m_pcoredata->m_bHasChar = phtmldata->m_pcoredata->m_layoutstate1.m_bHasChar = false;

         }
         else
         {

            phtmldata->m_pcoredata->m_bHasChar = phtmldata->m_pcoredata->m_layoutstate1.m_bHasChar = m_pimpl->m_bHasChar;

         }

      }

      /*      if(m_pimpl->m_cxMin > m_pimpl->get_bound_size().cx())
            {

            m_pimpl->set_bound_size(phtmldata, ::float_size(m_pimpl->m_cxMin, m_pimpl->get_bound_size().cx()));

            }

            m_pimpl->set_x(phtmldata, maximum(m_pimpl->get_bound_size().cx(), m_pimpl->get_x()));*/


   }


   void element::layout_phase2(html_data * phtmldata)
   {

      if (m_pimpl == nullptr)
         return;

      m_pimpl->layout_phase2(phtmldata);

      for (int i = 0; i < m_elementalptra.get_size(); i++)
      {

         m_elementalptra[i]->layout_phase2(phtmldata);

      }

   }

   void element::layout_phase3(html_data * phtmldata)
   {

      if (m_pimpl == nullptr)
         return;

      if (m_pimpl != nullptr)
      {

         if (m_etag == tag_html || m_etag == tag_body || m_etag == tag_head)
         {

            if (m_etag == tag_head || m_etag == tag_html)
            {

               m_pimpl->set_dim(phtmldata, 0, 0, 0, 0);

            }

         }

      }

      ::pointer<::html::impl::cell>pcell = m_pimpl;

      if (m_elementalptra.has_elements() && m_etag != tag_select)
      {

         if (m_bTagVisible)
         {

            if (pcell != nullptr)
            {

            }
            else if (phtmldata->m_pcoredata->m_layoutstate3.m_bLastBlock
                     || m_pstyle->m_edisplay == display_block
                     || m_pstyle->m_edisplay == display_table_row)
            {

               phtmldata->m_pcoredata->m_layoutstate3.m_y += phtmldata->m_pcoredata->m_layoutstate3.m_cya.last();

               phtmldata->m_pcoredata->m_layoutstate3.m_x = phtmldata->m_pcoredata->m_layoutstate3.m_xParent.last();

               phtmldata->m_pcoredata->m_layoutstate3.m_cya.last() = 0;

               phtmldata->m_pcoredata->m_layoutstate3.m_bLastBlock = false;

               phtmldata->m_pcoredata->m_layoutstate3.m_bLastCell = false;

            }

         }

         m_pimpl->layout_phase3(phtmldata);

         auto pointContent = m_pimpl->get_content_top_left();

         phtmldata->m_pcoredata->m_layoutstate3.m_y = pointContent.y();

         phtmldata->m_pcoredata->m_layoutstate3.m_cya.add(0.f);

         phtmldata->m_pcoredata->m_layoutstate3.m_xParent.add(pointContent.x());

         phtmldata->m_pcoredata->m_layoutstate3.m_x = pointContent.x();

         m_pimpl->m_iLayoutChildLineStartIndex = 0;

         for (m_pimpl->m_iLayoutChildIndex = 0;
            m_pimpl->m_iLayoutChildIndex < m_elementalptra.get_size();
            m_pimpl->m_iLayoutChildIndex++)
         {

            auto pelemental = m_elementalptra[m_pimpl->m_iLayoutChildIndex];

            pelemental->layout_phase3(phtmldata);

            if (pelemental->m_etag == tag_br
               || pelemental->m_pstyle->m_edisplay == display_block
               || pelemental->m_pstyle->m_edisplay == display_table)
            {

               m_pimpl->m_iLayoutChildLineStartIndex = m_pimpl->m_iLayoutChildIndex + 1;

            }

         }

         phtmldata->m_pcoredata->m_layoutstate3.m_cya.pop_max_last_add_up(0.0f);

         //m_pimpl->m_margin.top()
         //+ m_pimpl->m_border.top()
         //+ m_pimpl->m_padding.top()
         //+ m_pimpl->m_padding.bottom()
         //+ m_pimpl->m_border.bottom()
         //+ m_pimpl->m_margin.bottom());

         phtmldata->m_pcoredata->m_layoutstate3.m_xParent.pop();

         if (m_bTagVisible)
         {

            if (m_pstyle->m_edisplay == display_table_row)
            {

               ::pointer<::html::impl::table_row>prow = m_pimpl;

               if (prow->m_iRow == prow->get_table()->m_rowptra.get_upper_bound())
               {

                  phtmldata->m_pcoredata->m_layoutstate3.m_y = prow->get_table()->m_box.top();

                  phtmldata->m_pcoredata->m_layoutstate3.m_cya.last() = prow->get_table()->m_box.height();

                  phtmldata->m_pcoredata->m_layoutstate3.m_x = phtmldata->m_pcoredata->m_layoutstate3.m_xParent.last();

               }
               else
               {

                  phtmldata->m_pcoredata->m_layoutstate3.m_y = m_pimpl->m_box.top();

                  phtmldata->m_pcoredata->m_layoutstate3.m_cya.last() = m_pimpl->m_box.height();

               }

            }
            else if (phtmldata->m_pcoredata->m_layoutstate3.m_bLastBlock || m_pstyle->m_edisplay == display_block)
            {

               phtmldata->m_pcoredata->m_layoutstate3.m_y += phtmldata->m_pcoredata->m_layoutstate3.m_cya.last();

               phtmldata->m_pcoredata->m_layoutstate3.m_x = phtmldata->m_pcoredata->m_layoutstate3.m_xParent.last();

               phtmldata->m_pcoredata->m_layoutstate3.m_cya.last() = 0;

               phtmldata->m_pcoredata->m_layoutstate3.m_bLastBlock = false;

               phtmldata->m_pcoredata->m_layoutstate3.m_bLastCell = false;

            }

         }

      }
      else
      {

         m_pimpl->layout_phase3(phtmldata);

      }

      m_pimpl->layout_phase3_end(phtmldata);

   }


   void element::_001OnDraw(html_data * phtmldata)
   {

      if (m_pstyle->m_edisplay == display_table)
      {

         for (int i = 0; i < m_elementalptra.get_size(); i++)
         {

            m_elementalptra[i]->_001OnDraw(phtmldata);

         }

         if (m_pimpl != nullptr)
         {

            m_pimpl->_001OnDraw(phtmldata);

         }

      }
      else
      {

         if (m_pimpl != nullptr)
         {

            m_pimpl->_001OnDraw(phtmldata);

         }

         for (int i = 0; i < m_elementalptra.get_size(); )
         {

            element * pelemental = m_elementalptra[i];

            if (::is_null(pelemental))
            {

               continue;

            }

            try
            {

               pelemental->_001OnDraw(phtmldata);

               i++;

            }
            catch(...)
            {

               m_elementalptra.erase_at(i);

            }

         }

      }

   }


   void element::load(html_data * phtmldata, ::html::base * phtmlbase)
   {

      if (phtmldata == nullptr)
      {

         return;

      }

      if (phtmldata->m_pcoredata->m_pform == nullptr)
      {

         return;

      }

      if (phtmlbase == nullptr)
      {

         return;

      }

      synchronous_lock lock(phtmldata->m_pcoredata->synchronization());

      m_phtmlbase = phtmlbase;

      m_elementalptra.erase_all();

      ::payload payload;

      payload.set_type(::e_type_string);

      if (m_phtmlbase->get_type() == ::html::base::type_tag)
      {

         ::html::tag * ptag = dynamic_cast < ::html::tag * > (m_phtmlbase);

         m_atomTagName = ptag->get_name();

         for (int i = 0; i < ptag->attra().get_size(); i++)
         {

            m_propertyset[ptag->attra()[i]->get_name()] = ptag->attra()[i]->get_value();

         }

         if (m_atomTagName == "html_link" && get_tag()->get_attr_value("rel").case_insensitive_order("stylesheet") == 0)
         {

            ::pointer<style_sheet>pstylesheet(__create_new < style_sheet > ());

            string strUrl(get_tag()->get_attr_value("href"));

            if(strUrl.contains(":"))
            {

            }
            else if(strUrl[0] == '\\')
            {

            }
            else if(m_pdata->m_pcoredata->m_strPathName.case_insensitive_begins("http://") ||
                    m_pdata->m_pcoredata->m_strPathName.case_insensitive_begins("https://"))
            {

               ::url::parts parts(m_pdata->m_pcoredata->m_strPathName);

               parts.set_href(strUrl);

               strUrl = parts.as_string();

            }
            else
            {
               
               strUrl = m_pdata->m_pcoredata->m_strPathName.sibling(strUrl);
               
               strUrl.find_replace("/","\\");

            }

            // auto pcontext = get_context();

            ::string str = file()->as_string(strUrl);

            auto range = str();

            pstylesheet->parse(phtmldata, range);

            phtmldata->m_pcoredata->m_stylesheeta.add(pstylesheet);

         }

         for (int i = 0; i < ptag->baseptra().get_size(); i++)
         {
            auto pelemental  = __allocate ::html::element();

            pelemental->initialize_html_elemental(phtmldata, this);
            pelemental->load(phtmldata, ptag->baseptra()[i]);
            m_elementalptra.add(pelemental);
         }
      }
      else if (m_phtmlbase->get_type() == ::html::base::type_value)
      {

         ::html::value * pvalue = dynamic_cast < ::html::value * > (m_phtmlbase);

         ::html::tag * ptag = dynamic_cast < ::html::tag * > (m_pparent->m_phtmlbase);

         m_atomTagName = ptag->get_name();
         m_strBody = pvalue->get_value();
         if (m_atomTagName == "html_style")
         {
            
            ::pointer<style_sheet>pstylesheet(__create_new < style_sheet >());

            ::string str(pvalue->get_value());

            auto range = str();

            pstylesheet->parse(phtmldata, range);

            phtmldata->m_pcoredata->m_stylesheeta.add(pstylesheet);

         }
         else if (m_atomTagName == "html_link"
                  && m_pparent->get_tag()->get_attr_value("rel").case_insensitive_order("stylesheet") == 0)
         {
            
            ::pointer<style_sheet>pstylesheet(__create_new < style_sheet > ());

            // auto pcontext = get_context();

            string str = file()->as_string(m_pparent->get_tag()->get_attr_value("href"));

            auto range = str();

            pstylesheet->parse(phtmldata, range);

            phtmldata->m_pcoredata->m_stylesheeta.add(pstylesheet);

         }
      }
      else
      {
         ASSERT(false);
      }
   }


   bool element::parse(html_data * phtmldata, ::ansi_range & range)
   {

      const_char_pointer pszStart = range.m_begin;

      // skip white space
      range.consume_spaces(0);

      if (*range.m_begin != '<')
      {

         while (*range.m_begin != '<')
         {

            range.m_begin++;

         }

         return false;

      }

      range.m_begin++;
      
      // skip white space
      range.consume_spaces(0);

      const_char_pointer pszTag = range.m_begin;

      // skip valid char
      while (*range.m_begin != '\0' && !character_isspace(*range.m_begin) && *range.m_begin != '>')
      {
      
         range.m_begin++;

      }

      string strTag(pszTag, range.m_begin - pszTag);

      if (strTag[0] == '/')
      {
      
         return false;

      }

      m_atomTagName = (atom) ::str::ansi_lower(strTag);

      if (strTag == "!DOCTYPE")
      {
         
         while (*range.m_begin != '\0' && *range.m_begin != '>')
         {
         
            range.m_begin++;

         }

      }
      else
      {
         
         // skip white space
         range.consume_spaces(0);
         
         // Parse Attributes
         parse_attributes(phtmldata, range);
         
         // skip white space
         range.consume_spaces(0);

         if (*range.m_begin != '/' && *range.m_begin != '>')
         {

            throw ::parsing_exception("run tag fixer tabjs");

         }

         if (*range.m_begin == '/')
         {

            // skip white space
            range.consume_spaces(0);

            if (*range.m_begin != '>')
            {

               throw ::parsing_exception("run tag fixer tabjs");

            }

            return true;

         }

         range.m_begin++;

      }

      if (m_atomTagName == "html_br")
      {

         return true;

      }

      const_char_pointer pszBody = range.m_begin;

      while (true)
      {

         ::pointer<element>pelemental = __allocate element();

         pelemental->initialize_html_elemental(phtmldata, this);

         if (!pelemental->parse(phtmldata, range))
         {

            break;

         }

         m_elementalptra.add(pelemental);

      }

      string strBody(pszBody, range.m_begin - pszBody);

      m_strBody = strBody;

      if (strTag == "!DOCTYPE")
      {

         return true;

      }

      // skip white space
      range.consume_spaces(0);

      if (*range.m_begin != '>')
      {

         throw ::parsing_exception("run tag fixer tabjs");

      }

      range.m_begin++;
      
      // skip white space
      range.consume_spaces(0);      

      const_char_pointer pszCloseTag = range.m_begin;

      // skip valid char
      while (*range.m_begin != '\0' && !character_isspace(*range.m_begin) && *range.m_begin != '>')
      {

         range.m_begin++;

      }

      if (pszCloseTag[0] == '/' && case_insensitive_ansi_count_compare(m_atomTagName.m_str, pszCloseTag + 1, range.m_begin - pszCloseTag - 1) == 0)
      {

         range.m_begin++;

         return true;

      }

      throw ::parsing_exception("invalid xml file");

   }


   void element::parse_attributes(html_data * phtmldata, ::ansi_range & range)
   {

      __UNREFERENCED_PARAMETER(phtmldata);

      char chQuote;

      while (*range.m_begin != '\0' && *range.m_begin != '/' && *range.m_begin != '>')
      {

         // skip white space
         while (*range.m_begin != '\0' && character_isspace(*range.m_begin) && *range.m_begin != '/' && *range.m_begin != '>')
         {

            range.m_begin++;

         }

         if (*range.m_begin != '/' && *range.m_begin != '>')
         {

            range.m_begin--;

            return;

         }

         const_char_pointer pszKey = range.m_begin;

         // skip valid char
         while (*range.m_begin != '\0' && !character_isspace(*range.m_begin) && *range.m_begin != '=' && *range.m_begin != '/' && *range.m_begin != '>')
         {

            range.m_begin++;

         }

         string strKey(pszKey, range.m_begin - pszKey);

         if (*range.m_begin == '/' || *range.m_begin == '>')
         {

            m_propertyset[strKey] = "";

            return;

         }

         // skip valid char
         while (*range.m_begin != '\0' && character_isspace(*range.m_begin) && *range.m_begin != '=' && *range.m_begin != '/' && *range.m_begin != '>')
         {

            range.m_begin++;

         }

         if (*range.m_begin == '/' || *range.m_begin == '>')
         {

            m_propertyset[strKey] = "";

            return;

         }

         if (*range.m_begin != '=')
         {

            continue;

         }

         // skip space
         while (*range.m_begin != '\0' && character_isspace(*range.m_begin))
            range.m_begin++;

         const_char_pointer pszValue;
         if (*range.m_begin == '\"' || *range.m_begin == '\'')
         {
            chQuote = *range.m_begin;
            range.m_begin++;
            pszValue = range.m_begin;
            // skip space
            while (*range.m_begin != chQuote)
               range.m_begin++;
         }
         else
         {

            pszValue = range.m_begin;

            // skip space
            while (*range.m_begin != '\0' && character_isspace(*range.m_begin) && *range.m_begin != '/' && *range.m_begin != '>')
            {
             
               range.m_begin++;

            }

         }

         string strValue(pszValue, range.m_begin - pszValue);

         m_propertyset[strKey] = strValue;

      }

   }


   element * element::get_element_by_name(atom atom)
   {

      if (m_phtmlbase->get_type() == ::html::base::type_value)
      {

         return nullptr;

      }

      ::html::tag * ptag = m_phtmlbase->get_tag();

      if (atom == ptag->get_attr_value("name"))
      {

         return this;

      }

      element * pelemental = nullptr;

      for (int i = 0; i < m_elementalptra.get_size(); i++)
      {

         pelemental = m_elementalptra[i]->get_element_by_name(atom);

         if (pelemental != nullptr)
         {

            break;

         }

      }

      return pelemental;

   }


   element * element::get_element_by_id(atom atom)
   {

      if (m_phtmlbase->get_type() == ::html::base::type_value)
      {

         return nullptr;

      }

      ::html::tag * ptag = m_phtmlbase->get_tag();

      if (atom == ptag->get_attr_value("id"))
      {

         return this;

      }

      element * pelemental = nullptr;

      for (int i = 0; i < m_elementalptra.get_size(); i++)
      {

         pelemental = m_elementalptra[i]->get_element_by_id(atom);

         if (pelemental != nullptr)
         {

            break;

         }

      }

      return pelemental;

   }


   void element::OnLButtonDown(::message::message * pmessage)
   {

      m_pimpl->OnLButtonDown(pmessage);

   }


   void element::OnMouseMove(::message::message * pmessage)
   {

      m_pimpl->OnMouseMove(pmessage);

   }


   void element::OnLButtonUp(::message::message * pmessage)
   {

      m_pimpl->OnLButtonUp(pmessage);

   }


   element * element::hit_test(html_data * phtmldata, const ::float_point & point)
   {

      if (m_pimpl != nullptr)
      {

         if (m_pimpl->hit_test(phtmldata, point))
         {

            element * pelemental;

            for (int i = 0; i < m_elementalptra.get_size(); i++)
            {

               pelemental = m_elementalptra[i]->hit_test(phtmldata, point);

               if (pelemental != nullptr)
               {

                  return pelemental;

               }

            }

            if (m_pimpl->is_value() || m_elementalptra.get_size() <= 0)
            {

               string strBody = m_strBody;

               strBody.trim();

               if (strBody.is_empty())
               {

                  return nullptr;

               }

            }
            else
            {

               return nullptr;

            }

            return this;

         }
         else if (phtmldata->m_pcoredata->m_bEdit)
         {

            return bound_hit_test(phtmldata, point);

         }

      }

      return nullptr;

   }


   element * element::bound_hit_test(html_data * phtmldata, const ::float_point & point)
   {

      double dMin = -1.0;

      return bound_hit_test(phtmldata, point, dMin);

   }


   element * element::bound_hit_test(html_data * phtmldata, const ::float_point & point, double & dMin)
   {

      if (m_pimpl != nullptr)
      {

         double d = m_pimpl->bound_hit_test(phtmldata, point);

         if (dMin < 0.0 || (d <= dMin && d >= 0.0))
         {

            dMin = d;

            for (int i = 0; i < m_elementalptra.get_size(); i++)
            {

               element * pelemental = m_elementalptra[i]->bound_hit_test(phtmldata, point, dMin);

               if (pelemental != nullptr)
               {

                  return pelemental;

               }

            }

            return this;

         }

      }

      return nullptr;

   }


   void element::initialize_html_elemental(html_data * phtmldata, element * pparent)
   {

      //auto estatus =
      
      //::user::interaction_base::initialize(phtmldata);

      ::object::initialize(phtmldata);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      m_pstyle = __create_new < ::html::style > ();

      m_pparent = pparent;
      m_pimpl = nullptr;
      m_phtmlbase = nullptr;
      m_pdata = phtmldata;
      m_etag = tag_initial;
      m_bParent = false;
      m_bTagVisible = false;

      //return estatus;

   }


   void element::set_text(const ::scoped_string & scopedstr)
   {

      if (m_phtmlbase->get_type() == ::html::base::type_tag)
      {

         if (m_elementalptra.get_size() == 1)
         {

            m_elementalptra[0]->m_strBody = scopedstr;

         }
         else
         {

            m_strBody = scopedstr;

         }

      }
      else
      {

         m_strBody = scopedstr;

      }

   }


   void element::delete_implementation(html_data * phtmldata)
   {

      m_propertyset.clear();

      if(m_pimpl != nullptr)
      {

         if(phtmldata->m_pcoredata->m_pform != nullptr)
         {

            //if(phtmldata->m_pcoredata->m_pform->m_phtmlform != nullptr)
            //{

            //   if(phtmldata->m_pcoredata->m_pform->m_phtmlform->m_pelementalHover == this)
            //   {

            //      phtmldata->m_pcoredata->m_pform->m_phtmlform->m_pelementalHover = nullptr;

            //   }

            //}

         }

         try
         {

            m_pimpl->delete_implementation(phtmldata);

         }
         catch(...)
         {

         }

         m_pimpl = nullptr;

      }

   }


   void element::destroy(html_data * phtmldata)
   {

      m_propertyset.clear();


      try
      {

         if(phtmldata->m_pcoredata->m_pform != nullptr)
         {

            //if(phtmldata->m_pcoredata->m_pform->m_phtmlform != nullptr)
            //{

            //   if(phtmldata->m_pcoredata->m_pform->m_phtmlform->m_pelementalHover == this)
            //   {

            //      phtmldata->m_pcoredata->m_pform->m_phtmlform->m_pelementalHover = nullptr;

            //   }

            //}

         }

      }
      catch(...)
      {

      }

      try
      {

         for(int i = 0; i < m_elementalptra.get_size(); i++)
         {

            try
            {

               if(m_elementalptra[i] != nullptr)
               {

                  m_elementalptra[i]->destroy(phtmldata);

               }

            }
            catch(...)
            {

            }

            try
            {

               m_elementalptra[i].release();

            }
            catch(...)
            {

            }

         }

      }
      catch(...)
      {

      }


      if(m_pimpl != nullptr)
      {

         try
         {

            m_pimpl->delete_implementation(phtmldata);

         }
         catch(...)
         {

         }

         m_pimpl = nullptr;

      }

      m_elementalptra.erase_all();

      if (m_pparent != nullptr)
      {

         try
         {

            m_pparent->m_elementalptra.erase(this);

         }
         catch (...)
         {

         }

      }

   }


   void element::get_html(html_data * phtmldata, string & str)
   {

      if (m_phtmlbase->get_type() == ::html::base::type_value)
      {

         auto psession = phtmldata->m_pcoredata->session();

         auto puser = user();

         str += puser->m_phtml->entities(m_strBody);

      }
      else
      {

         str += "<";

         str += m_atomTagName;

         for(auto & pproperty : this->m_propertyset)
         {

            str += " ";

            str += pproperty->name().as_string();

            str += "=";

            str += "\"";

            str += pproperty->as_string();

            str += "\"";

         }

         str += ">";

         if (m_elementalptra.get_size() <= 0)
         {

            auto psession = phtmldata->m_pcoredata->session();

            auto puser = user();

            str += puser->m_phtml->entities(m_strBody);

         }
         else
         {

            for (int i = 0; i < m_elementalptra.get_size(); i++)
            {

               string strHtml;

               m_elementalptra[i]->get_html(phtmldata, strHtml);

               str += strHtml;

            }

         }

         str += "</";

         str += m_atomTagName;

         str += ">";

      }

   }


   //bool element::get_color(::color::color & color32, ::user::e_color ecolor, ::user::style_context * pcontext)
   //{

   //   if(ecolor == ::user::color_text)
   //   {

   //      if (m_pstyle->get_color("color", "", m_pdata, this, color32))
   //      {

   //         return true;

   //      }

   //   }
   //   else if(ecolor == ::user::color_background)
   //   {

   //      if (m_pstyle->get_color("background-color", "", m_pdata, this, color32))
   //      {

   //         return true;

   //      }

   //   }

   //   if (m_pparent != nullptr && m_pparent->get_color(color32, ecolor, pcontext))
   //   {

   //      return true;

   //   }

   //   return m_pdata->m_pcoredata->m_pform->get_color(color32, ecolor, pcontext);

   //}


   ::color::color element::get_color(::user::style * pstyle, ::css::enum_plain_color ecolor)
   {

      ::color::color color;

      if(ecolor == ::css::color_text)
      {

         if (m_pstyle->get_color("color", "", m_pdata, this, color))
         {

            return color;

         }

         return m_pdata->m_pcoredata->m_pform->get_color(pstyle, ::e_element_text);

      }
      else if(ecolor == ::css::color_background)
      {

         if (m_pstyle->get_color("background-color", "", m_pdata, this, color))
         {

            return color;

         }

      }

      if (m_pparent != nullptr)
      {

         return m_pparent->get_color(pstyle, ecolor);

      }

      return ::color::color();

      //return m_pdata->m_pcoredata->m_pform->get_color(color32, ecolor);

   }


   ::write_text::font_pointer element::get_font()
   {

      //font = m_pdata->get_font(this)->m_pfont;

      return m_pdata->get_font(this)->m_pfont;

      //if (font.is_null())
      //{
      //
      //   return m_pdata->m_pcoredata->m_pform->get_font(font, efont, pcontext);

      //}

      //return true;

   }


   //void element::nextstyle(::user::style_context * pcontext)
   //{

   //   pcontext->m_pstyle = m_pdata->m_pcoredata->m_pform;

   //}


} // namespace html


