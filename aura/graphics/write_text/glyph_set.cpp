// From draw2d component by camilo on 2022-08-28 16:58 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "glyph_set.h"


namespace write_text
{


   glyph_set::glyph_set()
   {

   }


   glyph_set::~glyph_set()
   {

   }


   glyph * glyph_set::GetGlyph(::u32 user)
   {

      index i = find_first(user);

      if (i >= 0)
      {

         return &this->element_at(i);

      }
      else
      {

         return nullptr;

      }

   }


   index glyph_set::find_first(::u32 user)
   {

      index iLoBound = 0;
      index iHiBound = this->get_size() - 1;
      index iIndex = 0;;
      while(true)
      {
         if(iLoBound > iHiBound)
         {
            return -1;
         }
         iIndex = (iHiBound + iLoBound) / 2;
         if(user == this->element_at(iIndex).m_ui)
            break;
         else if(user < this->element_at(iIndex).m_ui)
         {
            iHiBound = iIndex - 1;
            if(iHiBound < iLoBound)
            {
               return -1;
            }
         }
         else if(user > this->element_at(iIndex).m_ui)
         {
            iLoBound = iIndex + 1;
            if(iLoBound > iHiBound)
            {
               return -1;
            }
         }
         else
            ASSERT(0);
      }
      index iLastIndex = iIndex;
      while(true)
      {
         iIndex--;
         if(iIndex < 0)
            break;
         if(user != this->element_at(iIndex).m_ui)
            break;
         iLastIndex = iIndex;
      }
      return iLastIndex;
   }

   void glyph_set::quick_sort()
   {
      index_array stackLowerBound;
      index_array stackUpperBound;
      index iLowerBound;
      index iUpperBound;
      index iLPos, iUPos, iMPos;
      glyph glyph;

      if(this->get_size() >= 2)
      {
         stackLowerBound.push(0UL);
         stackUpperBound.push(this->get_size() - 1);
         while(true)
         {
            iLowerBound = stackLowerBound.pop();
            iUpperBound = stackUpperBound.pop();
            iLPos = iLowerBound;
            iMPos = iLowerBound;
            iUPos = iUpperBound;
            while(true)
            {
               while(true)
               {
                  if(iMPos == iUPos)
                     break;
                  if(this->element_at(iMPos) <= this->element_at(iUPos))
                     iUPos--;
                  else
                  {
                     glyph = this->element_at(iMPos);
                     set_at(iMPos, this->element_at(iUPos));
                     set_at(iUPos, glyph);
                     break;
                  }
               }
               if(iMPos == iUPos)
                  break;
               iMPos = iUPos;
               while(true)
               {
                  if(iMPos == iLPos)
                     break;
                  if(this->element_at(iLPos) <= this->element_at(iMPos))
                     iLPos++;
                  else
                  {
                     glyph = this->element_at(iMPos);
                     set_at(iMPos, this->element_at(iLPos));
                     set_at(iLPos, glyph);
                     break;
                  }
               }
               if(iMPos == iLPos)
                  break;
               iMPos = iLPos;
            }
            if(iLowerBound < iMPos - 1)
            {
               stackLowerBound.push(iLowerBound);
               stackUpperBound.push(iMPos - 1);
            }
            if(iMPos + 1 < iUpperBound)
            {
               stackLowerBound.push(iMPos + 1);
               stackUpperBound.push(iUpperBound);
            }
            if(stackLowerBound.get_size() == 0)
               break;
         }
      }

   }


   index glyph_set::add(class glyph &glyph)
   {
      iptr i = (int)array < class glyph, class glyph & >::add(glyph);
      quick_sort();
      return i;
   }


} // namespace write_text



