#include "framework.h"

#define N1_A 0
#define N1_B 1
#define N1_C 2
#define N1_D 3
#define N1_E 4
#define N1_F 5
#define N1_G 6
#define N1_H 7
#define N1_I 8
#define N1_J 9
#define N1_K 10
#define N1_L 11
#define N1_M 12
#define N1_N 13
#define N1_O 14
#define N1_P 15
#define N1_Q 16
#define N1_R 17
#define N1_S 18
#define N1_T 19
#define N1_U 20
#define N1_V 21
#define N1_W 22
#define N1_X 23
#define N1_Y 24
#define N1_Z 25
#define N1_a 26
#define N1_b 27
#define N1_c 28
#define N1_d 29
#define N1_e 30
#define N1_f 31
#define N1_g 32
#define N1_h 33
#define N1_i 34
#define N1_j 35
#define N1_k 36
#define N1_l 37
#define N1_m 38
#define N1_n 39
#define N1_o 40
#define N1_p 41
#define N1_q 42
#define N1_r 43
#define N1_s 44
#define N1_t 45
#define N1_u 46
#define N1_v 47
#define N1_w 48
#define N1_x 49
#define N1_y 50
#define N1_z 51
#define N1_0 52
#define N1_1 53
#define N1_2 54
#define N1_3 55
#define N1_4 56
#define N1_5 57
#define N1_6 58
#define N1_7 59
#define N1_8 60
#define N1_9 61
#define N1_plus 62
#define N1_slash 63


static const char base64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

CLASS_DECL_ACME char* _crypto_base64_encode(const BYTE* data, int length)
{
   int c;
   const BYTE* q;
   char* point;
   char* ret;
   int i = 0;
   int blocks;

   q = data;
   point = ret = (char*)malloc((length + 3) * 4 / 3 + 1);
   if (!point)
      return nullptr;

   /* b1, b2, b3 are input bytes
    *
    * 0         1         2
    * 012345678901234567890123
    * |  b1  |  b2   |  b3   |
    *
    * [ c1 ]     [  c3 ]
    *      [  c2 ]     [  c4 ]
    *
    * c1, c2, c3, c4 are output chars in base64
    */

   /* first treat complete blocks */
   blocks = length - (length % 3);
   for (i = 0; i < blocks; i += 3, q += 3)
   {
      c = (q[0] << 16) + (q[1] << 8) + q[2];

      *point++ = base64[(c & 0x00FC0000) >> 18];
      *point++ = base64[(c & 0x0003F000) >> 12];
      *point++ = base64[(c & 0x00000FC0) >> 6];
      *point++ = base64[c & 0x0000003F];
   }

   /* then remainder */
   switch (length % 3)
   {
   case 0:
      break;
   case 1:
      c = (q[0] << 16);
      *point++ = base64[(c & 0x00FC0000) >> 18];
      *point++ = base64[(c & 0x0003F000) >> 12];
      *point++ = '=';
      *point++ = '=';
      break;
   case 2:
      c = (q[0] << 16) + (q[1] << 8);
      *point++ = base64[(c & 0x00FC0000) >> 18];
      *point++ = base64[(c & 0x0003F000) >> 12];
      *point++ = base64[(c & 0x00000FC0) >> 6];
      *point++ = '=';
      break;
   }

   *point = 0;

   return ret;
}

static int _base64_decode_char(char c)
{
   if (c >= 'A' && c <= 'Z')
      return c - 'A';

   if (c >= 'a' && c <= 'z')
      return c - 'a' + 26;

   if (c >= '0' && c <= '9')
      return c - '0' + 52;

   if (c == '+')
      return 62;

   if (c == '/')
      return 63;

   if (c == '=')
      return -1;

   return -1;
}

