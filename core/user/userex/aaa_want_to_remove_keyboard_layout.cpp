#include "framework.h"
#include "aqua/xml.h"
#include "core/user/userex/_userex.h"


namespace userex
{


   keyboard_layout::keyboard_layout()
   {

      m_pdocument   = nullptr;
      m_pview  = nullptr;

   }


   keyboard_layout::~keyboard_layout()
   {
   }


   void keyboard_layout::assert_valid() const
   {

      ::object::assert_valid();

   }

   
   void keyboard_layout::dump(dump_context & dumpcontext) const
   {

      ::object::dump(dumpcontext);

   }


   bool keyboard_layout::CreateViews()
   {

      m_pdocument = User.create_form(this, this, this);

      SetPaneCount(2);

      SetSplitOrientation(orientation_vertical);

      set_position_rate(0, 0.30);

      initialize_split_layout();

      m_plistview = create_view < simple_list_view > ();

      m_plistview->m_bHoverSelect = false;
      m_plistview->m_bMultiSelect = false;


      {

         auto pcolumn = m_plistview->new_list_column();
         pcolumn->m_iWidth = 584;

      }

      if(m_plistview == nullptr)
      {
         System.message_box("Could not create list view");
      }


      ::file::listing patha(get_context());

      patha.ls(Context.dir().install()/ "app/_matter/main/_std/_std/keyboard on_layout");

      for(i32 i = 0; i < patha.get_count(); i++)
      {
         ::user::keyboard_layout_id layoutid;
         if(Session.keyboard().initialize(&layoutid, patha[i]))
         {
            m_layoutida.add(layoutid);
         }
      }

      ::sort::quick_sort(m_layoutida,true);

      if(is_set_ref(Session.keyboard().on_layout()))
      {

         i32 iFind = -1;

         for(i32 i = 0; i < m_layoutida.get_count(); i++)
         {

            if(m_layoutida[i].m_strPath.compare_ci(Session.keyboard().on_layout().m_strPath) == 0)
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

      m_plistview->m_pmeshdata = this;

      m_plistview->set_form_callback(this);
      m_plistview->_001OnUpdateItemCount();
      SetPane(0, m_plistview, false);

      if(m_pdocument != nullptr)
      {
         m_pview = m_pdocument->get_typed_view < ::user::form > ();
         m_pview->set_form_callback(this);
      }


      SetPane(1, m_pview, false);

      set_need_layout();

      return true;

   }


   void keyboard_layout::on_show()
   {
      if(!m_pdocument->on_open_document(Context.dir().matter("keyboard on_layout configuration/form.html")))
      {
         return;
      }
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


   void keyboard_layout::update(::update * pupdate)
   {



   }

   void keyboard_layout::on_control_event(::user::control_event * pevent)
   {

      if(pevent->m_eevent == ::user::event_list_clicked)
      {

         if(pevent->m_puie == m_plistview)
         {

            ::user::range range;

            m_plistview->_001GetSelection(range);

            if(range.get_item_count() > 0)
            {

               index iItem = range.ItemAt(0).get_lower_bound();

               if(iItem >= 0 && iItem < m_layoutida.get_count())
               {

                  Application.set_keyboard_layout(m_layoutida[iItem].m_strPath, ::source_user);

               }

            }

         }

      }
      else if(pevent->m_eevent == ::user::event_button_clicked)
      {

         if(pevent->m_puie->m_id == "submit")
         {

            auto pinteraction = m_pview->get_child_by_name("server");

            string strServer;

            pinteraction->_001GetText(strServer);

            if(strServer.get_length() == 0)
            {

               Context.file().del(Context.dir().appdata()/"proxy.xml");

            }
            else
            {

               xml::document doc;

               doc.root()->set_name("proxy");

               doc.root()->set_attribute("server", strServer);

               pinteraction = m_pview->get_child_by_name("port");

               string strPort;

               pinteraction->_001GetText(strPort);

               doc.set_attribute("port", strPort);

               Context.file().put_contents(Context.dir().appdata()/ "proxy.xml", doc.get_xml());

            }

         }

      }

   }


   void keyboard_layout::_001GetItemText(::user::mesh_item * pitem)
   {

      if(pitem->m_iItem <  0 || pitem->m_iItem >= m_layoutida.get_size())
      {

         return_(pitem->m_bOk, false);

      }

      pitem->m_strText = m_layoutida[pitem->m_iItem].m_strName;

      pitem->m_bOk = true;

   }


   ::count keyboard_layout::_001GetItemCount()
   {

      return m_layoutida.get_size();

   }

   
   //::form_property_set * keyboard_layout::get_form_property_set()
   //{
   //   
   //   auto pset = form_callback::get_form_property_set();
   //   
   //   if(pset)
   //   {
   //      
   //      return pset;
   //      
   //   }
   //   
   //   pset = ::user::impact_host::get_form_property_set();
   //   
   //   if(pset)
   //   {
   //      
   //      return pset;
   //      
   //   }
   //   
   //   return nullptr;
   //   
   //}


} // namespace userex



