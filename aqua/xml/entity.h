#pragma once



//#include "acme/prototype/collection/array.h"


namespace xml
{

   
   class CLASS_DECL_AQUA entity
   {
   public:

      
      char     m_chEntity;      // entity ( & " ' < > )
      string   m_strRef;      // entity object ( &amp; &quot; etc )
      int      m_iRefLen;      // entity object length

      
      entity();
      entity(char chEntity, const_char_pointer  pszReference);
      entity(const entity & entity);
      entity & operator = (const entity & entity);
      
      
   };

   
   class CLASS_DECL_AQUA entities :
	   public ::array < entity >
   {
   public:
   
      
      entity * get_entity( int entity );
      entity * get_entity(const_char_pointer  pszEntity);

      int get_entity_count( const_char_pointer  str );

      int ref_to_entity( const_char_pointer  estr, char * str, int strlen );
      int entity_to_ref( const_char_pointer  str, char * estr, int estrlen );

      string ref_to_entity( const_char_pointer  estr );
      string entity_to_ref( const_char_pointer  str );   

      void ref_to_entity(string & str, const_char_pointer  estr);
      void entity_to_ref(string & s, const_char_pointer  str);

      void add_entity(char chEntity, const_char_pointer  pszReference);

      
   };

   
   string XRef2Entity( const_char_pointer  estr );
   string XEntity2Ref( const_char_pointer  str );   
   

} // namespace xml




