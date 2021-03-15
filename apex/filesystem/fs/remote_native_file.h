#pragma once


namespace fs
{


   class CLASS_DECL_APEX remote_native_file : 
      virtual public ::sockets::http_batch_buffer,
      virtual public ::context_object
   {
   public:


      ::memory_file            m_httpfile;
      ::memory_file            m_memfile;
      ::payload                              m_varFile;


      remote_native_file(::payload varFile);
      virtual ~remote_native_file();

      using ::sockets::http_batch_buffer::read;
      virtual memsize read(void *pdata, memsize nCount);

      
      using ::sockets::http_batch_buffer::write;
      virtual void write(const void * pdata, memsize nCount);


      filesize seek(filesize lOff, ::file::e_seek  nFrom);

      virtual filesize get_size() const;

      virtual void get_file_data();
      virtual void set_file_data();


   };


} // namespace fs




