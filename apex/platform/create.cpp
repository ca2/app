#include "framework.h"
#include "apex/user/primitive.h"

#include "acme/filesystem/filesystem/acme_directory.h"
#include "acme/filesystem/filesystem/acme_file.h"



create::create()
{

   m_bMakeVisible = true;
   common_construct();

}




void create::initialize_create(arguments arguments) 
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
         initialize_command_line2(arg.string());

         //if (!estatus)
         //{

         //   return estatus;

         //}

      }
      //else if(auto pcommandline = arg.cast<create>())
      //{

      //   m_pcommandline = pcommandline;

      //}
      //else if(auto pcreate = arg.cast < create >())
      //{

      //   throw ::exception(todo, "Fix this. This shouldn't happen. (create is \"fat\" object, so it is not meant to be copied through copy constructors, assign operators,...)");
      //   //operator = (*pcreate);

      //}

   }

   return finish_initialization();

}


void create::initialize_create(string strAppId, ::payload payloadFile, const ::payload & varOptions, ::user::primitive * puiParent, ewindowflag ewindowflag, ::atom atom)
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

   m_puserprimitiveParent = puiParent;

   ///return estatus;

}


create::~create()
{

}


void create::create_common_construct(const ::payload & varOptions, ::user::primitive * puiParent)
{

   m_bNew                              = true;
   m_ecommand                          = e_command_default;
   m_payloadOptions                    = varOptions;
   m_bTransparentBackground            = true;
   m_bExperienceMainFrame              = false;
   m_bOuterPopupAlertLike              = false;
   m_bHold                             = true;
   m_bMakeVisible                      = m_payloadOptions.is_true("visible", true);

}


::app * create::create_get_app(::app * pappFallback)
{

   auto pobject = this;

   if (pobject)
   {

      auto papp = pobject->get_app();

      if (papp)
      {

         return papp;

      }

   }

   return pappFallback;

}


void create::finish_initialization()
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


string create::get_description()
{

   return m_strDescription;

}


void create::set_description(string strDescription)
{

   m_strDescription = strDescription;

}


index create::get_edge()
{

   //if(!m_pcommandline)
   //{

   //   return 0;

   //}

   return m_iEdge;

}


bool create::has_file() const
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


::payload create::get_file() const
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


void create::set_file_path(const ::payload& payload)
{

   m_payloadFile = payload;

   //if (m_pcommandline)
   //{

   //   m_pcommandline->m_payloadFile = payload;

   //}

}




//
//
//create::create()
//{
//
//   common_construct();
//
//}


void create::common_construct()
{

   m_bShowSplash = true;
   m_bRunEmbedded = false;
   m_bRunAutomated = false;
   m_ecommand = e_command_application_start;
   m_iEdge = 0;
   m_puserinteractionParent = nullptr;
   //m_pappbias     = nullptr;
}

//create::~create()
//{
//}


void create::initialize_command_line2(const string& strCommandLine)
{

   common_construct();

   _001ParseCommandFork(strCommandLine);

   //return ::success;

}


void create::initialize_arguments(::string_array& straArguments)
{

   common_construct();

   _001ParseCommandArguments(straArguments);

   //return ::success;

}


void create::ParseParam(const ::string& strParam, bool bFlag, bool bLast)
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


void create::ParseParamFlag(const ::string& strParam)
{
   // OLE command switches are case insensitive, while
   // shell command switches are case sensitive

   if (strParam.compare_ci("point_i32") == 0)
   {

      m_ecommand = e_command_file_print_to;

   }
   else if (strParam.compare_ci("point_i32") == 0)
   {

      m_ecommand = e_command_file_print;

   }
   else if (strParam.compare_ci("Unregister") == 0 || strParam.compare_ci("Unregserver") == 0)
   {

      m_ecommand = e_command_app_unregister;

   }
   else if (strParam.compare_ci("dde") == 0)
   {

      m_ecommand = e_command_file_dde;

   }
   else if (strParam.compare_ci("Embedding") == 0)
   {

      m_bRunEmbedded = true;

      m_bShowSplash = false;

   }
   else if (strParam.compare_ci("Automation") == 0)
   {

      m_bRunAutomated = true;

      m_bShowSplash = false;

   }

}


void create::ParseParamNotFlag(const ::string& strParam)
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

void create::ParseLast(bool bLast)
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


//create & create::operator = (const create & info)
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


void create::_001ParseCommandLine(const ::string& strCommandLine)
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

      if (m_psystem->m_pacmefile->exists(m_psystem->m_pacmedirectory->system() / "config\\plugin\\build.txt"))
      {

         string str = m_psystem->m_pacmefile->as_string(m_psystem->m_pacmedirectory->system() / "config\\plugin\\build.txt");

         payload("build") = str;

      }

   }

}


void create::_001ParseCommandLineUri(const ::string& strCommandLine)
{

   m_strCommandLine = strCommandLine;

   throw ::interface_only();

}

void create::_001ParseCommandFork(const ::string& strCommandFork)
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


void create::_001ParseCommandArguments(::string_array& straArguments)
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


void create::_001ParseCommandForkUri(const ::string& strCommandFork)
{

   string strQuery(strCommandFork);

   strsize iFind = strQuery.find('?');

   if (iFind < 0)
   {

      strQuery = "";

   }
   else
   {

      strQuery = strQuery.Mid(iFind + 1);

   }

   string strScript(strCommandFork);

   strsize iPos = strScript.find("://");

   if (iPos >= 0)
   {

      iPos += 3;

      strsize iStart = strScript.find("/", iPos);

      if (iStart < 0)
         strScript = "/";
      else
         strScript = strScript.Mid(iStart);

   }

   iFind = strScript.find('?');

   if (iFind >= 0)
   {

      strScript = strScript.Left(iFind);

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
//   pointer < create > (allocer)
//{
//
//}




