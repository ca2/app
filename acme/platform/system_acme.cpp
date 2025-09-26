#include "framework.h"
#include "library.h"
#include "node.h"
#include "acme.h"
#include "system_setup.h"
#include "system.h"
#include "system_factory.h"
//#include "sequencer.h"
#include "application.h"
#include "acme/nano/nano.h"
#include "acme/nano/http/http.h"
#include "session.h"
#include "simple_log.h"
#include "hyperlink.h"
#include "acme/compress/compress.h"
#include "acme/compress/uncompress.h"
#include "acme/constant/id.h"
//#include "acme/constant/idpool.h"
#include "acme/exception/library_not_loaded.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/filesystem/filesystem/file_system.h"
#include "acme/filesystem/filesystem/path_system.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "acme/filesystem/filesystem/file_system.h"
#include "acme/filesystem/file/transfer.h"
#include "acme/exception/interface_only.h"
#include "acme/exception/translator.h"
#include "acme/handler/extended_topic.h"
#include "acme/handler/request.h"
#include "acme/handler/topic.h"
#include "acme/operating_system/process.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/debug.h"
#include "acme/prototype/datetime/datetime.h"
#include "acme/prototype/mathematics/mathematics.h"
#include "acme/prototype/prototype/prototype.h"
#include "acme/prototype/prototype/url.h"
#include "acme/regular_expression/context.h"
//#include "acme/prototype/prototype/payload.h"
//#include "acme/prototype/string/hex.h"
#include "acme/user/micro/user.h"
#include "acme/nano/http/http.h"
#include "acme/nano/speech/speech.h"
#include "acme/windowing/windowing.h"
#include "handler/task_handler.h"
//#include "acme/user/user/conversation.h"


//extern "C" void acme_system_layer::nano_dynamic_library_factory(::factory::factory * pfactory);


//#elif defined(UNIVERSAL_WINDOWS)
//
//extern "C" void acme_system_layer::nano_user_universal_windows_factory(::factory::factory * pfactory);
//
//#endif
//
//#elif defined(MACOS)
//
//extern "C" void acme_system_layer::nano_user_macos_factory(::factory::factory* pfactory);
//
//#endif

//
//  void acme_system_layer::exception_message_box(::particle* pparticle, ::exception& exception,
//                                            const ::scoped_string & scopedstrMoreDetails)
//  {
//
//
//  }
//
//
// void acme_system_layer::trace_category_static_init(::platform::system* psystem)
//  {
//
//
//  }
//
//
// void acme_system_layer::trace_category_static_term()
//  {
//
//
//  }
//
//
// ::file::path acme_system_layer::_system_config_folder_path()
// {
//
//    ::file::path pathSystemConfigFolder;
//
// #ifdef WINDOWS
//
//    pathSystemConfigFolder = getenv("AppData");
//
// #else // WINDOWS
//
//    pathSystemConfigFolder = getenv("HOME");
//
// #ifdef MACOS
//
//    pathSystemConfigFolder /= "Application Support";
//
// #else // MACOS
//
//    pathSystemConfigFolder /= ".config";
//
// #endif // !MACOS
//
// #endif // !WINDOWS
//
//    return pathSystemConfigFolder;
//
// }
//
//
// ::file::path _ca2_config_system_folder_path()
// {
//
//    auto pathSystemConfigFolder = _system_config_folder_path();
//
//    auto pathCa2ConfigSystemFolder = pathSystemConfigFolder / "ca2/config/system";
//
//    return pathCa2ConfigSystemFolder;
//
// }
//
//
// //static ::platform::system * g_psystem = nullptr;
//
//
// //extern const_char_pointer g_pszTopLevelDomainList[];
//
//
// enum_dialog_result message_box_for_console(const ::scoped_string& scopedstr, const ::scoped_string& scopedstrTitle,
//                                            const ::user::enum_message_box& emessagebox);
//
//
// #include "acme/_operating_system.h"
//
//
// void acme_system_layer::initialize_nano_http(::factory::factory* pfactory);


namespace platform
{

