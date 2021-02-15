//
// Created by camilo on 19/01/2021. <33TBS!!
//

//
// Created by camilo on 19/01/2021. <3-<3ThomasBS!!
//
#pragma once


namespace node_ansios
{


   class CLASS_DECL_ACME node :
      virtual public ::aura::node
   {
   public:


      gpointer m_pGtkSettingsDefault;
      string   m_strTheme;

      node();
      virtual ~node();



      virtual ::color::color get_system_color(enum_system_color esystemcolor) override;


      virtual int node_init_check(int * pi, char *** ppz) override;

      virtual void os_application_system_run() override;

      virtual ::e_status initialize(::layered * pobjectContext) override;

      using ::aura::node::node_fork;

      virtual void node_fork(const ::promise::routine & routine) override;

      virtual void node_post_quit() override;

      virtual ::linux::appindicator * appindicator_allocate() override;

      virtual void os_post_quit() override;

      virtual bool should_launch_on_node(::promise::subject * psubject);

      virtual bool launch_on_node(::promise::subject * psubject);

      virtual void get_system_time_as_file_time(filetime_t * pfiletime);

      virtual time_t system_time_to_time(const system_time_t &systemtime, i32 nDST) override;

      virtual system_time_t time_to_system_time(const ::datetime::time & time) override;

   };


} // namespace node_ansios




