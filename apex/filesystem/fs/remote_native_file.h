#pragma once


#include "apex/networking/sockets/http_batch_buffer.h"
//#include "acme/prototype/prototype/payload.h"


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
      memsize read(void * p, ::memsize s) override;

      
      using ::sockets::http_batch_buffer::write;
      void write(const void * p, ::memsize s) override;


      void seek(filesize lOff, ::enum_seek eseek);

      filesize size() const override;

      void get_file_data() override;
      void set_file_data() override;


   };


} // namespace fs




