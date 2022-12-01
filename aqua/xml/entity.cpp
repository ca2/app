#include "framework.h"
#include "entity.h"


namespace xml
{


   entity::entity()
   {
   }

   entity::entity(char chEntity, const char * pszReference)
   {
      m_chEntity  = chEntity;
      if(*pszReference == '&')
         pszReference++;
      m_strRef    = pszReference;
      m_iRefLen   = (i32) strlen(pszReference);
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


   void entities::add_entity(char chEntity, const char * pszReference)
   {
      add(entity(chEntity, pszReference));
   }

   entity * entities::get_entity( i32 m_chEntity )
   {
      for( i32 i = 0 ; i < this->get_size(); i ++ )
      {
         if( this->element_at(i).m_chEntity == m_chEntity )
            return (class entity *)(&this->element_at(i));
      }
      return nullptr;
   }

   entity * entities::get_entity(const char * pszEntity)
   {
      for( i32 i = 0 ; i < this->get_size(); i ++ )
      {
         const char * pszRef = this->element_at(i).m_strRef;
         const char * psz = pszEntity;
         while(*pszRef)
            if(*pszRef++ != *psz++)
               break;
         if(!*pszRef)   // found!
            return (class entity *)(&this->element_at(i));
      }
      return nullptr;
   }

   i32 entities::get_entity_count( const char * str )
   {
      i32 nCount = 0;
      char * ps = (char *)str;
      while( ps && *ps )
         if( get_entity( *ps++ ) ) nCount ++;
      return nCount;
   }


   i32 entities::ref_to_entity(const char * estr, char * str, i32 strlen)
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

               wd32char wd32char;

               if(*pes == 'X' || *pes == 'x')
               {

                  pes++;

                  wd32char = strtol(pes, &end, 16);

               }
               else
               {

                  wd32char = strtol(pes, &end, 10);

               }

               auto iLength = wd32_to_ansi(ps, &wd32char, 1);

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
      return (i32) (ps-str);

   }


   i32 entities::entity_to_ref( const char * str, char * estr, i32 estrlen )
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
            const char * pszRef = ent->m_strRef;
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
      return (i32) (pes-estr);
   }

   string entities::ref_to_entity(const char * pszSrc)
   {

      string strRet;
      if(pszSrc != nullptr)
      {
         strsize iLen = strlen(pszSrc);
         char * pszRet = strRet.get_string_buffer(iLen);
         if(pszRet != nullptr)
            ref_to_entity(pszSrc, pszRet, (i32) iLen);
         strRet.release_string_buffer();
      }
      return strRet;
   }

   string entities::entity_to_ref( const char * str )
   {
      string s;
      if( str )
      {
         i32 nEntityCount = get_entity_count(str);
         if( nEntityCount == 0 )
            return string(str);
         strsize len = strlen(str) + nEntityCount*10 ;
         char * sbuf = s.get_string_buffer(len + 1);
         if( sbuf )
            entity_to_ref( str, sbuf, (i32) len);
         s.release_string_buffer();
      }
      return s;
   }

   void entities::ref_to_entity(string & str, const char * pszSrc)
   {
      if(pszSrc != nullptr)
      {
         strsize iLen = strlen(pszSrc);
         char * pszRet = str.get_string_buffer(iLen);
         if(pszRet != nullptr)
            iLen = ref_to_entity(pszSrc,pszRet,(i32)iLen);
         str.release_string_buffer(iLen);
      }

   }

   void entities::entity_to_ref(string & s, const char * str)
   {
      if(str)
      {
         i32 nEntityCount = get_entity_count(str);
         if(nEntityCount == 0)
         {
            s = str;
            return;
         }
         strsize len = strlen(str) + nEntityCount * 10 ;
         char * sbuf = s.get_string_buffer(len + 1);
         if(sbuf)
         {
            len = entity_to_ref(str,sbuf,(i32)len);
         }
         s.release_string_buffer(len);
      }

   }

/*   string XRef2Entity( const char * estr )
   {
      return acmesystem()->m_entities.ref_to_entity( estr );
   }

   string XEntity2Ref( const char * str )
   {
      return acmesystem()->m_entities.entity_to_ref( str );
   }*/

} // namespace xml
