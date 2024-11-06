// Brought back on 2022-03-01 22:57 <3ThomasBorregaardS~rensen!!
#include "framework.h"
#include "true_type_font_utilities.h"
#include "acme/filesystem/file/file.h"
#include "acme/include/_c_swap.h"
#include "acme/platform/application.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "apex/platform/context.h"


// https://www.codeproject.com/Articles/2293/Retrieving-Font-Name-from-TTF-File
// Philip Patrick
// Team Leader Varonis
// Israel Israel


typedef struct _tagTT_OFFSET_TABLE
{
   unsigned short	uMajorVersion;
   unsigned short	uMinorVersion;
   unsigned short	uNumOfTables;
   unsigned short	uSearchRange;
   unsigned short	uEntrySelector;
   unsigned short	uRangeShift;
} TT_OFFSET_TABLE;

typedef struct _tagTT_TABLE_DIRECTORY
{
   char	szTag[4];			//table name
   unsigned int	uCheckSum;			//Check sum
   unsigned int	uOffset;			//Offset from beginning of file
   unsigned int	uLength;			//length of the table in bytes
} TT_TABLE_DIRECTORY;

typedef struct _tagTT_NAME_TABLE_HEADER
{
   unsigned short	uFSelector;			//format selector. Always 0
   unsigned short	uNRCount;			//Name Records count
   unsigned short	uStorageOffset;		//Offset for strings storage, from start of the table
} TT_NAME_TABLE_HEADER;

typedef struct _tagTT_NAME_RECORD
{
   unsigned short	uPlatformID;
   unsigned short	uEncodingID;
   unsigned short	uLanguageID;
   unsigned short	uNameID;
   unsigned short	uStringLength;
   unsigned short	uStringOffset;	//from start of storage area
} TT_NAME_RECORD;



true_type_font_utilities::true_type_font_utilities()
{


}


true_type_font_utilities::~true_type_font_utilities()
{


}


string true_type_font_utilities::GetFontNameFromFile(const ::file::path & path)
{

   auto pcontext = m_papplication;

   file_pointer f = file()->get_file(path, ::file::e_open_read | ::file::e_open_share_deny_write);

   string csRetVal;

   if (f.is_null())
   {

      return "";

   }

   TT_OFFSET_TABLE ttOffsetTable;
   f->read({ e_as_block, ttOffsetTable });
   ttOffsetTable.uNumOfTables = swap_u16(ttOffsetTable.uNumOfTables);
   ttOffsetTable.uMajorVersion = swap_u16(ttOffsetTable.uMajorVersion);
   ttOffsetTable.uMinorVersion = swap_u16(ttOffsetTable.uMinorVersion);

   //check is this is a true type font and the version is 1.0
   if (ttOffsetTable.uMajorVersion != 1 || ttOffsetTable.uMinorVersion != 0)
      return csRetVal;

   TT_TABLE_DIRECTORY tblDir;
   int_bool bFound = false;
   string csTemp;

   for (int i = 0; i < ttOffsetTable.uNumOfTables; i++)
   {
      f->read({ e_as_block, &tblDir });
      ansi_ncpy(csTemp.get_buffer(5), tblDir.szTag, 4);
      csTemp.release_buffer(4);
      if (csTemp.case_insensitive_order("name") == 0)
      {
         bFound = true;
         tblDir.uLength = swap_u32(tblDir.uLength);
         tblDir.uOffset = swap_u32(tblDir.uOffset);
         break;
      }
   }

   if (bFound)
   {
      f->set_position(tblDir.uOffset);
      TT_NAME_TABLE_HEADER ttNTHeader;
      f->read({ e_as_block, ttNTHeader });
      ttNTHeader.uNRCount = swap_u16(ttNTHeader.uNRCount);
      ttNTHeader.uStorageOffset = swap_u16(ttNTHeader.uStorageOffset);
      TT_NAME_RECORD ttRecord;
      bFound = false;

      for (int i = 0; i < ttNTHeader.uNRCount; i++)
      {
         f->read({ e_as_block, ttRecord });
         ttRecord.uNameID = swap_u16(ttRecord.uNameID);
         if (ttRecord.uNameID == 1)
         {
            ttRecord.uStringLength = swap_u16(ttRecord.uStringLength);
            ttRecord.uStringOffset = swap_u16(ttRecord.uStringOffset);
            
            auto nPos = f->get_position();
            
            f->set_position(tblDir.uOffset + ttRecord.uStringOffset + ttNTHeader.uStorageOffset);

            //bug fix: see the post by SimonSays to read more about it
            char* lpszNameBuf = csTemp.get_buffer(ttRecord.uStringLength + 1);
            memory_set(lpszNameBuf, 0, ttRecord.uStringLength + 1);
            f->read({ lpszNameBuf, ttRecord.uStringLength });
            csTemp.release_buffer();
            if (csTemp.length() > 0)
            {

               csRetVal = csTemp;

               break;

            }

            f->set_position(nPos);

         }

      }

   }

   f->close();

   return csRetVal;

}