   //
   //    system::system()
   //    {
   //
   //       m_psystem = this;
   //       // m_papexsystem = nullptr;
   //       // m_paquasystem = nullptr;
   //       // m_paurasystem = nullptr;
   //       // m_paxissystem = nullptr;
   //       // m_pbasesystem = nullptr;
   //       // m_pbredsystem = nullptr;
   //       // m_pcoresystem = nullptr;
   //
   // #ifndef WINDOWS
   //
   //       ::unsetenv("LD_LIBRARY_PATH");
   //
   // #endif
   //
   //       m_etracelevelMinimum = e_trace_level_undefined;
   //
   // #ifdef _DEBUG
   //       ::atom atom;
   //       int iAtom1 = sizeof(atom);
   //       int iAtomType = sizeof(atom.m_etype);
   //       int iDomainId = sizeof(atom.m_domainid);
   //       ::payload payload;
   //       auto pType = &payload.m_etype;
   //       auto pAll = &payload.m_payloadall;
   //       int iType = sizeof(payload.m_etype);
   //       int iAll = sizeof(payload.m_payloadall);
   //       int iThis = sizeof(payload);
   //       int iAddUp;
   // #if REFERENCING_DEBUGGING
   //       iAddUp += sizeof(payload.m_preferer);
   // #endif
   //       int iComputed = (int) (((unsigned char*)pAll - (unsigned char*)pType) + iAll + iAddUp);
   //       int iColor = sizeof(payload.m_color);
   //       int iStr = sizeof(payload.m_str);
   //       int iHls = sizeof(payload.m_hls);
   //       int iTime = sizeof(payload.m_time);
   //       int iAtom = sizeof(payload.id());
   //       int iFileTime = sizeof(payload.m_filetime);
   //       int iEarthTime = sizeof(payload.m_earthtime);
   //       if (iThis != iComputed)
   //       {
   //
   //          throw 0;
   //
   //       }
   // #endif
   //
   //
   //       m_bFinalizeIfNoSession = false;
   //       m_bFinalizeIfNoSessionSetting = true;
   //       m_bGraphicsAndWindowingSystemInitialized = false;
   //
   //    }
   //
   //
   //    system::~system()
   //    {
   //
   //       print_line("platform::system::~system() (start)");
   //
   //       trace_category_static_term();
   //
   //       m_psystem = nullptr;
   //       // m_papexsystem = nullptr;
   //       // m_paquasystem = nullptr;
   //       // m_paurasystem = nullptr;
   //       // m_paxissystem = nullptr;
   //       // m_pbasesystem = nullptr;
   //       // m_pbredsystem = nullptr;
   //       // m_pcoresystem = nullptr;
   //
   //       print_line("platform::system::~system() (end)");
   //
   //       //::acme::get()->m_pmanualresethappeningReadyToExit->set_happening();
   //
   //    }
   //
   //
   //    // void acme_system_layer::system::on_set_platform()
   //    // {
   //    //
   //    //    ::platform::context::on_set_platform();
   //    //
   //    // }
   //    //
   //
   //    enum_trace_level system::get_trace_level()
   //    {
   //
   //       if(m_etracelevelMinimum != e_trace_level_undefined)
   //       {
   //
   //          return m_etracelevelMinimum;
   //
   //       }
   //
   //       enum_trace_level etracelevel = e_trace_level_none;
   //
   //       // if(is_debugger_attached())
   //       // {
   //
   //       //    etracelevel = e_trace_level_information;
   //
   //       // }
   //       // else
   //       // {
   //
   //       //    etracelevel = e_trace_level_warning;
   //
   //       // }
   //
   // #ifdef _DEBUG
   //
   //       etracelevel = e_trace_level_information;
   //
   // #else
   //
   //       auto pathCa2ConfigSystemFolder = _ca2_config_system_folder_path();
   //
   //       auto pathTraceLevelInformation = pathCa2ConfigSystemFolder / "trace_level_information.txt";
   //
   //       if (this->has_argument("--log"))
   //       {
   //
   //          informationf("selecting informational trace\n");
   //
   //          etracelevel = e_trace_level_information;
   //
   //       }
   //       else if (file_exists(pathTraceLevelInformation))
   //       {
   //
   //          etracelevel = e_trace_level_information;
   //
   //       }
   //       else
   //       {
   //
   //          etracelevel = e_trace_level_warning;
   //
   //       }
   //
   // #endif
   //
   //       //if (etracelevel > e_trace_level_debug)
   //       //{
   //
   //       auto strTraceLevel = this->get_argument_begins_eat("--trace-level=");
   //
   //       if (strTraceLevel == "debug")
   //       {
   //
   //          etracelevel = e_trace_level_debug;
   //
   //       }
   //       else if (strTraceLevel == "information")
   //       {
   //
   //          etracelevel = e_trace_level_information;
   //
   //       }
   //       else if (strTraceLevel == "warning")
   //       {
   //
   //          etracelevel = e_trace_level_warning;
   //
   //       }
   //
   //       //         for (int i; i < this->get_argument_count1(); i++)
   //       //         {
   //       //
   //       //            string strArg = this->get_argument1(i);
   //       //
   //       //            if (strArg == "verbose")
   //       //            {
   //       //
   //       //               etracelevel = e_trace_level_information;
   //       //
   //       //               break;
   //       //
   //       //            }
   //       //
   //       //         }
   //
   //       //      }
   //
   //       m_etracelevelMinimum = etracelevel;
   //
   //       return m_etracelevelMinimum;
   //
   //    }
   //
   //
   //    void acme_system_layer::system::initialize_matter()
   //    {
   //
   //    }
   //
   //
   //
   //    void acme_system_layer::system::on_initialize_particle()
   //    {
   //
   //
   //    }
   //    //
   //    //
   //    // void acme_system_layer::system::initialize_system()
   //    // {
   //    //
   //    // }
   //    //
   //    //
   //    // void acme_system_layer::system::on_pre_run_task()
   //    // {
   //    //
   //    //
   //    // }
   //
   //
   //    void acme_system_layer::system::on_branch_system_from_main_thread_startup()
   //    {
   //
   //    }
   //
   //
   //    void acme_system_layer::system::main()
   //    {
   //
   //
   //    }
   //
   //
   //    class ::mathematics::mathematics* system::mathematics()
   //    {
   //
   //       return nullptr;
   //
   //    }
   //
   //
   //    class ::image::imaging* system::imaging()
   //    {
   //
   //       throw ::interface_only("imaging requires aura layer or upper layer");
   //
   //       return nullptr;
   //
   //    }
   //
   //
   //
   //    ::platform::system_factory* system::system_factory()
   //    {
   //
   //       return m_psystemfactory;
   //
   //    }
   //
   //
   //    ::xml::xml* system::_xml()
   //    {
   //
   //       return nullptr;
   //
   //    }
   //
   //
   //    void acme_system_layer::system::create_os_node()
   //    {
   //
   //       if (m_pnode)
   //       {
   //
   //          return;
   //
   //       }
   //
   //       //information() <<"::platform::system create_os_node";
   //
   //       auto& pfactory = node_factory();
   //
   //       if (!pfactory)
   //       {
   //
   //          fatal() << "node_factory has failed";
   //
   //          throw ::exception(error_resource);
   //
   //       }
   //
   // #if !defined(WINDOWS)
   //
   //       øconstruct(m_pexceptiontranslator);
   //
   //       m_pexceptiontranslator->attach();
   //
   // #endif
   //
   //       //information() << "create_os_node going to create node";
   //
   //       øconstruct(m_pnode);
   //
   //       m_pnode = m_pnode;
   //
   //       // if (m_psession)
   //       // {
   //       //
   //       //    m_psession->m_pnode = m_pnode;
   //       //
   //       // }
   //       //
   //       if (m_papplication)
   //       {
   //
   //          m_papplication->m_pnode = m_pnode;
   //
   //       }
   //
   //       m_pmutexHttpDownload = node()->create_mutex();
   //
   //
   //       //if(!estatus)
   //       //{
   //
   //       //   fatal() <<"Failed to construct node " << estatus;
   //
   //       //   return estatus;
   //
   //       //}
   //
   //       //estatus = m_pnode->initialize_matter(this);
   //       //m_pnode->initialize_matter(this);
   //
   //       //if(!estatus)
   //       //{
   //
   //       //   return estatus;
   //
   //       //}
   //
   //       //::acme::g_pengine;
   //
   //       //return estatus;
   //
   //    }
   //
   //
   //    void acme_system_layer::system::speak(const ::scoped_string & scopedstr, const ::scoped_string & scopedstrLang, enum_gender egender)
   //    {
   //
   //       nano()->speech()->speak(scopedstr, scopedstrLang, egender);
   //
   //    }
   //
   //
   //    ::pointer<::factory::factory>& system::node_factory()
   //    {
   //
   //       auto& pfactory = factory("acme", OPERATING_SYSTEM_NAME);
   //
   //       if (!pfactory)
   //       {
   //
   //          return pfactory;
   //
   //       }
   //
   //       pfactory->merge_to_global_factory();
   //
   //       return pfactory;
   //
   //    }
   //
   //
   //    void acme_system_layer::system::process_init()
   //    {
   //
   //       application()->initialize_application_flags();
   //
   //       factory()->add_factory_item<::request>();
   //
   //
   //
   // #if REFERENCING_DEBUGGING
   //
   //       ::refdbg_top_track toptrack(this);
   //
   // #endif
   //
   //       øconstruct_new(m_purlcontext);
   //
   //       //::acme::idpool::init(this);
   //
   // //      /// Create/Replace logger
   //
   //       øconstruct_new(m_pdatetime);
   //
   //
   //
   //       m_pnode->m_htaskSystem = m_htask;
   //
   //       //auto estatus = ødefer_construct_new(m_pfactorysquare);
   //
   //       //if (!estatus)
   //       //{
   //
   //       //   return estatus;
   //
   //       //}
   //
   //       // auto estatus = ([a-z0-9_]+)_factory("acme", OPERATING_SYSTEM_NAME);
   //
   //       // if (!estatus)
   //       // {
   //
   //       //    return estatus;
   //
   //       // }
   //
   //       //estatus = øconstruct(m_pnode);
   //
   //       //if (!m_pnode)
   //       //{
   //
   //       //   return error_no_memory;
   //
   //       //}
   //
   //       //auto estatus = øraw_construct(m_pdirectorysystem);
   //
   //       øraw_construct(m_pdirectorysystem);
   //
   //       /*if (!estatus)
   //        {
   //
   //        return estatus;
   //
   //        }*/
   //
   //        //      m_pdirectorysystem = pdirectorysystem;
   //
   //        //    m_pdirectorysystem->increment_reference_count();
   //
   //        //estatus = øraw_construct(m_pfilesystem);
   //
   //       øraw_construct(m_pfilesystem);
   //
   //       //if (!estatus)
   //       //{
   //
   //       //   return estatus;
   //
   //       //}
   //
   //       //estatus = øraw_construct(m_ppathsystem);
   //
   //       øraw_construct(m_ppathsystem);
   //
   //       //if (!estatus)
   //       //{
   //
   //       //   return estatus;
   //
   //       //}
   //
   //       m_pdirectorysystem->m_pfilesystem = m_pfilesystem;
   //       m_pdirectorysystem->m_ppathsystem = m_ppathsystem;
   //       m_pfilesystem->m_pdirectorysystem = m_pdirectorysystem;
   //       m_pfilesystem->m_ppathsystem = m_ppathsystem;
   //       m_ppathsystem->m_pdirectorysystem = m_pdirectorysystem;
   //       m_ppathsystem->m_pfilesystem = m_pfilesystem;
   //
   //       //estatus = m_pfilesystem->initialize(this);
   //
   //       m_pfilesystem->initialize(this);
   //
   //       //if (!estatus)
   //       //{
   //
   //       //   return estatus;
   //
   //       //}
   //
   //       //estatus = m_ppathsystem->initialize(this);
   //
   //       m_ppathsystem->initialize(this);
   //
   //       //if (!estatus)
   //       //{
   //
   //       //   return estatus;
   //
   //       //}
   //
   //       //estatus = m_pdirectorysystem->initialize(this);
   //
   //       m_pdirectorysystem->initialize(this);
   //
   //
   //       //throw ::exception(error_failed);
   //
   //
   //
   //       //if (!estatus)
   //       //{
   //
   //       //   return estatus;
   //
   //       //}
   //
   //       //return estatus;
   //
   //       m_timeStart.Now();
   //
   //       m_timeAfterApplicationFirstRequest = m_timeStart;
   //
   //       //if (file_system()->exists(::file::path(APP_CORE_BASE_DIR) / "wait_on_beg.txt"))
   //       //{
   //
   //       //   sleep(10_s);
   //
   //       //}
   //
   //       //if (file_system()->exists(::file::path(APP_CORE_BASE_DIR) / "beg_debug_box.txt"))
   //       //{
   //
   //       //   //debug_box("zzzAPPzzz app", "zzzAPPzzz app", ::user::e_message_box_icon_information);
   //
   //       //}
   //       //estatus =
   //
   //       øconstruct(m_pfilesystem);
   //
   //       //if(!estatus)
   //       //{
   //
   //       //   ERROR("failed to initialize file-system");
   //
   //       //   return estatus;
   //
   //       //}
   //
   //       //estatus =
   //
   //       //::allocator::add_referer(REFERENCING_DEBUGGING_THIS_FUNCTION_FILE_LINE);
   //
   //       øconstruct(m_pdirectorysystem);
   //
   //       //if (!estatus)
   //       //{
   //
   //       //   ERROR("failed to initialize dir-system");
   //
   //       //   return false;
   //
   //       //}
   //
   //       ///INFORMATION("apex::session::process_init .3");
   //
   //       //estatus =
   //       m_pfilesystem->init_system();
   //
   //       //if (!estatus)
   //       //{
   //
   //       //   m_estatus = estatus;
   //
   //       //   return estatus;
   //
   //       //}
   //
   //       //estatus =
   //       m_pdirectorysystem->init_system();
   //
   //       //if (!estatus)
   //       //{
   //
   //       //   m_estatus = estatus;
   //
   //       //   return estatus;
   //
   //       //}
   //
   //       //estatus = ::platform::context::initialize_context();
   //
   //       //if (!estatus)
   //       //{
   //
   //       //   return estatus;
   //
   //       //}
   //
   // #if !defined(APPLE_IOS)
   //
   //       auto pid = node()->current_process_identifier();
   //
   //       string strPid = ::as_string(pid);
   //
   //       //auto psystem = system();
   //
   //       auto pdatetime = datetime();
   //
   //       string strLogTime = pdatetime->date_time_text_for_file_with_no_spaces();
   //
   //       strLogTime.replace_with("/", "-");
   //
   //       strLogTime.replace_with("/", "_");
   //
   //       {
   //
   //          string strExecutable = this->get_executable();
   //
   //          string_array_base straArguments;
   //
   //          for (int i; i < this->get_argument_count1(); i++)
   //          {
   //
   //             string strArgument = this->get_argument1(i);
   //
   //             straArguments.add(strArgument);
   //
   //          }
   //
   //          string strCmd = strExecutable + " " + straArguments.implode("\n");
   //
   //          string strAppId = application()->m_strAppId;
   //
   //          string strCmdLineDumpFileName = strAppId / (strLogTime + "-pid" + strPid + "-command_line.txt");
   //
   //          ::file::path pathCmdLineDumpFile = directory_system()->home() / "application" / strCmdLineDumpFileName;
   //
   //          file_system()->put_contents(pathCmdLineDumpFile, strCmd);
   //
   //       }
   //
   //       {
   //
   //          string_array_base straEnv;
   // #ifdef WINDOWS_DESKTOP
   //          if (this->m_wenvp)
   //          {
   //
   //             int iIndex;
   //
   //             for (auto wenv = this->m_wenvp; *wenv != 0; wenv++, iIndex++)
   //             {
   //
   //                auto thisEnv = *wenv;
   //
   //                int iLen = (int) wcslen(thisEnv);
   //
   //                /*if (iLen >= 42)
   //                {
   //                   output_debug_string("aaa");
   //                }
   //                else*/ if (!wcsncmp(thisEnv, L"Path=", 5))
   //                {
   //
   //                   output_debug_string("aaa");
   //
   //                }
   //                else if (!wcsncmp(thisEnv, L"VsPer", 5))
   //                {
   //
   //                   output_debug_string("aaa");
   //
   //                }
   //
   //                straEnv.add(thisEnv);
   //
   //             }
   //
   //          }
   //          else
   // #endif
   //             if (this->m_envp)
   //             {
   //
   //                for (auto env = this->m_envp; *env != 0; env++)
   //                {
   //
   //                   auto thisEnv = *env;
   //
   //                   straEnv.add(thisEnv);
   //
   //                }
   //
   //             }
   //
   //          string strEnv = straEnv.implode("\n");
   //
   //          string strAppId = application()->m_strAppId;
   //
   //          string strEnvDumpFileName = strAppId / strLogTime + "-pid" + strPid + "-environment_variables.txt";
   //
   //          ::file::path pathEnvDumpFile = directory_system()->home() / "application" / strEnvDumpFileName;
   //
   //          file_system()->put_contents(pathEnvDumpFile, strEnv);
   //
   //       }
   //
   // #endif
   //
   // #if !defined(APPLE_IOS)
   //
   //       report_system_instance();
   //
   // #endif
   //
   //
   //
   //
   //
   //    }
   //
   //
   //    //   void acme_system_layer::system::start()
   //    //   {
   //    //
   //    ////      auto estatus = create_os_node();
   //    ////
   //    ////      if (!estatus)
   //    ////      {
   //    ////
   //    ////         //return estatus;
   //    ////
   //    ////         estatus = ::success_none;
   //    ////
   //    ////      }
   //    //
   //    //      estatus = os_application_system_run();
   //    //
   //    //      if (!estatus)
   //    //      {
   //    //
   //    //         return estatus;
   //    //
   //    //      }
   //    //
   //    //      return estatus;
   //    //
   //    //   }
   //
   //
   //    void acme_system_layer::system::TermSystem()
   //    {
   //
   //       auto pacmewindowing = m_pacmewindowing;
   //
   //       if (pacmewindowing)
   //       {
   //
   //          ::acme::get()->m_pmanualresethappeningReadyToExit = __raw_new manual_reset_happening();
   //          ::acme::get()->m_pmanualresethappeningMainLoopEnd = __raw_new manual_reset_happening();
   //
   //          if (!m_procedureTaskEnded)
   //          {
   //
   //             m_procedureTaskEnded = [pacmewindowing]()
   //                {
   //
   //                   ::acme::get()->m_pmanualresethappeningReadyToExit->set_happening();
   //
   //                };
   //
   //             m_pacmewindowing->windowing_post_quit();
   //
   //             ::acme::get()->m_pmanualresethappeningMainLoopEnd->_wait(2.5_min);
   //
   //             delete ::acme::get()->m_pmanualresethappeningMainLoopEnd;
   //
   //             ::acme::get()->m_pmanualresethappeningMainLoopEnd = nullptr;
   //
   //          }
   //
   //       }
   //
   //       m_pacmewindowing.release();
   //
   //       m_pmapRegularExpressionContext.release();
   //
   //       m_pfactoryFolder.release();
   //
   //       m_pdirectorysystem.release();
   //       m_pfilesystem.release();
   //       m_pfilesystem.release();
   //       m_pdirectorysystem.release();
   //       m_ppathsystem.release();
   //
   //       m_purlcontext.release();
   //
   //       m_pdatetime.release();
   //
   //       //::acme::idpool::term();
   //
   //       //m_pnode->user_post_quit();
   //
   //       m_pnode.release();
   //
   //       //try
   //       //{
   //
   //       //   ::acme::acme::g_pacme->factory_close();
   //
   //       //}
   //       //catch (...)
   //       //{
   //
   //       //}
   //
   //       //m_mapFactory.clear();
   //
   //       //m_mapComponentFactory.clear();
   //
   //
   //
   //
   //       destroy();
   //
   //
   //
   //
   //       //m_mapLibrary4.clear();
   //
   //    }
   //
   //
   //    void acme_system_layer::system::erase_from_any_hook(::matter* pmatter)
   //    {
   //
   //
   //    }
   //
   //
   //    string system::os_get_user_theme()
   //    {
   //
   //       return m_strOsUserTheme;
   //
   //    }
   //
   //
   //    unsigned int system::crc32(unsigned int uCrc, const ::block& block)
   //    {
   //
   //       _synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
   //
   //       if (!m_pcompressZlibCrc32)
   //       {
   //
   //          m_pcompressZlibCrc32 = new_zlib_compress();
   //
   //       }
   //
   //       auto pcompress = m_pcompressZlibCrc32;
   //
   //       if (!pcompress)
   //       {
   //
   //          throw "Couldn't create compress_zlib::compress instance.";
   //
   //       }
   //
   //       return pcompress->crc32(uCrc, block);
   //
   //    }
   //
   //
   //    void acme_system_layer::system::open_profile_link(const ::scoped_string & scopedstrUrl, const ::scoped_string & scopedstrProfile, const ::scoped_string & scopedstrTarget)
   //    {
   //
   //       throw ::interface_only();
   //
   //    }
   //
   //
   //    void acme_system_layer::system::open_link(const ::scoped_string & scopedstrUrl, const ::scoped_string & scopedstrProfile, const ::scoped_string & scopedstrTarget)
   //    {
   //
   //       open_profile_link(strUrl, strProfile, strTarget);
   //
   //    }
   //
   //
   //    void acme_system_layer::system::open_url(const ::scoped_string & scopedstrUrl, const ::scoped_string & scopedstrProfile, const ::scoped_string & scopedstrTarget)
   //    {
   //
   //       throw ::exception(::error_interface_only);
   //
   //    }
   //
   //
   //    //void acme_system_layer::system::__tracea(enum_trace_level elevel, const ::scoped_string & scopedstrFunction, const ::scoped_string & scopedstrFile, int iLine, const ::scoped_string & scopedstr) const
   //    //{
   //
   //    //   if (!m_ptracelog)
   //    //   {
   //
   //    //      ::information(scopedstr);
   //
   //    //      return;
   //
   //    //   }
   //
   //    //   m_ptracelog->__tracea(elevel, pszFunction, pszFile, iLine, psz);
   //
   //    //}
   //
   //
   //    //   void acme_system_layer::system::main_user_async(const ::procedure & procedure, ::enum_priority epriority)
   //    //   {
   //    //
   //    //      throw ::interface_only();
   //    //
   //    //   }
   //    //
   //    //
   //    //   void acme_system_layer::system::main_user_sync(const ::procedure & procedure, const class time & time, enum_priority epriority)
   //    //   {
   //    //
   //    //      auto proutine = ___sync_routine(routine);
   //    //
   //    //      main_user_async(proutine, epriority);
   //    //
   //    //      auto waitresult = proutine->wait(time);
   //    //
   //    //      if (!waitresult.succeeded())
   //    //      {
   //    //
   //    //         return ::error_timeout;
   //    //
   //    //      }
   //    //
   //    //      return proutine->m_estatus;
   //    //
   //    //   }
   //
   //
   //
   //
   //    void acme_system_layer::system::init_task()
   //    {
   //
   //       __check_refdbg
   //
   //       task::init_task();
   //
   //       __check_refdbg
   //
   //       call_init_system();
   //
   //    }
   //
   //
   //    void acme_system_layer::system::term_task()
   //    {
   //
   //       //term_system();
   //
   //       task::term_task();
   //
   //    }
   //
   //    string system::__get_text(const ::scoped_string & scopedstr)
   //    {
   //
   //       return str;
   //
   //    }
   //
   //
   //    //pointer< ::extended::sequence < ::conversation > > system::message_box(::user::interaction * puserinteraction, const ::scoped_string & scopedstrText, const ::scoped_string & scopedstrTitle, const ::user::e_message_box & emessagebox)
   //    //{
   //
   //    //   auto psequence = øallocate ::sequence < ::conversation > ();
   //
   //    //   psequence->set_status(error_interface_only);
   //
   //    //   //return presult;
   //
   //    //   //auto pprocess = øallocate status < enum_dialog_result > ();
   //
   //    //   //pprocess->set_result(message_box_for_console(scopedstrText, pszTitle, emessagebox));
   //
   //    //   return psequence;
   //
   //    //}
   //
   //
   //    //void acme_system_layer::system::on_initialize_window_object()
   //    //{
   //
   //    //   if (m_bOnInitializeWindowObject)
   //    //   {
   //
   //    //      return ::success_none;
   //
   //    //   }
   //
   //    //   m_bOnInitializeWindowObject = true;
   //
   //    //   auto estatus = _on_initialize_window_object();
   //
   //    //   if (!estatus)
   //    //   {
   //
   //    //      return estatus;
   //
   //    //   }
   //
   //    //   return estatus;
   //
   //    //}
   //
   //
   //    //CLASS_DECL_ACME class system * system()
   //    //{
   //    //
   //    //   return ::g_psystem;
   //    //
   //    //}
   //    //
   //
   //
   //    task_group* system::task_group(enum enum_priority)
   //    {
   //
   //       return nullptr;
   //
   //    }
   //
   //
   //    task_tool* system::task_tool(::enum_task_tool etool)
   //    {
   //
   //       return nullptr;
   //
   //    }
   //
   //
   //    void acme_system_layer::system::inline_init()
   //    {
   //
   //       init_system();
   //
   //    }
   //
   //
   //    void acme_system_layer::system::call_init_system()
   //    {
   //
   //       try
   //       {
   //
   //          init_system();
   //
   //       }
   //       catch (::exception& exception)
   //       {
   //
   //          //auto pmessagebox = __initialize_new ::message_box(exception.m_strMessage, m_strAppId, ::user::e_message_box_ok, exception.m_strDetails);
   //
   // //pmessagebox->sync();
   //
   //          string strMoreDetails;
   //
   //          strMoreDetails = "caught at system::call_init_system";
   //
   //          m_pnode->report_exception_to_user(this, exception, strMoreDetails);
   //
   //          m_estatus = exception.m_estatus;
   //
   //       }
   //
   //    }
   //
   //
   //    void acme_system_layer::system::init_system()
   //    {
   //
   //       __check_refdbg
   //
   //       set_current_handles();
   //
   //       __check_refdbg
   //
   //       //::platform::application * pappStartup = ::platform::application::g_p;
   //
   //       //if (::is_null(pappStartup))
   //       //{
   //
   //       //   pappStartup = new_app(m_strAppId);
   //
   //       //}
   //
   //       //if (!pappStartup)
   //       //{
   //
   //       //   return -1;
   //
   //       //}
   //
   //       //application() = pappStartup;
   //
   //       m_papplication->initialize(this);
   //
   //       m_papplication->get_property_set().merge(get_property_set());
   //
   //       //*((::APPLICATION_FLAGS *)this) = *application();
   //
   //       process_init();
   //
   //       init1();
   //
   //       init2();
   //
   //       //   auto & pfactory = node_factory();
   //       //
   //       //   if (!pfactory)
   //       //   {
   //       //
   //       //      //fatal() <<"node_factory has failed (status=" << (const void acme_system_layer::&) pfactory << ")";
   //       //
   //       //      throw ::exception(error_resource);
   //       //
   //       //   }
   //       //
   //       //   //auto estatus = create_os_node();
   //       //   create_os_node();
   //
   //       //if (!estatus)
   //       //{
   //
   //       //   fatal() <<"create_os_node has failed " << estatus;
   //
   //       //   return estatus;
   //
   //       //}
   //
   //       //estatus = process_init();
   //
   //       //if (!estatus)
   //       //{
   //
   //       //   return estatus;
   //
   //       //}
   //
   //       //return success;
   //
   //    }
   //
   //
   //    ::nano::nano* system::nano()
   //    {
   //
   //       if (!m_pnano)
   //       {
   //
   //          //initialize_nano_window(factory());
   //
   //          øconstruct_new(m_pnano);
   //
   //       }
   //
   //       return m_pnano;
   //
   //    }
   //
   //
   //    void acme_system_layer::system::defer_innate_ui()
   //    {
   //
   //
   //    }
   //
   //
   //    ::innate_ui::innate_ui * system::innate_ui()
   //    {
   //
   //       defer_innate_ui();
   //
   //       return m_pinnateui;
   //
   //    }
   //
   //
   //    void acme_system_layer::system::defer_audio()
   //    {
   //
   //       throw ::interface_only();
   //
   //    }
   //    //::nano::nano * system::nano()
   //    //{
   //    //
   //    //   if (!m_pnanohttp)
   //    //   {
   //    //
   //    //      initialize_nano_http(factory());
   //    //
   //    //      øconstruct(m_pnanohttp);
   //    //
   //    //   }
   //    //
   //    //   return m_pnanohttp;
   //    //
   //    //}
   //
   //
   //    //   ::nano::http * system::nano_http()
   //    //   {
   //    //
   //    //      if (!m_pnanohttp)
   //    //      {
   //    //
   //    //         initialize_nano_http(factory());
   //    //
   //    //         øconstruct(m_pnanohttp);
   //    //
   //    //      }
   //    //
   //    //      return m_pnanohttp;
   //    //
   //    //   }
   //    //
   //    //
   //    bool system::has_audio()
   //    {
   //
   //       return false;
   //
   //    }
   //
   //
   //    void acme_system_layer::system::init1()
   //    {
   //
   //       //initialize_context_1();
   //
   //    }
   //
   //
   //    void acme_system_layer::system::init2()
   //    {
   //
   //
   //       initialize_matter();
   //
   //       if (application()->m_bSession)
   //       {
   //
   //          //return ::success;
   //          create_session();
   //
   //       }
   //
   //       //::string strRoot = "ca2.network";
   //
   //       //::file::path pathGooglePayload = "C:\\sensitive\\sensitive\\api\\google\\account\\" + strRoot + ".network_payload";
   //
   //       //auto payloadGoogle = file()->as_network_payload(pathGooglePayload);
   //
   //       //::string strClientId = payloadGoogle["web"]["client_id"];
   //
   //       //auto straRedirectUri = payloadGoogle["web"]["redirect_uris"].as_string_array();
   //
   //       //auto iFind = straRedirectUri.find_first_begins("https://" + strRoot + "/");
   //
   //       //if (iFind < 0)
   //       //{
   //
   //       //   throw ::exception(error_failed);
   //
   //       //}
   //
   //       if (application()->m_bSession)
   //       {
   //
   //          session()->branch_synchronously();
   //
   //       }
   //
   //
   //    }
   //
   //
   //    void acme_system_layer::system::set_current_handles()
   //    {
   //
   //
   //    }
   //
   //
   //
   //    //::pointer<::acme::library> system::library(const ::scoped_string & scopedstrComponent, const ::scoped_string & scopedstrImplementationParam)
   //    //{
   //
   //    //   string strImplementation(strImplementationParam);
   //
   //    //   strImplementation.case_insensitive_begins_eat(strComponent + "_");
   //
   //    //   string strLibrary;
   //
   //    //   strLibrary = strComponent + "_" + strImplementation;
   //
   //    //   auto& plibrary = library(strLibrary);
   //
   //    //   if (!plibrary)
   //    //   {
   //
   //    //      return plibrary;
   //
   //    //   }
   //
   //    //   return plibrary;
   //
   //    //}
   //
   //
   //
   //
   //
   //
   //    //::pointer<::acme::library>& system::library(const ::scoped_string & scopedstrComponent, const ::scoped_string & scopedstrImplementation)
   //    //{
   //
   //    //   // Ex. "draw2d" (Component) and implementation: either "draw2dcairo", "cairo", "draw2d_cairo"
   //
   //    //   if (strComponent.is_empty() || strImplementation.is_empty())
   //    //   {
   //
   //    //      throw error_bad_argument;
   //
   //    //   }
   //
   //    //   auto psystem = system();
   //
   //    //   _synchronous_lock synchronouslock(&psystem->m_pmutexLibrary2);
   //
   //    //   auto & plibrary = psystem->m_mapLibrarySquare[strComponent][strImplementation];
   //
   //    //   if (plibrary.is_initialized())
   //    //   {
   //
   //    //      return plibrary;
   //
   //    //   }
   //
   //    //   string strLibrary;
   //
   //    //   strLibrary = strComponent + "_" + strImplementation;
   //
   //    //   _load_library(plibrary, strLibrary);
   //
   //    //   return plibrary;
   //
   //    //}
   //
   //
   //    //::pointer<::acme::library>system::open_containerized_component_library(const ::scoped_string & scopedstrComponent, const ::scoped_string & scopedstrImplementation)
   //    //{
   //
   //    //   // Ex. "draw2d" (Component) and implementation: either "draw2dcairo", "cairo", "draw2d_cairo"
   //
   //    //   string strComponent(scopedstrComponent);
   //
   //    //   string strImplementation(scopedstrImplementation);
   //
   //    //   strComponent.trim();
   //
   //    //   strImplementation.trim();
   //
   //    //   string strLibrary;
   //
   //    //   if (strImplementation.is_empty())
   //    //   {
   //
   //    //      return nullptr;
   //
   //    //   }
   //
   //    //   strImplementation.case_insensitive_begins_eat(strComponent + "_");
   //
   //    //   strImplementation.case_insensitive_begins_eat(strComponent);
   //
   //    //   auto psystem = system();
   //
   //    //   _synchronous_lock synchronouslock(&psystem->m_pmutexContainerizedLibrary);
   //
   //    //   ::pointer<::acme::library>plibrary = psystem->m_mapContainerizedLibrary[strComponent][strImplementation];
   //
   //    //   if (plibrary && plibrary->is_opened())
   //    //   {
   //
   //    //      return plibrary;
   //
   //    //   }
   //
   //    //   strLibrary = strComponent + "_" + strImplementation;
   //
   //    //#ifdef CUBE
   //
   //    //   auto plibraryfactory = ::system_setup::get_first(::system_setup::flag_library, strLibrary);
   //
   //    //   if (!plibraryfactory)
   //    //   {
   //
   //    //      return nullptr;
   //
   //    //   }
   //
   //    //   plibrary = plibraryfactory->create_library();
   //
   //    //#else
   //
   //    //   if (!plibrary)
   //    //   {
   //
   //    //      plibrary = øallocate ::acme::library();
   //
   //    //      plibrary->initialize_matter(this);
   //
   //    //   }
   //
   //    //   if (!plibrary->open(strLibrary))
   //    //   {
   //
   //    //      return nullptr;
   //
   //    //   }
   //
   //    //   if (!plibrary->is_opened())
   //    //   {
   //
   //    //      return nullptr;
   //
   //    //   }
   //
   //    //#endif
   //
   //    //   return plibrary;
   //
   //    //}
   //
   //
   //    class ::time system::get_update_poll_time(const ::atom& atom)
   //    {
   //
   //       return 0_s;
   //
   //    }
   //
   //
   //    ::acme::library* system::on_get_library(const ::scoped_string & scopedstrLibrary)
   //    {
   //
   //       return nullptr;
   //
   //    }
   //
   //
   //    //   ::extended::transport < ::factory::factory > system::([a-z0-9_]+)_factory(const ::scoped_string & scopedstrComponent, const ::scoped_string & scopedstrImplementation)
   //    //   {
   //    //
   //    //      auto& pfactory = m_mapFactoryMap[strComponent][strImplementation];
   //    //
   //    //      string strComponent(scopedstrComponent);
   //    //
   //    //      string strImplementation(scopedstrImplementation);
   //    //
   //    //      strImplementation.case_insensitive_begins_eat(strComponent + "_");
   //    //
   //    //      strImplementation.case_insensitive_begins_eat(strComponent);
   //    //
   //    //   //#ifdef CUBE
   //    //
   //    //      //auto pfnFactoryExchange = m_mapFactoryExchange[strComponent][strImplementation];
   //    //
   //    //      //if (::is_null(pfnFactoryExchange))
   //    //      //{
   //    //
   //    //      //   return ::error_failed;
   //    //
   //    //      //}
   //    //
   //    //#ifdef CUBE
   //    //
   //    //      _synchronous_lock synchronouslock(m_pmutexContainerizedLibrary, DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
   //    //
   //    //      auto & plibrary = m_mapContainerizedLibrary[strComponent][strImplementation];
   //    //
   //    //      if (plibrary && plibrary->is_opened())
   //    //      {
   //    //
   //    //         return plibrary;
   //    //
   //    //      }
   //    //
   //    //      string strLibrary = strComponent + "_" + strImplementation;
   //    //
   //    //      auto pfnFactoryExchange = ::system_setup::get_factory_item_exchange(strLibrary);
   //    //
   //    //      //if (::is_null(pfnFactoryExchange))
   //    //      if (::is_null(pfnFactoryExchange))
   //    //      {
   //    //
   //    //         return ::error_failed;
   //    //
   //    //      }
   //    //
   //    //      plibrary = øallocate ::acme::library();
   //    //
   //    //      plibrary->initialize_matter(this);
   //    //
   //    //      øconstruct_new(plibrary->m_pfactory);
   //    //
   //    //      plibrary->m_pfactory->initialize_matter(this);
   //    //
   //    //      pfnFactoryExchange(plibrary->m_pfactory);
   //    //
   //    //      return plibrary;
   //    //
   //    //   #else
   //    //
   //    //      auto plibrary = open_containerized_component_library(scopedstrComponent, pszImplementation);
   //    //
   //    //      if (!plibrary)
   //    //      {
   //    //
   //    //         return ::error_failed;
   //    //
   //    //      }
   //    //
   //    //      string strFunctionName = strComponent + "_" + strImplementation + "_factory";
   //    //
   //    //      PFN_factory ([a-z0-9_]+)_factory = plibrary->get < PFN_factory >(strFunctionName);
   //    //
   //    //      if (([a-z0-9_]+)_factory == nullptr)
   //    //      {
   //    //
   //    //         ([a-z0-9_]+)_factory = plibrary->get < PFN_factory >(strComponent + "_factory");
   //    //
   //    //         if (([a-z0-9_]+)_factory == nullptr)
   //    //         {
   //    //
   //    //            ([a-z0-9_]+)_factory = plibrary->get < PFN_factory >("factory_exchange");
   //    //
   //    //            if (([a-z0-9_]+)_factory == nullptr)
   //    //            {
   //    //
   //    //               return ::error_failed;
   //    //
   //    //            }
   //    //
   //    //         }
   //    //
   //    //      }
   //    //
   //    //      øconstruct_new(pfactory);
   //    //
   //    //      plibrary->m_pfactory->initialize_matter(this);
   //    //
   //    //      ([a-z0-9_]+)_factory(plibrary->m_pfactory);
   //    //
   //    //      return plibrary;
   //    //
   //    //#endif
   //    //
   //    //   }
   //
   //
   //    void acme_system_layer::system::check_exit()
   //    {
   //
   //
   //    }
   //
   //
   //    ::regular_expression_pointer system::create_regular_expression(const ::scoped_string & scopedstrStyle, const ::scoped_string & scopedstr)
   //    {
   //
   //       auto pcontext = get_regular_expression_context(scopedstrStyle);
   //
   //       if (!pcontext)
   //       {
   //
   //          return nullptr;
   //
   //       }
   //
   //       auto pregularexpression = pcontext->compile(str);
   //
   //       if (!pregularexpression)
   //       {
   //
   //          return nullptr;
   //
   //       }
   //
   //       return pregularexpression;
   //
   //    }
   //
   //
   //    ::pointer<::regular_expression::context>system::get_regular_expression_context(const ::scoped_string & scopedstrStyle)
   //    {
   //
   //       _synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);
   //
   //       ødefer_construct_new(m_pmapRegularExpressionContext);
   //
   //       auto& pcontext = (*m_pmapRegularExpressionContext)[pszStyle];
   //
   //       if (!pcontext)
   //       {
   //
   //          auto& pfactory = factory("regular_expression", pszStyle);
   //
   //          if (!pfactory)
   //          {
   //
   //             throw ::exception(error_resource);
   //
   //          }
   //
   //          pfactory->øconstruct(this, pcontext);
   //
   //       }
   //
   //       return pcontext;
   //
   //    }
   //
   //
   //    ::regular_expression_pointer system::compile_pcre(const ::scoped_string & scopedstr)
   //    {
   //
   //       return create_regular_expression("pcre2", str);
   //
   //    }
   //
   //
   //    ::pointer<::regular_expression::context>system::get_pcre_context()
   //    {
   //
   //       return get_regular_expression_context("pcre2");
   //
   //    }
   //
   //
   //    //   int system::pcre_add_tokens(string_array_base& stra, const ::scoped_string & scopedstrTopic, const ::scoped_string & scopedstrRegexp, int nCount)
   //    //   {
   //    //
   //    //      throw_todo();
   //    //
   //    //      return -1;
   //    //
   //    //   }
   //
   //
   //    ::string system::fetch_public_internet_domain_extension_list_text()
   //    {
   //
   //       throw interface_only();
   //
   //       return {};
   //
   //    }
   //
   //
   //    void acme_system_layer::system::get_public_internet_domain_extension_list(string_array_base& stra)
   //    {
   //
   //       //::file::path pathPublicDomainExtensionList = "https://ca2.network/public_internet_domain_extension_list.txt";
   //
   //       //file()->load_lines(stra, pathPublicDomainExtensionList);
   //
   //       string str = fetch_public_internet_domain_extension_list_text();
   //
   //       auto psz = str.c_str();
   //
   //       while (*psz != '\0')
   //       {
   //
   //          string str(*psz);
   //
   //          auto pStart = str.find('(');
   //
   //          if (::is_null(pStart))
   //          {
   //
   //             stra.add(str);
   //
   //             continue;
   //
   //          }
   //
   //          auto pEnd = str(pStart + 1).find(')');
   //
   //          if (::is_null(pEnd))
   //          {
   //
   //             string strItem = str(0, pStart);
   //
   //             stra.add(strItem);
   //
   //             continue;
   //
   //          }
   //
   //          stra.add({ pStart, pEnd - pStart - 1 });
   //
   //       }
   //
   //       stra.trim();
   //
   //       stra.erase_empty();
   //
   //       information() << "platform::system::get_public_internet_domain_extension_list";
   //
   //       for (auto& str : stra)
   //       {
   //
   //          informationf("%s", str.c_str());
   //
   //       }
   //
   //       //return ::success;
   //
   //    }
   //
   //
   //    void acme_system_layer::system::create_session(::collection::index iEdge)
   //    {
   //
   //       if (session(iEdge))
   //       {
   //
   //          //return ::success;
   //          return;
   //
   //       }
   //
   //       auto psession = on_create_session(iEdge);
   //
   //       //if (!psession)
   //       //{
   //
   //       //   return false;
   //
   //       //}
   //
   //       add_session(iEdge, psession);
   //
   //       //return ::success;
   //
   //    }
   //
   //
   //
   //    ::pointer<::platform::session>system::on_create_session(::collection::index iEdge)
   //    {
   //
   //       ::pointer<::platform::session>psession;
   //
   //       //auto estatus =
   //       øraw_construct(psession);
   //
   //       //psession->set_platform();
   //
   //       psession->initialize(this);
   //
   //       psession->m_papplication = m_papplication;
   //       //psession->m_psystem = this;
   //       //psession->m_pnode = m_pnode;
   //
   //       if (m_papplication)
   //       {
   //
   //          m_papplication->m_psession = psession;
   //
   //       }
   //
   //       //if (!estatus)
   //       //{
   //
   //       //   return estatus;
   //
   //       //}
   //
   //       psession->m_iEdge = iEdge;
   //
   //       return psession;
   //
   //    }
   //
   //
   //    ::platform::session* system::session(::collection::index iEdge)
   //    {
   //
   //       auto iterator = m_sessionmap.find(iEdge);
   //
   //       if (iterator.is_null())
   //       {
   //
   //          return nullptr;
   //
   //       }
   //
   //       return iterator->element2();
   //
   //    }
   //
   //
   //    void acme_system_layer::system::add_session(::collection::index iEdge, ::platform::session* psession)
   //    {
   //
   //       if (!::is_set(psession))
   //       {
   //
   //          return;
   //
   //       }
   //
   //       bool bWasEmpty = m_sessionmap.is_empty();
   //
   //       m_sessionmap[iEdge] = psession;
   //
   //       on_add_session(psession);
   //
   //       if (bWasEmpty)
   //       {
   //
   //          m_bFinalizeIfNoSession = m_bFinalizeIfNoSessionSetting;
   //
   //       }
   //
   //    }
   //
   //
   //    void acme_system_layer::system::on_add_session(::platform::session* pacmesession)
   //    {
   //
   //       if (pacmesession->m_iEdge == 0)
   //       {
   //
   //          if (!m_psession)
   //          {
   //
   //             m_psession = pacmesession;
   //
   //          }
   //
   //       }
   //
   //       //pacmesession->m_psystem = this;
   //
   //    }
   //
   //
   //    void acme_system_layer::system::erase_session(::collection::index iEdge)
   //    {
   //
   //       auto psession = m_sessionmap[iEdge];
   //
   //       m_sessionmap.erase_item(iEdge);
   //
   //       if (m_sessionmap.is_empty() && m_bFinalizeIfNoSession)
   //       {
   //
   //          set_finish();
   //
   //       }
   //
   //       //   if (psession)
   //       //   {
   //       //
   //       //      class time time;
   //       //
   //       //      time.Now();
   //       //
   //       //      while (true)
   //       //      {
   //       //
   //       //         if (psession->m_countReference <= 1)
   //       //         {
   //       //
   //       //            break;
   //       //
   //       //         }
   //       //
   //       //         preempt(100_ms);
   //       //
   //       //         if (time.elapsed() > 10_s)
   //       //         {
   //       //
   //       //            break;
   //       //
   //       //         }
   //       //
   //       //      }
   //       //
   //       //   }
   //       //
   //    }
   //
   //
   //    void acme_system_layer::system::on_request(::request* prequest)
   //    {
   //
   //       auto psession = session();
   //
   //       if (psession == nullptr)
   //       {
   //
   //          return;
   //
   //       }
   //
   //       information() << "::apex::system::on_request session = " << ::type(psession).name() << "(" << ((iptr)psession) << ")";
   //
   //       psession->post_request(prequest);
   //
   //    }
   //
   //
   //
   //    void acme_system_layer::system::process_exit_status(::particle* pparticle, const ::e_status& estatus)
   //    {
   //
   //       if (estatus == error_exit_system)
   //       {
   //
   //          pparticle->system()->set_finish();
   //
   //       }
   //
   //    }
   //
   //
   //    void acme_system_layer::system::on_start_system()
   //    {
   //
   //       ////*auto estatus =*/ m_pnode->on_start_system();
   //
   //       //if (!estatus)
   //       //{
   //
   //       //   return estatus;
   //
   //       //}
   //
   //       //return estatus;
   //
   //    }
   //
   //
   //    void acme_system_layer::system::defer_post_initial_request()
   //    {
   //
   //       if (!m_bPostedInitialRequest)
   //       {
   //
   //          m_bPostedInitialRequest = true;
   //
   //          auto prequest = øcreate_new< ::request>();
   //
   //          auto strCommandLine = this->m_strCommandLine;
   //
   //          strCommandLine.trim();
   //
   //          prequest->m_strAppId = application()->m_strAppId;
   //
   //          ::string strApp;
   //
   //          if (strCommandLine.has_character())
   //          {
   //
   //             information() << "system::defer_post_initial_request ***strCommandLine*** : ***" << strCommandLine << "***";
   //
   //             prequest->m_strCommandLine = strCommandLine;
   //
   //             prequest->get_property_set()._008ParseCommandFork(
   //                strCommandLine,
   //                prequest->m_payloadFile,
   //                strApp);
   //
   //          }
   //          else
   //          {
   //
   //             strApp = this->m_args[0];
   //
   //             ::string_array_base straFiles;
   //
   //             for (int iArgument; iArgument < this->m_argc; )
   //             {
   //
   //                auto iArgumentBefore = iArgument;
   //
   //                if (node()->defer_consume_main_arguments(
   //                   this->m_argc,
   //                   this->m_args,
   //                   iArgument)
   //                   && iArgument > iArgumentBefore)
   //                {
   //
   //                   continue;
   //
   //                }
   //
   //                if (application()->defer_consume_main_arguments(
   //                   this->m_argc,
   //                   this->m_args,
   //                   iArgument)
   //                   && iArgument > iArgumentBefore)
   //                {
   //
   //                   continue;
   //
   //                }
   //
   //                ::string strArgument = this->m_args[iArgument];
   //
   //                if (strArgument.begins("-"))
   //                {
   //
   //                   prequest->get_property_set()._008AddArgument(strArgument);
   //
   //                }
   //                else
   //                {
   //
   //                   straFiles.add(strArgument);
   //
   //                }
   //
   //                iArgument++;
   //
   //             }
   //
   //             if (straFiles.has_elements())
   //             {
   //
   //                if (straFiles.size() == 1)
   //                {
   //
   //                   prequest->m_payloadFile = straFiles[0];
   //
   //                }
   //                else
   //                {
   //
   //                   prequest->m_payloadFile.string_array_reference() = straFiles;
   //
   //                }
   //
   //             }
   //
   //          }
   //
   //          payload("command_line_arg0") = strApp;
   //
   //          application()->get_property_set().merge(prequest->get_property_set());
   //
   //          post_request(prequest);
   //
   //       }
   //
   //    }
   //
   //
   //    void acme_system_layer::system::canonical_system_main()
   //    {
   //
   //       process_init();
   //
   //       if (this->is_console())
   //       {
   //
   //          application()->main();
   //
   //       }
   //       else
   //       {
   //
   //          // on canonical system on_start_system is called before main loop
   //          on_start_system();
   //
   //          //auto estatus =
   //          main();
   //
   //          //if (!estatus)
   //          //{
   //
   //          //   return estatus;
   //
   //          //}
   //
   //          //return estatus;
   //
   //       }
   //
   //       if (m_iExitCode == 0 && m_estatus.failed())
   //       {
   //
   //          m_iExitCode = m_estatus.exit_code();
   //
   //       }
   //
   //
   //    }
   //
   //
   //    void acme_system_layer::system::system_main()
   //    {
   //
   //       init_system();
   //
   //       m_pnode->system_main();
   //
   //    }
   //
   //
   //
   //    //::application* system::get_main_application()
   //    //{
   //
   //    //   throw ::interface_only();
   //
   //    //   return nullptr;
   //
   //    //}
   //
   //
   //    //void acme_system_layer::system::system_construct(int argc, char** argv, char** envp)
   //    //{
   //
   //    //   throw ::interface_only();
   //
   //    //}
   //
   //
   //    //void acme_system_layer::system::system_construct(int argc, wchar_t** argv, wchar_t** envp)
   //    //{
   //
   //    //   throw ::interface_only();
   //
   //    //}
   //
   //    //
   //    //   void acme_system_layer::system::inline_init()
   //    //   {
   //    //
   //    //      auto estatus = process_init();
   //    //
   //    //      if (!estatus)
   //    //      {
   //    //
   //    //         return estatus;
   //    //
   //    //      }
   //    //
   //    //      return ::success;
   //    //
   //    //   }
   //    //
   //    //
   //    void acme_system_layer::system::inline_term()
   //    {
   //
   //       //return ::success;
   //
   //    }
   //
   //
   //    //   void acme_system_layer::system::on_start_system()
   //    //   {
   //    //
   //    //      return ::success;
   //    //
   //    //   }
   //    //
   //    //
   //    void acme_system_layer::system::on_end()
   //    {
   //
   //       TermSystem();
   //
   //       //return ::success;
   //
   //    }
   //
   //    void acme_system_layer::system::end()
   //    {
   //
   //       /*auto estatus = */ on_end();
   //
   //       //if (!estatus)
   //       //{
   //
   //       //   return estatus;
   //
   //       //}
   //
   //       /*estatus = */ inline_term();
   //
   //       //if (!estatus)
   //       //{
   //
   //       //   return estatus;
   //
   //       //}
   //
   //       //return estatus;
   //       //
   // #ifdef __MCRTDBG
   //
   //       _CrtDumpMemoryLeaks();
   //
   // #endif
   //
   //    }
   //
   //
   //    void acme_system_layer::system::report_system_instance()
   //    {
   //
   //       string strAppId = application()->m_strAppId;
   //
   //       if (strAppId.has_character())
   //       {
   //
   //          string strModifier;
   //
   //          string strDate;
   //
   //          strDate = datetime()->date_time_text_for_file_with_no_spaces();
   //
   //          string strPid;
   //
   //          strPid = ::as_string(node()->current_process_identifier());
   //
   //          strModifier = strDate + "_" + strPid;
   //
   //          ::file::path pathFolder;
   //
   // #ifdef __ANDROID__
   //
   //          pathFolder = system()->m_pathCacheDirectory;
   //
   // #else
   //
   //          pathFolder = directory_system()->roaming();
   //
   // #endif
   //
   //          pathFolder /= strAppId;
   //
   //          pathFolder /= "instance";
   //
   //          ::file::path path = pathFolder / (strModifier + "_command_line.txt");
   //
   //          file_system()->put_contents(path, this->m_strCommandLine);
   //
   //          ::file::path pathExecutable = file_system()->module();
   //
   //          string strAppTitle = node()->executable_title_from_appid(strAppId);
   //
   //          path = pathFolder / (strModifier + "_executable.txt");
   //
   //          file_system()->put_contents(path, pathExecutable);
   //
   //       }
   //
   //    }
   //
   //
   //
   //
   //    ::platform::application* system::get_main_app()
   //    {
   //
   //
   //       throw ::interface_only();
   //
   //
   //       return nullptr;
   //
   //    }
   //
   //
   //    ::pointer<::factory::factory>& system::folder_factory()
   //    {
   //
   //       if (m_pfactoryFolder)
   //       {
   //
   //          return m_pfactoryFolder;
   //
   //       }
   //
   //       m_pfactoryFolder = factory("folder", "zip");
   //
   //       m_pfactoryFolder->merge_to_global_factory();
   //
   //       return m_pfactoryFolder;
   //
   //    }
   //
   //
   //    void acme_system_layer::system::system_construct(::platform::application* papplication)
   //    {
   //
   //       m_papplication = papplication;
   //
   //
   //       ///*auto estatus = */ ::main::system_construct(papplication);
   //
   //       /*  if (!estatus)
   //        {
   //
   //        return estatus;
   //
   //        }
   //
   //        return estatus;*/
   //
   //       if (m_papplication)
   //       {
   //
   //          m_papplication->m_psystem = this;
   //
   //       }
   //
   //
   //    }
   //
   //
   //    //void acme_system_layer::system::system_construct(int argc, wchar_t** argv, wchar_t** envp)
   //    //{
   //
   //    //   acme_main_data::system_construct(argc, argv, envp);
   //
   //    //}
   //
   //
   //
   // //   void acme_system_layer::system::os_construct()
   // //   {
   // //
   // //
   // //   }
   //
   //
   // #ifdef _DEBUG
   //
   //
   //    long long system::increment_reference_count()
   //    {
   //
   //       return ::object::increment_reference_count();
   //
   //    }
   //
   //
   //    long long system::decrement_reference_count()
   //    {
   //
   //       return ::object::decrement_reference_count();
   //
   //    }
   //
   //
   // #endif
   //
   //
   //    void acme_system_layer::system::system_id_update(long long iId, long long iPayload)
   //    {
   //
   //       call((::enum_id)iId, iPayload);
   //
   //    }
   //
   //    void acme_system_layer::system::handle(::topic * ptopic, ::handler_context * phandlercontext)
   //    {
   //
   //       if (ptopic->id() == id_get_operating_system_dark_mode_reply)
   //       {
   //
   //          if (ptopic->payload("wparam").is_true())
   //          {
   //
   //             background_color(::color::black);
   //
   //          }
   //          else
   //          {
   //
   //             background_color(::color::white);
   //
   //          }
   //
   //          if (m_pnano)
   //          {
   //
   //             m_pnano->handle(ptopic, phandlercontext);
   //
   //          }
   //
   //       }
   //       else if (ptopic->id() == id_operating_system_user_theme_change)
   //       {
   //
   //          // auto pnode = node();
   //          //
   //          // string strTheme = pnode->os_get_user_theme();
   //          //
   //          // if (strTheme != m_strOsUserTheme)
   //          // {
   //          //
   //          //    m_strOsUserTheme = strTheme;
   //          //
   //          // }
   //
   //       }
   //       else if (ptopic->id() == id_open_hyperlink)
   //       {
   //
   //          auto plink = ptopic->_extended_topic()->m_payload.cast < ::hyperlink >();
   //
   //          if (plink)
   //          {
   //
   //             //if (plink->m_bProfile)
   //             {
   //
   //                open_profile_link(plink->m_strLink, plink->m_strBrowserAccount, plink->m_strTarget);
   //
   //             }
   //             //else
   //             {
   //
   //                // open_link(plink->m_strLink, plink->m_strProfile, plink->m_strTarget);
   //
   //             }
   //
   //          }
   //
   //       }
   //       else if (ptopic->id() == id_app_activated)
   //       {
   //
   //          node()->on_app_activated();
   //
   //          if (::is_set(application()))
   //          {
   //
   //             application()->handle(ptopic, phandlercontext);
   //
   //          }
   //
   //       }
   //       else if (ptopic->id() == id_did_pick_document_at_url)
   //       {
   //
   //          if (::is_set(application()))
   //          {
   //
   //             auto pszUrl = (const_char_pointer )ptopic->payload("wparam").as_iptr();
   //
   //             application()->did_pick_document_at_url(scopedstrUrl);
   //
   //          }
   //
   //       }
   //
   //    }
   //
   //
   //    //   void acme_system_layer::system::add_handler(::matter * pmatter, bool bPriority)
   //    //   {
   //    //
   //    //
   //    //   }
   //
   //
   //    void acme_system_layer::system::add_signal_handler(const ::signal_handler& signalhandler, const ::atom& atomSignal)
   //    {
   //
   //
   //    }
   //
   //
   //    void acme_system_layer::system::erase_signal_handler(::signal_handler::base* pbase)
   //    {
   //
   //    }
   //
   //
   //    //   void acme_system_layer::system::erase_signal_handlers(::particle * pparticle)
   //    //   {
   //    //
   //    //   }
   //
   //
   //    void acme_system_layer::system::node_will_finish_launching()
   //    {
   //
   //       //   auto pnode = node();
   //       //
   //       //   pnode->_will_finish_launching();
   //
   //       //   auto pnode = session();
   //       //
   //       //   auto puser = user();
   //       //
   //       //   auto pwindowing = system()->windowing();
   //       //
   //       //   pwindowing->_will_finish_launching();
   //
   //       auto pnode = node();
   //
   //       pnode->_will_finish_launching();
   //
   //       //return ::success;
   //
   //    }
   //
   //
   //    void acme_system_layer::system::on_open_untitled_file()
   //    {
   //
   //       if (!m_bPostedInitialRequest)
   //       {
   //
   //          defer_post_initial_request();
   //
   //       }
   //
   //       //      throw ::interface_only();
   //
   //       //throw ::interface_only();
   //
   //    }
   //
   //
   //    void acme_system_layer::system::on_open_file(const ::scoped_string & scopedstrFile)
   //    {
   //
   //       throw ::interface_only();
   //
   //    }
   //
   //
   //    ::pointer < ::compress > system::_new_compress(const ::scoped_string& scopedstrImplementation)
   //    {
   //
   //       auto pcompress = create < ::compress >("compress", scopedstrImplementation);
   //
   //       if (!pcompress)
   //       {
   //
   //          throw ::exception(error_resource);
   //
   //       }
   //
   //       return pcompress;
   //
   //    }
   //
   //
   //    ::pointer < ::uncompress > system::_new_uncompress(const ::scoped_string& scopedstrImplementation)
   //    {
   //
   //       auto puncompress = create < ::uncompress >("compress", scopedstrImplementation);
   //
   //       if (!puncompress)
   //       {
   //
   //          throw ::exception(error_resource);
   //
   //       }
   //
   //       /// *ppuncompress = puncompress;
   //
   //       //puncompress->increment_reference_count();
   //
   //       return puncompress;
   //
   //    }
   //
   //
   //    ::pointer < ::compress > system::new_zlib_compress()
   //    {
   //
   //       if (!m_pfactoryitemCompressZlib)
   //       {
   //
   //          auto& pfactory = this->factory("compress", "zlib");
   //
   //          m_pfactoryitemCompressZlib = pfactory->get_factory_item< ::compress>();
   //
   //       }
   //
   // #if REFERENCING_DEBUGGING
   //       ::allocator::add_referer({refdbg_this(), __FUNCTION_FILE_LINE__});
   // #endif
   //
   //       auto pcompress = m_pfactoryitemCompressZlib->__call__create_particle();
   //
   //       pcompress->initialize(this);
   //
   //       return pcompress;
   //
   //    }
   //
   //
   //
   //    ::pointer < ::uncompress > system::new_zlib_uncompress()
   //    {
   //
   //       if (!m_pfactoryitemUncompressZlib)
   //       {
   //
   //          auto& pfactory = this->factory("compress", "zlib");
   //
   //          m_pfactoryitemUncompressZlib = pfactory->get_factory_item< ::uncompress>();
   //
   //       }
   //
   //       auto puncompress = m_pfactoryitemUncompressZlib->__call__create_particle();
   //
   //       puncompress->initialize(this);
   //
   //       return puncompress;
   //
   //    }
   //
   //
   //    void acme_system_layer::system::_compress(const ::payload& payloadTarget, const ::payload& payloadSource, const ::scoped_string& scopedstrImplementation)
   //    {
   //
   //       ::pointer<::compress>pcompress = _new_compress(scopedstrImplementation);
   //
   //       ///*auto estatus =*/ new_compress(&pcompress.m_p, scopedstrImplementation);
   //
   //       /*  if (!estatus)
   //        {
   //
   //        return estatus;
   //
   //        }*/
   //
   //       auto pfileTarget = file_system()->get_file(payloadTarget, ::file::e_open_write | ::file::e_open_defer_create_directory | ::file::e_open_binary);
   //
   //       auto pfileSource = file_system()->get_file(payloadSource, ::file::e_open_read | ::file::e_open_binary);
   //
   //       /*estatus = */ pcompress->transfer(pfileTarget, pfileSource);
   //
   //       //if (!estatus)
   //       //{
   //
   //       //   return estatus;
   //
   //       //}
   //
   //       //return estatus;
   //
   //    }
   //
   //
   //    void acme_system_layer::system::_uncompress(const ::payload& payloadTarget, const ::payload& payloadSource, const ::scoped_string& scopedstrImplementation, transfer_progress_function transferprogressfunction)
   //    {
   //
   //       ::pointer<::uncompress>puncompress = _new_uncompress(scopedstrImplementation);
   //
   //       ///*auto estatus = */ new_uncompress(&puncompress.m_p, scopedstrImplementation);
   //
   //       //if (!estatus)
   //       //{
   //
   //       //   return estatus;
   //
   //       //}
   //
   //       auto pfileTarget = file_system()->get_file(payloadTarget, ::file::e_open_write | ::file::e_open_defer_create_directory | ::file::e_open_binary);
   //
   //       auto pfileSource = file_system()->get_file(payloadSource, ::file::e_open_read | ::file::e_open_binary);
   //
   //       /*estatus = */ puncompress->transfer(pfileTarget, pfileSource, transferprogressfunction);
   //
   //       //if (!estatus)
   //       //{
   //
   //       //   return estatus;
   //
   //       //}
   //
   //       //return estatus;
   //
   //    }
   //
   //
   //    void acme_system_layer::system::zlib_compress(const ::payload& payloadTarget, const ::payload& payloadSource)
   //    {
   //
   //       ::pointer<::compress>pcompress = new_zlib_compress();
   //
   //       ///*auto estatus =*/ new_compress(&pcompress.m_p, scopedstrImplementation);
   //
   //       /*  if (!estatus)
   //        {
   //
   //        return estatus;
   //
   //        }*/
   //
   //       auto pfileTarget = file_system()->get_file(payloadTarget, ::file::e_open_write | ::file::e_open_defer_create_directory | ::file::e_open_binary);
   //
   //       auto pfileSource = file_system()->get_file(payloadSource, ::file::e_open_read | ::file::e_open_binary);
   //
   //       /*estatus = */ pcompress->transfer(pfileTarget, pfileSource);
   //
   //       //if (!estatus)
   //       //{
   //
   //       //   return estatus;
   //
   //       //}
   //
   //       //return estatus;
   //
   //    }
   //
   //
   //    void acme_system_layer::system::zlib_uncompress(const ::payload& payloadTarget, const ::payload& payloadSource, transfer_progress_function transferprogressfunction)
   //    {
   //
   //       ::pointer<::uncompress>puncompress = new_zlib_uncompress();
   //
   //       ///*auto estatus = */ new_uncompress(&puncompress.m_p, scopedstrImplementation);
   //
   //       //if (!estatus)
   //       //{
   //
   //       //   return estatus;
   //
   //       //}
   //
   //       auto pfileTarget = file_system()->get_file(payloadTarget, ::file::e_open_write | ::file::e_open_defer_create_directory | ::file::e_open_binary);
   //
   //       auto pfileSource = file_system()->get_file(payloadSource, ::file::e_open_read | ::file::e_open_binary);
   //
   //       /*estatus = */ puncompress->transfer(pfileTarget, pfileSource, transferprogressfunction);
   //
   //       //if (!estatus)
   //       //{
   //
   //       //   return estatus;
   //
   //       //}
   //
   //       //return estatus;
   //
   //    }
   //
   //
   //    bool system::fast_is_decompressable_folder(const ::file::path& path)
   //    {
   //
   //       auto bZip = path.case_insensitive_ends(".zip");
   //
   //       if (bZip)
   //       {
   //
   //          return true;
   //
   //       }
   //
   //       return false;
   //
   //    }
   //
   //
   //
   //
   //    //::pointer < ::subparticle > system::message_box(const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle, const ::user::e_message_box & emessagebox, const ::scoped_string & scopedstrDetails)
   //    //{
   //    //
   //    //   auto psequencer = nano()->message_box(strMessage, strTitle, emessagebox, strDetails);
   //    //
   //    //   pmessagebox->sync();
   //    //
   //    //   return psequencer;
   //    //
   //    //}
   //
   //    ::pointer<::platform::application>system::new_app(const ::scoped_string& scopedstrAppId)
   //    {
   //
   //       ::pointer<::platform::application>papp;
   //
   //       string strAppId = scopedstrAppId;
   //
   //       auto psetup = system_setup::get_first(::system_setup::flag_application, strAppId);
   //
   //       if (psetup)
   //       {
   //
   //          auto pelementApp = psetup->create_application_as_particle();
   //
   //          papp = pelementApp;
   //
   //          //papp.reset(papp.m_p REFERENCING_DEBUGGING_COMMA_THIS_FUNCTION_FILE_LINE);
   //
   //          if (papp)
   //          {
   //
   //             strAppId = papp->m_strAppId;
   //
   //          }
   //
   //       }
   //
   //       //#ifndef CUBE
   //
   //       if (!papp)
   //       {
   //
   //          if (strAppId.is_empty() || this->is_console())
   //          {
   //
   //             papp = øcreate < ::platform::application >();
   //
   //             papp->increment_reference_count();
   //
   //          }
   //          else
   //          {
   //
   //             string strLibrary = strAppId;
   //
   //             strLibrary.replace_with("_", "/");
   //
   //             strLibrary.replace_with("_", "-");
   //
   //             if (application()->m_bVerbose)
   //             {
   //
   //                informationf("\n\n::apex::session::get_new_application assembled library path " + strLibrary + "\n\n");
   //
   //             }
   //
   //             //auto psystem = system()->m_papexsystem;
   //
   //             auto& plibrary = this->library(strLibrary);
   //
   //             if (!plibrary)
   //             {
   //
   // #ifndef UNIVERSAL_WINDOWS
   //
   //                //            output_error_message("papp \"" + strAppId + "\" cannot be created.\n\nThe library \"" + strLibrary + "\" could not be loaded. " + plibrary->m_strMessage, "ca2", ::user::e_message_box_icon_error);
   //
   //                //output_error_message("papp \"" + strAppId + "\" cannot be created.\n\nThe library \"" + strLibrary + "\" could not be loaded. ", "ca2", ::user::e_message_box_icon_error);
   //
   //                informationf("papp \"" + strAppId + "\" cannot be created.\n\nThe library \"" + strLibrary + "\" could not be loaded. " + "ca2");
   //
   // #endif
   //
   //                return nullptr;
   //
   //             }
   //
   //             if (application()->m_bVerbose)
   //             {
   //
   //                informationf("\n\n::apex::session::get_new_application Found library : " + strLibrary + "\n\n");
   //
   //             }
   //
   //             // error anticipation is not perfect prediction and may affect results
   //             // so anticipation may be counter-self-healing
   //             // specially if what it would avoid on error is exactly we want if successful
   //             // who doesn't try it, won't taste it neither possibly enjoy it
   //             //          if (!plibrary->is_opened())
   //             //          {
   //             //
   //             //             informationf("\n\n::apex::session::get_new_application Failed to load library : " + strLibrary + "\n\n");
   //             //
   //             //             return nullptr;
   //             //
   //             //          }
   //
   //             if (application()->m_bVerbose)
   //             {
   //
   //                informationf("\n\n::apex::session::get_new_application Opened library : " + strLibrary + "\n\n");
   //
   //             }
   //
   //             ::factory::factory_pointer pfactory;
   //
   //             plibrary->create_factory(pfactory);
   //
   //             if (pfactory)
   //             {
   //
   //                papp = øcreate < ::platform::application >(pfactory);
   //
   //                if (!papp)
   //                {
   //
   //                   informationf("\n\n::apex::session::get_new_application\n...but this ___new found library:\n\n   -->  " + strLibrary + "  <--\n\ncannot instantiate application with following AppId:\n\n   -->  " + strAppId + "  <--\n\nIs it missing application factory_item?\n\n\n");
   //
   //                }
   //
   //                ::e_status estatus;
   //
   //                //         if(papp)
   //                //         {
   //                //
   //                //            estatus = papp->initialize(pparticle);
   //                //
   //                //         }
   //
   //                informationf("\n\n\n|(4)----");
   //                informationf("| app : " + strAppId + "(papp=0x" + ::hex::upper_case_from((uptr)papp.m_p) + ")\n");
   //                informationf("|\n");
   //                informationf("|\n");
   //                informationf("|----");
   //
   //             }
   //
   //          }
   //
   //       }
   //
   //       //#endif
   //
   //       if (!papp)
   //       {
   //
   //          return nullptr;
   //
   //       }
   //
   //       //#ifdef WINDOWS_DESKTOP
   //       //
   //       //      WCHAR wsz[1024];
   //       //
   //       //      DWORD dwSize = sizeof(wsz) / sizeof(WCHAR);
   //       //
   //       //      GetUserNameW(wsz, &dwSize);
   //       //
   //       //      string strUserName = wsz;
   //       //
   //       //#endif // WINDOWS_DESKTOP
   //
   //       //   if (is_verbose())
   //       //   {
   //       //
   //       //      informationf("\n\n\n|(3)----");
   //       //      informationf("| app : " + strAppId + "\n");
   //       //      informationf("|\n");
   //       //      informationf("|\n");
   //       //      informationf("|----");
   //       //
   //       //   }
   //       //
   //       //   if (is_verbose())
   //       //   {
   //       //
   //       //      informationf("\n\n\n|(2)----");
   //       //      informationf("| app : " + strAppId + "\n");
   //       //      informationf("|\n");
   //       //      informationf("|\n");
   //       //      informationf("|----");
   //       //
   //       //   }
   //       //
   //       //
   //       //   if (is_verbose())
   //       //   {
   //       //
   //       //      informationf("\n\n\n|(1)----");
   //       //      informationf("| app : " + strAppId + "\n");
   //       //      informationf("|\n");
   //       //      informationf("|\n");
   //       //      informationf("|----");
   //       //
   //       //   }
   //
   //       papp->m_strAppId = strAppId;
   //
   //       //if (m_strAppId.is_empty())
   //       //{
   //
   //       //   m_strAppId = strAppId;
   //
   //       //}
   //
   //       return papp;
   //
   //    }
   //
   //
   //    bool system::_handle_call(::payload& payload, const ::scoped_string & scopedstrObject, const ::scoped_string & scopedstrMember, ::property_set& propertyset)
   //    {
   //
   //       try
   //       {
   //
   //          bool bOk = false;
   //
   //          if (m_papplication)
   //          {
   //
   //             if (m_papplication->_handle_call(payload, strObject, strMember, propertyset))
   //             {
   //
   //                return true;
   //
   //             }
   //
   //          }
   //
   //       }
   //       catch (...)
   //       {
   //
   //       }
   //
   //       return false;
   //
   //    }
   //
   //
   //    string system::get_latest_deployment_number(const ::scoped_string & scopedstrBranch)
   //    {
   //
   //       return "(lastest deployed build)";
   //
   //    }
   //
   //
   //    //   void acme_system_layer::system::windowing_send(const ::procedure & procedure)
   //    //   {
   //    //
   //    //      auto pmanualresethappening = øallocate manual_reset_happening();
   //    //
   //    //      windowing_post([pmanualresethappening, procedure]()
   //    //                     {
   //    //
   //    //                        procedure();
   //    //
   //    //                        pmanualresethappening->set_happening();
   //    //
   //    //      }
   //    //
   //    //      );
   //    //
   //    //      pmanualresethappening->wait(procedure.m_timeTimeout);
   //    //
   //    //   }
   //
   //
   //    void acme_system_layer::system::destroy()
   //    {
   //
   // #if !defined(WINDOWS)
   //
   //       if (::is_set(m_pexceptiontranslator))
   //       {
   //
   //          m_pexceptiontranslator->detach();
   //
   //          m_pexceptiontranslator->destroy();
   //
   //          m_pexceptiontranslator.release();
   //
   //       }
   //
   // #endif
   //
   //       //::platform::context::destroy();
   //
   //       ::task::destroy();
   //
   //       auto ptask = ::get_task();
   //
   //       if (ptask == this)
   //       {
   //
   //          ::task_release();
   //
   //       }
   //
   //       // auto pplatform = ::platform::get();
   //       //
   //       // if(pplatform)
   //       // {
   //       //
   //       //    pplatform->m_psystem.release();
   //       //
   //       // }
   //
   //    }
   //
   //
   //    ::string system::implementation_name(const ::scoped_string& scopedstrComponent, const ::scoped_string& scopedstrImplementation)
   //    {
   //
   //       return scopedstrImplementation;
   //
   //    }
   //
   //
   //    ::string system::library_name(const ::scoped_string& scopedstrComponent, const ::scoped_string& scopedstrImplementation)
   //    {
   //
   //       return scopedstrComponent + "_" + scopedstrImplementation;
   //
   //    }
   //
   //
   //    ::file::path system::local_get_matter_path()
   //    {
   //
   //       return directory_system()->ca2roaming() / "appmatter";
   //
   //    }
   //
   //
   //    ::file::path system::local_get_matter_path(const ::scoped_string & scopedstrMatter)
   //    {
   //
   // #ifdef UNIVERSAL_WINDOWS
   //
   //       return "";
   //
   // #else
   //
   //       return local_get_matter_path() / strMatter;
   //
   // #endif
   //
   //    }
   //
   //
   //    ::file::path system::local_get_matter_cache_path()
   //    {
   //
   //       return directory_system()->ca2roaming() / "cache/appmatter";
   //
   //    }
   //
   //
   //    ::file::path system::local_get_matter_cache_path(const ::scoped_string & scopedstrMatter)
   //    {
   //
   //       return local_get_matter_cache_path() / strMatter;
   //
   //    }
   //
   //
   //    string system::get_system_configuration()
   //    {
   //
   // #ifndef CA2_PLATFORM_VERSION
   //
   // #error "CA2_PLATFORM_VERSION not defined"
   //
   // #endif
   //
   // #ifndef CA2_BASIS
   //
   // #error "CA2_BASIS not defined"
   //
   // #endif
   //
   // #ifndef CA2_STAGE
   //
   // #error "CA2_STAGE not defined"
   //
   // #endif
   //
   // #if CA2_PLATFORM_VERSION == CA2_BASIS
   //
   //       return "basis";
   //
   //       //#pragma message "CA2_PLATFORM_VERSION is CA2_BASIS"
   //
   // #elif CA2_PLATFORM_VERSION == CA2_STAGE
   //
   //       return "stage";
   //
   //       //#pragma message "CA2_PLATFORM_VERSION is CA2_STAGE"
   //
   // #else
   //
   // #error "CA2_PLATFORM_VERSION has unsupported definition"
   //
   // #endif
   //
   //    }
   //
   //
   //
   //    string system::get_system_platform()
   //    {
   //
   // #ifdef X86
   //
   //       return "x86";
   //
   // #else
   //
   //       return "x64";
   //
   // #endif
   //
   //    }
   //
   //
   //    void acme_system_layer::system::install_progress_add_up(int iAddUp)
   //    {
   //
   //
   //    }
   //
   //
   //    class ::manager_room * system::manager_room()
   //    {
   //
   //       return nullptr;
   //
   //    }
   //
   //
   //
   //    ::string system::get_application_server_name()
   //    {
   //
   //       string strApplicationServerName = application()->m_strAppId;
   //
   //       strApplicationServerName.replace_with(".", "/");
   //
   //       strApplicationServerName.replace_with("-", "_");
   //
   //       return strApplicationServerName;
   //
   //    }
   //
   //
   //    ::draw2d::draw2d* system::draw2d() const
   //    {
   //
   //       return nullptr;
   //
   //    }
   //
   //
   //    ::write_text::write_text* system::write_text() const
   //    {
   //
   //       return nullptr;
   //
   //    }
   //
   //
   //    ::color::color system::background_color() const
   //    {
   //
   //       return m_colorBackground;
   //
   //    }
   //
   //
   //    double system::luminance() const
   //    {
   //
   //       return m_dLuminance;
   //
   //    }
   //
   //
   //    void acme_system_layer::system::background_color(const ::color::color & color)
   //    {
   //
   //       if (m_colorBackground == color)
   //       {
   //
   //          return;
   //
   //       }
   //
   //       m_colorBackground = color;
   //
   //       m_dLuminance = m_colorBackground.get_luminance();
   //
   //       set_dark_mode(m_dLuminance < 0.5);
   //
   //    }
   //
   //
   //    ::color::color system::get_simple_ui_color(::enum_element eelement, ::user::enum_state estate)
   //    {
   //
   //       ::color::color color;
   //
   //       if (eelement == ::e_element_background)
   //       {
   //
   //          if (dark_mode())
   //          {
   //
   //             color = argb(255, 0x50, 0x50, 0x58);
   //
   //          }
   //          else
   //          {
   //
   //             color = argb(255, 0xcd, 0xcd, 0xc8);
   //
   //          }
   //
   //       }
   //       else
   //       {
   //
   //          if (dark_mode())
   //          {
   //
   //             color = argb(255, 255, 255, 255);
   //
   //          }
   //          else
   //          {
   //
   //             color = argb(255, 49, 50, 42);
   //
   //          }
   //
   //       }
   //
   //       return color;
   //
   //    }
   //
   //
   //    ::color::color system::get_default_color(::color::color color)
   //    {
   //
   //       return argb(255, 0, 0, 0);
   //
   //    }
   //
   //
   //    void acme_system_layer::system::set_dark_mode(bool bDark)
   //    {
   //
   //       m_bDarkMode = bDark;
   //
   //       if (m_bDarkMode)
   //       {
   //
   //          informationf("background_color :: Dark\n");
   //
   //       }
   //       else
   //       {
   //
   //          informationf("background_color :: Lite\n");
   //
   //       }
   //
   //       on_application_dark_mode_change();
   //
   //    }
   //
   //
   //    bool system::dark_mode() const
   //    {
   //
   //       return m_bDarkMode;
   //
   //    }
   //
   //
   //    void acme_system_layer::system::on_application_dark_mode_change()
   //    {
   //
   //       auto ptopic = øallocate ::topic(id_application_dark_mode_change);
   //
   //       application()->handle(ptopic, nullptr);
   //
   //    }
   //
   //
   //    bool system::defer_component_factory(const ::scoped_string & scopedstrComponent)
   //    {
   //
   //       auto pnode = node();
   //
   //       if (::is_set(pnode))
   //       {
   //
   //          if (pnode->defer_component_factory(scopedstrComponent))
   //          {
   //
   //             return true;
   //
   //          }
   //
   //          ::string strComponentDefaultImplementation = pnode->default_component_implementation(scopedstrComponent);
   //
   //          if (strComponentDefaultImplementation.has_character())
   //          {
   //
   //             auto pfactory = this->factory(scopedstrComponent, strComponentDefaultImplementation);
   //
   //             if (pfactory)
   //             {
   //
   //                pfactory->merge_to_global_factory();
   //
   //                return true;
   //
   //             }
   //
   //          }
   //
   //
   //       }
   //
   //       if(_defer_component_factory(scopedstrComponent))
   //       {
   //
   //          return true;
   //
   //       }
   //
   //       return false;
   //
   //
   //    }
   //
   //
   //    bool system::_defer_component_factory(const ::scoped_string & scopedstrComponent)
   //    {
   //
   //       //if (scopedstrComponent == "nano_dynamic_library")
   //       //{
   //
   //       //   auto pfactory = this->factory();
   //
   //       //   nano_dynamic_library_factory(pfactory);
   //
   //       //   return true;
   //
   //       //}
   //
   // //      else if (scopedstrComponent == "nano_user")
   // //      {
   // //
   // //
   // //#if defined(WINDOWS_DESKTOP)
   // //
   // //
   // //         auto pfactory = this->factory();
   // //
   // //         nano_user_win32_factory(pfactory);
   // //
   // //         return;
   // //
   // //#elif defined(UNIVERSAL_WINDOWS)
   // //
   // //
   // //         auto pfactory = this->factory();
   // //
   // //
   // //         nano_user_universal_windows_factory(pfactory);
   // //
   // //
   // //         return;
   // //
   // //#elif defined(MACOS)
   // //
   // //         auto pfactory = this->factory();
   // //
   // //         nano_user_macos_factory(pfactory);
   // //
   // //         return;
   // //
   // //#elif defined(APPLE_IOS)
   // //
   // //         return;
   // //
   // //#endif
   // //
   // //      }
   // //      else if (scopedstrComponent == "nano_user")
   // //      {
   // //
   // //
   // //#if defined(WINDOWS_DESKTOP)
   // //
   // //
   // //         auto pfactory = this->factory();
   // //
   // //         nano_user_win32_factory(pfactory);
   // //
   // //         return;
   // //
   // //#elif defined(UNIVERSAL_WINDOWS)
   // //
   // //
   // //         auto pfactory = this->factory();
   // //
   // //
   // //         nano_user_universal_windows_factory(pfactory);
   // //
   // //
   // //         return;
   // //
   // //#elif defined(MACOS)
   // //
   // //         auto pfactory = this->factory();
   // //
   // //         nano_user_macos_factory(pfactory);
   // //
   // //         return;
   // //
   // //#elif defined(APPLE_IOS)
   // //
   // //         return;
   // //
   // //#endif
   // //
   // //      }
   //
   //       return false;
   //
   //    }
   //
   //
   //    ::micro::user * system::micro_user()
   //    {
   //
   //       if (!m_pmicrouser)
   //       {
   //
   //          øconstruct_new(m_pmicrouser);
   //
   //       }
   //
   //       return m_pmicrouser;
   //
   //    }
   //
   //
   //    ::acme::windowing::windowing * system::acme_windowing()
   //    {
   //
   //       if (!m_pacmewindowing)
   //       {
   //
   //          do_graphics_and_windowing_system_factory();
   //
   //          øconstruct(m_pacmewindowing);
   //
   //       }
   //
   //       return m_pacmewindowing;
   //
   //    }
   //
   //
   //    ::windowing::windowing * system::windowing()
   //    {
   //
   //       return acme_windowing()->windowing_windowing();
   //
   //    }
   //
   //
   //    void acme_system_layer::system::do_graphics_and_windowing_system_factory()
   //    {
   //
   //       if(!m_bGraphicsAndWindowingSystemInitialized)
   //       {
   //
   //          m_bGraphicsAndWindowingSystemInitialized = true;
   //
   //          nano()->graphics();
   //
   //          ::string strToolkit = ::windowing::get_user_toolkit_id();
   //
   //          m_pfactoryAcmeWindowing = this->factory("acme_windowing", strToolkit);
   //
   //          m_pfactoryAcmeWindowing->merge_to_global_factory();
   //
   //       }
   //
   //    }
   //
   //
   //    //::pointer < ::message_box > & system::realize(::pointer < ::message_box > & pmessagebox)
   //    //{
   //
   //    //   return micro_user()->realize(pmessagebox);
   //
   //    //}
   //
   //
   // //   ::pointer < ::message_box > system::message_box(const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle,
   // //                                                       const ::user::e_message_box & emessagebox,
   // //                                                       const ::scoped_string & scopedstrDetails, ::nano::graphics::icon * picon)
   // //   {
   // //
   // //
   // //      return micro_user()->message_box(
   // //strMessage,
   // //strTitle,
   // //emessagebox,
   // //strDetails,
   // //picon);
   // //   }
   //
   //
   //    //::pointer < ::message_box > system::exception_message_box(
   //    //    const ::exception & exception, const ::scoped_string & scopedstrMessage,
   //    //   const ::scoped_string & scopedstrTitle,
   //    //    const ::user::e_message_box & emessagebox, const ::scoped_string & scopedstrDetails, ::nano::graphics::icon * picon)
   //    //{
   //    //   return micro_user()->exception_message_box(
   //    //exception,
   //    //strMessage,
   //    //strTitle,
   //    //emessagebox,
   //    //strDetails,
   //    //picon);
   //
   //    //}
   //
   //
   //    //::pointer < ::message_box > system::message_console(const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle,
   //    //                                                           const ::user::e_message_box & emessagebox,
   //    //                                                           const ::scoped_string & scopedstrDetails, ::nano::graphics::icon * picon)
   //    //{
   //    //
   //    //   return micro_user()->message_console(
   //    //      strMessage,
   //    //      strTitle,
   //    //      emessagebox,
   //    //      strDetails,
   //    //      picon);
   //
   //    //}
   //
   //
   //    //::pointer < ::message_box > system::exception_message_console(
   //    //    const ::exception & exception, const ::scoped_string & scopedstrMessage,
   //    //   const ::scoped_string & scopedstrTitle,
   //    //    const ::user::e_message_box & emessagebox, const ::scoped_string & scopedstrDetails, ::nano::graphics::icon * picon)
   //    //{
   //
   //    //   return micro_user()->exception_message_console(
   //    //      exception,
   //    //      strMessage,
   //    //      strTitle,
   //    //      emessagebox,
   //    //      strDetails,
   //    //      picon);
   //
   //    //}
   //
   //
   //    //::windowing::windowing_base * system::windowing_base()
   //    //{
   //
   //    //   if(!m_pwindowingbase)
   //    //   {
   //
   //    //      do_graphics_and_windowing_system_factory();
   //
   //    //      øconstruct(m_pwindowingbase);
   //
   //    //   }
   //
   //    //   return m_pwindowingbase;
   //
   //    //}
   //


