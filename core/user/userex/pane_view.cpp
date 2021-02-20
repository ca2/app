#include "framework.h"
#include "core/user/userex/_userex.h"


namespace userex
{


   pane_view::pane_view()
   {

   }


   pane_view::~pane_view()
   {

   }


   void pane_view::on_command_probe(::message::command * pcommand)
   {

      for(i32 i = 0; i < m_menua.get_size(); i++)
      {

         if(pcommand->m_id == m_menua[i]->m_id.compounded(::id::e_type_command_probe))
         {

            pcommand->enable(true);

            pcommand->m_bRet = true;

            return;

         }

      }

      ::user::impact::on_command_probe(pcommand);

   }


   void pane_view::on_command(::message::command * pcommand)
   {

      for(i32 i = 0; i < m_menua.get_size(); i++)
      {

         if(pcommand->m_id == m_menua[i]->m_id.compounded(::id::e_type_command))
         {
            
            // show_view where??

            pcommand->m_bRet = true;

            return;

         }

      }
      
      ::user::impact::on_command(pcommand);

   }


   void pane_view::on_create_impact(::user::impact_data * pimpactdata)
   {
      
      for(i32 i = 0; i < m_menua.get_size(); i++)
      {
         
         if(pimpactdata->m_id == m_menua[i]->m_id)
         {
            
            //create_context cc;
            //cc.m_pCurrentDoc = get_document();
            //cc.m_typeNewView = __type(::user::menu_list_view);

            __pointer(::user::impact) pview = create_view < ::user::impact > ();
            if(pview != nullptr)
            {
//               __pointer(::user::menu_list_view) pmenuview = (__pointer(::user::menu_list_view)) pview;
   /* xxx           xml::node node(get_object());
               node.load(Context.file().as_string(Context.dir().matter(
                  "mplite_popup_lyricview.xml")));
               pmenuview->LoadMenu(&node);*/
               pimpactdata->m_puserinteraction = pview;
            }
            break;
         }
      }
   }

   void pane_view::set_new_pane_info(id id, const char * pszMatter)
   {
      set_menu_info(id, pszMatter, "new_pane");
   }

   void pane_view::set_menu_info(id id, const char * pszMatter, ::id idCommand)
   {

      __pointer(menu) pmenu;

      for(i32 i = 0; i < m_menua.get_size(); i++)
      {

         if(m_menua[i]->m_id == id)
         {

            pmenu = m_menua[i];

            break;

         }

      }

      if(pmenu.is_null())
      {

         pmenu = new menu;

         pmenu->m_id = id;

         m_menua.add(pmenu);

      }

      pmenu->m_strMatter = pszMatter;

      pmenu->m_id = idCommand;

   }


} // namespace userex




