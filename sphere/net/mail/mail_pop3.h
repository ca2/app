#pragma once


#include "sphere/net/mail/pop3_socket.h"


namespace mail
{


   class pop3_socket;


   class CLASS_DECL_SPHERE pop3 :
      virtual public ::object
   {
   public:


      __pointer(::sockets::socket_handler)    m_phandler;
      __pointer(pop3_socket)                  m_psocket;
      event                            m_evFinish;

      string_array                          m_straIndex;
      string_array                          m_straId;

      string                           m_id;
      string                           m_strHeaders;
      string                           m_strBody;
      property_set                     m_setHeaders;

      i32                              m_iHeaderLine;

      critical_section                 m_csDataset;


      pop3(::object * pobject);
      virtual ~pop3();


      virtual string get_user();
      virtual string get_pass();
      virtual string get_host();
      virtual string get_transaction();

      virtual void set_stat_count(i32 iCount);
      virtual void set_stat_size(i32 iSize);

      virtual void set_list_size(i32 iSize);




      virtual void update_lists();

      virtual void store();

      virtual void filter_id();

      virtual void     run() override;

      virtual void on_finished_transaction();

   };

}