   ::particle* acme_system_layer::matter_mutex()
   {
      return nullptr;
   }


   ::particle* acme_system_layer::http_download_mutex()
   {
      return nullptr;
   }


   ::string_array_base * acme_system_layer::http_download_array()
   {
      
      return nullptr;
      
   }


   ::string_array_base * acme_system_layer::http_exists_array()
   {
      
      return nullptr;
      
   }


   class ::time * acme_system_layer::file_listing_cache_time()
   {
      
      return nullptr;
      
   }


   ::task_message_queue * acme_system_layer::task_message_queue()
   {

      return nullptr;

   }


   ::thread_storage * acme_system_layer::thread_storage(const ::task_index & taskindex)
   {

      return nullptr;

   }


   ::thread_storage * acme_system_layer::_thread_storage_unlocked(const ::task_index & taskindex)
   {

      return nullptr;

   }



   //void acme_system_layer::on_set_platform() override{}


   //void acme_system_layer::on_initialize_particle() override{}


   void acme_system_layer::process_machine_event_data(machine_event_data* pdata)
   {
   }


   void acme_system_layer::do_operating_ambient_factory()
   {


   }


   void acme_system_layer::do_graphics_and_windowing_factory()
   {


   }


   void acme_system_layer::initialize_layer()
   {
   }


