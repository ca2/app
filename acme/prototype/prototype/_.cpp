#include "framework.h"
#include "acme/prototype/prototype/atom.h"
//#include "acme/prototype/prototype/matter.h"
#include "acme/prototype/string/str.h"


//extern ::pointer< ::mutex > g_pmutexChildren;


void _debug_debug_string_string()
{

   ::atom atom("a-ha");

   /*auto bEndsInHa1 = string_ends<const ::ansi_character>(atom, "ha");
   auto bEndsInHa2 = case_insensitive_string_ends<const ::ansi_character>(atom, "Ha");*/

}


void __assert_particle_ok(const ::particle * p, const_char_pointer pszFileName, ::i32 nLine)
{

   if (p == nullptr)
   {

      if(!__assert_failed_line(pszFileName, nLine))
      {

         debug_break();

      }

      return;

   }

   if (!is_memory_segment_ok(p, sizeof(::particle)))
   {

      if (__assert_failed_line(pszFileName, nLine))
      {

         debug_break();

      }

      return;

   }

   if (!is_memory_segment_ok(*(const void **)p, sizeof(void *)))
   {

      if (!__assert_failed_line(pszFileName, nLine))
      {

         debug_break();

      }

      return;

   }

   p->assert_particle_ok();

}


CLASS_DECL_ACME void __call(::particle * pparticle)
{
   
   pparticle->run();
   
}




CLASS_DECL_ACME ::pointer_array<::string_array> parse_comma_separated_file(const ::scoped_string &scopedstrCsv)
{

   ::pointer_array<::string_array> straa;
   ::pointer<::string_array> pstra;
   ::string strField;
   bool bQuoted = false;
   bool bRecordStarted = false;

   auto add_field = [&]()
   {
      if (!pstra)
      {

         pstra = straa.main_add();
      }

      pstra->add(strField);
      strField.empty();
      bRecordStarted = true;
   };

   auto finish_record = [&]()
   {
      add_field();
      pstra.release();
      bRecordStarted = false;
   };

   auto psz = scopedstrCsv.begin();
   auto pszEnd = scopedstrCsv.end();

   while (psz < pszEnd)
   {

      auto iRemaining = pszEnd - psz;
      auto pszNext = ::unicode_next(psz, &iRemaining);

      if (::is_null(pszNext) || pszNext <= psz || pszNext > pszEnd)
      {

         throw_encoding_exception("Invalid UTF-8 character in comma-separated file");

      }

      ::string strCharacter(psz, pszNext);

      psz = pszNext;

      if (bQuoted)
      {

         if (strCharacter == "\"")
         {

            if (psz < pszEnd && *psz == '"')
            {

               strField += "\"";
               ++psz;
            }
            else
            {

               bQuoted = false;
            }
         }
         else
         {

            strField += strCharacter;
         }
      }
      else if (strCharacter == "\"" && strField.is_empty())
      {

         bQuoted = true;
         bRecordStarted = true;
      }
      else if (strCharacter == ",")
      {

         add_field();
      }
      else if (strCharacter == "\r" || strCharacter == "\n")
      {

         finish_record();

         if (strCharacter == "\r" && psz < pszEnd && *psz == '\n')
         {

            ++psz;
         }
      }
      else
      {

         strField += strCharacter;
         bRecordStarted = true;
      }
   }

   if (bRecordStarted || strField.has_character() || pstra)
   {

      finish_record();
   }

   return straa;
}
