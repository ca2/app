#include "framework.h"
#include "core/filesystem/filemanager/_filemanager.h"
#include "_data.h"
#include "core/user/user/_tree.h"


namespace filemanager
{


   namespace fs
   {


      namespace simple
      {


         view::view()
         {

            //   m_pinetsession = nullptr;
            m_prequestinterface = nullptr;

         }


         view::~view()
         {
            // if(m_pinetsession != nullptr)
            //  delete m_pinetsession;
         }


         void view::install_message_routing(::channel * pchannel)
         {

            ::user::split_view::install_message_routing(pchannel);

            MESSAGE_LINK(e_message_destroy, pchannel, this, &::filemanager::fs::simple::view::_001OnDestroy);

         }



         void view::assert_valid() const
         {
            ::user::split_view::assert_valid();
         }

         void view::dump(dump_context & dumpcontext) const
         {
            ::user::split_view::dump(dumpcontext);
         }


         void view::_001OnDestroy(::message::message * pmessage)
         {

            __release(m_ptree);

            m_plist.release();

         }


         void view::CreateViews()
         {

            SetPaneCount(2);

            SetSplitOrientation(e_orientation_vertical);

            set_position_rate(0, 0.2);

            initialize_split_layout();

            __compose_new(m_ptree);

            m_ptree->m_pserver = this;

            m_pusertree = create_view < ::user::tree > ();

            m_pusertree->merge(m_ptree, true);

            SetPane(0, m_pusertree, false);

            m_plist = create_view < list_view > ();

            m_plist->m_pserver = this;

            SetPane(1, m_plist, false);

            set_need_layout();

         }


         void view::start_music()
         {

            property_set set;

//            pcontext->m_papexcontext->http().get("http://file.ca2.cc/", set);

            open_folder(1000); // user ::music folder

         }


         void view::start_root()
         {

            property_set set;

            //          pcontext->m_papexcontext->http().get("http://file.ca2.cc/", set);

            open_folder(1); // user root folder

         }


         void view::on_request_response(::message::message * pmessage)
         {

            __pointer(::http::message) psignal(pmessage);

            string strResponse;

            strResponse = psignal->payload("get_memory");

            m_ptree->parse(strResponse);

            m_pusertree->_001SelectItem(m_ptree->FindTreeItem(m_ptree->m_iParentFolder));

            m_plist->parse(strResponse);

            set_need_layout();

         }


         void view::open_folder(i64 iFolder)
         {

            fork([this, iFolder]()
            {

                  auto pcontext = get_context();

               auto phttpmessage = __new(::http::message);

               phttpmessage->payload("request") = "";

               phttpmessage->m_strUrl.Format("http://file.ca2.cc/ifs/ls?id=%I64d", iFolder);

               phttpmessage->want_memory_response();

               pcontext->m_papexcontext->http().get(phttpmessage);

               on_request_response(phttpmessage);

            });

         }


         void view::open_file(i64 iFolder, const char * pszFileName, const char * pszExtension)
         {

            string strUrl;

            auto psystem = m_psystem;

            auto purl = psystem->url();

            strUrl.Format("http://file.ca2.cc/ifs/get?name=" + purl->url_encode(pszFileName)+ "&folder=%I64d&extension=.%s", iFolder, pszExtension);

            //if(m_prequestinterface != nullptr)
            //{

            //   m_prequestinterface->request({strUrl});

            //}

         }


         void view::set_request_interface(::object * prequestinterface)
         {

            m_prequestinterface = prequestinterface;

         }


      } // namespace simple


   } // namespace library


} // namespace mplite



