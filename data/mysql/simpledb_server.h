#pragma once


namespace simpledb
{

   class CLASS_DECL_AURA server :
      virtual public ::object
   {
   public:


      base *     m_pbase;


      server(::object * pobject);
      virtual ~server();

      
      virtual bool open(const ::string & pszDatabase);
      virtual bool close();


      virtual bool sql(const ::string & pszQuery, ::payload & payload);
      

   };


} // namespace simpledb


