#pragma once


namespace aura
{


   class command_line;


} // namespace aura


class db_server;


namespace simpledb
{


   class CLASS_DECL_AURA simpledb :
      virtual public ::acme::department,
      virtual public ::database::database
   {
   public:


      db_server   *  m_pserver;


      simpledb(::particle * pparticle);
      virtual ~simpledb();

      virtual bool init2();
      virtual bool initialize();
      virtual bool destroy();

      virtual ::database::server * get_data_server();
      virtual db_server & db();

      virtual void on_set_locale(const ::scoped_string & scopedstr, const ::action_context & action_context);
      virtual void on_set_schema(const ::scoped_string & scopedstr, const ::action_context & action_context);


      virtual bool InitializeDataCentral();
      virtual bool FinalizeDataCentral();

      virtual bool set_keyboard_layout(const ::scoped_string & scopedstrPath, const ::action_context & action_context);
      virtual void on_set_keyboard_layout(const ::scoped_string & scopedstrPath, const ::action_context & action_context);

   };


} // namespace simpledb






