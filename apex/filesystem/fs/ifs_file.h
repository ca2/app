#pragma once


#include "apex/networking/sockets/http_batch_buffer.h"
#include "acme/primitive/primitive/payload.h"


class CLASS_DECL_APEX ifs_file :
   virtual public ::sockets::http_batch_buffer,
   virtual public ::particle
{
public:


   ::memory_file_pointer            m_phttpfile;
   ::memory_file_pointer            m_pmemfile;
   ::payload                        m_payloadFile;


   ifs_file(::payload payloadFile);
   ~ifs_file() override;

   using ::sockets::http_batch_buffer::read;
   virtual memsize read(void *pdata, memsize nCount) override;

   using ::sockets::http_batch_buffer::write;
   virtual void write(const void * pdata, memsize nCount) override;


   filesize translate(filesize offset, ::enum_seek eseek) override;

   virtual filesize get_size() const override;

   virtual void get_file_data() override;
   virtual void set_file_data() override;


};


