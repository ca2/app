#pragma once


#ifdef WINDOWS


class CLASS_DECL_ACME condition_variable
{
public:

#ifdef __REACTOS__

   struct state;
   state * m_pstate;

   condition_variable();
   ~condition_variable();

   condition_variable(const condition_variable &) = delete;
   condition_variable & operator=(const condition_variable &) = delete;

   bool wake_all();
   bool wait(unsigned long timeout);

#else


   ::i8 sz[32]; // I hope it is enough to hold CONDITION_VARIABLE

   typedef void WINDOWS_API construct(void *);

   static construct * s_pconstruct;

   
   condition_variable() { s_pconstruct(this); }

#endif


};


#endif



