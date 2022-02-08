#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/user/userex/_userex.h"
#endif



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

         if(pcommand->m_atom == m_menua[i]->m_atom.compounded(::atom::e_type_command_probe))
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

         if(pcommand->m_atom == m_menua[i]->m_atom.compounded(::atom::e_type_command))
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
         
         if(pimpactdata->m_atom == m_menua[i]->m_atom)
         {
            
            //create_context cc;
            //cc.m_pCurrentDoc = get_document();
            //cc.m_typeNewImpact = __type(::user::menu_list_view);

            __pointer(::user::impact) pview = create_view < ::user::impact > ();
            if(pview != nullptr)
            {
//               __pointer(::user::menu_list_view) pmenuview = (__pointer(::user::menu_list_view)) pview;
   /* xxx           xml::node node(this);
               node.load(pcontext->m_papexcontext->file().as_string(pcontext->m_papexcontext->dir().matter(
                  "mplite_popup_lyricview.xml")));
               pmenuview->LoadMenu(&node);*/
               pimpactdata->m_puserinteraction = pview;
            }
            break;
         }
      }
   }

   void pane_view::set_new_pane_info(atom atom, const ::string & pszMatter)
   {
      set_menu_info(atom, pszMatter, "new_pane");
   }

   void pane_view::set_menu_info(atom atom, const ::string & pszMatter, ::atom idCommand)
   {

      __pointer(menu) pmenu;

      for(i32 i = 0; i < m_menua.get_size(); i++)
      {

         if(m_menua[i]->m_atom == atom)
         {

            pmenu = m_menua[i];

            break;

         }

      }

      if(pmenu.is_null())
      {

         pmenu = new menu;

         pmenu->m_atom = atom;

         m_menua.add(pmenu);

      }

      pmenu->m_strMatter = pszMatter;

      pmenu->m_atom = idCommand;

   }


} // namespace userex




