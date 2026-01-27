#include "framework.h"
#include "request.h"
#include "acme/user/user/element.h"
#include "acme/exception/interface_only.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/filesystem/filesystem/file_system.h"
#include "acme/platform/application.h"
#include "acme/prototype/data/data.h"


request_stack::request_stack(::request * prequest):
m_prequestHold(prequest)
{
   
   
}

request_stack::~request_stack()
{
   
   
}


class ::request * request_stack::request()
{
   
   return m_prequestHold;
   
}

request_scope::request_scope(::pointer < request_stack > && prequeststack):
m_prequeststack(::transfer(prequeststack))
{
   

}

request_scope::request_scope(const ::pointer < request_stack > & prequeststack):
m_prequeststack(prequeststack)
{
   

}


request_scope::~request_scope()
{
   
   try
   {
      
      m_prequeststack->m_prequestHold->pop_request(m_prequeststack);

   }
   catch (...)
   {
      
   }
   
}


class ::request * request_scope::request()
{
   
   return m_prequeststack->request();
   
}


request::request()
{

   //m_bMakeVisible = true;
   m_egraphicsoutputpurpose = ::graphics::e_output_purpose_screen;

   common_construct();

}


request::~request()
{

}



long long request::increment_reference_count()
{

   return ::object::increment_reference_count();

}


long long request::decrement_reference_count()
{

   return ::object::decrement_reference_count();

}


