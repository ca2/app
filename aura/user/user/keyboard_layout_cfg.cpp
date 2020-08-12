#include "framework.h"

namespace user
{

   keyboard_layout_cfg::keyboard_layout_cfg()
      //      ::data::data(pobject)
      //      ::user::list_data(pobject),
      //    ::user::split_layout(pobject),
      //
      //::user::split_view(pobject),
      //place_holder_container(pobject)
   {
      //m_pdocument   = nullptr;
      //m_pview  = nullptr;
   }

   keyboard_layout_cfg::~keyboard_layout_cfg()
   {
   }

   bool keyboard_layout_cfg::CreateViews()
   {

      /*m_pdocument = Application.create_form(this, this);

      SetPaneCount(2);

      SetSplitOrientation(orientation_vertical);

      set_position_rate(0, 0.30);


      m_plistview = create_view < simple_list_view > ();

      m_plistview->m_bHoverSelect = false;
      m_plistview->m_bMultiSelect = false;

      auto pcolumn = new_list_column();
      pcolumn->m_iWidth = 584;
      m_plistview->_001InsertColumn(column);
      if(m_plistview == nullptr)
      {
         System.message_box(nullptr, "Could not create list view");
      }


      ::file::patha patha;
      Context.dir().ls(Context.dir().install() / "app/_matter/main/_std/_std/keyboard on_layout"), &patha);
      for(i32 i = 0; i < patha.get_count(); i++)
      {
         ::user::keyboard_layout_cfg_id layoutid;
         if(Session.keyboard().initialize(&layoutid, patha[i]))
         {
            m_layoutida.add(layoutid);
         }
      }

      m_layoutida.quick_sort(true);
      if(&Session.keyboard().on_layout(::draw2d::graphics_pointer & pgraphics) != nullptr)
      {
         i32 iFind = -1;
         for(i32 i = 0; i < m_layoutida.get_count(); i++)
         {
            if(m_layoutida[i].m_strPath.compare_ci(Session.keyboard().on_layout(::draw2d::graphics_pointer & pgraphics).m_strPath) == 0)
            {
               iFind = i;
               break;
            }
         }
         if(iFind >= 0)
         {
            ::user::range range;
            ::user::item_range itemrange;
            itemrange.set_lower_bound(iFind);
            itemrange.set_upper_bound(iFind);
            range.add_item(itemrange);
            m_plistview->_001SetSelection(range);
         }
      }

      m_plistview->m_pdata = this;
      m_plistview->m_pformcallback = this;
      m_plistview->_001OnUpdateItemCount();
      SetPane(0, m_plistview, false);

      if(m_pdocument != nullptr)
      {
         m_pview = m_pdocument->get_typed_view < ::user::form > ();
         m_pview->m_pcallback = this;
      }


      SetPane(1, m_pview, false);

      on_layout(::draw2d::graphics_pointer & pgraphics);*/


      return true;
   }

   void keyboard_layout_cfg::on_show()
   {
      /*      if(!m_pdocument->on_open_document(Context.dir().matter("keyboard on_layout configuration/form.html")))
            {
               return;
            }*/
      /*xml::node node(get_object());
      if(node.load(System.file_as_string(Context.dir().appdata("proxy.xml"))))
      {
         string strProxy = node.get_attr("server");
         i32 iProxyPort = node.get_attr("port");
         __pointer(::user::interaction) pinteraction = m_pview->get_child_by_name("server");
         __pointer(::user::primitive) ptext =  (pinteraction);
         ptext->_001SetText(strProxy, false);
         pinteraction = m_pview->get_child_by_name("port");
         ptext =  (pinteraction);
         ptext->_001SetText(__str(iProxyPort), false);
      }*/
   }


   /*   void keyboard_layout_cfg::_001GetItemText(::user::mesh_item * pitem)
      {
         if(pitem->m_iItem <  0 || pitem->m_iItem >= m_layoutida.get_size())
            return_(pitem->m_bOk, false);
         pitem->m_strText = m_layoutida[pitem->m_iItem].m_strName;
         pitem->m_bOk = true;
      }*/

   /*
   iptr keyboard_layout_cfg::_001GetItemCount()
   {
      return m_layoutida.get_size();
   }
   */




} // namespace user
