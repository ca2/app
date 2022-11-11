#include "framework.h"
#include "font.h"
#include "acme/primitive/string/international.h"


namespace write_text
{


   string font::get_sample_text(enum_character_set echarset)
   {

      if (echarset == e_character_set_chinesebig5)
      {

         return unitext("示例文本");

      }
      else if (echarset == e_character_set_gb2312)
      {

         return unitext("示例文本");

      }
      else if (echarset == e_character_set_shiftjis)
      {

         return unitext("サンプルテキスト");

      }
      else if (echarset == e_character_set_hebrew)
      {

         return unitext("טקסט לדוגמה");

      }
      else if (echarset == e_character_set_arabic)
      {

         return unitext("نص بسيط");

      }
      else if (echarset == e_character_set_greek)
      {

         return unitext("Δείγμα κειμένου");

      }
      else if (echarset == e_character_set_turkish)
      {

         return unitext("Örnek yazı");

      }
      else if (echarset == e_character_set_vietnamese)
      {

         return unitext("văn bản mẫu");

      }
      else if (echarset == e_character_set_thai)
      {

         return unitext("ตัวอย่างข้อความ");

      }
      else if (echarset == e_character_set_easteurope)
      {

         return unitext("Sample Text");

      }
      else if (echarset == e_character_set_russian)
      {

         return unitext("Образец текста");

      }
      else if (echarset == e_character_set_johab)
      {

         return unitext("샘플 텍스트");

      }
      else if (echarset == e_character_set_hangul)
      {

         return unitext("샘플 텍스트");

      }

      return "";

   }


} // namespace write_text



