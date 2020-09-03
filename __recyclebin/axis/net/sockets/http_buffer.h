#pragma once


namespace sockets
{


   class CLASS_DECL_AXIS http_buffer :
      virtual public ::file::transfer_file
   {
   public:


      http_buffer(::object * pobject, ::mutex * pmutex = nullptr);
      http_buffer(::object * pobject, ::memory_file * pmemoryfileIn);
      virtual ~http_buffer();


      virtual ::status::result open(const ::file::path & pszFileName, UINT nOpenFlags);



      DECL_GEN_SIGNAL(on_http_request_response);


   };


} // namespace sockets




