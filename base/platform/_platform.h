#pragma once




class image_list;


#ifdef WINDOWS

interface ID2D1DeviceContext;

#endif

namespace user
{

   class printer;
   //class tree;
   class form;
   class single_document_template;
   class main_frame;



} // namespace user


namespace experience
{

   class frame_window;

} // namespace experience


class service_base;


namespace bergedge
{


   class document;
   class view;


} // namespace bergedge


namespace filehandler
{


   class handler;


} // namespace filehandler


namespace html
{


   class html_ex;


} // namespace html


namespace userfs
{

   
   class userfs;


} // namespace userfs


namespace userex
{


   class userex;
   //class pane_tab_view;


} // namespace userex


namespace filemanager
{


   class document;
   class data;
   //class filemanager;


} // namespace filemanager


namespace user
{


   class impact_data;
   class form_callback;
   class split_view;

   class combo_box;
   class combo_list;


} // namespace user





namespace dynamic_source
{


   class script;
   class script_manager;


} // namespace dynamic_source




//
//
//#define SYSTEM_TYPE ::base::system
//#define SESSION_TYPE ::base::session
//#define APP_TYPE ::base::application

#undef Sys
#define Sys(pobject) (*(::get_context_system(pobject))->m_pbasesystem)

#undef Sess
#define Sess(pobject) (*(::get_context_session(pobject))->m_pbasesession)

#undef App
#define App(pobject) (*(::get_context_application(pobject))->m_pbaseapplication)




namespace base
{

   //class run_start_installer;

   CLASS_DECL_BASE bool init_core();

   CLASS_DECL_BASE bool term_core();


} // namespace base


CLASS_DECL_BASE int get_core_init();
//extern "C"
//CLASS_DECL_BASE int_bool defer_aura_init();
//extern "C"
//CLASS_DECL_BASE int_bool defer_aura_term();


namespace base
{


   //static_start g_staticstart;
   //{


   //   CLASS_DECL_BASE void init(void);

   //   CLASS_DECL_BASE void term(void);


   //} // namespace static_start


} // namespace base







class task;




#pragma warning(disable: 4250)


class stdio_file;
struct memory_state;


