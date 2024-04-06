// Created by camilo on 2021-07-17 23:24 BRT <3ThomasBorregaardSorensen!!
#pragma once


////#include "acme/primitive/primitive/object.h"


class logger :
   virtual public ::object
{
public:


   enum_trace_level     m_etracelevelMinimum = e_trace_level_none;

   
   static void t_construct(::acme::context * pcontext);
   static void t_release();


   virtual void print(::trace_statement & tracestatement, bool bFlush) = 0;


};


class CLASS_DECL_ACME log :
   virtual public ::logger
{
public:


   bool                       m_bLog;
   bool                       m_bExtendedLog;
   bool                       m_bLogFileName;
   bool                       m_bLogFunctionName;
   bool                       m_bLogThreadName;


   log();
   ~log() override;


   void initialize(::particle * pparticle) override;
   

   virtual void initialize_log(enum_trace_level etracelevelMin, const ::atom& atom);


   virtual void process_init();

   virtual void set_extended_log(bool bSet = true);
   virtual bool get_extended_log();



};





