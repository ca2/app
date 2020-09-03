#include "framework.h"
#include "aura/id.h"
#include "core/html/html/_.h"
#include "core/html/impl/_impl.h"
#include "core/user/user/_.h"
#include "internal.h"


namespace html
{


   elemental::elemental()
   {

      m_pstyle = __new(::html::style(this));

   }


   elemental::~elemental()
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


   void elemental::implement(html_data * pdata)
   {

      m_pdata = pdata;

      sync_lock lock(pdata->mutex());

      implement_phase1(pdata);

      implement_phase2(pdata);

   }


   tag * elemental::get_tag()
   {

      if (m_pbase == nullptr)
      {
         return nullptr;
      }
      else if (m_pbase->get_type() == base::type_tag)
      {
         return dynamic_cast < ::html::tag * > (m_pbase);
      }
      else
      {
         return nullptr;
      }

   }


   void elemental::initialize()
   {

      if (m_pparent != nullptr && m_idTagName.is_empty())
      {

         m_bParent = true;

      }
      else
      {
         m_bParent = false;

      }

      m_etag = User.m_phtml->tag_name_to_id(m_idTagName);

      if (m_etag == tag_initial)
      {

         m_etag = tag_unknown;

         m_bTagVisible = false;

      }
      else
      {

         m_bTagVisible = ::html::html::tag_visible(m_etag);

      }

      m_pstyle->initialize(m_etag);

      if (m_pbase->get_type() == ::html::base::type_value)
      {

         m_strClass = m_pparent->get_tag()->get_attr_value(__id(html_class));

         m_strInlineStyle = m_pparent->get_tag()->get_attr_value("style");

      }
      else
      {

         m_strClass = get_tag()->get_attr_value(__id(html_class));

         m_strInlineStyle = get_tag()->get_attr_value("style");

      }


   }



   void elemental::implement_phase1(html_data * pdata)
   {

      if (m_pbase == nullptr)
         return;

      if (m_etag == tag_initial)
      {

         initialize();

      }

      tag * ptag = get_tag();

      if (ptag != nullptr)
      {
         string str = ptag->get_attr_value("style");

         if (!str.is_empty())
         {

            m_pstyle->parse(pdata, str);

         }

         if (m_etag == tag_font)
         {

            string str = ptag->get_attr_value("face");

            if (str.has_char())
            {

               m_pstyle->m_propertyset["font-family"] = str;

            }

            str = ptag->get_attr_value("color");

            if (str.has_char())
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

               m_pimpl = __new(::html::impl::elemental());

            }
            else if (m_etag == tag_body)
            {

               m_pimpl = __new(::html::impl::text());

            }
            else
            {

               m_pimpl = __new(::html::impl::elemental());

            }

         }
         else if (m_etag == tag_title)
         {

            if (m_pbase->get_type() == base::type_value)
            {

               pdata->m_pcoredata->m_strTitle = m_pbase->get_value()->get_value();

               m_pimpl = __new(::html::impl::elemental());

            }
            else
            {

               m_pimpl = __new(::html::impl::elemental());

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

               m_pimpl = __new(::html::impl::input_text());

            }
            else if(strType == "calculator")
            {

               m_pimpl = __new(::html::impl::input_text("calculator", m_propertyset["unit"]));

            }
            else if (strType == "password")
            {

               m_pimpl = __new(::html::impl::input_text());

            }
            else if (strType == "button")
            {

               m_pimpl = __new(::html::impl::input_button());

            }
            else if (strType == "checkbox")
            {

               m_pimpl = __new(::html::impl::input_checkbox());

            }
            else
            {

               m_pimpl = __new(::html::impl::text());

            }

         }
         else if (m_etag == tag_select)
         {

            m_pimpl = __new(::html::impl::select());

         }
         else if (m_etag == tag_option)
         {

            m_pimpl = nullptr;

         }
         else if (m_etag == tag_img)
         {

            m_pimpl = __new(::html::impl::image());

         }
         else if (m_etag == tag_table && m_elementalptra.has_elements())
         {

            m_pimpl = __new(::html::impl::table());

         }
         else if (m_etag == tag_tr && m_elementalptra.has_elements())
         {

            m_pimpl = __new(::html::impl::table_row());

         }
         else if (m_etag == tag_td && m_elementalptra.has_elements())
         {

            m_pimpl = __new(::html::impl::cell());

         }
         else
         {

            m_pimpl = __new(::html::impl::text());

         }

         if (m_pimpl != nullptr)
         {

            m_pimpl->initialize_html_impl_elemental(pdata);

         }

      }

