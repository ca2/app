#include "framework.h"
//#include "acme/filesystem/filesystem/acme_directory.h"
//#include "acme/filesystem/filesystem/acme_file.h"
//
//
//command_line::command_line()
//{
//
//   common_construct();
//
//}
//
//
//void command_line::common_construct()
//{
//
//   m_bShowSplash     = true;
//   m_bRunEmbedded    = false;
//   m_bRunAutomated   = false;
//   m_ecommand        = command_application_start;
//   m_iEdge           = 0;
//   m_puserinteractionParent       = nullptr;
//   //m_pappbias     = nullptr;
//}
//
//command_line::~command_line()
//{
//}
//
//
//void command_line::initialize_command_line2(const string& strCommandLine)
//{
//
//   common_construct();
//
//   _001ParseCommandFork(strCommandLine);
//
//   //return ::success;
//
//}
//
//
//void command_line::initialize_arguments(const ::string_array & straArguments)
//{
//
//   common_construct();
//
//   _001ParseCommandArguments(straArguments);
//
//   //return ::success;
//
//}
//
//
//void command_line::ParseParam(const ::string & strParam,bool bFlag,bool bLast)
//{
//
//   if(bFlag)
//   {
//
//      ParseParamFlag(strParam);
//
//   }
//   else
//   {
//
//      ParseParamNotFlag(strParam);
//
//   }
//
//   ParseLast(bLast);
//
//}
//
//
//void command_line::ParseParamFlag(const ::string & strParam)
//{
//   // OLE command switches are case insensitive, while
//   // shell command switches are case sensitive
//
//   if(strParam.compare_ci("point_i32") == 0)
//   {
//
//      m_ecommand = command_file_print_to;
//
//   }
//   else if(strParam.compare_ci("point_i32") == 0)
//   {
//
//      m_ecommand = command_file_print;
//
//   }
//   else if(strParam.compare_ci("Unregister") == 0 || strParam.compare_ci("Unregserver") == 0)
//   {
//
//      m_ecommand = command_app_unregister;
//
//   }
//   else if(strParam.compare_ci("dde") == 0)
//   {
//
//      m_ecommand = command_file_dde;
//
//   }
//   else if(strParam.compare_ci("Embedding") == 0)
//   {
//
//      m_bRunEmbedded = true;
//
//      m_bShowSplash = false;
//
//   }
//   else if(strParam.compare_ci("Automation") == 0)
//   {
//
//      m_bRunAutomated = true;
//
//      m_bShowSplash = false;
//
//   }
//
//}
//
//
//void command_line::ParseParamNotFlag(const ::string & strParam)
//{
//
//   if(m_payloadFile.is_empty())
//   {
//
//      m_payloadFile = strParam;
//
//   }
//   else if(m_ecommand == command_file_print_to && m_strPrinterName.is_empty())
//   {
//
//      m_payloadFile = strParam;
//
//   }
//   else if(m_ecommand == command_file_print_to && m_strDriverName.is_empty())
//   {
//
//      m_payloadFile = strParam;
//
//   }
//   else if(m_ecommand == command_file_print_to && m_strPortName.is_empty())
//   {
//
//      m_payloadFile = strParam;
//
//   }
//
//}
//
//void command_line::ParseLast(bool bLast)
//{
//
//   if (bLast)
//   {
//      if(m_ecommand == command_file_new && !m_payloadFile.is_empty())
//      {
//
//         m_ecommand = command_file_open;
//
//      }
//
//      m_bShowSplash = !m_bRunEmbedded && !m_bRunAutomated;
//
//   }
//
//}
//
//
////command_line & command_line::operator = (const command_line & info)
////{
////
////   m_bShowSplash     = info.m_bShowSplash;
////   m_bRunEmbedded    = info.m_bRunEmbedded;
////   m_bRunAutomated   = info.m_bRunAutomated;
////   m_payloadFile         = info.m_payloadFile;
////   m_strPrinterName  = info.m_strPrinterName;
////   m_strPortName     = info.m_strPortName;
////
////   return *this;
////
////}
//
//
//void command_line::_001ParseCommandLine(const ::string & strCommandLine)
//{
//
//   m_strCommandLine = strCommandLine;
//
//   get_property_set()._008Parse(true, strCommandLine,m_payloadFile, m_strExe);
//
//   if(!m_payloadFile.is_empty())
//   {
//
//      m_ecommand = command_line::command_file_open;
//
//   }
//
//   if(has_property("uri"))
//   {
//
//      if(m_payloadFile.has_char())
//      {
//
//         m_payloadFile += ";";
//
//         m_payloadFile += payload("uri");
//
//      }
//      else
//      {
//
//         m_payloadFile = payload("uri");
//
//      }
//
//      if(m_ecommand == command_line::command_file_new)
//      {
//
//         m_ecommand = command_line::command_file_open;
//
//      }
//
//   }
//
//   if(m_ecommand == command_line::command_file_open)
//   {
//
//      payload("show_platform") = 1;
//
//   }
//
//   if(has_property("app"))
//   {
//
//      m_strApp = payload("app");
//
//   }
//
//   if(m_strApp == "session" && has_property("session_start"))
//   {
//
//      m_strApp = payload("session_start");
//
//   }
//
//   if(has_property("app_type"))
//   {
//
//      m_strAppType = payload("app_type");
//
//   }
//
//   if (!has_property("build") || payload("build").is_empty())
//   {
//
//      if (m_psystem->m_pacmefile->exists(m_psystem->m_pacmedirectory->system() / "config\\plugin\\build.txt"))
//      {
//
//         string str = m_psystem->m_pacmefile->as_string(m_psystem->m_pacmedirectory->system() / "config\\plugin\\build.txt");
//
//         payload("build") = str;
//
//      }
//
//   }
//
//}
//
//
//void command_line::_001ParseCommandLineUri(const ::string & strCommandLine)
//{
//
//   m_strCommandLine = strCommandLine;
//
//   throw ::interface_only();
//
//}
//
//void command_line::_001ParseCommandFork(const ::string & strCommandFork)
//{
//
//   m_strCommandLine = strCommandFork;
//
//   get_property_set()._008ParseCommandFork(strCommandFork, m_payloadFile, m_strExe);
//
//   if(!m_payloadFile.is_empty())
//   {
//
//      m_ecommand = command_line::command_file_open;
//
//   }
//
//   if(has_property("uri"))
//   {
//
//      if(m_payloadFile.has_char())
//      {
//
//         m_payloadFile += ";";
//
//         m_payloadFile += payload("uri");
//
//      }
//      else
//      {
//
//         m_payloadFile = payload("uri");
//
//      }
//
//      if(m_ecommand == command_line::command_file_new)
//      {
//
//         m_ecommand = command_line::command_file_open;
//
//      }
//
//   }
//
//   if(m_ecommand == command_line::command_file_open)
//   {
//
//      payload("show_platform") = 1;
//
//   }
//
//   if(has_property("app"))
//   {
//
//      m_strApp = payload("app");
//
//   }
//
//   if(m_strApp == "session" && has_property("session_start"))
//   {
//
//      m_strApp = payload("session_start");
//
//   }
//
//   if(has_property("app_type"))
//   {
//
//      m_strAppType = payload("app_type");
//
//   }
//
//   //      m_pthreadParent->consolidate(this);
//
//}
//
//
//void command_line::_001ParseCommandArguments(const ::string_array & straArguments)
//{
//
//   get_property_set()._008ParseCommandArguments(straArguments, m_payloadFile, m_strExe);
//
//   if (!m_payloadFile.is_empty())
//   {
//
//      m_ecommand = command_line::command_file_open;
//
//   }
//
//   if (has_property("uri"))
//   {
//
//      if (m_payloadFile.has_char())
//      {
//
//         m_payloadFile += ";";
//
//         m_payloadFile += payload("uri");
//
//      }
//      else
//      {
//
//         m_payloadFile = payload("uri");
//
//      }
//
//      if (m_ecommand == command_line::command_file_new)
//      {
//
//         m_ecommand = command_line::command_file_open;
//
//      }
//
//   }
//
//   if (m_ecommand == command_line::command_file_open)
//   {
//
//      payload("show_platform") = 1;
//
//   }
//
//   if (has_property("app"))
//   {
//
//      m_strApp = payload("app");
//
//   }
//
//   if (m_strApp == "session" && has_property("session_start"))
//   {
//
//      m_strApp = payload("session_start");
//
//   }
//
//   if (has_property("app_type"))
//   {
//
//      m_strAppType = payload("app_type");
//
//   }
//
//   //      m_pthreadParent->consolidate(this);
//
//}
//
//
//void command_line::_001ParseCommandForkUri(const ::string & strCommandFork)
//{
//
//   string strQuery(strCommandFork);
//
//   strsize iFind = strQuery.find('?');
//
//   if (iFind < 0)
//   {
//
//      strQuery = "";
//
//   }
//   else
//   {
//
//      strQuery = strQuery.Mid(iFind + 1);
//
//   }
//
//   string strScript(strCommandFork);
//
//   strsize iPos = strScript.find("://");
//
//   if(iPos >= 0)
//   {
//
//      iPos += 3;
//
//      strsize iStart = strScript.find("/",iPos);
//
//      if(iStart < 0)
//         strScript= "/";
//      else
//         strScript= strScript.Mid(iStart);
//
//   }
//
//   iFind = strScript.find('?');
//
//   if (iFind >= 0)
//   {
//
//      strScript = strScript.Left(iFind);
//
//   }
//
//   get_property_set().parse_url_query(strQuery);
//
//   m_strApp = strScript;
//
//   if(has_property("file"))
//   {
//
//      m_payloadFile = payload("file");
//
//   }
//
//}
//
//
////command_line_pointer::command_line_pointer()
////{
////
////}
////
////
////command_line_pointer::command_line_pointer(const ::apex::allocatorsp & allocer) :
////   pointer < command_line > (allocer)
////{
////
////}
//
//
//
//
