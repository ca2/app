// Created by camilo on 2021-10-13 00:53 BRT <3ThomasBorregaardSørensen!!
#pragma once


class CLASS_DECL_ACME ___keep_task_flag
{
public:


   bool m_bOld;


   enum_task_flag       m_etaskflag;


   ___keep_task_flag(enum_task_flag etaskflag) :
      m_etaskflag(etaskflag),
      m_bOld(task_flag().is_set(etaskflag))
   {

   }


   ~___keep_task_flag()
   {

      task_flag().set(m_etaskflag, m_bOld);

   }


};


inline ___keep_task_flag keep_task_flag(enum_task_flag etaskflag)
{

   return etaskflag;

}


#define __keep_task_flag(...) auto TOKEN_AT_LINE(__keep_task_flag) = keep_task_flag(__VA_ARGS__)



