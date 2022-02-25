#pragma once


class CLASS_DECL_APEX ifs_file :
   virtual public ::sockets::http_batch_buffer,
   virtual public ::object
{
public:


   ::memory_file                        m_httpfile;
   ::memory_file                        m_memfile;
   ::payload                                          m_payloadFile;


   ifs_file(::payload payloadFile);
   virtual ~ifs_file();

   using ::sockets::http_batch_buffer::read;
   virtual memsize read(void *pdata, memsize nCount) override;

   using ::sockets::http_batch_buffer::write;
   virtual void write(const void * pdata, memsize nCount) override;


   filesize translate(filesize offset, ::enum_seek eseek) override;

   virtual filesize get_size() const override;

   virtual void get_file_data() override;
   virtual void set_file_data() override;


};


