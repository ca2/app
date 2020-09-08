#pragma once


namespace file
{


   class CLASS_DECL_APEX file_stream:
      virtual public stream
   {
   public:


      file_stream();
      file_stream(const char * pszFileName,u32 nOpenFlags,::aura::application * papp = ::get_context_application());

      file_stream(file * preader);
//      file_stream(const file_stream & preader);
      virtual ~file_stream();


      void open(const ::file::path & pszFileName,u32 nOpenFlags,::aura::application * papp = ::get_context_application());



   };


} // namespace file