   enum_trace_level acme_system_layer::get_trace_level()
   {
      return e_trace_level_none;
   }


   //void acme_system_layer::os_construct(){}

   void acme_system_layer::initialize_matter()
   {
   }


   //
   // #ifdef _DEBUG
   //
   //
   //       long long increment_reference_count() override{}
   //
   //
   //       long long decrement_reference_count() override{}
   //
   //
   // #endif

   ::mathematics::mathematics* acme_system_layer::mathematics()
   {
      return nullptr;
   }


   ::image::imaging* acme_system_layer::imaging()
   {
      return nullptr;
   }


   // #if defined(WITH_X11) || defined(WITH_XCB)
   //       ::particle * acme_system_layer::x11_synchronization(){}
   // #endif

   ::networking::networking* acme_system_layer::networking()
   {
      return nullptr;
   }


   ::platform::node * acme_system_layer::node()
   {

      return nullptr;
      
   }


   class ::base64* acme_system_layer::base64()
   {
      
      return nullptr;
      
   }


   ::xml::xml* acme_system_layer::xml()
   {
      
      return nullptr;
      
   }


   ::file_system* acme_system_layer::file_system()
   {
      return nullptr;
   }


   ::directory_system* acme_system_layer::directory_system()
   {
      return nullptr;
   }


