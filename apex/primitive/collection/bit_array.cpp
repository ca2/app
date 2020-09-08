#include "framework.h"


#undef new


bit_array::bit_array()
{
   m_pdata        = nullptr;
   m_iDataCount   = 0;
   m_iBitCount    = 0;
}

bit_array::~bit_array()
{
   if(m_pdata != nullptr && ::index(m_pdata) != 1)
      delete[] m_pdata;
}

void bit_array::ensure_size(i32 iSize, bool bSet)
{
   if(m_pdata == nullptr
   || ::index(m_pdata) == 1
   || iSize > m_iBitCount)
   {
      set_size(iSize, bSet);
   }
}

void bit_array::set_size(i32 iBitCount, bool bSet)
{
   i32 * pdataOld       = m_pdata;
//   i32 iOldDataCount    = m_iDataCount;
   i32 iOldBitCount     = m_iBitCount;
   m_iBitCount          = iBitCount;
   m_iDataCount         = (i32) ceil_div(m_iBitCount, (i32) 8 * sizeof(i32));
   if(m_iDataCount > 0)
   {
      m_pdata              = new i32[m_iDataCount];
      if(m_pdata != nullptr)
      {
         if(::index(pdataOld) == 1)
         {
            ::apex::bit::set(m_pdata, true, 0, m_iDataCount * 8 * sizeof(i32) - 1);
         }
         else if(pdataOld != nullptr)
         {
            ::apex::bit::int_aligned_copy(m_pdata, 0, pdataOld, 0, iOldBitCount - 1);
            delete [] pdataOld;
         }
         if(iOldBitCount < m_iBitCount)
         {
            ::apex::bit::set(m_pdata, bSet, iOldBitCount, m_iBitCount - 1);
         }
      }
   }
   else
   {
      if(bSet)
      {
         m_pdata = (i32 *) 1;
      }
      else
      {
         m_pdata = 0;
      }
   }
}

i32 bit_array::get_size()
{
   return m_iBitCount;
}

void bit_array::set_bit(i32 pos)
{
   if(::index(m_pdata)== 1)
      return;
   ensure_size(pos + 1);
   m_pdata[pos>>5] |= 1 << (pos&0x1f);
}

void bit_array::clear_bit(i32 pos)
{
   if(m_pdata == nullptr)
      return;
   ensure_size(pos + 1, true);
   m_pdata[pos>>5] &= ~(1 << (pos&0x1f));
}

void bit_array::add_range(i32 s, i32 e)
{
   if(::index(m_pdata) == 1)
      return;
   ensure_size(e + 1);
   i32 cs = s>>5;
   i32 ce = e >> 5;
   if (s&0x1f)
   {
      i32 fillbytes = 0xffffffff << (s& 0x1f);
      if(cs == ce)
         fillbytes &= 0xffffffff >> (0x1f - (e & 0x1f));
      m_pdata[cs] |= fillbytes;
      cs++;
   }
   if (s>>5 != ce && (e&0x1f) != 0x1f)
   {
      m_pdata[ce] |= 0xffffffff >> ((0x1F - e) & 0x1F);
      ce--;
   }
   for(i32 idx = cs; idx <= ce; idx++)
      m_pdata[idx] = 0xffffffff;
   if (cs == 0 && ce == m_iDataCount-1)
   {
      delete[] m_pdata;
      m_pdata = (i32*)1;
   }
}

void bit_array::clear_range(i32 s, i32 e)
{
   if(m_pdata == nullptr)
      return;
   ensure_size(e + 1, true);
   i32 cs = s >> 5;
   i32 ce = e >> 5;
   if (s&0x1f)
   {
      i32 fillbytes = 0xffffffff << (s& 0x1f);
      if(cs == ce)
         fillbytes &= 0xffffffff >> (0x1f - (e & 0x1f));
      m_pdata[cs] &= ~fillbytes;
      cs++;
   }
   if (cs < ce && (e&0x1f) != 0x1f)
   {
      m_pdata[ce] &= ~(0xffffffff >> (0x1f - (e & 0x1f)));
      ce--;
   }
   for(i32 idx = cs; idx <= ce; idx++)
      m_pdata[idx] = 0x0;
   if(cs == 0 && ce == m_iDataCount - 1 && m_pdata != 0 && m_pdata != (i32 *) 1)
   {
      delete[] m_pdata;
      m_pdata = (i32*)0;
   }
}

void bit_array::add_bit_array(bit_array & ba)
{
   if(::index(m_pdata) == 1)
      return;
   if(::is_null_ref(ba) || ::is_null(ba.m_pdata))
      return;
   if(::index(ba.m_pdata) == 1)
   {
      m_pdata = (i32*)1;
      return;
   }
   ensure_size(ba.get_size());
   for(i32 i = 0; i < m_iDataCount; i++)
      m_pdata[i] |= ba.m_pdata[i];
}

void bit_array::clear_bit_array(bit_array & ba)
{

  if(m_pdata == nullptr)
  {

     return;

  }

  if(is_null_ref(ba) || ::is_null(ba.m_pdata))
  {

     return;

  }

  if(::index(ba.m_pdata) == 1)
  {
    if(m_pdata != nullptr && ::index(m_pdata) != 1)
       delete[] m_pdata;
    m_pdata = nullptr;
    return;
  }
  ensure_size(ba.get_size(), true);
  for(i32 i = 0; i < ba.m_iDataCount && i < m_iDataCount; i++)
   m_pdata[i] &= ~ba.m_pdata[i];
}

void bit_array::intersect_bit_array(bit_array & ba)
{
   if(m_pdata == nullptr)
      return;
   if(ba.m_pdata == nullptr)
   {
      delete[] m_pdata;
      m_pdata = 0;
      return;
   }
   if(::index(ba.m_pdata) == 1)
      return;
   ensure_size(ba.get_size(), true);
   for(i32 i = 0; i < ba.m_iDataCount && i < m_iDataCount; i++)
      m_pdata[i] &= ba.m_pdata[i];
}

void bit_array::add_bit_array(char *bits, i32 count)
{
   if (::index(m_pdata) == 1) return;
   ensure_size(count * 8);
   for(i32 i = 0; i < count && i < m_iDataCount*4;i++)
      ((char*)m_pdata)[i] |= bits[i];
}

void bit_array::clear_bit_array(char *bits, i32 count)
{
   if(m_pdata == nullptr)
      return;
   ensure_size(count * 8, true);
   for(i32 i = 0; i < count && i < m_iDataCount*4;i++)
      ((char*)m_pdata)[i] &= ~bits[i];
}

bool bit_array::get_bit(i32 pos) const
{
   if(m_pdata == nullptr)
      return false;
   if(::index(m_pdata) == 1)
      return true;
   if(pos >= m_iBitCount)
      return false;
   return (m_pdata[pos>>5] & (1<<(pos&0x1f))) != 0;
}


/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is the Colorer Library.
 *
 * The Initial Developer of the Original Code is
 * Cail Lomecb <cail@nm.ru>.
 * Portions created by the Initial Developer are Copyright (C) 1999-2005
 * the Initial Developer.
 *
 * Contributor(s):
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */
