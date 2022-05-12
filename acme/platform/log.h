// Created by camilo on 2021-07-17 23:24 BRT <3ThomasBorregaardSørensen!!
#pragma once


class logger :
   virtual public ::object
{
public:

   
   static void t_construct(class ::system * psystem);
   static void t_release();


   virtual void print(enum_trace_level etracelevel, enum_trace_category etracecategory, const char * pszFunction, const char * pszFile, int iLine, const char * psz) = 0;


};


class CLASS_DECL_ACME log :
   virtual public ::logger
{
public:


   bool                       m_bLog : 1;
   bool                       m_bExtendedLog : 1;
   bool                       m_bLogFileName : 1;
   bool                       m_bLogFunctionName : 1;
   bool                       m_bLogThreadName : 1;


   log();
   ~log() override;


   void initialize(::object* pobject) override;
   

   virtual void initialize_log(enum_trace_level etracelevelMin, const ::atom& atom);


   virtual void process_init();

   virtual void set_extended_log(bool bSet = true);
   virtual bool get_extended_log();



};


CLASS_DECL_ACME void set_verbose_log(bool bVerbose);


CLASS_DECL_ACME bool is_verbose_log();



