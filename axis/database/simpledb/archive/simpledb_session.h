#pragma once


namespace simpledb
{

   class server;

   class CLASS_DECL_CORE session :
      virtual public ::object
   {
   public:


      server *       m_pserver;

      session(::particle * pparticle);
      virtual ~session();


      virtual bool open(const ::scoped_string & scopedstrDatabase);
      virtual bool close();


      virtual bool query(const ::scoped_string & scopedstrQuery, ::payload & payload);


   };


} // namespace simpledb


