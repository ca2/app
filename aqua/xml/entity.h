#pragma once



//#include "acme/prototype/collection/array.h"


namespace xml
{

   
   class CLASS_DECL_AQUA entity
   {
   public:

      
      ::i8     m_chEntity;      // entity ( & " ' < > )
      string   m_strRef;      // entity object ( &amp; &quot; etc )
      ::i32      m_iRefLen;      // entity object length

      
      entity();
      entity(::i8 chEntity, const_char_pointer pszReference);
      entity(const entity & entity);
      entity & operator = (const entity & entity);
      
      
   };

   
   class CLASS_DECL_AQUA entities :
	   virtual public ::array < entity >
   {
   public:
   
      
      entity * get_entity( ::i32 entity );
      entity * get_entity(const_char_pointer pszEntity);

      ::i32 get_entity_count( const_char_pointer str );

      ::i32 ref_to_entity( const_char_pointer estr, char_pointer str, ::i32 strlen );
      ::i32 entity_to_ref( const_char_pointer str, char_pointer estr, ::i32 estrlen );

      string ref_to_entity( const_char_pointer estr );
      string entity_to_ref( const_char_pointer str );

      void ref_to_entity(string & str, const_char_pointer estr);
      void entity_to_ref(string & s, const_char_pointer str);

      void add_entity(::i8 chEntity, const_char_pointer pszReference);

      
   };

   
   string XRef2Entity( const_char_pointer estr );
   string XEntity2Ref( const_char_pointer str );
   

} // namespace xml




