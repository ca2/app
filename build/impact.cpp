#include "framework.h"
//#include "aura/update.h"
#include "acme/filesystem/filesystem/acme_directory.h"
#include "acme/operating_system.h"

namespace app_core_build
{


   impact::impact()
   {

      m_straLine.add("app_core_build");
      m_straLine.add("The build log follows...");

   }


   impact::~impact()
   {

   }


#ifdef _DEBUG

   void impact::assert_ok() const
   {

      ::user::impact::assert_ok();

   }

   void impact::dump(dump_context& dumpcontext) const
   {

      ::user::impact::dump(dumpcontext);

   }

#endif //_DEBUG


   void impact::handle(::topic* ptopic, ::context* pcontext)
   {

      ::user::impact::handle(ptopic, pcontext);

   }



   void impact::install_message_routing(::channel* pchannel)
   {

      ::user::impact::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_create, pchannel, this, &impact::on_message_create);

   }


   void impact::on_message_create(::message::message* pmessage)
   {

      ::pointer<::message::create>pcreate(pmessage);

      pcreate->previous();

      if (pcreate->m_bRet)
      {

         return;

      }

      __defer_construct(m_pbuild);

      m_pbuild->branch();

      //fork([this]()
        // {

          //  prepare();
            //build();

         //});

   }


//   void impact::prepare()
//   {
//
//#ifdef WINDOWS
//
//      prepare_windows()
//
//#elif defined(LINUX)
//
//      prepare_linux();
//
//#else
//
//      throw ::not_implemented();
//
//#endif
//
//   }
//


#ifdef WINDOWS

   void impact::prepare_windows()
   {
   

      string      strBuildCmd = "\"C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Auxiliary/Build/vcvars64.bat\"";

   

   ::operating_system::process_pointer process(e_create, this);

   ::file::path pathEnvTxt;

   auto pacmedirectory = m_psystem->m_pacmedirectory;

   pathEnvTxt = pacmedirectory->system() / "env.txt";

   m_psystem->m_pacmefile->put_contents(pacmedirectory->system() / "env1.bat", pacmedirectory->system() / "env.bat > \"" + pathEnvTxt + "\"");

   m_psystem->m_pacmefile->put_contents(pacmedirectory->system() / "env.bat", "@call " + strBuildCmd + "\r\n@set");

   auto psystem = m_psystem;

   auto pnode = psystem->node();

   pnode->run_silent(pacmedirectory->system() / "env1.bat", "");

   string strLog = m_psystem->m_pacmefile->as_string(pacmedirectory->system() / "env.txt");
   string_array stra;
   stra.add_lines(strLog);

   //sleep(10000_ms);

   property_set setEnvironment;

   setEnvironment.parse_environment_variable(stra);

   for (auto& pproperty : setEnvironment)
   {

      SetEnvironmentVariableW(wstring(pproperty->m_atom), wstring(pproperty->string()));

   }


   }

#endif


//   void impact::build()
//   {
//
//      bool bTimeout = false;
//
//      ::operating_system::process_pointer process(e_create, this);
//
//      ::parallelization::set_priority(::e_priority_highest);
//
//      //process->prop("inherit") = false;
//
//      string strCompiler = "msbuild \"C:/basis/operating-system/operating-system-windows/_seed/basic.sln\" -p:Configuration=basis;Platform=x64";
//
//      m_straLine.add(strCompiler);
//
//      process->create_child_process(strCompiler, true, "C:\\basis\\source", ::e_priority_highest);
//
//      //::system(str + " > " + "\"" + strClog + "\"");
//
//      auto tickStart = ::duration::now();
//
//      string strLog;
//
//      while (::task_get_run())
//      {
//
//         string strRead = process->read();
//
//         write_log(strRead);
//
//         if (process->has_exited())
//            break;
//
//         preempt(100_ms);
//
//         if (tickStart.elapsed() > 890_s) // 14 minutes
//         {
//
//            bTimeout = true;
//
//            break;
//
//         }
//
//      }
//
//      string strRead = process->read();
//
//      write_log(strRead);
//
//   }


   void impact::_001OnDraw(::draw2d::graphics_pointer& pgraphics)
   {

      auto rectangleClient = get_client_rect();

      pgraphics->fill_rectangle(rectangleClient, argb(127, 255, 255, 255));


      string_array straLine;

      m_pcontext->m_papexcontext->file().get_lines(straLine, m_psystem->m_pacmedirectory->home() /"build.log");

      ::point_i32 p;

      p.x = 10;

      p.y = rectangleClient.height();

      pgraphics->set_text_color(argb(255,89, 89, 89));
      if (straLine.has_element())
      {

         for (int i = straLine.get_upper_bound(); i>= 0 && p.y >= 0; i--)
         {
            p.y -= 20;

            pgraphics->text_out(p, straLine[i]);

         }

      }

   }


} // namespace app_core_build



