#include "framework.h"
#include "request.h"
#include "acme/user/user/element.h"
#include "acme/exception/interface_only.h"
#include "acme/filesystem/filesystem/acme_directory.h"
#include "acme/filesystem/filesystem/acme_file.h"
#include "acme/platform/application.h"


request::request()
{

   m_bMakeVisible = true;
   common_construct();

}


void request::initialize_create(arguments arguments)
{

   create_common_construct(::e_type_empty_argument, nullptr);

   for(auto & arg : arguments)
   {

      if(arg.get_type() == e_type_enum_command)
      {

         m_ecommand = arg.m_ecommand;

      }
      else if(arg.get_type() == e_type_string)
      {

         //auto estatus = 
         
         //__construct(m_pcommandline);

         //if (!estatus)
         //{

         //   return estatus;

         //}
         
         // estatus = 
         initialize_command_line2(arg);

         //if (!estatus)
         //{

         //   return estatus;

         //}

      }
      //else if(auto pcommandline = arg.cast<request>())
      //{

      //   m_pcommandline = pcommandline;

      //}
      //else if(auto pcreate = arg.cast < request >())
      //{

      //   throw ::exception(todo, "Fix this. This shouldn't happen. (request is \"fat\" object, so it is not meant to be copied through copy constructors, assign operators,...)");
      //   //operator = (*pcreate);

      //}

   }

   return finish_initialization();

}


void request::initialize_create(string strAppId, ::payload payloadFile, const ::payload & varOptions, ::user::element * puiParent, e_window_flag ewindowflag, ::atom atom)
{

   m_ewindowflag = ewindowflag;
      
   m_atom = atom;

   create_common_construct(varOptions, puiParent);

   if(strAppId.has_char())
   {

      m_strAppId = strAppId;

   }

   //auto estatus = 
   finish_initialization();

   //if (!estatus)
   //{
   //   
   //   return estatus;

   //}
   
   m_payloadFile = payloadFile;

   m_puserelementParent = puiParent;

   ///return estatus;

}


request::~request()
{

}


void request::create_common_construct(const ::payload & varOptions, ::user::element * puiParent)
{

   m_bNew                              = true;
   m_ecommand                          = e_command_default;
   m_payloadOptions                    = varOptions;
   m_bTransparentBackground            = true;
   m_bExperienceMainFrame              = false;
   m_bOuterPopupAlertLike              = false;
   m_bHold                             = true;
   m_bMakeVisible                      = m_payloadOptions.is_property_true("visible", true);

}


::acme::application * request::create_get_app(::acme::application * pappFallback)
{

   auto pparticle = this;

   if (pparticle)
   {

      auto papp = pparticle->get_app();

      if (papp)
      {

         return papp;

      }

   }

   return pappFallback;

}


void request::finish_initialization()
{

   ::e_status estatus = ::success;

   //if(!m_pcommandline)
   //{

   //   //estatus = 
   //   
   //   __construct(m_pcommandline);

   //   //if (!estatus)
   //   //{

   //   //   return estatus;

   //   //}

   //}

   if(get_app())
   {

      if(get_app()->m_bExperienceMainFrame)
      {

         m_bExperienceMainFrame = true;

      }

   }

   //return estatus;

}


string request::get_description()
{

   return m_strDescription;

}


void request::set_description(string strDescription)
{

   m_strDescription = strDescription;

}


index request::get_edge()
{

   //if(!m_pcommandline)
   //{

   //   return 0;

   //}

   return m_iEdge;

}


bool request::has_file() const
{

   if (!m_payloadFile.is_empty())
   {

      return true;

   }

   //if (m_pcommandline && !m_pcommandline->m_payloadFile.is_empty())
   //{

   //   return true;

   //}

   return false;

}


::payload request::get_file() const
{

   if (!m_payloadFile.is_empty())
   {

      return m_payloadFile;

   }

   //if (m_pcommandline && !m_pcommandline->m_payloadFile.is_empty())
   //{

   //   return m_pcommandline->m_payloadFile;

   //}

   return ::payload();

}


