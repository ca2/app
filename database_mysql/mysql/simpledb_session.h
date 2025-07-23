#pragma once


namespace simpledb
{

   class server;

   class CLASS_DECL_AURA session :
      virtual public ::object
   {
   public:


      server *       m_pserver;

      session(::particle * pparticle);
      virtual ~session_parent;


      virtual bool open(const ::string & pszDatabase);
      virtual bool close();


      virtual bool query(const ::string & pszQuery, ::payload & payload);


   };


} // namespace simpledb