static void* _base64_decode(const char* s, int length, int* data_len)
{
   int n[4];
   BYTE* q;
   BYTE* data;
   int nBlocks, i, outputLen;

   if (length % 4)
      return nullptr;

   q = data = (BYTE*)malloc(length / 4 * 3 + 1);
   if (!q)
      return nullptr;

   /* first treat complete blocks */
   nBlocks = (length / 4);
   outputLen = 0;

   for (i = 0; i < nBlocks - 1; i++, q += 3)
   {
      n[0] = _base64_decode_char(*s++);
      n[1] = _base64_decode_char(*s++);
      n[2] = _base64_decode_char(*s++);
      n[3] = _base64_decode_char(*s++);

      if ((n[0] == -1) || (n[1] == -1) || (n[2] == -1) || (n[3] == -1))
         goto out_free;

      q[0] = (n[0] << 2) + (n[1] >> 4);
      q[1] = ((n[1] & 15) << 4) + (n[2] >> 2);
      q[2] = ((n[2] & 3) << 6) + n[3];
      outputLen += 3;
   }

   /* treat last block */
   n[0] = _base64_decode_char(*s++);
   n[1] = _base64_decode_char(*s++);
   if ((n[0] == -1) || (n[1] == -1))
      goto out_free;

   n[2] = _base64_decode_char(*s++);
   n[3] = _base64_decode_char(*s++);

   q[0] = (n[0] << 2) + (n[1] >> 4);
   if (n[2] == -1)
   {
      /* XX== */
      outputLen += 1;
      if (n[3] != -1)
         goto out_free;

      q[1] = ((n[1] & 15) << 4);
   }
   else if (n[3] == -1)
   {
      /* yyy= */
      outputLen += 2;
      q[1] = ((n[1] & 15) << 4) + (n[2] >> 2);
      q[2] = ((n[2] & 3) << 6);
   }
   else
   {
      /* XXXX */
      outputLen += 3;
      q[0] = (n[0] << 2) + (n[1] >> 4);
      q[1] = ((n[1] & 15) << 4) + (n[2] >> 2);
      q[2] = ((n[2] & 3) << 6) + n[3];
   }

   *data_len = outputLen;
   data[outputLen] = '\0';

   return data;
out_free:
   free(data);
   return nullptr;
}

CLASS_DECL_ACME void _crypto_base64_decode(const char* enc_data, int length, BYTE** dec_data, int* res_length)
{
   *dec_data = (BYTE *) _base64_decode(enc_data, length, res_length);
}



namespace str
{


   base64::base64()
   {

      i32 i, j;

      // etable
      for (j = 0; j < 3; j++)
      {
         for (i = 0; i < 9; i++)
         {
            etable[j][i + N1_A] = (uchar)('A' + i);
            etable[j][i + N1_J] = (uchar)('J' + i);
            etable[j][i + N1_a] = (uchar)('a' + i);
            etable[j][i + N1_j] = (uchar)('j' + i);
         }
         for (i = 0; i < 8; i++)
         {
            etable[j][i + N1_S] = (uchar)('S' + i);
            etable[j][i + N1_s] = (uchar)('s' + i);
         }
         for(i= 0; i<10; i++)
         {
            etable[j][i+N1_0]    = (uchar) ('0'+i);
         }
      }
      etable[mode_normal][N1_plus]      = (uchar) ('+');
      etable[mode_normal][N1_slash]     = (uchar) ('/');
      etable[mode_url_safe][N1_plus] = (uchar)('-');
      etable[mode_url_safe][N1_slash] = (uchar)('_');
      etable[mode_ex][N1_plus] = (uchar)('.');
      etable[mode_ex][N1_slash] = (uchar)('_');


      // dtable
      for(i= 0; i<255; i++)
      {
         dtable[i]= 0x80;
      }
      for(i= 'A'; i<='I'; i++)
      {
         dtable[i]= (uchar) (N1_A+(i-'A'));
      }
      for(i= 'J'; i<='R'; i++)
      {
         dtable[i]= (uchar) (N1_J+(i-'J'));
      }
      for(i= 'S'; i<='Z'; i++)
      {
         dtable[i]= (uchar) (N1_S+(i-'S'));
      }
      for(i= 'a'; i<='i'; i++)
      {
         dtable[i]= (uchar) (N1_a+(i-'a'));
      }
      for(i= 'j'; i<='r'; i++)
      {
         dtable[i]= (uchar) (N1_j+(i-'j'));
      }
      for(i= 's'; i<='z'; i++)
      {
         dtable[i]= (uchar) (N1_s+(i-'s'));
      }
      for(i= '0'; i<='9'; i++)
      {
         dtable[i]= (uchar) (N1_0+(i-'0'));
      }
      dtable['+']= (uchar) (N1_plus);
      dtable['/']= (uchar) (N1_slash);
      dtable['-'] = (uchar)(N1_plus);
      dtable['_'] = (uchar)(N1_slash);
      dtable['.'] = (uchar)(N1_plus);
      dtable['=']= (uchar) (0);
   }


