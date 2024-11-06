// Created by camilo on 2022-11-02 05:06 <3ThomasBorregaardSorensen!!
#pragma once


struct use_t {};
struct transfer_t {};
struct allocate_t {};
struct function_t {};
struct continuation_t {};

struct sequence_t {};


template < ::collection::count t_iSize >
struct sequence_size_t
{
   inline static const ::collection::count sequence_size = t_iSize;
};


struct pointer_type_t{};
struct enum_type_t {};
struct raw_type_t {};


struct i32_sz
{

   int                m_i;
   const char *         m_psz;

};


union message_union
{

   void* m_p;
   ::message::particle* m_pparticle;
   ::message::key* m_pkey;
   ::message::mouse* m_pmouse;
   ::message::context_menu* m_pcontextmenu;

};


struct now_t {};
struct infinite_t {};
struct zero_t {};