      if (m_pimpl != nullptr)
      {

         //if (m_elementalptra.has_elements())
         {

            if (m_strClass.has_char() || m_strInlineStyle.has_char())
            {
               if (m_strClass == "field")
               {

                  output_debug_string("field");

               }
               m_pstyle->get_surround_box(__id(html_padding), "", pdata, this, m_pimpl->m_padding);

               m_pstyle->get_border_box(__id(html_border), "", pdata, this, m_pimpl->m_border);

               m_pstyle->get_border_color(__id(html_border), "", pdata, this, m_pimpl->m_border);

               m_pstyle->get_surround_box(__id(html_margin), "", pdata, this, m_pimpl->m_margin);

            }

            if (m_pimpl->m_margin.left > 1.0f)
            {
               TRACE("margin-left greater than 1.0f");
            }

         }

         m_pimpl->implement_phase1(pdata, this);

         for (i32 i = 0; i < m_elementalptra.get_size(); i++)
         {

            m_elementalptra[i]->implement_phase1(pdata);

         }

         if (m_elementalptra.is_empty())
         {

            if (m_pstyle->m_edisplay == display_block || m_pimpl == nullptr)
            {

               pdata->m_pcoredata->m_bHasChar = false;

            }
            else
            {

               pdata->m_pcoredata->m_bHasChar = m_pimpl->m_bHasChar;

            }

         }

      }

   }


   void elemental::implement_phase2(html_data * pdata)
   {

      UNREFERENCED_PARAMETER(pdata);

   }


   void elemental::on_layout(html_data * pdata)
   {

      pdata->m_pcoredata->m_bHasChar = false;

      layout_phase0(pdata);

      layout_phase1(pdata);

      layout_phase2(pdata);

      layout_phase3(pdata);

   }


   void elemental::layout_phase0(html_data * pdata)
   {

      if (m_pimpl == nullptr)
         return;

      e_tag etag = m_etag;

      m_pimpl->layout_phase0(pdata);

      if (m_elementalptra.has_elements()
            && etag != tag_table
            && etag != tag_tbody
            && etag != tag_tr)
      {

         for (i32 i = 0; i < m_elementalptra.get_size(); i++)
         {

            m_elementalptra[i]->layout_phase0(pdata);

         }

      }

      m_pimpl->layout_phase0_end(pdata);

   }


   void elemental::layout_phase1(html_data * pdata)
   {

      if (m_pimpl == nullptr)
         return;

      if (m_etag == tag_html || m_etag == tag_body || m_etag == tag_head || m_pparent == nullptr)
      {

         m_pimpl->move_bound_to(pdata, nullptr);

         m_pimpl->set_bound_size(pdata, pdata->m_pcoredata->m_box.size());

      }

      float xMax;

      float x;

      float fLastX;

      float fLastY;

      bool bLayout = m_pimpl->layout_phase1(pdata);

      if (m_elementalptra.has_elements() &&
            m_etag != tag_select)
      {

         pdata->m_pcoredata->m_layoutstate1.m_cya.add(0.f);
         pdata->m_pcoredata->m_layoutstate1.m_cxa.add(0.f);
         pdata->m_pcoredata->m_layoutstate1.m_cxMax.add(0.f);

         pdata->m_pcoredata->m_layoutstate1.m_cy = 0.f;

         for (i32 i = 0; i < m_elementalptra.get_size(); i++)
         {

            m_elementalptra[i]->layout_phase1(pdata);

         }

         pdata->m_pcoredata->m_layoutstate1.m_cya.last() += m_pimpl->get_extra_content_height();

         m_pimpl->layout_phase1_end(pdata);

         if (m_etag != tag_tr)
         {

            if (m_pstyle->m_edisplay == display_block || m_pstyle->m_edisplay == display_table)
            {

               fLastY = pdata->m_pcoredata->m_layoutstate1.m_cya.pop();

               pdata->m_pcoredata->m_layoutstate1.m_cya.last() += fLastY;

            }
            else
            {

               pdata->m_pcoredata->m_layoutstate1.m_cya.pop_max();

            }


            {

               xMax = pdata->m_pcoredata->m_layoutstate1.m_cxMax.pop();

               x = pdata->m_pcoredata->m_layoutstate1.m_cxa.pop();

               fLastX = MAX(xMax, x);

               pdata->m_pcoredata->m_layoutstate1.m_cxMax.last() = fLastX;

            }

         }

      }
      else if (bLayout)
      {

         m_pimpl->layout_phase1_end(pdata);

         pdata->m_pcoredata->m_layoutstate1.m_cy = m_pimpl->m_box.height();

         int iExtraCy;

         iExtraCy = (int) (m_pimpl->get_extra_content_height());

         if (iExtraCy > 0)
         {

            output_debug_string("extra_cy > 0");

         }

         pdata->m_pcoredata->m_layoutstate1.m_cy += iExtraCy;

         if (m_etag == tag_br)
         {

            //pdata->m_pcoredata->m_layoutstate1.m_cya.last() += m_pimpl->m_box.get_cy();
            pdata->m_pcoredata->m_layoutstate1.m_cya.last() = MAX(pdata->m_pcoredata->m_layoutstate1.m_cya.last(), pdata->m_pcoredata->m_layoutstate1.m_cy);

         }
         else
         {

            pdata->m_pcoredata->m_layoutstate1.m_cya.last() = MAX(pdata->m_pcoredata->m_layoutstate1.m_cya.last(), pdata->m_pcoredata->m_layoutstate1.m_cy);

            pdata->m_pcoredata->m_layoutstate1.m_cxa.last() += m_pimpl->m_box.width() + m_pimpl->get_extra_content_width();

         }

         xMax = pdata->m_pcoredata->m_layoutstate1.m_cxMax.last();

         x = pdata->m_pcoredata->m_layoutstate1.m_cxa.last();

         fLastX = MAX(xMax, x);

         pdata->m_pcoredata->m_layoutstate1.m_cxMax.last() = fLastX;

      }


      if (m_elementalptra.is_empty())
      {

         if (m_pstyle->m_edisplay == display_block)
         {

            pdata->m_pcoredata->m_bHasChar = pdata->m_pcoredata->m_layoutstate1.m_bHasChar = false;

         }
         else
         {

            pdata->m_pcoredata->m_bHasChar = pdata->m_pcoredata->m_layoutstate1.m_bHasChar = m_pimpl->m_bHasChar;

         }

      }

      /*      if(m_pimpl->m_cxMin > m_pimpl->get_bound_size().cx)
            {

            m_pimpl->set_bound_size(pdata, ::sizef(m_pimpl->m_cxMin, m_pimpl->get_bound_size().cx));

            }

            m_pimpl->set_x(pdata, MAX(m_pimpl->get_bound_size().cx, m_pimpl->get_x()));*/


   }


   void elemental::layout_phase2(html_data * pdata)
   {

      if (m_pimpl == nullptr)
         return;

      m_pimpl->layout_phase2(pdata);

      for (i32 i = 0; i < m_elementalptra.get_size(); i++)
      {

         m_elementalptra[i]->layout_phase2(pdata);

      }

   }

   void elemental::layout_phase3(html_data * pdata)
   {

      if (m_pimpl == nullptr)
         return;

      if (m_pimpl != nullptr)
      {

         if (m_etag == tag_html || m_etag == tag_body || m_etag == tag_head)
         {

            if (m_etag == tag_head || m_etag == tag_html)
            {

               m_pimpl->set_dim(pdata, 0, 0, 0, 0);

            }

         }

      }

      __pointer(::html::impl::cell) pcell = m_pimpl;

      if (m_elementalptra.has_elements() && m_etag != tag_select)
      {

         if (m_bTagVisible)
         {

            if (pcell != nullptr)
            {

            }
            else if (pdata->m_pcoredata->m_layoutstate3.m_bLastBlock
                     || m_pstyle->m_edisplay == display_block
                     || m_pstyle->m_edisplay == display_table_row)
            {

               pdata->m_pcoredata->m_layoutstate3.m_y += pdata->m_pcoredata->m_layoutstate3.m_cya.last();

               pdata->m_pcoredata->m_layoutstate3.m_x = pdata->m_pcoredata->m_layoutstate3.m_xParent.last();

               pdata->m_pcoredata->m_layoutstate3.m_cya.last() = 0;

               pdata->m_pcoredata->m_layoutstate3.m_bLastBlock = false;

               pdata->m_pcoredata->m_layoutstate3.m_bLastCell = false;

            }

         }

         m_pimpl->layout_phase3(pdata);

         auto pointContent = m_pimpl->get_content_top_left();

         pdata->m_pcoredata->m_layoutstate3.m_y = pointContent.y;

         pdata->m_pcoredata->m_layoutstate3.m_cya.add(0.f);

         pdata->m_pcoredata->m_layoutstate3.m_xParent.add(pointContent.x);

         pdata->m_pcoredata->m_layoutstate3.m_x = pointContent.x;

         i32 i;

         for (i = 0; i < m_elementalptra.get_size(); i++)
         {

            m_elementalptra[i]->layout_phase3(pdata);

         }

         pdata->m_pcoredata->m_layoutstate3.m_cya.pop_max_last_add_up(0.0f);

         //m_pimpl->m_margin.top
         //+ m_pimpl->m_border.top
         //+ m_pimpl->m_padding.top
         //+ m_pimpl->m_padding.bottom
         //+ m_pimpl->m_border.bottom
         //+ m_pimpl->m_margin.bottom);

         pdata->m_pcoredata->m_layoutstate3.m_xParent.pop();

         if (m_bTagVisible)
         {

            if (m_pstyle->m_edisplay == display_table_row)
            {

               __pointer(::html::impl::table_row) prow = m_pimpl;

               if (prow->m_iRow == prow->get_table()->m_rowptra.get_upper_bound())
               {

                  pdata->m_pcoredata->m_layoutstate3.m_y = prow->get_table()->m_box.top;

                  pdata->m_pcoredata->m_layoutstate3.m_cya.last() = prow->get_table()->m_box.height();

                  pdata->m_pcoredata->m_layoutstate3.m_x = pdata->m_pcoredata->m_layoutstate3.m_xParent.last();

               }
               else
               {

                  pdata->m_pcoredata->m_layoutstate3.m_y = m_pimpl->m_box.top;

                  pdata->m_pcoredata->m_layoutstate3.m_cya.last() = m_pimpl->m_box.height();

               }

            }
            else if (pdata->m_pcoredata->m_layoutstate3.m_bLastBlock || m_pstyle->m_edisplay == display_block)
            {

               pdata->m_pcoredata->m_layoutstate3.m_y += pdata->m_pcoredata->m_layoutstate3.m_cya.last();

               pdata->m_pcoredata->m_layoutstate3.m_x = pdata->m_pcoredata->m_layoutstate3.m_xParent.last();

               pdata->m_pcoredata->m_layoutstate3.m_cya.last() = 0;

               pdata->m_pcoredata->m_layoutstate3.m_bLastBlock = false;

               pdata->m_pcoredata->m_layoutstate3.m_bLastCell = false;

            }

         }

      }
      else
      {

         m_pimpl->layout_phase3(pdata);

      }

      m_pimpl->layout_phase3_end(pdata);

   }


   void elemental::_001OnDraw(html_data * pdata)
   {

      if (m_pstyle->m_edisplay == display_table)
      {

         for (i32 i = 0; i < m_elementalptra.get_size(); i++)
         {

            m_elementalptra[i]->_001OnDraw(pdata);

         }

         if (m_pimpl != nullptr)
         {

            m_pimpl->_001OnDraw(pdata);

         }

      }
      else
      {

         if (m_pimpl != nullptr)
         {

            m_pimpl->_001OnDraw(pdata);

         }

         for (i32 i = 0; i < m_elementalptra.get_size(); )
         {

            elemental * pelemental = m_elementalptra[i];

            if (::is_null(pelemental))
            {

               continue;

            }

            try
            {

               pelemental->_001OnDraw(pdata);

               i++;

            }
            catch(...)
            {

               m_elementalptra.remove_at(i);

            }

         }

      }

   }


   void elemental::load(html_data * pdata, base * pbase)
   {

      if (pdata == nullptr)
      {

         return;

      }

      if (pdata->m_pcoredata->m_pform == nullptr)
      {

         return;

      }

      if (pbase == nullptr)
      {

         return;

      }

      sync_lock lock(pdata->m_pcoredata->mutex());

      m_pbase = pbase;

      m_elementalptra.remove_all();

      var var;

      var.set_type(::type_string);

      if (m_pbase->get_type() == base::type_tag)
      {

         ::html::tag * ptag = dynamic_cast < ::html::tag * > (m_pbase);

         m_idTagName = ptag->get_name();

         for (i32 i = 0; i < ptag->attra().get_size(); i++)
         {

            m_propertyset[ptag->attra()[i]->get_name()] = ptag->attra()[i]->get_value();

         }

         if (m_idTagName == __id(html_link) && get_tag()->get_attr_value("rel").compare_ci("stylesheet") == 0)
         {

            __pointer(style_sheet) pstylesheet(__new(style_sheet(get_context_application())));

            string strUrl(get_tag()->get_attr_value("href"));

            if(strUrl.find(":") >= 0)
            {

            }
            else if(strUrl[0] == '\\')
            {

            }
            else if(::str::begins(m_pdata->m_pcoredata->m_strPathName,"http://") ||
                    ::str::begins(m_pdata->m_pcoredata->m_strPathName,"https://"))
            {
               strUrl = System.url().path(m_pdata->m_pcoredata->m_strPathName,strUrl);
            }
            else
            {
               strUrl = m_pdata->m_pcoredata->m_strPathName.sibling(strUrl);
               strUrl.replace("/","\\");
            }
            pstylesheet->parse(pdata, Ctx(pdata).file().as_string(strUrl));
            pdata->m_pcoredata->m_stylesheeta.add(pstylesheet);
         }
         for (i32 i = 0; i < ptag->baseptra().get_size(); i++)
         {
            auto pelemental  = __new(elemental);

            pelemental->initialize_html_elemental(pdata, this);
            pelemental->load(pdata, ptag->baseptra()[i]);
            m_elementalptra.add(pelemental);
         }
      }
      else if (m_pbase->get_type() == base::type_value)
      {

         ::html::value * pvalue = dynamic_cast < ::html::value * > (m_pbase);

         ::html::tag * ptag = dynamic_cast < ::html::tag * > (m_pparent->m_pbase);

         m_idTagName = ptag->get_name();
         m_strBody = pvalue->get_value();
         if (m_idTagName == __id(html_style))
         {
            __pointer(style_sheet) pstylesheet(__new(style_sheet(get_context_application())));
            pstylesheet->parse(pdata, pvalue->get_value());
            pdata->m_pcoredata->m_stylesheeta.add(pstylesheet);
         }
         else if (m_idTagName == __id(html_link)
                  && m_pparent->get_tag()->get_attr_value("rel").compare_ci("stylesheet") == 0)
         {
            __pointer(style_sheet) pstylesheet(__new(style_sheet(get_context_application())));
            pstylesheet->parse(pdata, Ctx(pdata).file().as_string(m_pparent->get_tag()->get_attr_value("href")));
            pdata->m_pcoredata->m_stylesheeta.add(pstylesheet);
         }
      }
      else
      {
         ASSERT(FALSE);
      }
   }

   bool elemental::parse(html_data * pdata, const char * & pszParam)
   {
      const char * psz = pszParam;
      // skip white space
      while (*psz != '\0' && isspace(*psz))
         psz++;
      if (*psz != '<')
      {
         while (*psz != '<')
            psz++;
         pszParam = psz;
         return false;
      }
      psz++;
      // skip white space
      while (*psz != '\0' && isspace(*psz))
         psz++;
      const char * pszTag = psz;
      // skip valid char
      while (*psz != '\0' && !isspace(*psz) && *psz != '>')
         psz++;
      string strTag(pszTag, psz - pszTag);
      if (strTag[0] == '/')
         return false;
      m_idTagName = (id) ::str::ansi_lower(strTag);
      if (strTag == "!DOCTYPE")
      {
         // skip white space
         while (*psz != '\0' && *psz != '>')
            psz++;
      }
      else
      {
         // skip white space
         while (*psz != '\0' && isspace(*psz))
            psz++;
         // Parse Attributes
         parse_attributes(pdata, psz);
         // skip white space
         while (*psz != '\0' && isspace(*psz))
            psz++;
         if (*psz != '/' && *psz != '>')
         {
            __throw(::exception::exception("run tag fixer tabjs"));
         }
         if (*psz == '/')
         {
            // skip white space
            while (*psz != '\0' && isspace(*psz))
               psz++;
            if (*psz != '>')
            {
               __throw(::exception::exception("run tag fixer tabjs"));
            }
            return true;
         }
         psz++;
      }

      if (m_idTagName == __id(html_br))
      {

         return true;

      }

      const char * pszBody = psz;

      while (true)
      {

         __pointer(elemental) pelemental = __new(elemental);

         pelemental->initialize_html_elemental(pdata, this);

         if (!pelemental->parse(pdata, psz))
         {

            pszParam = psz;

            break;

         }

         m_elementalptra.add(pelemental);
      }

      string strBody(pszBody, psz - pszBody);

      m_strBody = strBody;

      if (strTag == "!DOCTYPE")
         return true;

      // skip white space
      while (*psz != '\0' && isspace(*psz))
         psz++;
      if (*psz != '<')
      {
         __throw(::exception::exception("run tag fixer tabjs"));
      }
      psz++;
      // skip white space
      while (*psz != '\0' && isspace(*psz))
         psz++;
      const char * pszCloseTag = psz;
      // skip valid char
      while (*psz != '\0' && !isspace(*psz) && *psz != '>')
         psz++;

      if (pszCloseTag[0] == '/' && ansi_count_compare_ci(m_idTagName.m_psz, pszCloseTag + 1, psz - pszCloseTag - 1) == 0)
      {
         psz++;
         pszParam = psz;
         return true;
      }

      __throw(::exception::exception("invalid xml file"));

   }


   void elemental::parse_attributes(html_data * pdata, const char * & psz)
   {
      UNREFERENCED_PARAMETER(pdata);
      char chQuote;
      while (*psz != '\0' && *psz != '/' && *psz != '>')
      {
         // skip white space
         while (*psz != '\0' && isspace(*psz) && *psz != '/' && *psz != '>')
            psz++;
         if (*psz != '/' && *psz != '>')
         {
            psz--;
            return;
         }
         const char * pszKey = psz;
         // skip valid char
         while (*psz != '\0' && !isspace(*psz) && *psz != '=' && *psz != '/' && *psz != '>')
            psz++;
         string strKey(pszKey, psz - pszKey);

         if (*psz == '/' || *psz == '>')
         {
            m_propertyset[strKey] = "";
            return;
         }
         // skip valid char
         while (*psz != '\0' && isspace(*psz) && *psz != '=' && *psz != '/' && *psz != '>')
            psz++;

         if (*psz == '/' || *psz == '>')
         {
            m_propertyset[strKey] = "";
            return;
         }

         if (*psz != '=')
         {
            continue;
         }
         // skip space
         while (*psz != '\0' && isspace(*psz))
            psz++;

         const char * pszValue;
         if (*psz == '\"' || *psz == '\'')
         {
            chQuote = *psz;
            psz++;
            pszValue = psz;
            // skip space
            while (*psz != chQuote)
               psz++;
         }
         else
         {
            pszValue = psz;
            // skip space
            while (*psz != '\0' && isspace(*psz) && *psz != '/' && *psz != '>')
               psz++;
         }

         string strValue(pszValue, psz - pszValue);

         m_propertyset[strKey] = strValue;

      }

   }




   elemental * elemental::get_element_by_name(id id)
   {
      if (m_pbase->get_type() == base::type_value)
         return nullptr;
      ::html::tag * ptag = m_pbase->get_tag();
      if (id == ptag->get_attr_value("name"))
         return this;
      elemental * pelemental = nullptr;
      for (i32 i = 0; i < m_elementalptra.get_size(); i++)
      {
         pelemental = m_elementalptra[i]->get_element_by_name(id);
         if (pelemental != nullptr)
            break;
      }

      return pelemental;

   }


   elemental * elemental::get_element_by_id(id id)
   {

      if (m_pbase->get_type() == base::type_value)
      {

         return nullptr;

      }

      ::html::tag * ptag = m_pbase->get_tag();

      if (id == ptag->get_attr_value("id"))
      {

         return this;

      }

      elemental * pelemental = nullptr;

      for (i32 i = 0; i < m_elementalptra.get_size(); i++)
      {

         pelemental = m_elementalptra[i]->get_element_by_id(id);

         if (pelemental != nullptr)
         {

            break;

         }

      }

      return pelemental;

   }


   void elemental::OnLButtonDown(::message::message * pmessage)
   {

      m_pimpl->OnLButtonDown(pmessage);

   }


   void elemental::OnMouseMove(::message::message * pmessage)
   {

      m_pimpl->OnMouseMove(pmessage);

   }


   void elemental::OnLButtonUp(::message::message * pmessage)
   {

      m_pimpl->OnLButtonUp(pmessage);

   }


   elemental * elemental::hit_test(html_data * pdata, const ::pointf & point)
   {

      if (m_pimpl != nullptr)
      {

         if (m_pimpl->hit_test(pdata, point))
         {

            elemental * pelemental;

            for (i32 i = 0; i < m_elementalptra.get_size(); i++)
            {

               pelemental = m_elementalptra[i]->hit_test(pdata, point);

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
         else if (pdata->m_pcoredata->m_bEdit)
         {

            return bound_hit_test(pdata, point);

         }

      }

      return nullptr;

   }


   elemental * elemental::bound_hit_test(html_data * pdata, const ::pointf & point)
   {

      double dMin = -1.0;

      return bound_hit_test(pdata, point, dMin);

   }


   elemental * elemental::bound_hit_test(html_data * pdata, const ::pointf & point, double & dMin)
   {

      if (m_pimpl != nullptr)
      {

         double d = m_pimpl->bound_hit_test(pdata, point);

         if (dMin < 0.0 || (d <= dMin && d >= 0.0))
         {

            dMin = d;

            for (i32 i = 0; i < m_elementalptra.get_size(); i++)
            {

               elemental * pelemental = m_elementalptra[i]->bound_hit_test(pdata, point, dMin);

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


   ::estatus elemental::initialize_html_elemental(html_data * pdata, elemental * pparent)
   {

      auto estatus = ::user::primitive::initialize(pdata);

      if (!estatus)
      {

         return estatus;

      }

      set_context_app(pdata->get_context_application());
      m_pparent = pparent;
      m_pimpl = nullptr;
      m_pbase = nullptr;
      m_pdata = pdata;
      m_etag = tag_initial;
      m_bParent = false;
      m_bTagVisible = false;

      return estatus;

   }


   void elemental::_001SetText(const string & str, const ::action_context & context)
   {

      if (m_pbase->get_type() == base::type_tag)
      {

         if (m_elementalptra.get_size() == 1)
         {

            m_elementalptra[0]->m_strBody = str;

         }
         else
         {

            m_strBody = str;

         }

      }
      else
      {

         m_strBody = str;

      }

   }


   void elemental::delete_implementation(html_data * pdata)
   {

      m_propertyset.clear();

      if(m_pimpl != nullptr)
      {

         if(pdata->m_pcoredata->m_pform != nullptr)
         {

            //if(pdata->m_pcoredata->m_pform->m_phtmlform != nullptr)
            //{

            //   if(pdata->m_pcoredata->m_pform->m_phtmlform->m_pelementalHover == this)
            //   {

            //      pdata->m_pcoredata->m_pform->m_phtmlform->m_pelementalHover = nullptr;

            //   }

            //}

         }

         try
         {

            m_pimpl->delete_implementation(pdata);

         }
         catch(...)
         {

         }

         m_pimpl = nullptr;

      }

   }


   void elemental::destroy(html_data * pdata)
   {

      m_propertyset.clear();


      try
      {

         if(pdata->m_pcoredata->m_pform != nullptr)
         {

            //if(pdata->m_pcoredata->m_pform->m_phtmlform != nullptr)
            //{

            //   if(pdata->m_pcoredata->m_pform->m_phtmlform->m_pelementalHover == this)
            //   {

            //      pdata->m_pcoredata->m_pform->m_phtmlform->m_pelementalHover = nullptr;

            //   }

            //}

         }

      }
      catch(...)
      {

      }

      try
      {

         for(i32 i = 0; i < m_elementalptra.get_size(); i++)
         {

            try
            {

               if(m_elementalptra[i] != nullptr)
               {

                  m_elementalptra[i]->destroy(pdata);

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

            m_pimpl->delete_implementation(pdata);

         }
         catch(...)
         {

         }

         m_pimpl = nullptr;

      }

      m_elementalptra.remove_all();

      if (m_pparent != nullptr)
      {

         try
         {

            m_pparent->m_elementalptra.remove(this);

         }
         catch (...)
         {

         }

      }

   }


   void elemental::get_html(html_data * pdata, string & str)
   {

      if (m_pbase->get_type() == base::type_value)
      {

         str += Usr(pdata->m_pcoredata->get_context_application()).m_phtml->entities(m_strBody);

      }
      else
      {

         str += "<";

         str += m_idTagName;

         for(auto & pproperty : this->m_propertyset)
         {

            str += " ";

            str += pproperty->m_id.to_string();

            str += "=";

            str += "\"";

            str += pproperty->get_string();

            str += "\"";

         }

         str += ">";

         if (m_elementalptra.get_size() <= 0)
         {

            str += Usr(pdata->m_pcoredata->get_context_application()).m_phtml->entities(m_strBody);

         }
         else
         {

            for (i32 i = 0; i < m_elementalptra.get_size(); i++)
            {

               string strHtml;

               m_elementalptra[i]->get_html(pdata, strHtml);

               str += strHtml;

            }

         }

         str += "</";

         str += m_idTagName;

         str += ">";

      }

   }


   //bool elemental::get_color(COLORREF & cr, ::user::e_color ecolor, ::user::style_context * pcontext)
   //{

   //   if(ecolor == ::user::color_text)
   //   {

   //      if (m_pstyle->get_color("color", "", m_pdata, this, cr))
   //      {

   //         return true;

   //      }

   //   }
   //   else if(ecolor == ::user::color_background)
   //   {

   //      if (m_pstyle->get_color("background-color", "", m_pdata, this, cr))
   //      {

   //         return true;

   //      }

   //   }

   //   if (m_pparent != nullptr && m_pparent->get_color(cr, ecolor, pcontext))
   //   {

   //      return true;

   //   }

   //   return m_pdata->m_pcoredata->m_pform->get_color(cr, ecolor, pcontext);

   //}


   ::color elemental::get_color(::css::enum_color ecolor)
   {

      COLORREF cr;

      if(ecolor == ::css::color_text)
      {

         if (m_pstyle->get_color("color", "", m_pdata, this, cr))
         {

            return cr;

         }

      }
      else if(ecolor == ::css::color_background)
      {

         if (m_pstyle->get_color("background-color", "", m_pdata, this, cr))
         {

            return cr;

         }

      }

      if (m_pparent != nullptr)
      {

         return m_pparent->get_color(ecolor);

      }

      return ::color();

      //return m_pdata->m_pcoredata->m_pform->get_color(cr, ecolor);

   }


   ::draw2d::font_pointer elemental::get_font()
   {

      //font = m_pdata->get_font(this)->m_font;

      return m_pdata->get_font(this)->m_font;

      //if (font.is_null())
      //{
      //
      //   return m_pdata->m_pcoredata->m_pform->get_font(font, efont, pcontext);

      //}

      //return true;

   }


   //void elemental::nextstyle(::user::style_context * pcontext)
   //{

   //   pcontext->m_pstyle = m_pdata->m_pcoredata->m_pform;

   //}


} // namespace html


