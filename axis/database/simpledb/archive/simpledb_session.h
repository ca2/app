#pragma once


namespace simpledb
{

   class server;

   class CLASS_DECL_CORE session :
      virtual public ::object
   {
   public:


      server *       m_pserver;

      session(::object * pobject);
      virtual ~session();


      virtual bool open(const ::string & pszDatabase);
      virtual bool close();


      virtual bool query(const ::string & pszQuery, ::payload & payload);


   };


} // namespace simpledb


