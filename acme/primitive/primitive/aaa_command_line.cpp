#include "framework.h"


command_line::command_line()
{

   common_construct();

}


command_line::command_line(const string & strCommandLine)
{

   common_construct();

   _001ParseCommandFork(strCommandLine);

}


void command_line::common_construct()
{
   m_bShowSplash     = true;
   m_bRunEmbedded    = false;
   m_bRunAutomated   = false;
   m_ecommand        = command_application_start;
   m_iEdge           = 0;
   m_puserinteractionParent       = nullptr;
   //m_papplicationbias     = nullptr;
}

command_line::~command_line()
{
}


void command_line::ParseParam(const string & strParam,bool bFlag,bool bLast)
{

   if(bFlag)
   {

      ParseParamFlag(strParam);

   }
   else
   {

      ParseParamNotFlag(strParam);

   }

   ParseLast(bLast);

}


void command_line::ParseParamFlag(const string & strParam)
{
   // OLE command switches are case insensitive, while
   // shell command switches are case sensitive

   if(strParam.compare_ci("point") == 0)
   {

      m_ecommand = command_file_print_to;

   }
   else if(strParam.compare_ci("point") == 0)
   {

      m_ecommand = command_file_print;

   }
   else if(strParam.compare_ci("Unregister") == 0 || strParam.compare_ci("Unregserver") == 0)
   {

      m_ecommand = command_app_unregister;

   }
   else if(strParam.compare_ci("dde") == 0)
   {

      m_ecommand = command_file_dde;

   }
   else if(strParam.compare_ci("Embedding") == 0)
   {

      m_bRunEmbedded = true;

      m_bShowSplash = false;

   }
   else if(strParam.compare_ci("Automation") == 0)
   {

      m_bRunAutomated = true;

      m_bShowSplash = false;

   }

}


void command_line::ParseParamNotFlag(const string & strParam)
{

   if(m_varFile.is_empty())
   {

      m_varFile = strParam;

   }
   else if(m_ecommand == command_file_print_to && m_strPrinterName.is_empty())
   {

      m_varFile = strParam;

   }
   else if(m_ecommand == command_file_print_to && m_strDriverName.is_empty())
   {

      m_varFile = strParam;

   }
   else if(m_ecommand == command_file_print_to && m_strPortName.is_empty())
   {

      m_varFile = strParam;

   }

}

void command_line::ParseLast(bool bLast)
{

   if (bLast)
   {
      if(m_ecommand == command_file_new && !m_varFile.is_empty())
      {

         m_ecommand = command_file_open;

      }

      m_bShowSplash = !m_bRunEmbedded && !m_bRunAutomated;

   }

}


//command_line & command_line::operator = (const command_line & info)
//{
//
//   m_bShowSplash     = info.m_bShowSplash;
//   m_bRunEmbedded    = info.m_bRunEmbedded;
//   m_bRunAutomated   = info.m_bRunAutomated;
//   m_varFile         = info.m_varFile;
//   m_strPrinterName  = info.m_strPrinterName;
//   m_strPortName     = info.m_strPortName;
//
//   return *this;
//
//}


void command_line::_001ParseCommandLine(const string & strCommandLine)
{

   m_strCommandLine = strCommandLine;

   m_varQuery.propset()._008Parse(true, strCommandLine,m_varFile, m_strExe);

   if(!m_varFile.is_empty())
   {

      m_ecommand = command_line::command_file_open;

   }

   if(m_varQuery.has_property("uri"))
   {

      if(m_varFile.has_char())
      {

         m_varFile += ";";

         m_varFile += m_varQuery["uri"];

      }
      else
      {

         m_varFile = m_varQuery["uri"];

      }

      if(m_ecommand == command_line::command_file_new)
      {

         m_ecommand = command_line::command_file_open;

      }

   }

   if(m_ecommand == command_line::command_file_open)
   {

      m_varQuery["show_platform"] = 1;

   }

   if(m_varQuery.propset().has_property("app"))
   {

      m_strApp = m_varQuery.propset()["app"];

   }

   if(m_strApp == "session" && m_varQuery.propset().has_property("session_start"))
   {

      m_strApp = m_varQuery.propset()["session_start"];

   }

   if(m_varQuery.propset().has_property("app_type"))
   {

      m_strAppType = m_varQuery.propset()["app_type"];

   }

   if (!m_varQuery.propset().has_property("build") || m_varQuery["build"].is_empty())
   {

      if (file_exists(pacmedir->system() / "config\\plugin\\build.txt"))
      {

         string str = file_as_string(pacmedir->system() / "config\\plugin\\build.txt");

         m_varQuery["build"] = str;

      }

   }

}


void command_line::_001ParseCommandLineUri(const string & strCommandLine)
{

   m_strCommandLine = strCommandLine;

   ::exception::throw_not_implemented();

}

void command_line::_001ParseCommandFork(const string & strCommandFork)
{

   m_strCommandLine = strCommandFork;

   m_varQuery.propset()._008ParseCommandFork(strCommandFork,m_varFile,m_strExe);

   if(!m_varFile.is_empty())
   {

      m_ecommand = command_line::command_file_open;

   }

   if(m_varQuery.has_property("uri"))
   {

      if(m_varFile.has_char())
      {

         m_varFile += ";";

         m_varFile += m_varQuery["uri"];

      }
      else
      {

         m_varFile = m_varQuery["uri"];

      }

      if(m_ecommand == command_line::command_file_new)
      {

         m_ecommand = command_line::command_file_open;

      }

   }

   if(m_ecommand == command_line::command_file_open)
   {

      m_varQuery["show_platform"] = 1;

   }



   if(m_varQuery.propset().has_property("app"))
   {

      m_strApp = m_varQuery.propset()["app"];

   }

   if(m_strApp == "session" && m_varQuery.propset().has_property("session_start"))
   {

      m_strApp = m_varQuery.propset()["session_start"];

   }

   if(m_varQuery.propset().has_property("app_type"))
   {

      m_strAppType = m_varQuery.propset()["app_type"];

   }

   //      m_pthreadParent->consolidate(this);

}



void command_line::_001ParseCommandForkUri(const string & strCommandFork)
{

   string strQuery(strCommandFork);

   strsize iFind = strQuery.find('?');

   if(iFind < 0)
      strQuery = "";
   else
      strQuery = strQuery.Mid(iFind + 1);

   string strScript(strCommandFork);

   strsize iPos = strScript.find("://");

   if(iPos >= 0)
   {

      iPos += 3;

      strsize iStart = strScript.find("/",iPos);

      if(iStart < 0)
         strScript= "/";
      else
         strScript= strScript.Mid(iStart);

   }

   iFind = strScript.find('?');

   if(iFind >= 0)
      strScript = strScript.Left(iFind);

   m_varQuery.propset().parse_url_query(strQuery);

   m_strApp = strScript;

   if(m_varQuery.has_property("file"))
   {

      m_varFile = m_varQuery["file"];

   }

}


//command_line_pointer::command_line_pointer()
//{
//
//}
//
//
//command_line_pointer::command_line_pointer(const ::acme::allocatorsp & allocer) :
//   pointer < command_line > (allocer)
//{
//
//}




