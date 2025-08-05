#pragma once





//#ifdef WINDOWS
//
//interface ID2D1DeviceContext;
//
//#endif

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
   class impact;


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
   //class pane_tab_impact;


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
   class split_impact;

   class combo_box;
   class list_box;


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





namespace berg
{

   //class run_start_installer;

   CLASS_DECL_BERG bool init_core();

   CLASS_DECL_BERG bool term_core();


} // namespace berg


CLASS_DECL_BERG int get_core_init();
//extern "C"
//CLASS_DECL_BERG int_bool defer_aura_init();
//extern "C"
//CLASS_DECL_BERG int_bool defer_aura_term();


namespace berg
{


   //static_start g_staticstart;
   //{


   //   CLASS_DECL_BERG void init(void);

   //   CLASS_DECL_BERG void term(void);


   //} // namespace static_start


} // namespace berg







class task;




#pragma warning(disable: 4250)


class stdio_file;
struct memory_state;


