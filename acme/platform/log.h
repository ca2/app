// Created by camilo on 2021-07-17 23:24 BRT <3ThomasBorregaardS�rensen!!
#pragma once


//namespace trace
//{

         //static thread_local logger * t_plogger;

         //namespace acme
         //{

class logger :
   virtual public ::object
{
public:

   
   static void t_construct(class ::system * psystem);
   static void t_release();


   virtual void print(enum_trace_level etracelevel, enum_trace_category etracecategory, const char * pszFunction, const char * pszFile, int iLine, const char * psz) = 0;


};


//::logger & log() { return *(::logger::t_plogger ? ::logger::t_plogger : ::logger::create()); }



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


      //virtual void print(const char* pszFormat, ...);
      //virtual void print_v(const char* pszFormat, va_list valist);

      
      virtual void process_init();

      virtual void set_extended_log(bool bSet = true);
      virtual bool get_extended_log();



   };


//} // namespace trace
//
//
//
