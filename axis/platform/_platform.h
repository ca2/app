#pragma once




#undef SYSTEM_TYPE
#undef SESSION_TYPE
#undef APP_TYPE

#define SYSTEM_TYPE ::axis::system
#define SESSION_TYPE ::axis::session
#define APP_TYPE ::axis::application
//
//#undef Sys
//#define Sys(pobject) (*(::get_context_system(pobject))->cast < SYSTEM_TYPE >())
//
//#undef Sess
//#define Sess(pobject) (*(::get_context_session(pobject))->cast < SESSION_TYPE >())
//
//#undef App
//#define App(pobject) (*(::get_context_application(pobject))->cast < APP_TYPE >())
//



namespace axis
{

   //class run_start_installer;

   CLASS_DECL_AXIS bool init_core();

   CLASS_DECL_AXIS bool term_core();


} // namespace axis


CLASS_DECL_AXIS int get_core_init();
//extern "C"
//CLASS_DECL_AXIS int_bool defer_aura_init();
//extern "C"
//CLASS_DECL_AXIS int_bool defer_aura_term();


namespace axis
{


   //static_start g_staticstart;
   //{


   //   CLASS_DECL_AXIS void init(void);

   //   CLASS_DECL_AXIS void term(void);


   //} // namespace static_start


} // namespace axis







class task;




#pragma warning(disable: 4250)


class stdio_file;
struct memory_state;



