#pragma once


#include "mail_pop3.h"


namespace mail
{


   class pop3_socket;


   class CLASS_DECL_SPHERE simple_pop3 :
      virtual public pop3
   {
   public:


      string                  m_strUser;
      string                  m_strPass;
      string                  m_strHost;
      string                  m_strTransaction;

      i32                     m_iStatCount;
      i32                     m_iStatSize;

      i32                     m_iListSize;


      simple_pop3(::particle * pparticle);


      virtual string get_user();
      virtual string get_pass();
      virtual string get_host();
      virtual string get_transaction();

      virtual void set_stat_count(i32 iCount);
      virtual void set_stat_size(i32 iSize);

      virtual void set_list_size(i32 iSize);

      void store();

   };


}




