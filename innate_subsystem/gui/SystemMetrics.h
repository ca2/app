// Created by camilo on 2026-04-07 08:46 <3ThomasBorregaardSørensen!!
#pragma once


#include "subsystem/_common_header.h"

namespace innate_subsystem
{

    class SystemMetricsInterface :
        virtual public particle_interface<SystemMetricsInterface>
    {
    public:
        //virtual ~SystemMetricsInterface() = 0;


    virtual ::int_size get_small_icon_size_in_pixels() = 0;


    };



    class CLASS_DECL_INNATE_SUBSYSTEM SystemMetrics :
        virtual public composite <SystemMetricsInterface>
    {
    public:

        SystemMetrics();
        ~SystemMetrics() override;


        ::int_size get_small_icon_size_in_pixels() override;


    };


} // namespace innate_subsystem