   ::path_system*acme_system_layer:: path_system()
   {
      return nullptr;
   }


   ::platform::system_factory* acme_system_layer::system_factory()
   {
return nullptr;

   }


   ::xml::xml* acme_system_layer::_xml()
   {
      return nullptr;
   }


   geometry::geometry* acme_system_layer::geometry()
   {
      return nullptr;
   }


   ::datetime::datetime* acme_system_layer::datetime()
   {
      return nullptr;
   }


   ::text::table*acme_system_layer::texttable()
   {
      return nullptr;
   }


   ::internet::internet* acme_system_layer::internet()
   {
      return nullptr;
   }


   ::url::url_context* acme_system_layer::url()
   {
      return nullptr;
   }


   ::particle*acme_system_layer::ui_destroyed_synchronization()
   {
      return nullptr;
   }


   ::nano::nano* acme_system_layer::nano()
   {
      return nullptr;
   }


   ::micro::user*acme_system_layer:: micro_user()
   {
      return nullptr;
   }


   ::acme::windowing::windowing* acme_system_layer::acme_windowing()
   {
      return nullptr;
   }


   ::windowing::windowing*acme_system_layer:: windowing()
   {
      
      return nullptr;

   }


   ::component * acme_system_layer::component(const ::scoped_string & scopedstrComponent)
   {

      return nullptr;

   }


