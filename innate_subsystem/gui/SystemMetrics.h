// Created by camilo on 2026-04-07 08:46 <3ThomasBorregaardSørensen!!
#pragma once


#include "subsystem/_common_header.h"

namespace innate_subsystem
{

    class SystemMetricsInterface :
        virtual public ::particle_base
    {
    public:
        //virtual ~SystemMetricsInterface() = 0;


    virtual ::int_size get_small_icon_size_in_pixels() = 0;


    };



    class CLASS_DECL_INNATE_SUBSYSTEM SystemMetricsComposite :
        virtual public composite <SystemMetricsInterface>
    {
    public:


       implement_compositeø(SystemMetrics, systemmetrics)



        //SystemMetrics();
        //~SystemMetrics() override;


        ::int_size get_small_icon_size_in_pixels() override;


    };




   class CLASS_DECL_INNATE_SUBSYSTEM SystemMetrics:
       virtual public aggregate <SystemMetricsComposite>
   {
   public:

      implement_baseø(SystemMetrics);

   };

} // namespace innate_subsystem
