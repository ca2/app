#include "framework.h"


//SMatch *SMatchHash::setItem(string name, SMatch &smatch)
//{
//   m_map.set_at(name, smatch);
//   return &m_map[name];
//}
//
//SMatch *SMatchHash::getItem(string name)
//{
//   return &m_map[name];
//}
//
//
//SRegInfo::SRegInfo()
//{
//   next = prev = parent = nullptr;
//   un.lparam = nullptr;
//   op = ReEmpty;
//   param0 = param1 = 0;
//};
//SRegInfo::~SRegInfo()
//{
//   if (next) delete next;
//   if (un.lparam) switch(op)
//      {
//      case ReEnum:
//      case ReNEnum:
//         delete un.charclass;
//         break;
//      case ReWord:
//         delete un.u;
//         break;
//      case ReSymb:
//         delete un.symbol;
//         break;
////#ifdef NAMED_MATCHES_IN_HASH
//      case ReNamedBrackets:
//      case ReBkBrackName:
//      //if(namedata) delete namedata;
////#endif
//      default:
//         if((op > ReBlockOps && op < ReSymbolOps) || op == ReBrackets || op == ReNamedBrackets)
//            delete un.lparam;
//         break;
//      };
//};
//
//////////////////////////////////////////////////////////////////////////////
//// cregexp class
//void cregexp::init()
//{
//   tree_root = 0;
//   positionMoves = false;
//   error = EERROR;
//   cMatch = 0;
//#ifdef COLORERMODE
//   backRE = 0;
//#endif
//   namedMatches = 0;
//}
//
//cregexp::cregexp()
//{
//
//   init();
//
//}
//
//cregexp::cregexp(string text)
//{
//
//   init();
//
//   if(text.has_char())
//      setRE(text);
//
//}
//
//cregexp::~cregexp()
//{
//   if (tree_root) delete tree_root;
//};
//
//EError cregexp::setRELow(const char * expr)
//{
//
//   strsize len = ::str::ilen(expr);
//
//   if (!len) return EERROR;
//
//   if (tree_root) delete tree_root;
//   tree_root = nullptr;
//
//   cMatch = 0;
//   endChange = startChange = false;
//   i32 start = 0;
//   while(::str::ch::is_whitespace(&expr[start])) start++;
//   if (expr[start] == '/') start++;
//   else return ESYNTAX;
//
//   bool ok = false;
//   ignoreCase = extend = singleLine = multiLine = false;
//   for (strsize i = len-1; i >= start && !ok; i--)
//      if (expr[i] == '/')
//      {
//         for (strsize j = i+1; j < len; j++)
//         {
//            if (expr[j] == 'i') ignoreCase = true;
//            if (expr[j] == 'x') extend = true;
//            if (expr[j] == 's') singleLine = true;
//            if (expr[j] == 'm') multiLine = true;
//         };
//         len = i-start;
//         ok = true;
//      };
//   if (!ok) return ESYNTAX;
//
//   // making tree structure
//   tree_root = new SRegInfo;
//   tree_root->op = ReBrackets;
//   tree_root->un.lparam = new SRegInfo;
//   tree_root->un.lparam->parent = tree_root;
//   tree_root->param0 = cMatch++;
//
//   string strMid = string(expr).Mid(start, len);
//   len = strMid.get_length();
//   strsize endPos;
//   EError err = setStructs(tree_root->un.lparam, strMid, endPos);
//   if (endPos != len) err = EBRACKETS;
//
//   if (err) return err;
//   optimize();
//   return EOK;
//};
//
//
//void cregexp::optimize()
//{
//   SRegInfo *next = tree_root;
//   firstChar = BAD_WCHAR;
//   firstMetaChar = ReBadMeta;
//   while(next)
//   {
//      if (next->op == ReBrackets)
//      {
//         next = next->un.lparam;
//         continue;
//      };
//      /*    if (next->op == ReMetaSymb &&
//              next->un.metaSymbol >= ReWBound && next->un.metaSymbol < ReChrLast){
//            next = next->next;
//            continue;
//          };*/
//      if (next->op == ReMetaSymb)
//      {
//         if (next->un.metaSymbol != ReSoL && next->un.metaSymbol != ReWBound) break;
//         firstMetaChar = next->un.metaSymbol;
//         break;
//      };
//      if (next->op == ReSymb)
//      {
//         firstChar = *next->un.symbol;
//         break;
//      };
//      if (next->op == ReWord)
//      {
//         firstChar = (*next->un.u)[0];
//      }
//      break;
//   };
//};
//
//EError cregexp::setStructs(SRegInfo *&re, const char * expr, strsize &retPos)
//{
//   SRegInfo *next, *temp;
//
//   retPos = 0;
//   if (!::str::ilen(expr)) return EOK;
//   retPos = -1;
//
//   next = re;
//   for(strsize i = 0; i < ::str::ilen(expr); i++)
//   {
//      // simple character
//      if (extend && ::str::ch::is_whitespace(&expr[i])) continue;
//      // context return
//      if (expr[i] == ')')
//      {
//         retPos = i;
//         break;
//      };
//      // next matter
//      if (i != 0)
//      {
//         next->next = new SRegInfo;
//         next->next->parent = next->parent;
//         next->next->prev = next;
//         next = next->next;
//      };
//      // Escape symbol
//      if (expr[i] == '\\')
//      {
//         string br_name;
//         strsize blen;
//         switch (expr[i+1])
//         {
//         case 'd':
//            next->op = ReMetaSymb;
//            next->un.metaSymbol = ReDigit;
//            break;
//         case 'D':
//            next->op = ReMetaSymb;
//            next->un.metaSymbol = ReNDigit;
//            break;
//         case 'w':
//            next->op = ReMetaSymb;
//            next->un.metaSymbol = ReWordSymb;
//            break;
//         case 'W':
//            next->op = ReMetaSymb;
//            next->un.metaSymbol = ReNWordSymb;
//            break;
//         case 's':
//            next->op = ReMetaSymb;
//            next->un.metaSymbol = ReWSpace;
//            break;
//         case 'S':
//            next->op = ReMetaSymb;
//            next->un.metaSymbol = ReNWSpace;
//            break;
//         case 'u':
//            next->op = ReMetaSymb;
//            next->un.metaSymbol = ReUCase;
//            break;
//         case 'l':
//            next->op = ReMetaSymb;
//            next->un.metaSymbol = ReNUCase;
//            break;
//         case 't':
//            next->op = ReSymb;
//            next->un.symbol = new string('\t');
//            break;
//         case 'n':
//            next->op = ReSymb;
//            next->un.symbol = new string('\n');
//            break;
//         case 'r':
//            next->op = ReSymb;
//            next->un.symbol = new string('\r');
//            break;
//         case 'b':
//            next->op = ReMetaSymb;
//            next->un.metaSymbol = ReWBound;
//            break;
//         case 'B':
//            next->op = ReMetaSymb;
//            next->un.metaSymbol = ReNWBound;
//            break;
//         case 'c':
//            next->op = ReMetaSymb;
//            next->un.metaSymbol = RePreNW;
//            break;
//#ifdef COLORERMODE
//         case 'm':
//            next->op = ReMetaSymb;
//            next->un.metaSymbol = ReStart;
//            break;
//         case 'M':
//            next->op = ReMetaSymb;
//            next->un.metaSymbol = ReEnd;
//            break;
//#endif // NAMED_MATCHES_IN_HASH
//
//         case 'p':  // \p{name}
//            next->op = ReBkBrackName;
//            if (!::str::get_curly_content(&((const char *)expr)[i+2], br_name)) return ESYNTAX;
//            blen = br_name.get_length();
//            if(br_name.get_length() && namedMatches && !namedMatches->getItem(br_name))
//            {
////            delete br_name;
//               return EBRACKETS;
//            };
//            next->param0 = 0;
//            next->namedata = (br_name);
////          delete br_name;
//            i += blen+2;
//            break;
//         default:
//            next->op = ReBkBrack;
//            next->param0 = (i32) ::hex::utf8_char_to(&expr[i+1]);
//            if (next->param0 < 0 || next->param0 > 9)
//            {
//               strsize retEnd;
//               next->op = ReSymb;
//               next->un.symbol =
//               new string(
//               ::str::uni_to_utf8(
//               ::str::get_escaped_char(expr, i+1, retEnd)));
//               if (next->un.symbol->is_empty()) return ESYNTAX;
//               i += next->un.symbol->get_length() - 1;
//            };
//            break;
//         };
//         i++;
//         continue;
//      };
//
//      if (expr[i] == '.')
//      {
//         next->op = ReMetaSymb;
//         next->un.metaSymbol = ReAnyChr;
//         continue;
//      };
//      if (expr[i] == '^')
//      {
//         next->op = ReMetaSymb;
//         next->un.metaSymbol = ReSoL;
//         continue;
//      };
//      if (expr[i] == '$')
//      {
//         next->op = ReMetaSymb;
//         next->un.metaSymbol = ReEoL;
//         continue;
//      };
//#ifdef COLORERMODE
//      if (expr[i] == '~')
//      {
//         next->op = ReMetaSymb;
//         next->un.metaSymbol = ReSoScheme;
//         continue;
//      };
//#endif
//
//      next->un.lparam = 0;
//      next->param0 = 0;
//
//      if (::str::ilen(expr) > i+2)
//      {
//         if (expr[i] == '?' && expr[i+1] == '#' &&
//               expr[i+2] >= '0' && expr[i+2] <= '9')
//         {
//            next->op = ReBehind;
//            next->param0 = (i32) ::hex::utf8_char_to(&expr[i+2]);
//            i += 2;
//            continue;
//         };
//         if (expr[i] == '?' && expr[i+1] == '~' &&
//               expr[i+2]>='0' && expr[i+2]<='9')
//         {
//            next->op = ReNBehind;
//            next->param0 = (i32) ::hex::utf8_char_to(&expr[i+2]);
//            i += 2;
//            continue;
//         };
//      };
//      if (::str::ilen(expr) > i+1)
//      {
//         if (expr[i] == '*' && expr[i+1] == '?')
//         {
//            next->op = ReNGRangeN;
//            next->s = 0;
//            i++;
//            continue;
//         };
//         if (expr[i] == '+' && expr[i+1] == '?')
//         {
//            next->op = ReNGRangeN;
//            next->s = 1;
//            i++;
//            continue;
//         };
//         if (expr[i] == '?' && expr[i+1] == '=')
//         {
//            next->op = ReAhead;
//            i++;
//            continue;
//         };
//         if (expr[i] == '?' && expr[i+1] == '!')
//         {
//            next->op = ReNAhead;
//            i++;
//            continue;
//         };
//         if (expr[i] == '?' && expr[i+1] == '?')
//         {
//            next->op = ReNGRangeNM;
//            next->s = 0;
//            next->e = 1;
//            i++;
//            continue;
//         };
//      };
//
//      if (expr[i] == '*')
//      {
//         next->op = ReRangeN;
//         next->s = 0;
//         continue;
//      };
//      if (expr[i] == '+')
//      {
//         next->op = ReRangeN;
//         next->s = 1;
//         continue;
//      };
//      if (expr[i] == '?')
//      {
//         next->op = ReRangeNM;
//         next->s = 0;
//         next->e = 1;
//         continue;
//      };
//      if (expr[i] == '|')
//      {
//         next->op = ReOr;
//         continue;
//      };
//
//      // {n,m}
//      if (expr[i] == '{')
//      {
//         strsize st = i+1;
//         strsize en = -1;
//         strsize comma = -1;
//         bool nonGreedy = false;
//         strsize j;
//         for (j = i; j < ::str::ilen(expr); j++)
//         {
//            if (::str::ilen(expr) > j+1 && expr[j] == '}' && expr[j+1] == '?')
//            {
//               en = j;
//               nonGreedy = true;
//               j++;
//               break;
//            };
//            if (expr[j] == '}')
//            {
//               en = j;
//               break;
//            };
//            if (expr[j] == ',') comma = j;
//         };
//         if (en == -1) return EBRACKETS;
//         if (comma == -1) comma = en;
//         next->s = atoi(string(&((const char *)expr)[st], comma-st));
//         if (comma != en) next->e = atoi(string(&((const char *)expr)[comma+1], en-comma-1));
//         else next->e = next->s;
//         if (next->e == -1) return EOP;
//         next->un.lparam = 0;
//         if (en - comma == 1) next->e = -1;
//         if (next->e == -1) next->op = nonGreedy ? ReNGRangeN : ReRangeN;
//         else next->op = nonGreedy ? ReNGRangeNM : ReRangeNM;
//         i = j;
//         continue;
//      };
//      // ( ... )
//      if (expr[i] == '(')
//      {
//         //bool namedBracket = false;
//         // perl-like "uncaptured" brackets
//         if (::str::ilen(expr) >= i+2 && expr[i+1] == '?' && expr[i+2] == ':')
//         {
//            next->op = ReNamedBrackets;
//            next->param0 = -1;
//            //namedBracket = true;
//            i += 3;
//         }
//         else if (::str::ilen(expr) > i+2 && expr[i+1] == '?' && expr[i+2] == '{')
//         {
//            // named bracket
//            next->op = ReNamedBrackets;
//            //namedBracket = true;
//            string br_name;
//            if(!::str::get_curly_content(&((const char *)expr)[i+2], br_name)) return EBRACKETS;
//
//            strsize blen = br_name.get_length();
//            if (blen == 0)
//            {
//               next->param0 = -1;
//            }
//            else
//            {
//#ifdef CHECKNAMES
//               if(br_name->get_length() && namedMatches && namedMatches->getItem(br_name))
//               {
//                  delete br_name;
//                  return EBRACKETS;
//               };
//#endif
//               next->param0 = 0;
//               next->namedata = br_name;
//               if (namedMatches)
//               {
//                  SMatch mt = {-1, -1};
//                  namedMatches->setItem(br_name, mt);
//               };
//            };
//            i += blen+4;
//         }
//         else
//         {
//            next->op = ReBrackets;
//            if (cMatch < MATCHES_NUM)
//            {
//               next->param0 = cMatch;
//               cMatch++;
//            };
//            i += 1;
//         };
//         next->un.lparam = new SRegInfo;
//         next->un.lparam->parent = next;
//         strsize endPos;
//         EError err = setStructs(next->un.lparam, string(&((const char *)expr)[i]), endPos);
//         if (endPos == ::str::ilen(expr)-i) return EBRACKETS;
//         if (err) return err;
//         i += endPos;
//         continue;
//      };
//
//      // [] [^]
//      if (expr[i] == '[')
//      {
//         strsize endPos;
//         ::str::ch_class *cc = ::str::ch_class::createCharClass(expr, i, &endPos);
//         if (cc == nullptr) return EENUM;
////      next->op = (exprn[i] == ReEnumS) ? ReEnum : ReNEnum;
//         next->op = ReEnum;
//         next->un.charclass = cc;
//         i = endPos;
//         continue;
//      };
//      if (expr[i] == ')' || expr[i] == ']' || expr[i] == '}') return EBRACKETS;
//      next->op = ReSymb;
//      next->un.symbol = new string(::str::get_utf8_char(&((const char *)expr)[i]));
//      i += next->un.symbol->get_length() - 1;
//   };
//
//   // operators fixes
//   for(next = re; next; next = next->next)
//   {
//      // makes words from symbols
//      SRegInfo *reword = next;
//      SRegInfo *reafterword = next;
//      SRegInfo *resymb;
//      i32 wsize = 0;
//      for (resymb = next; resymb && resymb->op == ReSymb; resymb = resymb->next, wsize++);
//      if (resymb && resymb->op > ReBlockOps && resymb->op < ReSymbolOps)
//      {
//         //wsize--;
//         //resymb = resymb->prev;
//      };
//      if (wsize > 0)
//      {
//         reafterword = resymb;
//         resymb = reword;
//         string_array wcword;
//         for(i32 idx = 0; idx < wsize; idx++)
//         {
//            wcword.set_at_grow(idx, *resymb->un.symbol);
//            SRegInfo *retmp = resymb;
//            resymb = resymb->next;
//            retmp->next = nullptr;
//            if (idx > 0) delete retmp;
//         }
//         reword->op = ReWord;
//         wcword.implode(*reword->un.u);
//         reword->next = reafterword;
//         if (reafterword)
//            reafterword->prev = reword;
//         next = reword;
//         continue;
//      }
//
//      // adds is_empty alternative
//      while (next->op == ReOr)
//      {
//         temp = new SRegInfo;
//         temp->parent = next->parent;
//         // |foo|bar
//         if (!next->prev)
//         {
//            temp->next = next;
//            next->prev = temp;
//            continue;
//         };
//         // foo||bar
//         if (next->next && next->next->op == ReOr)
//         {
//            temp->prev = next;
//            temp->next = next->next;
//            if (next->next) next->next->prev = temp;
//            next->next = temp;
//            continue;
//         };
//         // foo|bar|
//         if (!next->next)
//         {
//            temp->prev = next;
//            temp->next = 0;
//            next->next = temp;
//            continue;
//         };
//         // foo|bar|*
//         if (next->next->op > ReBlockOps && next->next->op < ReSymbolOps)
//         {
//            temp->prev = next;
//            temp->next = next->next;
//            next->next->prev = temp;
//            next->next = temp;
//            continue;
//         };
//         delete temp;
//         break;
//      };
//   };
//
//   // op's generating...
//   next = re;
//   SRegInfo *realFirst;
//   while(next)
//   {
//      if (next->op > ReBlockOps && next->op < ReSymbolOps)
//      {
//         if (!next->prev) return EOP;
//         realFirst = next->prev;
//         realFirst->next = 0;
//         realFirst->parent = next;
//         while(next->op == ReOr && realFirst->prev && realFirst->prev->op != ReOr)
//         {
//            realFirst->parent = next;
//            realFirst = realFirst->prev;
//         };
//
//         if (!realFirst->prev)
//         {
//            re = next;
//            next->un.lparam = realFirst;
//            next->prev = 0;
//         }
//         else
//         {
//            next->un.lparam = realFirst;
//            next->prev = realFirst->prev;
//            realFirst->prev->next = next;
//         };
//         realFirst->prev = 0;
//      };
//      next = next->next;
//   };
//   if (retPos == -1) retPos = ::str::ilen(expr);
//   return EOK;
//};
//
//
//
//
//
//
//////////////////////////////////////////////////////////////////////////////
//// parsing
//////////////////////////////////////////////////////////////////////////////
//
//bool cregexp::isWordBoundary(strsize &toParse)
//{
//   strsize before = 0;
//   strsize after  = 0;
//   if (toParse < end && (::str::ch::is_letter_or_digit(&((const char *)global_pattern)[toParse]) ||
//                         ((const char *)global_pattern)[toParse] == '_')) after = 1;
//   if (toParse > 0 && (::str::ch::is_letter_or_digit(&((const char *)global_pattern)[toParse-1]) ||
//                       ((const char *)global_pattern)[toParse-1] == '_')) before = 1;
//   return before+after == 1;
//};
//bool cregexp::isNWordBoundary(strsize &toParse)
//{
//   return !isWordBoundary(toParse);
//};
//
//
//
//
//bool cregexp::checkMetaSymbol(EMetaSymbols symb, strsize &toParse)
//{
//   const string &pattern = global_pattern;
//
//   switch(symb)
//   {
//   case ReAnyChr:
//      if (toParse >= end) return false;
//      if (!singleLine && (((const char *)pattern)[toParse] == 0x0A || ((const char *)pattern)[toParse] == 0x0B ||
//                          ((const char *)pattern)[toParse] == 0x0C || ((const char *)pattern)[toParse] == 0x0D ||
//                          ((const u8 *)(const char *)pattern)[toParse] == 0x85 ||
//                          ((const unichar *)(const char *)pattern)[toParse] == 0x2028 ||
//                          ((const unichar *)(const char *)pattern)[toParse] == 0x2029)) return false;
//      toParse++;
//      return true;
//   case ReSoL:
//      if (multiLine)
//      {
//         bool ok = false;
//         if (toParse && (((const char *)pattern)[toParse-1] == 0x0A || ((const char *)pattern)[toParse-1] == 0x0B ||
//                         ((const char *)pattern)[toParse-1] == 0x0C || ((const char *)pattern)[toParse-1] == 0x0D ||
//                         ((const u8 *)(const char *)pattern)[toParse-1] == 0x85 ||
//                         ((const unichar *)(const char *)pattern)[toParse-1] == 0x2028 ||
//                         ((const unichar *)(const char *)pattern)[toParse-1] == 0x2029)) ok = true;
//         return (toParse == 0 || ok);
//      };
//      return (toParse == 0);
//   case ReEoL:
//      if (multiLine)
//      {
//         bool ok = false; // ???check
//         if (toParse && toParse < end &&
//               (((const char *)pattern)[toParse-1] == 0x0A || ((const char *)pattern)[toParse-1] == 0x0B ||
//                ((const char *)pattern)[toParse-1] == 0x0C || ((const char *)pattern)[toParse-1] == 0x0D ||
//                ((const u8 *)(const char *)pattern)[toParse-1] == 0x85 ||
//                ((const unichar *)(const char *)pattern)[toParse-1] == 0x2028 ||
//                ((const unichar *)(const char *)pattern)[toParse-1] == 0x2029)) ok = true;
//         return (toParse == end || ok);
//      };
//      return (end == toParse);
//   case ReDigit:
//      if (toParse >= end || !::str::ch::is_digit(&((const char *)pattern)[toParse])) return false;
//      toParse++;
//      return true;
//   case ReNDigit:
//      if (toParse >= end || ::str::ch::is_digit(&((const char *)pattern)[toParse])) return false;
//      toParse++;
//      return true;
//   case ReWordSymb:
//      if (toParse >= end || !(::str::ch::is_letter_or_digit(&((const char *)pattern)[toParse])
//                              || ((const char *)pattern)[toParse] == '_')) return false;
//      toParse++;
//      return true;
//   case ReNWordSymb:
//      if (toParse >= end || ::str::ch::is_letter_or_digit(&((const char *)pattern)[toParse])
//            || ((const char *)pattern)[toParse] == '_') return false;
//      toParse++;
//      return true;
//   case ReWSpace:
//      if (toParse >= end || !::str::ch::is_whitespace(&((const char *)pattern)[toParse])) return false;
//      toParse++;
//      return true;
//   case ReNWSpace:
//      if (toParse >= end || ::str::ch::is_whitespace(&((const char *)pattern)[toParse])) return false;
//      toParse++;
//      return true;
//   case ReUCase:
//      if (toParse >= end || !::str::ch::is_upper_case(&((const char *)pattern)[toParse])) return false;
//      toParse++;
//      return true;
//   case ReNUCase:
//      if (toParse >= end || !::str::ch::is_lower_case(&((const char *)pattern)[toParse])) return false;
//      toParse++;
//      return true;
//   case ReWBound:
//      return isWordBoundary(toParse);
//   case ReNWBound:
//      return isNWordBoundary(toParse);
//   case RePreNW:
//      if (toParse >= end) return true;
//      return toParse == 0 || !::str::ch::is_letter(&((const char *)pattern)[toParse-1]);
//#ifdef COLORERMODE
//   case ReSoScheme:
//      return (schemeStart == toParse);
//   case ReStart:
//      matches->s[0] = toParse;
//      startChange = true;
//      return true;
//   case ReEnd:
//      matches->e[0] = toParse;
//      endChange = true;
//      return true;
//#endif
//   default:
//      return false;
//   };
//}
//
//bool cregexp::lowParse(SRegInfo *re, SRegInfo *prev, strsize toParse)
//{
//   strsize i, sv, wlen;
//   bool leftenter = true;
//   const string pattern = global_pattern;
//
//   if (!re)
//   {
//      re = prev->parent;
//      leftenter = false;
//   };
//
//   while(re)
//   {
//      switch(re->op)
//      {
//      case ReEmpty:
//         break;
//      case ReBrackets:
//      case ReNamedBrackets:
//         if (leftenter)
//         {
//            re->s = toParse;
//            re = re->un.lparam;
//            leftenter = true;
//            continue;
//         };
//         if (re->param0 == -1) break;
//         if (re->op == ReBrackets)
//         {
//            if (re->param0 || !startChange)
//               matches->s[re->param0] = re->s;
//            if (re->param0 || !endChange)
//               matches->e[re->param0] = toParse;
//            if (matches->e[re->param0] < matches->s[re->param0])
//               matches->s[re->param0] = matches->e[re->param0];
//         }
//         else
//         {
//            SMatch mt = { re->s, toParse };
//            namedMatches->setItem(re->namedata, mt);
//         };
//         break;
//      case ReSymb:
//         if (toParse >= end) return false;
//         if (ignoreCase)
//         {
//            if (::str::ch::to_lower_case(&((const char *)pattern)[toParse]) != ::str::ch::to_lower_case(*re->un.symbol) &&
//                  ::str::ch::to_upper_case(&((const char *)pattern)[toParse]) != ::str::ch::to_upper_case(*re->un.symbol))
//               return false;
//         }
//         else if (::str::get_utf8_char(&((const char *)pattern)[toParse]) != *re->un.symbol) return false;
//         toParse++;
//         break;
//      case ReMetaSymb:
//         if (!checkMetaSymbol(re->un.metaSymbol, toParse)) return false;
//         break;
//      case ReWord:
//         wlen = re->un.u->get_length();
//         if (toParse+wlen > end) return false;
//         if (ignoreCase)
//         {
//            string strAnalyze = pattern.Mid(toParse, wlen);
//            if(strAnalyze.compare_ci(*re->un.u))
//               return false;
//            toParse += wlen;
//         }
//         else
//         {
//            for(i = 0; i < wlen; i++)
//            {
//               if(((const char *)pattern)[toParse+i] != (*re->un.u)[i]) return false;
//            };
//            toParse += wlen;
//         }
//         break;
//      case ReEnum:
//         if (toParse >= end) return false;
//         if (!re->un.charclass->in_class(&((const char *)pattern)[toParse])) return false;
//         toParse++;
//         break;
//      case ReNEnum:
//         if (toParse >= end) return false;
//         if (re->un.charclass->in_class(&((const char *)pattern)[toParse])) return false;
//         toParse++;
//         break;
//#ifdef COLORERMODE
//      case ReBkTrace:
//         sv = re->param0;
//         if(backStr.has_char() || !backTrace || sv == -1) return false;
//         for (i = backTrace->s[sv]; i < backTrace->e[sv]; i++)
//         {
//            if (toParse >= end || ((const char *)pattern)[toParse] != backStr[i]) return false;
//            toParse++;
//         };
//         break;
//      case ReBkTraceN:
//         sv = re->param0;
//         if (backStr.has_char() || !backTrace || sv == -1) return false;
//         for (i = backTrace->s[sv]; i < backTrace->e[sv]; i++)
//         {
//            if (toParse >= end || ::str::ch::to_lower_case(&((const char *)pattern)[toParse]) != ::str::ch::to_lower_case(&((const char *)backStr)[i])) return false;
//            toParse++;
//         };
//         break;
//      case ReBkTraceName:
//         return false;
//      case ReBkTraceNName:
//         return false;
//#endif // COLORERMODE
//
//      case ReBkBrackName:
//      {
//         SMatch *mt = namedMatches->getItem(re->namedata);
//         if (!mt) return false;
//         if (mt->s == -1 || mt->e == -1) return false;
//         for (i = mt->s; i < mt->e; i++)
//         {
//            if (toParse >= end || &((const char *)pattern)[toParse] != &((const char *)pattern)[i]) return false;
//            toParse++;
//         };
//      };
//      break;
//
//      case ReBkBrack:
//         sv = re->param0;
//         if (sv == -1 || cMatch <= sv) return false;
//         if (matches->s[sv] == -1 || matches->e[sv] == -1) return false;
//         for (i = matches->s[sv]; i < matches->e[sv]; i++)
//         {
//            if (toParse >= end || &((const char *)pattern)[toParse] != &((const char *)pattern)[i]) return false;
//            toParse++;
//         };
//         break;
//      case ReAhead:
//         if (!leftenter) return true;
//         if (!lowParse(re->un.lparam, 0, toParse)) return false;
//         break;
//      case ReNAhead:
//         if (!leftenter) return true;
//         if (lowParse(re->un.lparam, 0, toParse)) return false;
//         break;
//      case ReBehind:
//         if (!leftenter) return true;
//         if (toParse - re->param0 < 0 || !lowParse(re->un.lparam, 0, toParse - re->param0)) return false;
//         break;
//      case ReNBehind:
//         if (!leftenter) return true;
//         if (toParse - re->param0 >= 0 && lowParse(re->un.lparam, 0, toParse - re->param0)) return false;
//         break;
//
//      case ReOr:
//         if (!leftenter)
//         {
//            while (re->next)
//               re = re->next;
//            break;
//         };
//         if (lowParse(re->un.lparam, 0, toParse)) return true;
//         break;
//
//      case ReRangeN:
//         // first enter into op
//         if (leftenter)
//         {
//            re->param0 = re->s;
//            re->oldParse = -1;
//         };
//         if (!re->param0 && re->oldParse == toParse) break;
//         re->oldParse = toParse;
//         // making branch
//         if (!re->param0)
//         {
//            // if matches next
//            if(lowParse(re->next, re, toParse))
//               return true;
//            if (lowParse(re->un.lparam, 0, toParse))
//               return true;
//            return lowParse(re->next, re, toParse);
//         };
//         // go into
//         if (re->param0) re->param0--;
//         re = re->un.lparam;
//         leftenter = true;
//         continue;
//      case ReRangeNM:
//         if (leftenter)
//         {
//            re->param0 = re->s;
//            re->param1 = re->e - re->s;
//            re->oldParse = -1;
//         };
//         //
//         if (!re->param0)
//         {
//            if (re->param1) re->param1--;
//            else return lowParse(re->next, re, toParse);
//            if (!lowParse(re->un.lparam, 0, toParse)) return false;
//            if (lowParse(re->next, re, toParse)) return true;
//            re->param1++;
//            return false;
//         };
//         if (re->param0) re->param0--;
//         re = re->un.lparam;
//         leftenter = true;
//         continue;
//      case ReNGRangeN:
//         if (leftenter)
//         {
//            re->param0 = re->s;
//            re->oldParse = -1;
//         };
//         if (!re->param0 && re->oldParse == toParse) break;
//         re->oldParse = toParse;
//         //
//         if (!re->param0 && lowParse(re->next, re, toParse)) return true;
//         if (re->param0) re->param0--;
//         re = re->un.lparam;
//         leftenter = true;
//         continue;
//      case ReNGRangeNM:
//         if (leftenter)
//         {
//            re->param0 = re->s;
//            re->param1 = re->e - re->s;
//            re->oldParse = -1;
//         };
//         //
//         if (!re->param0)
//         {
//            if (re->param1) re->param1--;
//            else return lowParse(re->next, re, toParse);
//            if (lowParse(re->next, re, toParse)) return true;
//            if (lowParse(re->un.lparam, 0, toParse))
//               return true;
//            else
//            {
//               re->param1++;
//               return false;
//            };
//         };
//         if (re->param0) re->param0--;
//         re = re->un.lparam;
//         leftenter = true;
//         continue;
//      default:
//         break;
//      };
//      if (!re->next)
//      {
//         re = re->parent;
//         leftenter = false;
//      }
//      else
//      {
//         re = re->next;
//         leftenter = true;
//      };
//   };
//   return true;
//};
//
//inline bool cregexp::quickCheck(strsize toParse)
//{
//   if (firstChar != -1)
//   {
//      if (toParse >= end) return false;
//      if (ignoreCase)
//      {
//         if (::str::ch::to_lower_case(&((const char *)global_pattern)[toParse]) != ::str::ch::to_lower_case(firstChar)) return false;
//      }
//      else if (&((const char *)global_pattern)[toParse] != firstChar) return false;
//      return true;
//   };
//   if (firstMetaChar != ReBadMeta)
//      switch(firstMetaChar)
//      {
//      case ReSoL:
//         if (toParse != 0) return false;
//         return true;
//#ifdef COLORERMODE
//      case ReSoScheme:
//         if (toParse != schemeStart) return false;
//         return true;
//#endif
////    case ReWBound:
////      return relocale->cl_isword(*toParse) && (toParse == start || !relocale->cl_isword(*(toParse-1)));
//      default:
//         break;
//      };
//   return true;
//};
//
//inline bool cregexp::parseRE(strsize pos)
//{
//   if (error) return false;
//
//   strsize toParse = pos;
//
//   if (!positionMoves && (firstChar != -1 || firstMetaChar != ReBadMeta) && !quickCheck(toParse))
//      return false;
//
//   strsize i;
//   for (i = 0; i < cMatch; i++)
//      matches->s[i] = matches->e[i] = -1;
//   matches->cMatch = cMatch;
//   do
//   {
//      if (lowParse(tree_root, 0, toParse)) return true;
//      if (!positionMoves) return false;
//      toParse = ++pos;
//   }
//   while(toParse <= end);
//   return false;
//};
//
//bool cregexp::parse(string str, strsize pos, strsize eol, SMatches *mtch, PMatchHash nmtch, i32 soScheme, i32 posMoves)
//{
//   UNREFERENCED_PARAMETER(nmtch);
//   bool nms = positionMoves;
//   if (posMoves != -1) positionMoves = (posMoves != 0);
//#ifdef COLORERMODE
//   schemeStart = soScheme;
//#endif
//   global_pattern = str;
//   end = eol;
//   matches = mtch;
//#ifdef NAMED_MATCHES_IN_HASH
//   namedMatches = nmtch;
//#endif
//   bool result = parseRE(pos);
//   positionMoves = nms;
//   return result;
//};
//
//bool cregexp::parse(string str, SMatches *mtch
//                    ,PMatchHash nmtch
//                   )
//{
//   end = str.get_length();
//   global_pattern = str;
//#ifdef COLORERMODE
//   schemeStart = 0;
//#endif
//   matches = mtch;
////#ifdef NAMED_MATCHES_IN_HASH
//   namedMatches = nmtch;
////#endif
//   return parseRE(0);
//};
//
///////////////////////////////////////////////////////////////////
//// other methods
//
//bool cregexp::setRE(string re)
//{
//   error = EERROR;
////#ifdef NAMED_MATCHES_IN_HASH
//   PMatchHash oldnamedMatches = namedMatches;
//   SMatchHash tmpMatchHash;
//   namedMatches = &tmpMatchHash;
//   error = setRELow(re);
//   namedMatches = oldnamedMatches;
////#else
//   //error = setRELow(re);
////#endif
//   return error == EOK;
//};
//bool cregexp::isOk()
//{
//   return error == EOK;
//};
//EError cregexp::getError()
//{
//   return error;
//};
//
//bool cregexp::setPositionMoves(bool moves)
//{
//   positionMoves = moves;
//   return true;
//};
//
//
//#ifdef COLORERMODE
//bool cregexp::setBackRE(cregexp *bkre)
//{
//   this->backRE = bkre;
//   return true;
//};
//bool cregexp::setBackTrace(string str, SMatches *trace)
//{
//   backTrace = trace;
//   backStr = str;
//   return true;
//};
//bool cregexp::getBackTrace(string *str, SMatches **trace)
//{
//   *str = backStr;
//   *trace = backTrace;
//   return true;
//};
//#endif
///* ***** BEGIN LICENSE BLOCK *****
// * Version: MPL 1.1/GPL 2.0/LGPL 2.1
// *
// * The contents of this file are subject to the Mozilla Public License Version
// * 1.1 (the "License"); you may not use this file except in compliance with
// * the License. You may obtain a copy of the License at
// * http://www.mozilla.org/MPL/
// *
// * Software distributed under the License is distributed on an "AS IS" basis,
// * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
// * for the specific language governing rights and limitations under the
// * License.
// *
// * The Original Code is the Colorer Library.
// *
// * The Initial Developer of the Original Code is
// * Cail Lomecb <cail@nm.ru>.
// * Portions created by the Initial Developer are Copyright (C) 1999-2005
// * the Initial Developer.
// *
// * Contributor(s):
// *
// * Alternatively, the contents of this file may be used under the terms of
// * either the GNU General Public License Version 2 or later (the "GPL"), or
// * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
// * in which case the provisions of the GPL or the LGPL are applicable instead
// * of those above. If you wish to allow use of your version of this file only
// * under the terms of either the GPL or the LGPL, and not to allow others to
// * use your version of this file under the terms of the MPL, indicate your
// * decision by deleting the provisions above and replace them with the notice
// * and other provisions required by the GPL or the LGPL. If you do not delete
// * the provisions above, a recipient may use your version of this file under
// * the terms of any one of the MPL, the GPL or the LGPL.
// *
// * ***** END LICENSE BLOCK ***** */
//
//
//
//
//
//
//index cregexp::match(string_array & stra, const string & pcsz, strsize iSize)
//
//{
//   stra.erase_all();
//
//   if(iSize <= 0)
//      return 0;
//
//   string str(pcsz);
//
//
//   SMatches matches;
//
//   setPositionMoves(true);
//
//   bool bMatch = parse(pcsz, &matches);
//
//
//   for(index i = 0; i < matches.cMatch; i++)
//   {
//      strsize iStart   = matches.s[i];
//      strsize iEnd     = matches.e[i];
//      stra.add(str.Mid(iStart, iEnd - iStart));
//   }
//
//   return bMatch;
//}
//
//
//bool cregexp::find(string & strMatch, const string & str, index iSubString, strsize  * piStart, strsize  * piEnd)
//{
//
//   strsize iStart = piStart == nullptr ? 0 : *piStart;
//
//   strsize iEnd = piEnd == nullptr ? str.get_length() - 1 : *piEnd;
//
//   bool bOk = find(str, iSubString, &iStart, &iEnd);
//
//   if(bOk)
//   {
//      strMatch = str.substr(iStart, iEnd);
//   }
//
//   if(piStart != nullptr)
//   {
//      *piStart = iStart;
//   }
//
//   if(piEnd != nullptr)
//   {
//      *piEnd = iEnd;
//   }
//
//   return bOk;
//
//}
//
//
//
//bool cregexp::find(const string & str, index iSubString, strsize  * piStart, strsize  * piEnd)
//{
//
//   string strSubject;
//
//   strsize iStart;
//
//   strsize iEnd;
//
//   if(piStart != nullptr)
//      iStart = *piStart;
//   else
//      iStart = 0;
//
//   if(piEnd != nullptr)
//      iEnd = *piEnd;
//   else
//      iEnd = str.get_length() - 1;
//
//
//   if(iSubString < 0)
//      iSubString = 0;
//
//   iStart = minimum(str.get_length(), maximum(0, iStart));
//
//   iEnd = minimum(str.get_length(), maximum(0, iEnd));
//
//   SMatches matches;
//
//   matches.cMatch = 0;
//
//   const char * psz = str;
//
//
//   psz += iStart;
//
//
//   if(!parse(psz, &matches))
//
//      return false;
//
//   if(matches.cMatch == 0)
//      return false;
//
//   iEnd     = iStart + matches.e[iSubString];
//
//   iStart   = iStart + matches.s[iSubString];
//
//   if(piStart != nullptr)
//   {
//      *piStart = iStart;
//   }
//
//   if(piEnd != nullptr)
//   {
//      *piEnd = iEnd;
//   }
//
//   return true;
//
//}
//
//
//
//
//bool cregexp::split(string_array & stra, index_array & iaStart, index_array & iaEnd,  const string & str, int iLimit, bool bAddEmpty, bool bWithSeparator)
//{
//
//   strsize iStart = 0;
//   string strMatch;
//   strsize iPreviousStart;
//
//   ::count cInitial = stra.get_count();
//
//   while(true)
//   {
//
//      strsize iEnd = str.get_length() - 1;
//
//      iPreviousStart = iStart;
//
//      if(!find(strMatch, str, 0, &iStart, &iEnd))
//         break;
//
//      if(bAddEmpty || iStart > iPreviousStart)
//      {
//
//         if(bWithSeparator)
//         {
//            stra.add(str.substr(iPreviousStart, iEnd - iPreviousStart + 1));
//         }
//         else
//         {
//            stra.add(str.substr(iPreviousStart, iEnd - iStart));
//         }
//
//         iaStart.add(iStart);
//         iaEnd.add(iEnd);
//
//      }
//
//      iStart = iEnd + 1;
//
//      if(iStart >= str.length())
//         break;
//
//   }
//
//   return stra.get_count() > cInitial;
//
//}
//
//
//bool cregexp::split(string_array & stra, const string & str, int iLimit, bool bAddEmpty, bool bWithSeparator)
//{
//
//
//   strsize iStart = 0;
//   string strMatch;
//   strsize iPreviousStart;
//
//   ::count cInitial = stra.get_count();
//
//   while(true)
//   {
//
//      strsize iEnd = str.get_length() - 1;
//
//      iPreviousStart = iStart;
//
//      if(!find(strMatch, str,  0, &iStart, &iEnd))
//         break;
//
//      if(bAddEmpty || iStart > iPreviousStart)
//      {
//
//         if(bWithSeparator)
//         {
//            stra.add(str.substr(iPreviousStart, iEnd - iPreviousStart + 1));
//         }
//         else
//         {
//            stra.add(str.substr(iPreviousStart, iEnd - iStart));
//         }
//
//      }
//
//      iStart = iEnd + 1;
//
//      if(iStart >= str.length())
//         break;
//
//   }
//
//   return stra.get_count() > cInitial;
//
//}
//
//
//
//
//bool cregexp::match(const string & psz)
//
//{
//   string strSubject;
//
//
//   strSubject = psz;
//
//
//   string str;
//   string strToken;
//
//   SMatches matches;
//
//   return parse(strSubject, &matches);
//
//}
//
//
//
//bool cregexp::replace(string & str, const string & strTopicParam, index iSubString, const string & strReplace, strsize start, strsize end)
//{
//
//   str = strTopicParam;
//
//   return replace(str, iSubString, strReplace, start, end);
//
//}
//
//bool cregexp::replace(string & str, index iSubString, const string & strReplace, strsize start, strsize end)
//{
//   string strTopic(str.Left(end));
//   strsize iSubstLen = strReplace.length();
//   string strMatch;
//   while(true)
//   {
//      end = str.length();
//      if(!find(strMatch, str, iSubString, &start, &end))
//         break;
//      str = str.Left(start) + strReplace + str.Mid(end);
//      end = start + iSubstLen;
//   }
//   return true;
//}
