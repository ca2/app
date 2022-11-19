#include "framework.h"
#include "fs_simple_impact.h"
#include "fs_simple_list_impact.h"
#include "fs_simple_tree.h"
#include "acme/handler/item.h"
#include "acme/constant/message.h"
#include "acme/primitive/primitive/url.h"
#include "acme/platform/context.h"
#include "acme/platform/system.h"
#include "acme/primitive/data/listener.h"
#include "apex/networking/http/context.h"
#include "apex/networking/http/message.h"
#include "apex/platform/context.h"
#include "core/user/user/tree.h"


namespace filemanager
{


   namespace fs
   {


      namespace simple
      {


         impact::impact()
         {

            //   m_pinetsession = nullptr;
            m_prequestinterface = nullptr;

         }


         impact::~impact()
         {
            // if(m_pinetsession != nullptr)
            //  delete m_pinetsession;
         }


         void impact::install_message_routing(::channel * pchannel)
         {

            ::user::split_impact::install_message_routing(pchannel);

            MESSAGE_LINK(MESSAGE_DESTROY, pchannel, this, &::filemanager::fs::simple::impact::on_message_destroy);

         }



//         void impact::assert_ok() const
//         {
//            ::user::split_impact::assert_ok();
//         }
//
//         void impact::dump(dump_context & dumpcontext) const
//         {
//            ::user::split_impact::dump(dumpcontext);
//         }


         void impact::on_message_destroy(::message::message * pmessage)
         {

            m_ptree.release();

            m_plist.release();

         }


         void impact::CreateImpacts()
         {

            SetPaneCount(2);

            SetSplitOrientation(e_orientation_vertical);

            set_position_rate(0, 0.2);

            initialize_split_layout();

            __construct_new(m_ptree);

            m_ptree->m_pserver = this;

            m_pusertree = create_impact < ::user::tree > ();

            m_pusertree->merge(m_ptree, true);

            SetPane(0, m_pusertree, false);

            m_plist = create_impact < list_impact > ();

            m_plist->m_pserver = this;

            SetPane(1, m_plist, false);

            set_need_layout();

         }


         void impact::start_music()
         {

            property_set set;

//            pcontext->m_papexcontext->http().get("http://file.ca2.software/", set);

            open_folder(1000); // user ::music folder

         }


         void impact::start_root()
         {

            property_set set;

            //          pcontext->m_papexcontext->http().get("http://file.ca2.software/", set);

            open_folder(1); // user root folder

         }


         void impact::on_request_response(::message::message * pmessage)
         {

            ::pointer<::http::message>psignal(pmessage);

            string strResponse;

            strResponse = psignal->payload("get_memory");

            m_ptree->parse(strResponse);

            m_pusertree->_001SelectItem(m_ptree->FindTreeItem(m_ptree->m_iParentFolder));

            m_plist->parse(strResponse);

            set_need_layout();

         }


         void impact::open_folder(i64 iFolder)
         {

            fork([this, iFolder]()
            {

                  auto pcontext = get_context();

               auto phttpmessage = __create_new < ::http::message >();

               phttpmessage->payload("request") = "";

               phttpmessage->m_strUrl.format("http://file.ca2.software/ifs/ls?atom=%I64d", iFolder);

               phttpmessage->want_memory_response();

               pcontext->m_papexcontext->http().get(phttpmessage);

               on_request_response(phttpmessage);

            });

         }


         void impact::open_file(i64 iFolder, const ::string & pszFileName, const ::string & pszExtension)
         {

            string strUrl;

            auto psystem = acmesystem();

            auto purl = psystem->url();
            
            string strFileNameEncoded =  ::url::encode(pszFileName);

            strUrl.format("http://file.ca2.software/ifs/get?name=%s&folder=%I64d&extension=.%s",strFileNameEncoded.c_str(), iFolder, pszExtension.c_str());

            //if(m_prequestinterface != nullptr)
            //{

            //   m_prequestinterface->request({strUrl});

            //}

         }


         void impact::set_request_interface(::object * prequestinterface)
         {

            m_prequestinterface = prequestinterface;

         }


      } // namespace simple


   } // namespace library


} // namespace mplite



