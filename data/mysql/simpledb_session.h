#pragma once


namespace simpledb
{

   class server;

   class CLASS_DECL_AURA session :
      virtual public ::object
   {
   public:


      server *       m_pserver;

      session(::object * pobject);
      virtual ~session_parent;


      virtual bool open(const char * pszDatabase);
      virtual bool close();


      virtual bool query(const char * pszQuery, ::payload & payload);


   };


} // namespace simpledb


