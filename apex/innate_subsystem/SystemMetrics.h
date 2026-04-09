// Created by camilo on 2026-04-07 08:46 <3ThomasBorregaardSørensen!!
#pragma once


#include "acme/subsystem/_common_header.h"

namespace innate_subsystem
{

    class CLASS_DECL_APEX SystemMetricsInterface :
        virtual public ::subsystem::particle_interface<SystemMetricsInterface>
    {
    public:
        virtual ~SystemMetricsInterface() = 0;


    virtual ::int_size get_small_icon_size_in_pixels() = 0;


    };



    class CLASS_DECL_APEX SystemMetrics :
        virtual public ::subsystem::composite <SystemMetricsInterface>
    {
    public:

        SystemMetrics();
        ~SystemMetrics() override;


        ::int_size get_small_icon_size_in_pixels() override;


    };


} // namespace innate_subsystem
