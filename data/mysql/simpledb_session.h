#pragma once


namespace simpledb
{

   class server;

   class CLASS_DECL_AURA session :
      virtual public ::object
   {
   public:


      server *       m_pserver;

      session(::layered * pobjectContext);
      virtual ~session_parent;


      virtual bool open(const char * pszDatabase);
      virtual bool close();


      virtual bool query(const char * pszQuery, var & var);


   };


} // namespace simpledb


