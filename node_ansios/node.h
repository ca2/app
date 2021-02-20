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
      virtual public ::acme::node
   {
   public:


      //gpointer m_pGtkSettingsDefault;
      string   m_strTheme;

      node();
      virtual ~node();

      virtual ::color::color get_system_color(enum_system_color esystemcolor) override;

      virtual int node_init_check(int * pi, char *** ppz) override;

      virtual void os_application_system_run() override;

      virtual ::e_status initialize(::layered * pobjectContext) override;

      virtual ::e_status get_system_time(system_time_t * psystemtime) override;

      virtual double get_time_zone();

      virtual time_t system_time_to_time(const system_time_t & st, i32 nDST = -1);

      virtual time_t file_time_to_time(const filetime & ft, i32 nDST = -1);

      virtual system_time_t time_to_system_time(const ::datetime::time & time);

      virtual ::e_status get_system_time_as_file_time(filetime * pfiletime);

      virtual ::e_status system_time_to_tm(tm * ptm, const system_time_t * psystemtime);

      virtual ::e_status tm_to_system_time(system_time_t * psystemtime, const tm * ptm);

      virtual ::e_status system_time_to_file_time(filetime * pfiletime, const system_time_t * psystemtime);

      virtual ::e_status file_time_to_system_time(system_time_t * psystemtime, const filetime * pfiletime);

      virtual ::e_status file_time_to_local_file_time(filetime * pfiletimeLocal, const filetime * pfiletime);

      virtual ::e_status is_valid_filetime(const filetime & filetime);

      virtual filetime get_filetime_now();


   };


} // namespace node_ansios




