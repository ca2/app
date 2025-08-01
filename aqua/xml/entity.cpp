#include "framework.h"
#include "entity.h"


namespace xml
{


   entity::entity()
   {
   }

   entity::entity(char chEntity, const_char_pointer pszReference)
   {
      m_chEntity  = chEntity;
      if(*pszReference == '&')
         pszReference++;
      m_strRef    = pszReference;
      m_iRefLen   = (int) ansi_len(pszReference);
   }

   entity::entity(const entity & entity)
   {
      operator = (entity);
   }

   entity & entity::operator = (const entity & entity)
   {
      if(this != &entity)
      {
         m_chEntity  = entity.m_chEntity;
         m_strRef    = entity.m_strRef;
         m_iRefLen   = entity.m_iRefLen;
      }
      return *this;
   }


   void entities::add_entity(char chEntity, const_char_pointer pszReference)
   {
      add(entity(chEntity, pszReference));
   }

   entity * entities::get_entity( int m_chEntity )
   {
      for( int i = 0 ; i < this->get_size(); i ++ )
      {
         if( this->element_at(i).m_chEntity == m_chEntity )
            return (class entity *)(&this->element_at(i));
      }
      return nullptr;
   }

   entity * entities::get_entity(const_char_pointer pszEntity)
   {
      for( int i = 0 ; i < this->get_size(); i ++ )
      {
         const_char_pointer pszRef = this->element_at(i).m_strRef;
         const_char_pointer psz = pszEntity;
         while(*pszRef)
            if(*pszRef++ != *psz++)
               break;
         if(!*pszRef)   // found!
            return (class entity *)(&this->element_at(i));
      }
      return nullptr;
   }

   int entities::get_entity_count( const_char_pointer str )
   {
      int nCount = 0;
      char * ps = (char *)str;
      while( ps && *ps )
         if( get_entity( *ps++ ) ) nCount ++;
      return nCount;
   }


   int entities::ref_to_entity(const_char_pointer estr, char * str, int strlen)
   {

      char * pes = (char *)estr;

      char * ps = str;

      char * ps_end = ps+strlen;

      while(*pes && ps < ps_end )
      {

         if(*pes == '&')
         {

            if(*(pes + 1) == '#')
            {

               pes+=2;

               char * end = nullptr;

               ::wd32_character wd32_character;

               if(*pes == 'X' || *pes == 'x')
               {

                  pes++;

                  wd32_character = (::wd32_character) strtol(pes, &end, 16);

               }
               else
               {

                  wd32_character = (::wd32_character) strtol(pes, &end, 10);

               }

               auto iLength = wd32_to_ansi(ps, &wd32_character, 1);

               ps += iLength;

               pes = end;

               if(*pes == ';')
               {

                  pes++;

               }

            }
            else
            {

               entity * ent = get_entity(pes+1);

               if(ent)
               {

                  // copy m_chEntity meanning char

                  *ps = ent->m_chEntity;

                  pes += ent->m_iRefLen + 1;

               }
               else
               {

                  *ps = '&';   // default character copy

                  pes++;

               }

            }

         }
         else
         {

            *ps = *pes++;   // default character copy

         }

         ps++;

      }

      *ps = '\0';

      // total copied characters
      return (int) (ps-str);

   }


   int entities::entity_to_ref( const_char_pointer str, char * estr, int estrlen )
   {
      char * ps = (char *)str;
      char * pes = (char *)estr;
      char * pes_end = pes+estrlen;
      while( ps && *ps && pes < pes_end )
      {
         entity * ent = get_entity( *ps );
         if( ent )
         {
            // copy m_chEntity string
            const_char_pointer pszRef = ent->m_strRef;
            *pes++ = '&';
            while(*pszRef )
               *pes++ = *pszRef++;
         }
         else
            *pes++ = *ps;   // default character copy
         ps++;
      }
      *pes = '\0';

      // total copied characters
      return (int) (pes-estr);
   }

   string entities::ref_to_entity(const_char_pointer pszSrc)
   {

      string strRet;
      if(pszSrc != nullptr)
      {
         character_count iLen = ansi_len(pszSrc);
         char * pszRet = strRet.get_buffer(iLen);
         if(pszRet != nullptr)
            ref_to_entity(pszSrc, pszRet, (int) iLen);
         strRet.release_buffer();
      }
      return strRet;
   }

   string entities::entity_to_ref( const_char_pointer str )
   {
      string s;
      if( str )
      {
         int nEntityCount = get_entity_count(str);
         if( nEntityCount == 0 )
            return string(str);
         character_count len = ansi_len(str) + nEntityCount*10 ;
         char * sbuf = s.get_buffer(len + 1);
         if( sbuf )
            entity_to_ref( str, sbuf, (int) len);
         s.release_buffer();
      }
      return s;
   }

   void entities::ref_to_entity(string & str, const_char_pointer pszSrc)
   {
      if(pszSrc != nullptr)
      {
         character_count iLen = ansi_len(pszSrc);
         char * pszRet = str.get_buffer(iLen);
         if(pszRet != nullptr)
            iLen = ref_to_entity(pszSrc,pszRet,(int)iLen);
         str.release_buffer(iLen);
      }

   }

   void entities::entity_to_ref(string & s, const_char_pointer str)
   {
      if(str)
      {
         int nEntityCount = get_entity_count(str);
         if(nEntityCount == 0)
         {
            s = str;
            return;
         }
         character_count len = ansi_len(str) + nEntityCount * 10 ;
         char * sbuf = s.get_buffer(len + 1);
         if(sbuf)
         {
            len = entity_to_ref(str,sbuf,(int)len);
         }
         s.release_buffer(len);
      }

   }

/*   string XRef2Entity( const_char_pointer estr )
   {
      return system()->m_entities.ref_to_entity( estr );
   }

   string XEntity2Ref( const_char_pointer str )
   {
      return system()->m_entities.entity_to_ref( str );
   }*/

} // namespace xml
