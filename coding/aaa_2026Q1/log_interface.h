// From impact_interface.h Created 2024-05-01 03:43 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/constant/integration.h"


namespace coding
{


   class CLASS_DECL_CODING log_interface :
      virtual public ::matter
   {
   public:

      //enum_task                                    m_etask;
      int                                          m_iStatus1;
      ::collection::index                                 m_iIndex;
      ::collection::index                                 m_iStage;
      //::string_array                               m_straStage;
      //::numeric_array_base<::coding::enum_index>   m_eindexa;
      ::string_array                               m_straLog;
      //::pointer <::user::interaction>              m_puserinteraction;
      //::pointer <::coding::integration>       m_pintegration;
      //::pointer <::coding::task>              m_ptask;


      virtual void on_trace(enum_trace_level etracelevel, const ::scoped_string& scopedstrLine, bool bCarriage);

      virtual void defer_status(const ::scoped_string& scopedstrLine);

      virtual void on_lines_change();

      virtual ::user::interaction* userinteraction();


   };


} // namespace coding



