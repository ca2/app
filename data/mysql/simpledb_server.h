#pragma once


namespace simpledb
{

   class CLASS_DECL_AURA server :
      virtual public ::object
   {
   public:


      base *     m_pbase;


      server(::layered * pobjectContext);
      virtual ~server();

      
      virtual bool open(const char * pszDatabase);
      virtual bool close();


      virtual bool sql(const char * pszQuery, ::payload & payload);
      

   };


} // namespace simpledb


