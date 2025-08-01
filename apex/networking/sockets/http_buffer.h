#pragma once


namespace sockets
{


   class CLASS_DECL_APEX http_buffer :
      virtual public ::file::transfer_file
   {
   public:


      http_buffer(::particle * pparticle, ::pointer< ::mutex > pmutex = nullptr);
      http_buffer(::particle * pparticle, ::memory_file * pmemoryfileIn);
      virtual ~http_buffer();


      virtual ::extended::status open(const ::file::path & pathFileName, unsigned int nOpenFlags);



      DECLARE_MESSAGE_HANDLER(on_http_request_response);


   };


} // namespace sockets




