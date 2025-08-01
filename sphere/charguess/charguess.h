#pragma once


#include "charguess_c.h"


CLASS_DECL_SPHERE const_char_pointer GuessChardet(charguess_det p, const ::scoped_string & scopedstr);


class CLASS_DECL_SPHERE charguess
{
   public:

      charguess_det     m_pdet;
      string            m_strDet;

      charguess()
      {
         m_pdet = CharGuessInit();
      }
      charguess(const ::scoped_string & scopedstr)
      {
         m_pdet = CharGuessInit();
         det(str);
      }
      ~charguess()
      {
         CharGuessDestroy(m_pdet);
      }


      string det(const ::scoped_string & scopedstr)
      {
         return m_strDet = GuessChardet(m_pdet,str);
      }

      unsigned int operator () (void) { return get_code_page(m_strDet); }

      static unsigned int get_code_page(const ::scoped_string & scopedstrDet);

};































