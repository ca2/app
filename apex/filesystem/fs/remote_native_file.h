#pragma once


#include "apex/networking/sockets/http_batch_buffer.h"


namespace fs
{


   class CLASS_DECL_APEX remote_native_file : 
      virtual public ::sockets::http_batch_buffer
   {
   public:


      ::memory_file_pointer      m_phttpfile;
      ::memory_file_pointer      m_pmemfile;
      ::payload                  m_payloadFile;


      remote_native_file(::payload payloadFile);
      ~remote_native_file() override;

      using ::sockets::http_batch_buffer::read;
      virtual memsize read(void *pdata, memsize nCount);

      
      using ::sockets::http_batch_buffer::write;
      virtual void write(const void * pdata, memsize nCount);


      filesize seek(filesize lOff, ::enum_seek eseek);

      virtual filesize get_size() const;

      virtual void get_file_data();
      virtual void set_file_data();


   };


} // namespace fs




