#pragma once


#ifdef WINDOWS


class CLASS_DECL_ACME condition_variable
{
public:


   char sz[32]; // I hope it is enough to hold CONDITION_VARIABLE

   typedef void WINDOWS_API construct(void *);

   static construct * s_pconstruct;

   
   condition_variable() { s_pconstruct(this); }


};


#endif