   base64::~base64()
   {

   }


   ::estatus base64::initialize(::layered * pobjectContext)
   {

      auto estatus = ::matter::initialize(pobjectContext);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   void base64::encode(::file::file * pfileOutput, ::file::file * pfileInput, e_mode emode)
   {

      i32 i,hiteof= FALSE;
      byte igroup[3],ogroup[4];
      i32 n;
      char ch;

      uchar * enc_table = this->etable[emode];

      while(!hiteof)
      {
         igroup[0]= igroup[1]= igroup[2]= 0;
         for(n= 0; n<3; n++)
         {
            if(pfileInput->read(&ch, 1) == 0)
            {
               hiteof= TRUE;
               break;
            }
            igroup[n]= (uchar)ch;
         }
         if(n> 0)
         {
            ogroup[0]= enc_table[igroup[0]>>2];
            ogroup[1]= enc_table[((igroup[0]&3)<<4)|(igroup[1]>>4)];
            ogroup[2]= enc_table[((igroup[1]&0xF)<<2)|(igroup[2]>>6)];
            ogroup[3]= enc_table[igroup[2]&0x3F];
            if(n<3)
            {
               ogroup[3]= '=';
               if(n<2)
               {
                  ogroup[2]= '=';
               }
            }
            for(i= 0; i<4; i++)
            {
               pfileOutput->write(&ogroup[i], 1);
            }
         }
      }
   }


   void base64::encode(::file::file *pfileOutput, u8 * pdata, memsize size, e_mode emode)
   {

      i32 i, hiteof = FALSE;
      byte igroup[3], ogroup[4];
      i32 n;
      char ch;

      uchar * enc_table = this->etable[emode];

      memory m;

      while (!hiteof)
      {
         igroup[0] = igroup[1] = igroup[2] = 0;
         for (n = 0; n < 3; n++)
         {
            if (read_char(pdata, size, &ch) == 0)
            {
               hiteof = TRUE;
               break;
            }
            igroup[n] = (uchar)ch;
         }
         if (n > 0)
         {
            ogroup[0] = enc_table[igroup[0] >> 2];
            ogroup[1] = enc_table[((igroup[0] & 3) << 4) | (igroup[1] >> 4)];
            ogroup[2] = enc_table[((igroup[1] & 0xF) << 2) | (igroup[2] >> 6)];
            ogroup[3] = enc_table[igroup[2] & 0x3F];
            if (n < 3)
            {
               ogroup[3] = '=';
               if (n < 2)
               {
                  ogroup[2] = '=';
               }
            }
            for (i = 0; i < 4; i++)
            {
               m.append(&ogroup[i], 1);
            }
         }
      }
      pfileOutput->write(m.get_data(), m.get_size());
   }


   bool base64::decode(::file::file * pfileOutput, ::file::file * pfileInput)
   {
      i32 i;
      byte a[4],b[4],o[3];
      uchar uch;

      while(true)
      {
         for(i= 0; i<4; i++)
         {
            if(pfileInput->read(&uch, 1) == 0)
            {
               if( i > 0)
               {
                  //__throw(io_exception("Input file incomplete.\n"));
                  //ASSERT(FALSE);
                  return false;
               }
               return true;
            }
            if(dtable[uch]&0x80)
            {

               string str;

               str.Format("Illegal character '%ca' in input spfile->\n", uch);

               //__throw(io_exception(str));
               return false;

//               i--;
//
//               continue;

            }
            a[i]= (uchar) uch;
            b[i]= (uchar) dtable[uch];
         }
         o[0]= (b[0]<<2)|(b[1]>>4);
         o[1]= (b[1]<<4)|(b[2]>>2);
         o[2]= (b[2]<<6)|b[3];
         i= a[2]=='='?1:(a[3]=='='?2:3);
         pfileOutput->write(o, i);

         if (i < 3)
         {

            break;

         }

      }

      return true;

   }


   i64 base64::decode(const ::block & block, ::file::file * pfileInput)
   {
      i32 i;
      byte a[4],b[4],o[3];
      uchar uch;
      u8 * pdata = (u8 *)block.get_data();
      i64 iDecode = 0;
      memsize rem = block.get_size();
      while(rem > 0)
      {
         for(i= 0; i<4; i++)
         {
            if(pfileInput->read(&uch, 1) == 0)
            {
               if( i > 0)
               {
                  //__throw(io_exception("Input file incomplete.\n"));
                  //ASSERT(FALSE);
                  return -1;
               }
               return iDecode;
            }
            if(dtable[uch]&0x80)
            {

               string str;

               str.Format("Illegal character '%ca' in input spfile->\n", uch);

               //__throw(io_exception(str));
               return -1;

//               i--;
//
//               continue;

            }
            a[i]= (uchar) uch;
            b[i]= (uchar) dtable[uch];
         }
         o[0]= (b[0]<<2)|(b[1]>>4);
         o[1]= (b[1]<<4)|(b[2]>>2);
         o[2]= (b[2]<<6)|b[3];
         i= a[2]=='='?1:(a[3]=='='?2:3);
         i = min(i, (i32) rem);
         for (index idx = 0; idx < i; idx++)
         {
            *pdata = o[idx];

            pdata++;

         }
         rem -= i;
         iDecode += i;
         if (i < 3)
         {

            break;

         }

      }

      return iDecode;

   }


   string base64::encode(const ::block & block, e_mode emode)
   {

      ::string_file file;

      encode(&file, (u8 *) block.m_pdata, (memsize) block.m_iSize, emode);

      return file.m_str;

   }


//   string base64::encode(memory_base & mem, e_mode emode)
//   {
//
//      return encode(mem.get_data(), mem.get_size(), emode);
//
//   }


//   string base64::encode(const ::block & block, e_mode emode)
//   {
//
//      return encode(block.get_data(), block.get_size(), emode);
//
//   }



   string base64::decode(const char * pszBase64)
   {

      memory storage;

      decode(storage, pszBase64);

      string str;

      ::memcpy_dup(
      str.get_string_buffer(storage.get_size()),
      storage.get_data(),
      storage.get_size());

      str.release_string_buffer();

      return str;

   }


   bool base64::decode(memory_base & storageBinary, const char * pszBase64, strsize s)
   {

      string str(pszBase64, s);

      ::string_file fileIn(str);

      memory_file fileOut(storageBinary);

      return decode(&fileOut, &fileIn);

   }


   i64 base64::decode(const ::block & block, const char * pszBase64, strsize s)
   {

      string str(pszBase64, s);

      ::string_file fileIn(str);

      return decode(block, &fileIn);

   }


   string base64::encode_element(::matter & matter, e_mode emode)
   {

      ::memory_stream streamObject;

      streamObject.set_storing();

      matter.write(streamObject);

      auto str = encode(streamObject->memory());

      return str;

   }


   bool base64::decode(::matter & matter, const char * pszBase64)
   {

      ::string_file fileIn(pszBase64);

      ::memory_stream streamObject;

      if (!decode(streamObject->memory(), &fileIn))
      {
         return false;
      }

      matter.read(streamObject);

      return true;

   }

   // https://stackoverflow.com/questions/13195143/range-of-valid-character-for-a-base-64-encoding

   bool base64::is(int iChar)
   {

      if (iChar >= 'A' && iChar <= 'Z')
      {

         return true;

      }
      else if (iChar >= 'a' && iChar <= 'z')
      {

         return true;

      }
      else if (iChar >= '0' && iChar <= '9')
      {

         return true;

      }
      else if (iChar == '+')
      {

         return true;

      }
      else if (iChar == '/')
      {

         return true;

      }
      else if (iChar == '-')  // RFC 4648 (+)
      {

         return true;

      }
      else if (iChar == '_')// RFC 4648 (/)
      {

         return true;

      }
      else if (iChar == '=')
      {

         return true;

      }
      else
      {

         return false;

      }

   }

} // namespace str



