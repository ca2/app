// Created by camilo on 2026-04-07 08:46 <3ThomasBorregaardSørensen!!
#pragma once


#include "subsystem/_common_header.h"

namespace innate_subsystem
{

    class SystemMetricsInterface :
        virtual public ::Particle
    {
    public:
        //virtual ~SystemMetricsInterface() = 0;


    virtual ::int_size get_small_icon_size_in_pixels() = 0;


    };



    class CLASS_DECL_INNATE_SUBSYSTEM SystemMetricsComposite :
        virtual public Composite <SystemMetricsInterface>
    {
    public:


       ImplementCompositeø(SystemMetrics, systemmetrics)



        //SystemMetrics();
        //~SystemMetrics() override;


          ::int_size get_small_icon_size_in_pixels() override
       {
          return m_psystemmetrics->get_small_icon_size_in_pixels();
       }


    };




   class CLASS_DECL_INNATE_SUBSYSTEM SystemMetricsAggregate:
       virtual public Aggregate <SystemMetricsComposite>
   {
   public:

      ImplementBaseø(SystemMetrics);

   };


   class CLASS_DECL_INNATE_SUBSYSTEM  SystemMetrics:
virtual public Object<SystemMetricsAggregate>
   {
   public:


   };


} // namespace innate_subsystem