    ::string acme_system_layer::component_path(const ::scoped_string & scopedstrComponent)
   {

      return {};

   }

   void acme_system_layer::defer_innate_ui()
   {
   }


   ::innate_ui::innate_ui* acme_system_layer::innate_ui()
   {
      return nullptr;
   }


   //nano::nano * nano()

   class ::manager_room* acme_system_layer::manager_room()
   {
      return nullptr;
   }


   ::crypto::crypto* acme_system_layer::crypto()
   {
      return nullptr;
   }


   //::acme::acme * acme() const {}

   ::prototype::prototype* acme_system_layer::prototype()
   {
      return nullptr;
   }


   ::draw2d::draw2d* acme_system_layer::draw2d()
   {
      return nullptr;
   }


   ::write_text::write_text*acme_system_layer:: write_text()
   {
      return nullptr;
   }


   //::windowing::windowing_base * windowing_base(){}

   string acme_system_layer::get_system_platform()
   {
      return {};
   }


   string acme_system_layer:: get_system_configuration()
   {
      return {};
   }


   void acme_system_layer::defer_audio()
   {
   }


   bool acme_system_layer::has_audio()
   {
      return false;
   }


   void acme_system_layer::init1()
   {
   }


   void acme_system_layer::init2()
   {
   }


   //void acme_system_layer::set_current_handles() override{}