void request::set_file_path(const ::payload& payload)
{

   m_payloadFile = payload;

   //if (m_pcommandline)
   //{

   //   m_pcommandline->m_payloadFile = payload;

   //}

}




//
//
//request::request()
//{
//
//   common_construct();
//
//}


void request::common_construct()
{

   m_bShowSplash = true;
   m_bRunEmbedded = false;
   m_bRunAutomated = false;
   m_ecommand = e_command_application_start;
   m_iEdge = 0;

}


//request::~request()
//{
//}


void request::initialize_command_line2(const string& strCommandLine)
{

   common_construct();

   _001ParseCommandFork(strCommandLine);

   //return ::success;

}


void request::initialize_arguments(::string_array& straArguments)
{

   common_construct();

   _001ParseCommandArguments(straArguments);

   //return ::success;

}


void request::ParseParam(const ::string& strParam, bool bFlag, bool bLast)
{

   if (bFlag)
   {

      ParseParamFlag(strParam);

   }
   else
   {

      ParseParamNotFlag(strParam);

   }

   ParseLast(bLast);

}


void request::ParseParamFlag(const ::string& strParam)
{
   // OLE command switches are case insensitive, while
   // shell command switches are case sensitive

   if (strParam.case_insensitive_order("point_i32") == 0)
   {

      m_ecommand = e_command_file_print_to;

   }
   else if (strParam.case_insensitive_order("point_i32") == 0)
   {

      m_ecommand = e_command_file_print;

   }
   else if (strParam.case_insensitive_order("Unregister") == 0 || strParam.case_insensitive_order("Unregserver") == 0)
   {

      m_ecommand = e_command_app_unregister;

   }
   else if (strParam.case_insensitive_order("dde") == 0)
   {

      m_ecommand = e_command_file_dde;

   }
   else if (strParam.case_insensitive_order("Embedding") == 0)
   {

      m_bRunEmbedded = true;

      m_bShowSplash = false;

   }
   else if (strParam.case_insensitive_order("Automation") == 0)
   {

      m_bRunAutomated = true;

      m_bShowSplash = false;

   }

}


void request::ParseParamNotFlag(const ::string& strParam)
{

   if (m_payloadFile.is_empty())
   {

      m_payloadFile = strParam;

   }
   else if (m_ecommand == e_command_file_print_to && m_strPrinterName.is_empty())
   {

      m_payloadFile = strParam;

   }
   else if (m_ecommand == e_command_file_print_to && m_strDriverName.is_empty())
   {

      m_payloadFile = strParam;

   }
   else if (m_ecommand == e_command_file_print_to && m_strPortName.is_empty())
   {

      m_payloadFile = strParam;

   }

}

void request::ParseLast(bool bLast)
{

   if (bLast)
   {
      if (m_ecommand == e_command_file_new && !m_payloadFile.is_empty())
      {

         m_ecommand = e_command_file_open;

      }

      m_bShowSplash = !m_bRunEmbedded && !m_bRunAutomated;

   }

}


//request & request::operator = (const request & info)
//{
//
//   m_bShowSplash     = info.m_bShowSplash;
//   m_bRunEmbedded    = info.m_bRunEmbedded;
//   m_bRunAutomated   = info.m_bRunAutomated;
//   m_payloadFile         = info.m_payloadFile;
//   m_strPrinterName  = info.m_strPrinterName;
//   m_strPortName     = info.m_strPortName;
//
//   return *this;
//
//}


