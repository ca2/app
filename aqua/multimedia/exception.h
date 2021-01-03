#pragma once


namespace multimedia
{


   enum e_exception
   {

      exception_undefined,
      exception_multimedia,
      exception_midi,
      exception_music,

   };


   class CLASS_DECL_AQUA exception :
      public ::exception::exception
   {
   public:


      e_exception          m_eexception;


      exception(e_exception eexception = exception_undefined, const ::e_status & estatus = error_exception, const char * pszMessage = nullptr);
      virtual ~exception();


      virtual string get_message() const override;


   };


} // namespace multimedia