   void acme_system_layer::TermSystem()
   {
   }


   void acme_system_layer::erase_from_any_hook(::matter* pmatter)
   {
   }


   void acme_system_layer::create_os_node(::platform::application * papplication)
   {
   }


   string acme_system_layer::os_get_user_theme()
   {return {};
   }


   // template < typename BASE_TYPE >
   // ::pointer<BASE_TYPE> create(const ::scoped_string & scopedstrComponent, const ::scoped_string & scopedstrImplementation)
   // {
   //
   //    auto & pfactory = this->factory(strComponent, strImplementation){}
   //
   //    if (!pfactory)
   //    {
   //
   //       throw ::exception(error_resource){}
   //
   //    }
   //
   //    auto p = pfactory->__call__create< BASE_TYPE >(this){}
   //
   //    if (!p)
   //    {
   //
   //       return p{}
   //
   //    }
   //
   //    return p{}
   //
   // }


   unsigned int acme_system_layer::crc32(unsigned int uCrc, const ::block& block)
   {
      return 0;
   }


   void acme_system_layer::create_session(::collection::index iEdge)
   {
   }


   ::pointer<::platform::session> acme_system_layer::on_create_session(::collection::index iEdge)
   {
      return {};
   }


   ::platform::session* acme_system_layer::session(::collection::index iEdge)
   {
      return nullptr;
   }


   void acme_system_layer::add_session(::collection::index iEdge, ::platform::session* psession)
   {
   }


   void acme_system_layer::on_add_session(::platform::session* psession)
   {
   }


   void acme_system_layer::erase_session(::collection::index iEdge)
   {
   }


   //void acme_system_layer::on_request(::request * prequest) override{}


   void acme_system_layer::process_exit_status(::particle* pparticle, const ::e_status& estatus)
   {
   }


   ::platform::application* acme_system_layer::get_main_app()
   {
      return nullptr;
   }


   ::factory::factory* acme_system_layer::folder_factory()
   {
      return nullptr;
   }


   //using main::system_construct{}


   void acme_system_layer::system_construct(::platform::application* pacmeapplicationStartup)
   {
   }

#ifdef WINDOWS_DESKTOP

   void acme_system_layer::system_construct(hinstance hinstanceThis, hinstance hPrevInstance, char* pCmdLine, int nCmdShow)
   {
   }

#elif defined(UNIVERSAL_WINDOWS)

      void acme_system_layer::system_construct(const ::string_array_base & stra){}

      //#else

         //void acme_system_layer::system_construct(const ::scoped_string & scopedstrCommandLine, const ::e_display& edisplay = ::e_display_none){}

#endif

   void acme_system_layer::speak(const ::scoped_string& scopedstr, const ::scoped_string& scopedstrLang,
                      enum_gender egender)
   {
   }


   ::factory::factory * acme_system_layer::node_factory()
   {
      
      return nullptr;
      
   }


   void acme_system_layer::inline_init()
   {
   }


   void acme_system_layer::inline_term()
   {
   }


   void acme_system_layer::process_init()
   {
   }


   //void acme_system_layer::call_init_system()
   //{
   //}


   void acme_system_layer::init_system()
   {
   }


   void acme_system_layer::term_system()
   {

   }


   void acme_system_layer::on_start_system()
   {
   }

   ::request * acme_system_layer::application_start_file_open_request()
   {

      return nullptr;

   }


   void acme_system_layer::post_application_start()
   {


   }


   void acme_system_layer::defer_post_application_start_file_open_request()
   {


   }


   void acme_system_layer::post_application_started()
   {


   }


   void acme_system_layer::canonical_system_main()
   {
   }


   void acme_system_layer::system_main()
   {
   }


   //void acme_system_layer::on_pre_run_task() override{}


   void acme_system_layer::on_branch_system_from_main_thread_startup(::task_handler * ptaskhandler)
   {


   }


   //void acme_system_layer::main() override{}


    ::pointer<::platform::application> acme_system_layer::new_app(const ::scoped_string& scopedstrAppId)
   {return {};
   }


   void acme_system_layer::end()
   {
   }


   void acme_system_layer::on_end()
   {
   }


   void acme_system_layer::report_system_instance()
   {
   }


   //using ::manager::on_subject{}
   //void acme_system_layer::on_subject(::topic * ptopic) override{}

    class ::time acme_system_layer::get_update_poll_time(const ::atom& atom)
   {

      return {};
   }


    ::acme::library* acme_system_layer::on_get_library(const ::scoped_string & scopedstrLibrary)
   {
      return nullptr;
   }


   //virtual ::pointer<::acme::library> & library(const ::scoped_string & scopedstrComponent, const ::scoped_string & scopedstrImplementation){}


void acme_system_layer::open_internet_link_in_browser(const ::scoped_string & scopedstrUrl, const ::scoped_string & scopedstrBrowser, const ::scoped_string & scopedstrProfile, const ::scoped_string & scopedstrTarget)
   {
   }


void acme_system_layer::open_internet_link(const ::scoped_string & scopedstrUrl, const ::scoped_string & scopedstrProfile, const ::scoped_string & scopedstrTarget)
   {
   }


   // void acme_system_layer::open_url(const ::scoped_string & scopedstrUrl, const ::scoped_string & scopedstrProfile, const ::scoped_string & scopedstrTarget)
   // {
   // }


   //void acme_system_layer::__tracea(enum_trace_level elevel, const ::scoped_string & scopedstrFunction, const ::scoped_string & scopedstrFile, int iLine, const ::scoped_string & scopedstr) const override{}


   //void acme_system_layer::main_user_async(const ::procedure & procedure, ::enum_priority epriority = e_priority_normal){}

   //void acme_system_layer::main_user_sync(const ::procedure & procedure, const class time & time = one_minute(), enum_priority epriority = e_priority_normal){}


   //void acme_system_layer::init_task() override{}
   //void acme_system_layer::term_task() override{}


   string acme_system_layer::__get_text(const ::scoped_string & scopedstr)
   {
      return {};
   }

#ifdef LINUX

   //!!!      void acme_system_layer::deferx_initializex_x11(){}

#endif


   //pointer< ::extended::sequence < ::conversation > > message_box(::user::interaction * puserinteraction, const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle = nullptr, const ::user::e_message_box & emessagebox = ::user::e_message_box_ok) override{}


   //void acme_system_layer::on_initialize_window_object(){}
   //void acme_system_layer::_on_initialize_window_object(){}

   //
   //   template < typename ENUM >
   //   inline void acme_system_layer::set_enum_text(ENUM e, const ::scoped_string & scopedstr)
   //   {
   //
   //      critical_section_lock synchronouslock(&m_csEnumText){}
   //
   //      m_mapEnumToText[typeid(e).name()][(long long)e] = psz{}
   //
   //      m_mapTextToEnum[typeid(e).name()][psz] = (long long)e{}
   //
   //   }

   //
   //   template < typename ENUM >
   //   inline string enum_text(ENUM e)
   //   {
   //
   //      critical_section_lock synchronouslock(&m_csEnumText){}
   //
   //      return m_mapEnumToText[typeid(e).name()][(long long)e]{}
   //
   //   }

   //
   //   template < class ENUM >
   //   inline ENUM text_enum(ENUM& e, const ::scoped_string & scopedstr, ENUM eDefault = (ENUM)0)
   //   {
   //
   //      critical_section_lock lock(&m_csEnumText){}
   //
   //      long long iValue{}
   //
   //      if (m_mapTextToEnum[typeid(e).name()].find(scopedstr, iValue))
   //      {
   //
   //         e = (ENUM)iValue{}
   //
   //      }
   //      else
   //      {
   //
   //         e = eDefault{}
   //
   //      }
   //
   //      return e{}
   //
   //   }
   //
   //
   //   template < class ENUM, ENUM edefault>
   //   inline base_enum < ENUM, edefault >& text_enum(base_enum < ENUM, edefault >& b, const ::scoped_string & scopedstr, ENUM eDefault = edefault)
   //   {
   //
   //      return b = text_enum(b.m_evalue, psz, eDefault){}
   //
   //   }

