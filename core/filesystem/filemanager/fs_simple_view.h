#pragma once


namespace filemanager
{


   namespace fs
   {


      namespace simple
      {


         class list_view;
         class tree;


         class CLASS_DECL_CORE view :
            virtual public ::user::split_view
         {
         public:


            __composite(tree)             m_ptree;
            ::user::tree *                m_pusertree;

            __pointer(list_view)          m_plist;
            ::object *                    m_prequestinterface;


            view();
            virtual ~view();


            void install_message_routing(::channel * pchannel);

            void open_file(i64 iFolder, const char * pszFileName, const char * pszExt);

            void open_folder(i64 iFolder);
            void start_music();
            void start_root();
            void CreateViews();

            void set_request_interface(::object * prequestinterface);

            virtual void assert_valid() const;
            virtual void dump(dump_context & dumpcontext) const;

            DECL_GEN_SIGNAL(on_request_response);
            DECL_GEN_SIGNAL(_001OnDestroy);

         };


      } // namespace simple


   } // namespace fs


} // namespace mplite