void request::initialize_create(arguments arguments)
{

   create_common_construct(::e_type_empty_argument, nullptr);

   for(auto & arg : arguments)
   {

      if(arg.get_type() == e_type_atom && arg.as_atom().m_etype == atom::e_type_command)
      {

         m_ecommand = arg.as_atom().m_ecommand;

      }
      else if(arg.get_type() == e_type_string)
      {

         //auto estatus = 
         
         //øconstruct(m_pcommandline);

         //if (!estatus)
         //{

         //   return estatus;

         //}
         
         // estatus = 
         initialize_command_line2(arg.as_string());

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


void request::initialize_create(const ::scoped_string & scopedstrAppId, ::payload payloadFile, const ::payload & varOptions, ::user::element * puiParent, e_window_flag ewindowflag, ::atom atom)
{

   m_ewindowflag = ewindowflag;
      
   id() = atom;

   create_common_construct(varOptions, puiParent);

   if(scopedstrAppId.has_character())
   {

      m_strAppId = scopedstrAppId;

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


void request::initialize_create(::data::data * pdata, const ::payload & varOptions, ::user::element * puiParent, e_window_flag ewindowflag, ::atom atom)
{

   m_ewindowflag = ewindowflag;

   id() = atom;

   create_common_construct(varOptions, puiParent);

   //if (strAppId.has_character())
   //{

   //   m_strAppId = strAppId;

   //}

   //auto estatus = 
   finish_initialization();

   //if (!estatus)
   //{
   //   
   //   return estatus;

   //}

   //m_payloadFile = payloadFile;

   m_pdata = pdata;

   m_puserelementParent = puiParent;

   ///return estatus;

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

   if(m_payloadOptions.is_property_true_or_empty("screen_graphical_output_purpose"))
   {

      m_egraphicsoutputpurpose |= ::graphics::e_output_purpose_screen;

   }

}


::platform::application * request::create_get_app(::platform::application * pappFallback)
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
   //   øconstruct(m_pcommandline);

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


void request::set_description(const ::scoped_string & scopedstrDescription)
{

   m_strDescription = scopedstrDescription;

}


::collection::index request::get_edge()
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
   m_ecommand = e_command_default;
   m_iEdge = 0;

}


::pointer < ::request_stack > request::push_request()
{
   
   if(m_bFinishedStacking)
   {
      
      throw ::exception(error_failed, "Already popped all stacks");
      
   }
   
   auto prequeststack = øallocate request_stack(this);
   
   m_requeststacka.add(prequeststack);
   
   return ::transfer(prequeststack);
   
}


void request::pop_request(::request_stack * prequeststack)
{
   
   m_requeststacka.erase(prequeststack);
   
   if(m_requeststacka.is_empty())
   {
      
      m_bFinishedStacking = true;
      
      for(auto & procedure : m_procedureaOnFinishRequest)
      {
       
         try
         {
            
            procedure();
               
         }
         catch(...)
         {
            
         }
         
      }
   
      m_procedureaOnFinishRequest.clear();
   
   }
   
}



void request::destroy()
{

   m_puserelementParent.release();

   m_puserelementAlloc.release();

   m_pmatterUserPayload.release();

   m_pcontextFork.release();

   m_pdata.release();

   m_procedureaOnFinishRequest.clear();

   ::object::destroy();

   output_purpose::destroy();

}

//request::~request()
//{
//}


void request::initialize_command_line2(const ::scoped_string & scopedstrCommandLine)
{

   common_construct();

   _001ParseCommandFork(scopedstrCommandLine);

   //return ::success;

}


void request::initialize_arguments(::string_array_base& straArguments)
{

   common_construct();

   _001ParseCommandArguments(straArguments);

   //return ::success;

}


void request::ParseParam(const ::scoped_string & scopedstrParam, bool bFlag, bool bLast)
{

   if (bFlag)
   {

      ParseParamFlag(scopedstrParam);

   }
   else
   {

      ParseParamNotFlag(scopedstrParam);

   }

   ParseLast(bLast);

}


void request::ParseParamFlag(const ::scoped_string & scopedstrParam)
{
   // OLE command switches are case insensitive, while
   // shell command switches are case sensitive

   if (scopedstrParam.case_insensitive_order("int_point") == 0)
   {

      m_ecommand = e_command_file_print_to;

   }
   else if (scopedstrParam.case_insensitive_order("int_point") == 0)
   {

      m_ecommand = e_command_file_print;

   }
   else if (scopedstrParam.case_insensitive_order("Unregister") == 0 || scopedstrParam.case_insensitive_order("Unregserver") == 0)
   {

      m_ecommand = e_command_app_unregister;

   }
   else if (scopedstrParam.case_insensitive_order("dde") == 0)
   {

      m_ecommand = e_command_file_dde;

   }
   else if (scopedstrParam.case_insensitive_order("Embedding") == 0)
   {

      m_bRunEmbedded = true;

      m_bShowSplash = false;

   }
   else if (scopedstrParam.case_insensitive_order("Automation") == 0)
   {

      m_bRunAutomated = true;

      m_bShowSplash = false;

   }

}


void request::ParseParamNotFlag(const ::scoped_string & scopedstrParam)
{

   if (m_payloadFile.is_empty())
   {

      m_payloadFile = scopedstrParam;

   }
   else if (m_ecommand == e_command_file_print_to && m_strPrinterName.is_empty())
   {

      m_payloadFile = scopedstrParam;

   }
   else if (m_ecommand == e_command_file_print_to && m_strDriverName.is_empty())
   {

      m_payloadFile = scopedstrParam;

   }
   else if (m_ecommand == e_command_file_print_to && m_strPortName.is_empty())
   {

      m_payloadFile = scopedstrParam;

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


void request::_001ParseCommandLine(const ::scoped_string & scopedstrCommandLine)
{

   m_strCommandLine = scopedstrCommandLine;

   property_set()._008Parse(true, scopedstrCommandLine, m_payloadFile, m_strExe);

   if (!m_payloadFile.is_empty())
   {

      m_ecommand = e_command_file_open;

   }

   if (has_property("uri"))
   {

      if (m_payloadFile.has_character())
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

      if (file_system()->exists(directory_system()->userconfig() / "config\\plugin\\build.txt"))
      {

         string str = file_system()->as_string(directory_system()->userconfig() / "config\\plugin\\build.txt");

         payload("build") = str;

      }

   }

}


void request::_001ParseCommandLineUri(const ::scoped_string & scopedstrCommandLine)
{

   m_strCommandLine = scopedstrCommandLine;

   throw ::interface_only();

}


void request::_001ParseCommandFork(const ::scoped_string & scopedstrCommandFork)
{

   m_strCommandLine = scopedstrCommandFork;

   property_set()._008ParseCommandFork(scopedstrCommandFork, m_payloadFile, m_strExe);

   if (!m_payloadFile.is_empty())
   {

      m_ecommand = e_command_file_open;

   }

   if (has_property("uri"))
   {

      if (m_payloadFile.has_character())
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


void request::_001ParseCommandArguments(::string_array_base& straArguments)
{

   property_set()._008ParseCommandArguments(straArguments, m_payloadFile, m_strExe);

   if (!m_payloadFile.is_empty())
   {

      m_ecommand = e_command_file_open;

   }

   if (has_property("uri"))
   {

      if (m_payloadFile.has_character())
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


void request::_001ParseCommandForkUri(const ::scoped_string & scopedstrCommandFork)
{

   string strQuery(scopedstrCommandFork);

   auto pFind = strQuery.find('?');

   if (::is_null(pFind))
   {

      strQuery = "";

   }
   else
   {

      strQuery = strQuery(pFind + 1);

   }

   string strScript(scopedstrCommandFork);

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

   property_set().parse_network_arguments(strQuery);

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