   //
   //   template < class ENUM, ENUM edefault>
   //   inline string enum_text(const base_enum < ENUM, edefault >& b)
   //   {
   //
   //      return enum_text(b.m_evalue, (long long)(ENUM)b){}
   //
   //   }


   ::task_group* acme_system_layer::task_group(::enum_priority epriority)
   {
      return nullptr;
   }


   ::task_tool* acme_system_layer::task_tool(::enum_task_tool etool)
   {
      return nullptr;
   }


   // static inline ::atom acme_syatom(const ::std::type_info& info)
   // {
   // }
   //

   // static inline ::atom atom(const ::scoped_string& scopedstr)
   // {
   // }
   //

   // static inline ::atom atom(const ::scoped_string & scopedstr)
   // {
   // }


   // static inline ::atom atom(long long i)
   // {
   // }
   //

   //static inline ::atom_space & atom(){}
   ::atom acme_system_layer::atom(const ::payload& payload)
   {
      return {};
   }


   ::atom acme_system_layer::atom(const property& prop)
   {
      return {};
   }


   void acme_system_layer::check_exit()
   {
   }


   ::regular_expression_pointer acme_system_layer::create_regular_expression(const ::scoped_string & scopedstrStyle, const ::scoped_string & scopedstr)
   {
      return {};
   }


   //virtual ::pointer<::regular_expression::context> create_regular_expression_context(const ::scoped_string & scopedstrStyle, int iCount){}
   ::pointer<::regular_expression::context> acme_system_layer::get_regular_expression_context(const ::scoped_string & scopedstrStyle)
   {
      return {};
   }


   ::regular_expression_pointer acme_system_layer::compile_pcre(const ::scoped_string & scopedstr)
   {
      return {};
   }


   ::pointer<::regular_expression::context> acme_system_layer::get_pcre_context()
   {
      return {};
   }


   //virtual int system::pcre_add_tokens(string_array_base& stra, const ::scoped_string & scopedstrTopic, const ::scoped_string & scopedstrRegexp, int nCount)

   void acme_system_layer::get_public_internet_domain_extension_list(string_array_base& stra)
   {
   }


   ::string acme_system_layer::fetch_public_internet_domain_extension_list_text()
   {
      return {};
   }


   void acme_system_layer::system_id_update(int iUpdate, long long iPayload)
   {
   }


   //void acme_system_layer::handle(::topic * ptopic, ::handler_context * phandlercontext) override{}

   // void acme_system_layer::add_handler(::particle * pmatter)
   // {
   //
   //
   // }
   //
   //
   // void acme_system_layer::add_signal_handler(const ::signal_handler& signalhandler, const ::atom& atomSignal)
   // {
   //
   //
   // }
   //
   //
   // void acme_system_layer::erase_signal_handler(::matter * pmatter)
   // {
   //
   //
   // }
   //
   //
   // void acme_system_layer::erase_signal_handler(::signal_handler::base* pbase)
   // {
   //
   //
   // }


   //void acme_system_layer::erase_signal_handlers(::particle * ppparticle){}

   void acme_system_layer::node_will_finish_launching()
   {
   }


void acme_system_layer::node_did_finish_launching()
{
}


void acme_system_layer::on_open_untitled_file()
   {
   }


   void acme_system_layer::on_open_file(const ::scoped_string & scopedstrFile)
   {
   }


   //template < typename BASE_TYPE >
   //::pointer<BASE_TYPE> create(const ::scoped_string & scopedstrComponent, const ::scoped_string & scopedstrImplementation)
   //{

   //   auto plibrary = ([a-z0-9_]+)_factory(scopedstrComponent, pszImplementation){}

   //   if (!plibrary)
   //   {

   //      return error_not_found{}

   //   }

   //   auto p = plibrary->create<BASE_TYPE>(){}

   //   if (!p)
   //   {

   //      return error_not_found{}

   //   }

   //   return p{}

   //}


   ::pointer<::compress> acme_system_layer::_new_compress(const ::scoped_string& scopedstrImplementation)
   {
      return {};
   }


   ::pointer<::uncompress> acme_system_layer::_new_uncompress(const ::scoped_string& scopedstrImplementation)
   {
      return {};
   }


   ::pointer<::compress> acme_system_layer::new_zlib_compress()
   {
      return {};
   }


   ::pointer<::uncompress> acme_system_layer::new_zlib_uncompress()
   {
      return {};
   }


   void acme_system_layer::_compress(const ::payload& payloadTarget, const ::payload& payloadSource,
                          const ::scoped_string& scopedstrImplementation)
   {
   }


   void acme_system_layer::_uncompress(const ::payload& payloadTarget, const ::payload& payloadSource,
                            const ::scoped_string& scopedstrImplementation,
                            transfer_progress_function transferprogressfunction)
   {
   }


   void acme_system_layer::zlib_compress(const ::payload& payloadTarget, const ::payload& payloadSource)
   {
   }


   void acme_system_layer::zlib_uncompress(const ::payload& payloadTarget, const ::payload& payloadSource,
                                transfer_progress_function transferprogressfunction)
   {
   }


   bool acme_system_layer::fast_is_decompressable_folder(const ::file::path& path)
   {
      return false;
   }


   //void acme_system_layer::windowing_send(const ::procedure & procedure){}
   //void acme_system_layer::windowing_post(const ::procedure & procedure){}


   //bool _handle_call(::payload & payload, const ::scoped_string & scopedstrObject, const ::scoped_string & scopedstrMember, ::property_set & propertyset) override{}


   //void acme_system_layer::windowing_post_quit(){}

   string acme_system_layer::get_latest_deployment_number(const ::scoped_string & scopedstrBranch)
   {
      return {};
   }


   //void acme_system_layer::destroy() override{}


   //CLASS_DECL_ACME ::acme::library * lib(const ::scoped_string & scopedstr){}


   //::file::path library_file_name(const ::scoped_string & scopedstr){}


   //template < typename ENTRY >
   //ENTRY* library_call(const ::scoped_string & scopedstrLibrary, const ::scoped_string & scopedstrEntry)
   //{

   //   return lib(scopedstrLibrary)->get<decltype(&ENTRY)>(scopedstrEntry)){}

   //}

   //#define LIBCALL(library, entry)  (system()->lib(#library)->get<decltype(&entry)>(#entry))


   ::string acme_system_layer::implementation_name(const ::scoped_string& scopedstrComponent,
                                        const ::scoped_string& scopedstrImplementation)
   {
      return {};
   }


   ::string acme_system_layer::library_name(const ::scoped_string& scopedstrComponent,
                                 const ::scoped_string& scopedstrImplementation)
   {
      return {};
   }


   //class ::crypto::crypto * crypto(){}


   ::file::path acme_system_layer::local_get_matter_cache_path()
   {
      return {};
   }


   ::file::path acme_system_layer::local_get_matter_cache_path(const ::scoped_string & scopedstrMatter)
   {
      return {};
   }


   ::file::path acme_system_layer::local_get_matter_path()
   {
      return {};
   }


   ::file::path acme_system_layer::local_get_matter_path(const ::scoped_string & scopedstrMatter)
   {
      return {};
   }


   void acme_system_layer::install_progress_add_up(int iAddUp)
   {
   }


   ::string acme_system_layer::get_application_server_name()
   {
      return {};
   }


   ::color::color acme_system_layer::background_color() const
   {
      return {};
   }


   double acme_system_layer::luminance() const
   {
      return 0.;
   }


   void acme_system_layer::set_background_color(const ::color::color& color)
   {
   }


   bool acme_system_layer::dark_mode() const
   {
      
      return false;

   }


   class ::time acme_system_layer::dark_mode_time() const
   {
      
      return {};

   }


   void acme_system_layer::set_dark_mode_time(const class ::time & time) 
   {


   }


   void acme_system_layer::on_application_dark_mode_change()
   {
   }


   //      virtual int get_simple_ui_darkness(){}

   //      void acme_system_layer::set_simple_ui_darkness(int iWeatherDarkness){}

   void acme_system_layer::set_dark_mode(bool bDark)
   {
   }


    ::color::color acme_system_layer::get_simple_ui_color(::enum_element eelement, ::user::enum_state estate)
   {
      return {};
   }


   ::color::color acme_system_layer::get_default_color(::color::color color)
   {
      return{};
   }


   // #if defined(WITH_X11)
   //       void acme_system_layer::x11_sync(const ::procedure & procedure){}
   //       void acme_system_layer::x11_async(const ::procedure & procedure){}
   // #endif

   bool acme_system_layer::defer_component_factory(const ::scoped_string& scopedstrComponent)
   {
      return false;
   }


   bool acme_system_layer::_defer_component_factory(const ::scoped_string& scopedstrComponent)
   {
      return false;
   }


   //::pointer < ::message_box > & realize(::pointer < ::message_box > & pmessagebox);

   //::pointer < ::message_box > message_box(const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle = nullptr, const ::user::e_message_box & emessagebox = ::user::e_message_box_ok, const ::scoped_string & scopedstrDetails = nullptr, ::nano::graphics::icon * picon = nullptr);

   //::pointer < ::message_box > exception_message_box(const ::exception & exception, const ::scoped_string & scopedstrMessage = nullptr, const ::scoped_string & scopedstrTitle = nullptr, const ::user::e_message_box & emessagebox = ::user::e_message_box_ok, const ::scoped_string & scopedstrDetails = nullptr, ::nano::graphics::icon * picon = nullptr);

   //::pointer < ::message_box > message_console(const ::scoped_string & scopedstrMessage = nullptr, const ::scoped_string & scopedstrTitle = nullptr, const ::user::e_message_box & emessagebox = ::user::e_message_box_ok, const ::scoped_string & scopedstrDetails = nullptr, ::nano::graphics::icon * picon = nullptr);

   //::pointer < ::message_box > exception_message_console(const ::exception & exception, const ::scoped_string & scopedstrMessage = nullptr, const ::scoped_string & scopedstrTitle = nullptr, const ::user::e_message_box & emessagebox = ::user::e_message_box_ok, const ::scoped_string & scopedstrDetails = nullptr, ::nano::graphics::icon * picon = nullptr);


} // namespace platform

//
// //CLASS_DECL_ACME::platform::system * system()
// //{
//
// // return g_psystem;
//
// //}
//
//
// //CLASS_DECL_ACME class ::plane_system * get_plane_system()
// //{
// //
// //   return system();
// //
// ////}
// //
// //
// //CLASS_DECL_ACME string get_latest_deployment_number(const ::scoped_string & scopedstrBranch)
// //{
// //
// //   return system()->get_latest_deployment_number(strBranch);
// //
// //}
//
//
// //
// //CLASS_DECL_ACME string __get_text(const ::scoped_string & scopedstr)
// //{
// //
// //   return ::g_psystem->__get_text(str);
// //
// //}
//
// //
// //CLASS_DECL_ACME::platform::system * get_context_system()
// //{
// //
// //   return g_psystem;
// //
// //}
//
// //
// //CLASS_DECL_ACME::platform::system * acme_system_init()
// //{
// //
// //   g_psystem = ___new ::platform::system ();
// //
// //   return g_psystem;
// //
// //}
//
//
// //CLASS_DECL_ACME void acme_system_layer::acme_system_term()
// //{
// //
// //   ::acme::del(g_psystem);
// //
// //}
//
//
// void acme_system_layer::system_id_update(void* pSystem, long long iUpdate, long long iParam)
// {
//
//    auto psystem = (::platform::system *)pSystem;
//
//    psystem->system_id_update(iUpdate, iParam);
//
// }
//
//
// void acme_system_layer::node_will_finish_launching(void* pSystem);
//
//
// void acme_system_layer::system_on_open_untitled_file(void* pSystem);
//
//
// void acme_system_layer::system_on_open_file(void* pSystem, const_char_pointer pszFile);
//
//
// void acme_system_layer::node_will_finish_launching(void* pSystem)
// {
//
//    auto psystem = (::platform::system *)pSystem;
//
//    psystem->node_will_finish_launching();
//
// }
//
//
// void acme_system_layer::system_on_open_untitled_file(void* pSystem)
// {
//
//    auto psystem = (::platform::system *)pSystem;
//
//    psystem->on_open_untitled_file();
//
// }
//
//
// void acme_system_layer::system_on_open_file(void* pSystem, const_char_pointer pszFile)
// {
//
//    auto psystem = (::platform::system *)pSystem;
//
//    psystem->on_open_file(scopedstrFile);
//
//
// }
//
//
// //::pointer<::platform::system>platform_create_system(const ::scoped_string & scopedstrAppId)
// //{
// //
// //   string strAppId(scopedstrAppId);
// //
// //#if !defined(CUBE)
// //
// //   if (strAppId.has_character())
// //   {
// //
// //      string strMessage;
// //
// //      string strLibrary = strAppId;
// //
// //      strLibrary.replace_with("_", "/");
// //
// //      strLibrary.replace_with("_", "-");
// //
// //      strLibrary.replace_with("_", ".");
// //
// //      auto plibrary = psystem->operating_system_library_open(strLibrary, strMessage);
// //
// //      if (!plibrary)
// //      {
// //
// //         //{
// //
// //         //   //auto pfuture = __sync_future();
// //
// //         //   //message_box(strMessage, "Could not open required library. Want to give an yes/no answer insted of pression cancel?", ::user::e_message_box_icon_exclamation | ::user::e_message_box_yes_no_cancel, pfuture);
// //
// //         //   //pfuture->wait(10_s);
// //
// //         //   int iDialogResult = pfuture->m_var;
// //
// //         //   informationf("result " + as_string(iDialogResult));
// //
// //         //}
// //
// //         //throw ::exception(error_failed, strMessage + "\n\nCould not open required library.");
// //
// //         informationf("The application library for appid \"" + strAppId + "\" wasn't loaded.");
// //
// //      }
// //
// //   }
// //
// //#endif
// //
// //   auto pstaticsetup = ::system_setup::get_first(::system_setup::flag_system, "");
// //
// //   if (!pstaticsetup)
// //   {
// //
// //      return nullptr;
// //
// //   }
// //
// //   auto pelement = pstaticsetup->create_particle();
// //
// //   if (!pelement)
// //   {
// //
// //      return nullptr;
// //
// //   }
// //
// //   ::pointer<::platform::system>psystem = pelement;
// //
// //   if (!psystem)
// //   {
// //
// //      return nullptr;
// //
// //   }
// //
// //   //psystem->m_strAppId = strAppId;
// //
// //   return ::transfer(psystem);
// //
// //}
// //
//
// CLASS_DECL_ACME task_pointer fork(::particle* pparticle, const ::procedure& procedure)
// {
//
//    return pparticle->system()->fork(procedure);
//
// }
