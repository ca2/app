#pragma once



//typedef unsigned int unsigned int;


//CLASS_DECL_ACME unsigned long long translate_processor_affinity(int iOrder);


// CLASS_DECL_ACME unsigned int thread_alloc(void);
// CLASS_DECL_ACME int_bool thread_free(unsigned int dwIndex);
// CLASS_DECL_ACME void * thread_get_data(unsigned int dwIndex);
// CLASS_DECL_ACME int_bool thread_set_data(unsigned int dwIndex,void * pTlsValue);

// CLASS_DECL_ACME void thread_shutdown(void);



CLASS_DECL_ACME void set_main_htask(htask htask);
CLASS_DECL_ACME void set_main_itask(itask itask);
CLASS_DECL_ACME htask main_htask();
CLASS_DECL_ACME itask main_itask();



class CLASS_DECL_ACME os_task_init_term
{
public:


   //static thread_local thread_local_particle * t_pthreadlocalparticleList;


   os_task_init_term();

   ~os_task_init_term();


};