void request::_001ParseCommandLine(const ::string& strCommandLine)
{

   m_strCommandLine = strCommandLine;

   get_property_set()._008Parse(true, strCommandLine, m_payloadFile, m_strExe);

   if (!m_payloadFile.is_empty())
   {

      m_ecommand = e_command_file_open;

   }

   if (has_property("uri"))
   {

      if (m_payloadFile.has_char())
      {

         m_payloadFile += ";";

         m_payloadFile += payload("uri");

      }
      else
      {

         m_payloadFile = payload("uri");

      }

      if (m_ecommand == e_command_file_new)
      {

         m_ecommand = e_command_file_open;

      }

   }

   if (m_ecommand == e_command_file_open)
   {

      payload("show_platform") = 1;

   }

   if (has_property("app"))
   {

      m_strApp = payload("app");

   }

   if (m_strApp == "session" && has_property("session_start"))
   {

      m_strApp = payload("session_start");

   }

   if (has_property("app_type"))
   {

      m_strAppType = payload("app_type");

   }

   if (!has_property("build") || payload("build").is_empty())
   {

      if (acmefile()->exists(acmedirectory()->system() / "config\\plugin\\build.txt"))
      {

         string str = acmefile()->as_string(acmedirectory()->system() / "config\\plugin\\build.txt");

         payload("build") = str;

      }

   }

}


void request::_001ParseCommandLineUri(const ::string& strCommandLine)
{

   m_strCommandLine = strCommandLine;

   throw ::interface_only();

}


void request::_001ParseCommandFork(const ::string& strCommandFork)
{

   m_strCommandLine = strCommandFork;

   get_property_set()._008ParseCommandFork(strCommandFork, m_payloadFile, m_strExe);

   if (!m_payloadFile.is_empty())
   {

      m_ecommand = e_command_file_open;

   }

   if (has_property("uri"))
   {

      if (m_payloadFile.has_char())
      {

         m_payloadFile += ";";

         m_payloadFile += payload("uri");

      }
      else
      {

         m_payloadFile = payload("uri");

      }

      if (m_ecommand == e_command_file_new)
      {

         m_ecommand = e_command_file_open;

      }

   }

   if (m_ecommand == e_command_file_open)
   {

      payload("show_platform") = 1;

   }

   if (has_property("app"))
   {

      m_strApp = payload("app");

   }

   if (m_strApp == "session" && has_property("session_start"))
   {

      m_strApp = payload("session_start");

   }

   if (has_property("app_type"))
   {

      m_strAppType = payload("app_type");

   }

   //      m_pthreadParent->consolidate(this);

}


void request::_001ParseCommandArguments(::string_array& straArguments)
{

   get_property_set()._008ParseCommandArguments(straArguments, m_payloadFile, m_strExe);

   if (!m_payloadFile.is_empty())
   {

      m_ecommand = e_command_file_open;

   }

   if (has_property("uri"))
   {

      if (m_payloadFile.has_char())
      {

         m_payloadFile += ";";

         m_payloadFile += payload("uri");

      }
      else
      {

         m_payloadFile = payload("uri");

      }

      if (m_ecommand == e_command_file_new)
      {

         m_ecommand = e_command_file_open;

      }

   }

   if (m_ecommand == e_command_file_open)
   {

      payload("show_platform") = 1;

   }

   if (has_property("app"))
   {

      m_strApp = payload("app");

   }

   if (m_strApp == "session" && has_property("session_start"))
   {

      m_strApp = payload("session_start");

   }

   if (has_property("app_type"))
   {

      m_strAppType = payload("app_type");

   }

   //      m_pthreadParent->consolidate(this);

}


void request::_001ParseCommandForkUri(const ::string& strCommandFork)
{

   string strQuery(strCommandFork);

   auto pFind = strQuery.find('?');

   if (::is_null(pFind))
   {

      strQuery = "";

   }
   else
   {

      strQuery = strQuery(pFind + 1);

   }

   string strScript(strCommandFork);

   auto pPos = strScript.find("://");

   if (::is_set(pPos))
   {

      pPos += 3;

      auto pStart = strScript(pPos).find("/");

      if (::is_null(pStart))
         strScript = "/";
      else
         strScript.begin(pStart);

   }

   pFind = strScript.find('?');

   if (::is_set(pFind))
   {

      strScript = strScript(0, pFind);

   }

   get_property_set().parse_network_arguments(strQuery);

   m_strApp = strScript;

   if (has_property("file"))
   {

      m_payloadFile = payload("file");

   }

}


//command_line_pointer::command_line_pointer()
//{
//
//}
//
//
//command_line_pointer::command_line_pointer(const ::apex::allocatorsp & allocer) :
//   ::pointer<request>(allocer)
//{
//
//}




