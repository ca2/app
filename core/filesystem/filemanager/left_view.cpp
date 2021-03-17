#include "framework.h"
#include "core/filesystem/filemanager/_filemanager.h"
#include "_data.h"
#include "core/user/user/_tree.h"


namespace filemanager
{


   left_view::left_view()
   {

   }


   left_view::~left_view()
   {

   }


   void left_view::install_message_routing(::channel * pchannel)
   {

      ::filemanager_impact::install_message_routing(pchannel);
      ::user::split_view::install_message_routing(pchannel);

   }




   void left_view::assert_valid() const
   {
      ::user::split_view::assert_valid();
   }

   void left_view::dump(dump_context & dumpcontext) const
   {
      ::user::split_view::dump(dumpcontext);
   }




   void left_view::on_create_split_impact()
   {

      SetPaneCount(1);

      SetSplitOrientation(e_orientation_horizontal);

      initialize_split_layout();

      auto pusertree = create_pane_view < ::user::show < ::user::tree > >(0);

      m_pusertree = pusertree;

      if(pusertree.is_null())
      {

         message_box("Could not create file list ::user::impact");

      }

      auto pfilemanagerdocument = filemanager_document();

      auto ptree = pfilemanagerdocument->__create_new < tree >();

      m_ptree = ptree;

      m_ptree->m_usertreea.add(m_pusertree);

      __compose(m_pusertree->m_ptree, ptree);

      ptree->initialize_filemanager_tree(pfilemanagerdocument);

   }


   void left_view::on_subject(::subject::subject * psubject, ::subject::context * pcontext)
   {

      ::filemanager_impact::on_subject(psubject, pcontext);

      ::user::split_view::on_subject(psubject, pcontext);

//      //__update(::update)
//      {
//
//         if (filemanager_document() == pupdate->m_pdocument)
//         {
//
//            //if (psubject->id() == id_initialize)
//            //{
//
//            //   string str;
//
//            //   str.Format("frame(%s)", filemanager_data()->m_id.str().c_str());
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




