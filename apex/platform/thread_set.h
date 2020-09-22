#pragma once


inline var & thread_value(const ::id & id);
inline void thread_set(const ::id & id) { thread_value(id) = true; }
inline void thread_unset(const ::id & id) { thread_value(id) = false; }
inline bool thread_is_set(const ::id & id);


template  < >
inline ::thread * default_keep_value < ::thread * >()
{

   return ::get_thread();

}
#define __keep_thread_flag(...) auto TOKEN_AT_LINE(__keep_thread_flag) = keep_thread_flag(__VA_ARGS__)
#define __keep_current_thread(...) auto TOKEN_AT_LINE(__keep_current_thread) = keep(__VA_ARGS__, ::get_thread())


class CLASS_DECL_APEX ___keep_thread_flag
{
public:


   bool m_bChanged;


   ::var &      m_varThread;


   ___keep_thread_flag(const ::id & id) :
      m_varThread(thread_value(id))
   {

      if ((bool) m_varThread)
      {

         m_bChanged = false;

      }
      else
      {

         m_varThread = true;

         m_bChanged = true;

      }

   }


   ~___keep_thread_flag()
   {

      if (m_bChanged)
      {

         m_varThread = false;

      }

   }


};



inline ___keep_thread_flag keep_thread_flag(const ::id & id)
{

   return id;

}

