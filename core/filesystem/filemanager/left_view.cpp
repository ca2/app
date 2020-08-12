#include "framework.h"
//#include "_filemanager.h"
#include "_data.h"
#include "aura/user/user/_tree.h"


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

      ::filemanager::impact::install_message_routing(pchannel);
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

      SetSplitOrientation(orientation_horizontal);

      initialize_split_layout();

      auto pusertree = create_pane_view < ::user::show < ::user::tree > >(0);

      m_pusertree = pusertree;

      if(pusertree.is_null())
      {

         System.message_box("Could not create file list ::user::impact");

      }

      auto pfilemanagerdocument = filemanager_document();

      auto ptree = pfilemanagerdocument->__create_new < tree >();

      m_ptree = ptree;

      m_ptree->m_usertreea.add(m_pusertree);

      __compose(m_pusertree->m_ptree, ptree);

      ptree->initialize_filemanager_tree(pfilemanagerdocument);
      
   }


   void left_view::update(::update * pupdate)
   {

      ::filemanager::impact::update(pupdate);

      ::user::split_view::update(pupdate);

//      //__update(::update)
//      {
//
//         if (filemanager_document() == pupdate->m_pdocument)
//         {
//
//            //if (pupdate->m_id == id_initialize)
//            //{
//
//            //   string str;
//
//            //   str.Format("frame(%s)", filemanager_data()->m_id.str().c_str());
//
//            //   __pointer(::user::frame_window) pframe = GetParentFrame();
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




