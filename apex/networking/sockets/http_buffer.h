#pragma once


namespace sockets
{


   class CLASS_DECL_APEX http_buffer :
      virtual public ::file::transfer_file
   {
   public:


      http_buffer(::object * pobject, ::mutex * pmutex = nullptr);
      http_buffer(::object * pobject, ::memory_file * pmemoryfileIn);
      virtual ~http_buffer();


      virtual ::extended::status open(const ::file::path & pszFileName, ::u32 nOpenFlags);



      DECLARE_MESSAGE_HANDLER(on_http_request_response);


   };


} // namespace sockets




