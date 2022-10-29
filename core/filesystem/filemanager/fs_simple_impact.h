#pragma once


#include "base/user/user/split_impact.h"


namespace filemanager
{


   namespace fs
   {


      namespace simple
      {


         class list_impact;
         class tree;


         class CLASS_DECL_CORE impact :
            virtual public ::user::split_impact
         {
         public:


            ::pointer<tree>            m_ptree;
            ::user::tree *                m_pusertree;

            ::pointer<list_impact>         m_plist;
            ::object *                    m_prequestinterface;


            impact();
            ~impact() override;


            void install_message_routing(::channel * pchannel) override;

            void open_file(i64 iFolder, const ::string & pszFileName, const ::string & pszExt);

            void open_folder(i64 iFolder);
            void start_music();
            void start_root();
            void CreateImpacts();

            void set_request_interface(::object * prequestinterface);

            // void assert_ok() const override;
            void dump(dump_context & dumpcontext) const override;

            DECLARE_MESSAGE_HANDLER(on_request_response);
            DECLARE_MESSAGE_HANDLER(on_message_destroy);

         };


      } // namespace simple


   } // namespace fs


} // namespace mplite
