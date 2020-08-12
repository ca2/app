#pragma once


#include "charguess_c.h"


CLASS_DECL_SPHERE const char * GuessChardet(charguess_det p, const string & str);


class CLASS_DECL_SPHERE charguess
{
   public:

      charguess_det     m_pdet;
      string            m_strDet;

      charguess()
      {
         m_pdet = CharGuessInit();
      }
      charguess(const string & str)
      {
         m_pdet = CharGuessInit();
         det(str);
      }
      ~charguess()
      {
         CharGuessDestroy(m_pdet);
      }


      string det(const string & str)
      {
         return m_strDet = GuessChardet(m_pdet,str);
      }

      u32 operator () (void) { return get_code_page(m_strDet); }

      static u32 get_code_page(const string & strDet);

};































