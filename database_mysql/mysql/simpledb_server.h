#pragma once


namespace simpledb
{

   class CLASS_DECL_AURA server :
      virtual public ::object
   {
   public:


      base *     m_pbase;


      server(::particle * pparticle);
      virtual ~server();

      
      virtual bool open(const ::scoped_string & scopedstrDatabase);
      virtual bool close();


      virtual bool sql(const ::scoped_string & scopedstrQuery, ::payload & payload);
      

   };


} // namespace simpledb


