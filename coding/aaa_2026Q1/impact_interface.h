// From listener.h by camilo on 2022-09-17 00:13 <3ThomasBorregaardSørensen!!
#pragma once


#include "acme/constant/integration.h"
#include "_constant.h"


namespace coding
{


   class CLASS_DECL_CODING impact_interface :
      virtual public ::matter
   {
   public:


      enum_task                              m_etaskGroupDisplay;


      virtual void on_integrate_change() = 0;
      virtual void on_lines_change() = 0;
      virtual void enable_pulse(const ::scoped_string& scopedstr) = 0;
      virtual void set_topic_text(const ::scoped_string & scopedstr) = 0;
      virtual void set_topic_text2(const ::scoped_string& scopedstr) = 0;
      virtual void on_start_task_group(enum_task etaskGroup);
      virtual void defer_select_sequential_task_ordinal(enum_task etaskOrdinal);
      virtual void defer_select_main_impact();


   };


} // namespace coding



