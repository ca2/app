#pragma once


#include "sphere/net/mail/pop3_socket.h"


namespace mail
{


   class pop3_socket;


   class CLASS_DECL_SPHERE pop3 :
      virtual public ::object
   {
   public:


      ::pointer<::sockets::socket_handler>   m_phandler;
      ::pointer<pop3_socket>                 m_psocket;
      happening                            m_happeningFinish;

      string_array                          m_straIndex;
      string_array                          m_straId;

      string                           id();
      string                           m_strHeaders;
      string                           m_strBody;
      property_set                     m_setHeaders;

      int                              m_iHeaderLine;

      critical_section                 m_csDataset;


      pop3(::particle * pparticle);
      virtual ~pop3();


      virtual string get_user();
      virtual string get_pass();
      virtual string get_host();
      virtual string get_transaction();

      virtual void set_stat_count(int iCount);
      virtual void set_stat_size(int iSize);

      virtual void set_list_size(int iSize);




      virtual void update_lists();

      virtual void store();

      virtual void filter_id();

      virtual void     run() override;

      virtual void on_finished_transaction();

   };

}




