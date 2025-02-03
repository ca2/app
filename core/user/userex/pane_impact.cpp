#include "framework.h"
#include "pane_impact.h"


namespace userex
{


   pane_impact::pane_impact()
   {

   }


   pane_impact::~pane_impact()
   {

   }


   void pane_impact::on_command_probe(::message::command * pcommand)
   {

      for(int i = 0; i < m_menua.get_size(); i++)
      {

         if(pcommand->command_id() == m_menua[i]->m_atomMenu)
         {

            pcommand->enable(true);

            pcommand->m_bRet = true;

            return;

         }

      }

      ::user::impact::on_command_probe(pcommand);

   }


   void pane_impact::on_command(::message::command * pcommand)
   {

      for(int i = 0; i < m_menua.get_size(); i++)
      {

         if(pcommand->command_id() == m_menua[i]->m_atomMenu.compounded(::atom::e_type_command))
         {
            
            // show_impact where??

            pcommand->m_bRet = true;

            return;

         }

      }
      
      ::user::impact::on_command(pcommand);

   }


   void pane_impact::on_create_impact(::user::impact_data * pimpactdata)
   {
      
      for(int i = 0; i < m_menua.get_size(); i++)
      {
         
         if(pimpactdata->id() == m_menua[i]->m_atomMenu)
         {
            
            //create_context cc;
            //cc.m_pCurrentDoc = get_document();
            //cc.m_typeatomNewImpact = ::type < ::user::menu_list_impact >();

            ::pointer<::user::impact>pimpact = create_impact < ::user::impact > ();
            
            if(pimpact != nullptr)
            {

//               ::pointer<::user::menu_list_impact>pmenuview = (::pointer<::user::menu_list_impact>pimpact;
   /* xxx           xml::node node(this);
               node.load(file()->as_string(directory()->matter(
                  "mplite_popup_lyricview.xml")));
               pmenuview->LoadMenu(&node);*/
               pimpactdata->m_puserinteraction = pimpact;

            }

            break;

         }

      }

   }

   
   void pane_impact::set_new_pane_info(atom atom, const ::string & pszMatter)
   {
   
      set_menu_info(atom, pszMatter, "new_pane");

   }


   void pane_impact::set_menu_info(atom atom, const ::string & pszMatter, ::atom idCommand)
   {

      ::pointer<menu>pmenu;

      for(int i = 0; i < m_menua.get_size(); i++)
      {

         if(m_menua[i]->m_atomMenu == atom)
         {

            pmenu = m_menua[i];

            break;

         }

      }

      if(pmenu.is_null())
      {

         pmenu = ___new menu();

         pmenu->m_atomMenu = atom;

         m_menua.add(pmenu);

      }

      pmenu->m_strMatter = pszMatter;

      pmenu->m_atomMenu = idCommand;

   }


} // namespace userex




