// Created by camilo on 2022-11-02 05:06 <3ThomasBorregaardSorensen!!
// From acid by camilo on 2024-05-22 11:16 <3ThomasBorregaardSorensen!!


struct use_t {};
struct transfer_t {};
struct allocate_t {};
struct function_t {};


struct i32_sz
{

   ::i32                m_i;
   const char * m_psz;

};


struct now_t {};
struct infinite_t {};
struct zero_t {};





union message_union
{

   void* m_p;
   ::message::particle* m_pparticle;
   ::message::key* m_pkey;
   ::message::mouse* m_pmouse;
   ::message::context_menu* m_pcontextmenu;

};




