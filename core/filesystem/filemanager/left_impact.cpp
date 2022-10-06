#include "framework.h"
#include "left_impact.h"
#include "document.h"
#include "tree.h"
#include "core/user/user/tree.h"


namespace filemanager
{


   left_impact::left_impact()
   {

   }


   left_impact::~left_impact()
   {

   }


   void left_impact::install_message_routing(::channel * pchannel)
   {

      ::filemanager_impact_base::install_message_routing(pchannel);
      ::user::split_impact::install_message_routing(pchannel);

   }




   void left_impact::assert_ok() const
   {
      ::user::split_impact::assert_ok();
   }

   void left_impact::dump(dump_context & dumpcontext) const
   {
      ::user::split_impact::dump(dumpcontext);
   }




   void left_impact::on_create_split_impact()
   {

      SetPaneCount(1);

      SetSplitOrientation(e_orientation_horizontal);

      initialize_split_layout();

      auto pusertree = create_pane_impact < ::user::show < ::user::tree > >(0);

      m_pusertree = pusertree;

      if(pusertree.is_null())
      {

         output_error_message("Could not create file list ::user::impact");

      }

      auto pfilemanagerdocument = filemanager_document();

      auto ptree = pfilemanagerdocument->__create_new < tree >();

      m_ptree = ptree;

      m_ptree->m_usertreea.add(m_pusertree);

      __compose(m_pusertree->m_ptree, ptree);

      ptree->initialize_filemanager_tree(pfilemanagerdocument);

   }


   void left_impact::handle(::topic * ptopic, ::context * pcontext)
   {

      ::filemanager_impact_base::handle(ptopic, pcontext);

      ::user::split_impact::handle(ptopic, pcontext);

//      //__update(::update)
//      {
//
//         if (filemanager_document() == pupdate->m_pdocument)
//         {
//
//            //if (ptopic->m_atom == id_initialize)
//            //{
//
//            //   string str;
//
//            //   str.format("frame(%s)", filemanager_data()->m_atom.str().c_str());
//
//            //   __pointer(::user::frame_window) pframe = get_parent_frame();
//
//            //   if (pframe != nullptr)
//            //   {
//
//            //      pframe->set_data_key_modifier(str);
//
//            //   }
//
//            //}
//
//         }
//
//      }

   }


} // namespace filemanager




