// Created by camilo on 2023-11-23 04:50 <3ThomasBorregaardSorensen!!
#pragma once


class CLASS_DECL_ACME tracing :
   virtual public ::particle
{
public:


   tracing();
   ~tracing() override;


   //::trace_statement log_statement()
   //{

   //   return ::transfer(trace_statement(tracer())((::particle *)nullptr));

   //}


   //::trace_statement information()
   //{

   //   return ::transfer(trace_statement(tracer())(e_trace_level_information));

   //}


   //::trace_statement warning()
   //{

   //   return ::transfer(trace_statement(tracer())(e_trace_level_warning));

   //}


   //::trace_statement error()
   //{

   //   return ::transfer(trace_statement(tracer())(e_trace_level_error));

   //}


   //::trace_statement fatal()
   //{

   //   return ::transfer(trace_statement(tracer())(e_trace_level_fatal));

   //}


   //void informationf(const_char_pointer pszFormat, ...)
   //{

   //   va_list arguments;

   //   va_start(arguments, pszFormat);

   //   {

   //      auto statement = log_statement();

   //      statement(e_trace_level_information);

   //      statement.formatf_output_arguments(scopedstrFormat, arguments);

   //   }

   //   va_end(arguments);

   //}


   //void warningf(const_char_pointer pszFormat, ...)
   //{

   //   va_list arguments;

   //   va_start(arguments, pszFormat);

   //   {

   //      auto statement = log_statement();

   //      statement(e_trace_level_warning);

   //      statement.formatf_output_arguments(scopedstrFormat, arguments);

   //   }

   //   va_end(arguments);

   //}


   //void errorf(const_char_pointer pszFormat, ...)
   //{

   //   va_list arguments;

   //   va_start(arguments, pszFormat);

   //   {

   //      auto statement = log_statement();

   //      statement(e_trace_level_error);

   //      statement.formatf_output_arguments(scopedstrFormat, arguments);

   //   }

   //   va_end(arguments);

   //}


   //void fatalf(const_char_pointer pszFormat, ...)
   //{

   //   va_list arguments;

   //   va_start(arguments, pszFormat);

   //   {

   //      auto statement = log_statement();

   //      statement(e_trace_level_fatal);

   //      statement.formatf_output_arguments(scopedstrFormat, arguments);

   //   }

   //   va_end(arguments);

   //}


   void trace_last_error();


};



