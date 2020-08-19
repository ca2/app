/* zip.ca -- IO on .zip files using zlib
   Version 1.00, September 10th, 2003

   Copyright (C) 1998-2003 Gilles Vollant

   read zip.h for more info
*/
#include "framework.h"
#include "_internal.h"

#if defined(WINDOWS) || defined(LINUX)
const z_crc_t * zip_get_crc_table() { return (const z_crc_t * ) get_crc_table(); }
#else
const uLongf * zip_get_crc_table() { return (const uLongf *)get_crc_table(); }
#endif

/* compile with -Dlocal if your debugger can't find static symbols */

#ifndef VERSIONMADEBY
# define VERSIONMADEBY   (0x0) /* platform depedent */
#endif

#ifndef Z_BUFSIZE
#define Z_BUFSIZE (16384)
#endif

#ifndef Z_MAXFILENAMEINZIP
#define Z_MAXFILENAMEINZIP (256)
#endif

#ifndef ALLOC
# define ALLOC(size) (malloc(size))
#endif
#ifndef TRYFREE
# define TRYFREE(point) {if (point) free(point);}
#endif

/*
#define SIZECENTRALDIRITEM (0x2e)
#define SIZEZIPLOCALHEADER (0x1e)
*/

/* I've found an old Unix (a SunOS 4.1.3_U1) without all SEEK_* defined.... */

#ifndef SEEK_CUR
#define SEEK_CUR    1
#endif

#ifndef SEEK_END
#define SEEK_END    2
#endif

#ifndef SEEK_SET
#define SEEK_SET    0
#endif

#ifndef DEF_MEM_LEVEL
#if MAX_MEM_LEVEL >= 8
#  define DEF_MEM_LEVEL 8
#else
#  define DEF_MEM_LEVEL  MAX_MEM_LEVEL
#endif
#endif
//const char zip_copyright[] =
// " zip 1.00 Copyright 1998-2003 Gilles Vollant - http://www.winpimage->com/zLibDll";


#define SIZEDATA_INDATABLOCK (4096-(4*4))

#define LOCALHEADERMAGIC    (0x04034b50)
#define CENTRALHEADERMAGIC  (0x02014b50)
#define ENDHEADERMAGIC      (0x06054b50)

#define FLAG_LOCALHEADER_OFFSET (0x06)
#define CRC_LOCALHEADER_OFFSET  (0x0e)

#define SIZECENTRALHEADER (0x2e) /* 46 */

typedef struct linkedlist_datablock_internal_s
{
   struct linkedlist_datablock_internal_s* next_datablock;
   uptr  avail_in_this_block;
   uptr  filled_in_this_block;
   uptr  unused; /* for future use and alignement */
   uchar data[SIZEDATA_INDATABLOCK];
} linkedlist_datablock_internal;

typedef struct linkedlist_data_s
{
   linkedlist_datablock_internal* first_block;
   linkedlist_datablock_internal* last_block;
} linkedlist_data;


typedef struct
{
   z_stream stream;            /* zLib stream structure for inflate */
   i32  stream_initialised;    /* 1 is stream is initialised */
   uptr pos_in_buffered_data;  /* last written byte in buffered_data */

   uptr pos_local_header;     /* offset of the static header of the file
                                     currenty writing */
   char* central_header;       /* central header data for the current file */
   uptr size_centralheader;   /* size of the central header for cur file */
   uptr flag;                 /* flag of the file currently writing */

   i32  method;                /* compression method of file currenty wr.*/
   i32  raw;                   /* 1 for directly writing raw data */
   byte buffered_data[Z_BUFSIZE];/* buffer contain compressed data to be writ*/
   uptr dosDate;
   u32 crc32;
   i32  encrypt;
#ifndef NOCRYPT
   u32  keys[3];     /* keys defining the pseudo-random sequence */
#if defined(WINDOWS) || defined(LINUX)
   const z_crc_t * pcrc_32_tab;
#else
   const uLongf * pcrc_32_tab;
#endif
   i32 crypt_header_size;
#endif
} curfile_info;

typedef struct
{
   zlib_filefunc_def z_filefunc;
   voidpf filestream;        /* io structore of the zipfile */
   linkedlist_data central_dir;/* datablock with central dir in construction*/
   i32  in_opened_file_inzip;  /* 1 if a file in the zip is currently writ.*/
   curfile_info ci;            /* info on the file curretly writing */

   uptr begin_pos;            /* position of the beginning of the zipfile */
   uptr add_position_when_writting_offset;
   uptr number_entry;
} zip_internal;



#ifndef NOCRYPT
#define INCLUDECRYPTINGCODE_IFCRYPTALLOWED
#include "crypt.h"
#endif

static linkedlist_datablock_internal* allocate_new_datablock()
{
   linkedlist_datablock_internal* ldi;
   ldi = (linkedlist_datablock_internal*)
         ALLOC(sizeof(linkedlist_datablock_internal));
   if (ldi!=nullptr)
   {
      ldi->next_datablock = nullptr ;
      ldi->filled_in_this_block = 0 ;
      ldi->avail_in_this_block = SIZEDATA_INDATABLOCK ;
   }
   return ldi;
}

static void free_datablock(
linkedlist_datablock_internal* ldi)
{
   while (ldi!=nullptr)
   {
      linkedlist_datablock_internal* ldinext = ldi->next_datablock;
      TRYFREE(ldi);
      ldi = ldinext;
   }
}

static void init_linkedlist(
linkedlist_data* ll)
{
   ll->first_block = ll->last_block = nullptr;
}

void free_linkedlist(
linkedlist_data* ll);


void free_linkedlist(
linkedlist_data* ll)
{
   free_datablock(ll->first_block);
   ll->first_block = ll->last_block = nullptr;
}


static i32 add_data_in_datablock(
linkedlist_data* ll,
const void * buf,
uptr len)
{
   linkedlist_datablock_internal* ldi;
   const uchar* from_copy;

   if (ll==nullptr)
      return ZIP_INTERNALERROR;

   if (ll->last_block == nullptr)
   {
      ll->first_block = ll->last_block = allocate_new_datablock();
      if (ll->first_block == nullptr)
         return ZIP_INTERNALERROR;
   }

   ldi = ll->last_block;
   from_copy = (uchar*)buf;

   while (len>0)
   {
      u32 copy_this;
      u32 i;
      uchar* to_copy;

      if (ldi->avail_in_this_block==0)
      {
         ldi->next_datablock = allocate_new_datablock();
         if (ldi->next_datablock == nullptr)
            return ZIP_INTERNALERROR;
         ldi = ldi->next_datablock ;
         ll->last_block = ldi;
      }

      if (ldi->avail_in_this_block < len)
         copy_this = (u32)ldi->avail_in_this_block;
      else
         copy_this = (u32)len;

      to_copy = &(ldi->data[ldi->filled_in_this_block]);

      for (i=0; i<copy_this; i++)
         *(to_copy+i)=*(from_copy+i);

      ldi->filled_in_this_block += copy_this;
      ldi->avail_in_this_block -= copy_this;
      from_copy += copy_this ;
      len -= copy_this;
   }
   return ZIP_OK;
}



/****************************************************************************/

#ifndef NO_ADDFILEINEXISTINGZIP
/* ===========================================================================
   Inputs a long in LSB order to the given file
   nbByte == 1, 2 or 4 (byte, i16 or long)
*/

static i32 ziplocal_putValue OF((const zlib_filefunc_def* pzlib_filefunc_def,
                                    voidpf filestream, uptr x, i32 nbByte));
static i32 ziplocal_putValue (
const zlib_filefunc_def* pzlib_filefunc_def,
voidpf filestream,
uptr x,
i32 nbByte)
{
   uchar buf[4];
   i32 n;
   for (n = 0; n < nbByte; n++)
   {
      buf[n] = (uchar)(x & 0xff);
      x >>= 8;
   }
   if (ZWRITE(*pzlib_filefunc_def,filestream,buf,nbByte)!=(uptr)nbByte)
      return ZIP_ERRNO;
   else
      return ZIP_OK;
}

static void ziplocal_putValue_inmemory OF((void * dest, uptr x, i32 nbByte));
static void ziplocal_putValue_inmemory (
void * dest,
uptr x,
i32 nbByte)
{
   uchar* buf=(uchar*)dest;
   i32 n;
   for (n = 0; n < nbByte; n++)
   {
      buf[n] = (uchar)(x & 0xff);
      x >>= 8;
   }
}
/****************************************************************************/


static uptr ziplocal_TmzDateToDosDate(
const tm_zip* ptm,
uptr dosDate)
{
   uptr year = (uptr)ptm->tm_year;
   if (year>1980)
      year-=1980;
   else if (year>80)
      year-=80;
   return
   (uptr) (((ptm->tm_mday) + (32 * (ptm->tm_mon+1)) + (512 * year)) << 16) |
   ((ptm->tm_sec/2) + (32* ptm->tm_min) + (2048 * (uptr)ptm->tm_hour));
}


/****************************************************************************/

static i32 ziplocal_getByte OF((
                                  const zlib_filefunc_def* pzlib_filefunc_def,
                                  voidpf filestream,
                                  i32 *pi));

static i32 ziplocal_getByte(
const zlib_filefunc_def* pzlib_filefunc_def,
voidpf filestream,
i32 *pi)
{
   uchar ca;
   i32 err = (i32)ZREAD(*pzlib_filefunc_def,filestream,&ca,1);
   if (err==1)
   {
      *pi = (i32)ca;
      return ZIP_OK;
   }
   else
   {
      if (ZERROR(*pzlib_filefunc_def,filestream))
         return ZIP_ERRNO;
      else
         return ZIP_EOF;
   }
}


/* ===========================================================================
   Reads a long in LSB order from the given gz_stream. Sets
*/
static i32 ziplocal_getShort OF((
                                   const zlib_filefunc_def* pzlib_filefunc_def,
                                   voidpf filestream,
                                   uptr *pX));

static i32 ziplocal_getShort (
const zlib_filefunc_def* pzlib_filefunc_def,
voidpf filestream,
uptr *pX)
{
   uptr x ;
   i32 i = 0;
   i32 err;

   err = ziplocal_getByte(pzlib_filefunc_def,filestream,&i);
   x = (uptr)i;

   if (err==ZIP_OK)
      err = ziplocal_getByte(pzlib_filefunc_def,filestream,&i);
   x += ((uptr)i)<<8;

   if (err==ZIP_OK)
      *pX = x;
   else
      *pX = 0;
   return err;
}

static i32 ziplocal_getLong OF((
                                  const zlib_filefunc_def* pzlib_filefunc_def,
                                  voidpf filestream,
                                  uptr *pX));

static i32 ziplocal_getLong (
const zlib_filefunc_def* pzlib_filefunc_def,
voidpf filestream,
uptr *pX)
{
   uptr x ;
   i32 i = 0;
   i32 err;

   err = ziplocal_getByte(pzlib_filefunc_def,filestream,&i);
   x = (uptr)i;

   if (err==ZIP_OK)
      err = ziplocal_getByte(pzlib_filefunc_def,filestream,&i);
   x += ((uptr)i)<<8;

   if (err==ZIP_OK)
      err = ziplocal_getByte(pzlib_filefunc_def,filestream,&i);
   x += ((uptr)i)<<16;

   if (err==ZIP_OK)
      err = ziplocal_getByte(pzlib_filefunc_def,filestream,&i);
   x += ((uptr)i)<<24;

   if (err==ZIP_OK)
      *pX = x;
   else
      *pX = 0;
   return err;
}

#ifndef BUFREADCOMMENT
#define BUFREADCOMMENT (0x400)
#endif
/*
  Locate the Central directory of a zipfile (at the end, just before
    the global comment)
*/
static uptr ziplocal_SearchCentralDir OF((
      const zlib_filefunc_def* pzlib_filefunc_def,
      voidpf filestream));

static uptr ziplocal_SearchCentralDir(
const zlib_filefunc_def* pzlib_filefunc_def,
voidpf filestream)
{
   uchar* buf;
   uptr uSizeFile;
   uptr uBackRead;
   uptr uMaxBack=0xffff; /* maximum size of global comment */
   uptr uPosFound=0;

   if (ZSEEK(*pzlib_filefunc_def,filestream,0,ZLIB_FILEFUNC_SEEK_END) != 0)
      return 0;


   uSizeFile = ZTELL(*pzlib_filefunc_def,filestream);

   if (uMaxBack>uSizeFile)
      uMaxBack = uSizeFile;

   buf = (uchar*)ALLOC(BUFREADCOMMENT+4);
   if (buf==nullptr)
      return 0;

   uBackRead = 4;
   while (uBackRead<uMaxBack)
   {
      uptr uReadSize,uReadPos ;
      i32 i;
      if (uBackRead+BUFREADCOMMENT>uMaxBack)
         uBackRead = uMaxBack;
      else
         uBackRead+=BUFREADCOMMENT;
      uReadPos = uSizeFile-uBackRead ;

      uReadSize = ((BUFREADCOMMENT+4) < (uSizeFile-uReadPos)) ?
                  (BUFREADCOMMENT+4) : (uSizeFile-uReadPos);
      if (ZSEEK(*pzlib_filefunc_def,filestream,uReadPos,ZLIB_FILEFUNC_SEEK_SET)!=0)
         break;

      if (ZREAD(*pzlib_filefunc_def,filestream,buf,uReadSize)!=uReadSize)
         break;

      for (i=(i32)uReadSize-3; (i--)>0;)
         if (((*(buf+i))==0x50) && ((*(buf+i+1))==0x4b) &&
               ((*(buf+i+2))==0x05) && ((*(buf+i+3))==0x06))
         {
            uPosFound = uReadPos+i;
            break;
         }

      if (uPosFound!=0)
         break;
   }
   TRYFREE(buf);
   return uPosFound;
}
#endif /* !NO_ADDFILEINEXISTINGZIP*/

/************************************************************/
extern zipFile CLASS_DECL_AURA zipOpen2 (
const char *pathname,
i32 append,
zipcharpc* globalcomment,
zlib_filefunc_def* pzlib_filefunc_def)
{
   zip_internal ziinit;
   zip_internal* zi;
   i32 err=ZIP_OK;


   if (pzlib_filefunc_def==nullptr)
      fill_fopen_filefunc(&ziinit.z_filefunc);
   else
      ziinit.z_filefunc = *pzlib_filefunc_def;

   ziinit.filestream = (*(ziinit.z_filefunc.zopen_file))
                       (ziinit.z_filefunc.opaque,
                        pathname,
                        (append == APPEND_STATUS_CREATE) ?
                        (ZLIB_FILEFUNC_MODE_READ | ZLIB_FILEFUNC_MODE_WRITE | ZLIB_FILEFUNC_MODE_CREATE) :
                        (ZLIB_FILEFUNC_MODE_READ | ZLIB_FILEFUNC_MODE_WRITE | ZLIB_FILEFUNC_MODE_EXISTING));

   if (ziinit.filestream == nullptr)
      return nullptr;
   ziinit.begin_pos = ZTELL(ziinit.z_filefunc,ziinit.filestream);
   ziinit.in_opened_file_inzip = 0;
   ziinit.ci.stream_initialised = 0;
   ziinit.number_entry = 0;
   ziinit.add_position_when_writting_offset = 0;
   init_linkedlist(&(ziinit.central_dir));


   zi = (zip_internal*)ALLOC(sizeof(zip_internal));
   if (zi==nullptr)
   {
      ZCLOSE(ziinit.z_filefunc,ziinit.filestream);
      return nullptr;
   }

   /* now we add file in a zipfile */
#    ifndef NO_ADDFILEINEXISTINGZIP
   if (append == APPEND_STATUS_ADDINZIP)
   {
      uptr byte_before_the_zipfile;/* byte before the zipfile, (>0 for sfx)*/

      uptr size_central_dir;     /* size of the central directory  */
      uptr offset_central_dir;   /* offset of start of central directory */
      uptr central_pos,uL;

      uptr number_disk;          /* number of the current dist, used for
                                    spaning ZIP, unsupported, always 0*/
      uptr number_disk_with_CD;  /* number the the disk with central dir, used
                                    for spaning ZIP, unsupported, always 0*/
      uptr number_entry;
      uptr number_entry_CD;      /* total number of entries in
                                    the central dir
                                    (same than number_entry on nospan) */
      uptr size_comment;

      central_pos = ziplocal_SearchCentralDir(&ziinit.z_filefunc,ziinit.filestream);
      if (central_pos==0)
         err=ZIP_ERRNO;

      if (ZSEEK(ziinit.z_filefunc, ziinit.filestream,
                central_pos,ZLIB_FILEFUNC_SEEK_SET)!=0)
         err=ZIP_ERRNO;

      /* the signature, already checked */
      if (ziplocal_getLong(&ziinit.z_filefunc, ziinit.filestream,&uL)!=ZIP_OK)
         err=ZIP_ERRNO;

      /* number of this disk */
      if (ziplocal_getShort(&ziinit.z_filefunc, ziinit.filestream,&number_disk)!=ZIP_OK)
         err=ZIP_ERRNO;

      /* number of the disk with the start of the central directory */
      if (ziplocal_getShort(&ziinit.z_filefunc, ziinit.filestream,&number_disk_with_CD)!=ZIP_OK)
         err=ZIP_ERRNO;

      /* total number of entries in the central dir on this disk */
      if (ziplocal_getShort(&ziinit.z_filefunc, ziinit.filestream,&number_entry)!=ZIP_OK)
         err=ZIP_ERRNO;

      /* total number of entries in the central dir */
      if (ziplocal_getShort(&ziinit.z_filefunc, ziinit.filestream,&number_entry_CD)!=ZIP_OK)
         err=ZIP_ERRNO;

      if ((number_entry_CD!=number_entry) ||
            (number_disk_with_CD!=0) ||
            (number_disk!=0))
         err=ZIP_BADZIPFILE;

      /* size of the central directory */
      if (ziplocal_getLong(&ziinit.z_filefunc, ziinit.filestream,&size_central_dir)!=ZIP_OK)
         err=ZIP_ERRNO;

      /* offset of start of central directory with respect to the
          starting disk number */
      if (ziplocal_getLong(&ziinit.z_filefunc, ziinit.filestream,&offset_central_dir)!=ZIP_OK)
         err=ZIP_ERRNO;

      /* zipfile comment length */
      if (ziplocal_getShort(&ziinit.z_filefunc, ziinit.filestream,&size_comment)!=ZIP_OK)
         err=ZIP_ERRNO;

      if ((central_pos<offset_central_dir+size_central_dir) &&
            (err==ZIP_OK))
         err=ZIP_BADZIPFILE;

      if (err!=ZIP_OK)
      {
         ZCLOSE(ziinit.z_filefunc, ziinit.filestream);
         TRYFREE(zi);
         return nullptr;
      }

      byte_before_the_zipfile = central_pos -
                                (offset_central_dir+size_central_dir);
      ziinit.add_position_when_writting_offset = byte_before_the_zipfile ;

      {
         uptr size_central_dir_to_read = size_central_dir;
         size_t buf_size = SIZEDATA_INDATABLOCK;
         void * buf_read = (void *)ALLOC(buf_size);
         if (ZSEEK(ziinit.z_filefunc, ziinit.filestream,
                   offset_central_dir + byte_before_the_zipfile,
                   ZLIB_FILEFUNC_SEEK_SET) != 0)
            err=ZIP_ERRNO;

         while ((size_central_dir_to_read>0) && (err==ZIP_OK))
         {
            uptr read_this = SIZEDATA_INDATABLOCK;
            if (read_this > size_central_dir_to_read)
               read_this = size_central_dir_to_read;
            if (ZREAD(ziinit.z_filefunc, ziinit.filestream,buf_read,read_this) != read_this)
               err=ZIP_ERRNO;

            if (err==ZIP_OK)
               err = add_data_in_datablock(&ziinit.central_dir,buf_read,
                                           (uptr)read_this);
            size_central_dir_to_read-=read_this;
         }
         TRYFREE(buf_read);
      }
      ziinit.begin_pos = byte_before_the_zipfile;
      ziinit.number_entry = number_entry_CD;

      if (ZSEEK(ziinit.z_filefunc, ziinit.filestream,
                offset_central_dir+byte_before_the_zipfile,ZLIB_FILEFUNC_SEEK_SET)!=0)
         err=ZIP_ERRNO;
   }
#    endif /* !NO_ADDFILEINEXISTINGZIP*/

   if (err != ZIP_OK)
   {
      TRYFREE(zi);
      return nullptr;
   }
   else
   {
      *zi = ziinit;
      return (zipFile)zi;
   }
}

extern zipFile CLASS_DECL_AURA zipOpen (
const char *pathname,
i32 append)
{
   return zipOpen2(pathname,append,nullptr,nullptr);
}

extern i32 CLASS_DECL_AURA zipOpenNewFileInZip3 (
zipFile file,
const char* filename,
const zip_fileinfo* zipfi,
const void * extrafield_local,
u32 size_extrafield_local,
const void * extrafield_global,
u32 size_extrafield_global,
const char* comment,
i32 method,
i32 level,
i32 raw,
i32 windowBits,
i32 memLevel,
i32 strategy,
const char* password,
u32  crcForCrypting)
{
   zip_internal* zi;
   u32 size_filename;
   u32 size_comment;
   u32 i;
   i32 err = ZIP_OK;

#    ifdef NOCRYPT
   if (password != nullptr)
      return ZIP_PARAMERROR;
#    endif

   if (file == nullptr)
      return ZIP_PARAMERROR;
   if ((method!=0) && (method!=Z_DEFLATED))
      return ZIP_PARAMERROR;

   zi = (zip_internal*)file;

   if (zi->in_opened_file_inzip == 1)
   {
      err = zipCloseFileInZip (file);
      if (err != ZIP_OK)
         return err;
   }


   if (filename==nullptr)
      filename="-";

   if (comment==nullptr)
      size_comment = 0;
   else
      size_comment = (u32) strlen(comment);

   size_filename = (u32) strlen(filename);

   if (zipfi == nullptr)
      zi->ci.dosDate = 0;
   else
   {
      if (zipfi->dosDate != 0)
         zi->ci.dosDate = zipfi->dosDate;
      else zi->ci.dosDate = ziplocal_TmzDateToDosDate(&zipfi->tmz_date,zipfi->dosDate);
   }

   zi->ci.flag = 0;
   if ((level==8) || (level==9))
      zi->ci.flag |= 2;
   if (level==2)
      zi->ci.flag |= 4;
   if (level==1)
      zi->ci.flag |= 6;
   if (password != nullptr)
      zi->ci.flag |= 1;

   zi->ci.crc32 = 0;
   zi->ci.method = method;
   zi->ci.encrypt = 0;
   zi->ci.stream_initialised = 0;
   zi->ci.pos_in_buffered_data = 0;
   zi->ci.raw = raw;
   zi->ci.pos_local_header = ZTELL(zi->z_filefunc,zi->filestream) ;
   zi->ci.size_centralheader = SIZECENTRALHEADER + size_filename +
                               size_extrafield_global + size_comment;
   zi->ci.central_header = (char*)ALLOC((u32)zi->ci.size_centralheader);

   ziplocal_putValue_inmemory(zi->ci.central_header,(uptr)CENTRALHEADERMAGIC,4);
   /* version info */
   ziplocal_putValue_inmemory(zi->ci.central_header+4,(uptr)VERSIONMADEBY,2);
   ziplocal_putValue_inmemory(zi->ci.central_header+6,(uptr)20,2);
   ziplocal_putValue_inmemory(zi->ci.central_header+8,(uptr)zi->ci.flag,2);
   ziplocal_putValue_inmemory(zi->ci.central_header+10,(uptr)zi->ci.method,2);
   ziplocal_putValue_inmemory(zi->ci.central_header+12,(uptr)zi->ci.dosDate,4);
   ziplocal_putValue_inmemory(zi->ci.central_header+16,(uptr)0,4); /*crc*/
   ziplocal_putValue_inmemory(zi->ci.central_header+20,(uptr)0,4); /*compr size*/
   ziplocal_putValue_inmemory(zi->ci.central_header+24,(uptr)0,4); /*uncompr size*/
   ziplocal_putValue_inmemory(zi->ci.central_header+28,(uptr)size_filename,2);
   ziplocal_putValue_inmemory(zi->ci.central_header+30,(uptr)size_extrafield_global,2);
   ziplocal_putValue_inmemory(zi->ci.central_header+32,(uptr)size_comment,2);
   ziplocal_putValue_inmemory(zi->ci.central_header+34,(uptr)0,2); /*disk nm start*/

   if (zipfi==nullptr)
      ziplocal_putValue_inmemory(zi->ci.central_header+36,(uptr)0,2);
   else
      ziplocal_putValue_inmemory(zi->ci.central_header+36,(uptr)zipfi->internal_fa,2);

   if (zipfi==nullptr)
      ziplocal_putValue_inmemory(zi->ci.central_header+38,(uptr)0,4);
   else
      ziplocal_putValue_inmemory(zi->ci.central_header+38,(uptr)zipfi->external_fa,4);

   ziplocal_putValue_inmemory(zi->ci.central_header+42,(uptr)zi->ci.pos_local_header- zi->add_position_when_writting_offset,4);

   for (i=0; i<size_filename; i++)
      *(zi->ci.central_header+SIZECENTRALHEADER+i) = *(filename+i);

   for (i=0; i<size_extrafield_global; i++)
      *(zi->ci.central_header+SIZECENTRALHEADER+size_filename+i) =
      *(((const char*)extrafield_global)+i);

   for (i=0; i<size_comment; i++)
      *(zi->ci.central_header+SIZECENTRALHEADER+size_filename+
        size_extrafield_global+i) = *(comment+i);
   if (zi->ci.central_header == nullptr)
      return ZIP_INTERNALERROR;

   /* write the static header */
   err = ziplocal_putValue(&zi->z_filefunc,zi->filestream,(uptr)LOCALHEADERMAGIC,4);

   if (err==ZIP_OK)
      err = ziplocal_putValue(&zi->z_filefunc,zi->filestream,(uptr)20,2);/* version needed to extract */
   if (err==ZIP_OK)
      err = ziplocal_putValue(&zi->z_filefunc,zi->filestream,(uptr)zi->ci.flag,2);

   if (err==ZIP_OK)
      err = ziplocal_putValue(&zi->z_filefunc,zi->filestream,(uptr)zi->ci.method,2);

   if (err==ZIP_OK)
      err = ziplocal_putValue(&zi->z_filefunc,zi->filestream,(uptr)zi->ci.dosDate,4);

   if (err==ZIP_OK)
      err = ziplocal_putValue(&zi->z_filefunc,zi->filestream,(uptr)0,4); /* crc 32, unknown */
   if (err==ZIP_OK)
      err = ziplocal_putValue(&zi->z_filefunc,zi->filestream,(uptr)0,4); /* compressed size, unknown */
   if (err==ZIP_OK)
      err = ziplocal_putValue(&zi->z_filefunc,zi->filestream,(uptr)0,4); /* uncompressed size, unknown */

   if (err==ZIP_OK)
      err = ziplocal_putValue(&zi->z_filefunc,zi->filestream,(uptr)size_filename,2);

   if (err==ZIP_OK)
      err = ziplocal_putValue(&zi->z_filefunc,zi->filestream,(uptr)size_extrafield_local,2);

   if ((err==ZIP_OK) && (size_filename>0))
      if (ZWRITE(zi->z_filefunc,zi->filestream,filename,size_filename)!=size_filename)
         err = ZIP_ERRNO;

   if ((err==ZIP_OK) && (size_extrafield_local>0))
      if (ZWRITE(zi->z_filefunc,zi->filestream,extrafield_local,size_extrafield_local)
            !=size_extrafield_local)
         err = ZIP_ERRNO;

   zi->ci.stream.avail_in = (u32)0;
   zi->ci.stream.avail_out = (u32)Z_BUFSIZE;
   zi->ci.stream.next_out = zi->ci.buffered_data;
   zi->ci.stream.total_in = 0;
   zi->ci.stream.total_out = 0;

   if ((err==ZIP_OK) && (zi->ci.method == Z_DEFLATED) && (!zi->ci.raw))
   {
      zi->ci.stream.zalloc = (alloc_func)0;
      zi->ci.stream.zfree = (free_func)0;
      zi->ci.stream.opaque = (voidpf)0;

      if (windowBits>0)
         windowBits = -windowBits;

      err = deflateInit2(&zi->ci.stream, level,
                         Z_DEFLATED, windowBits, memLevel, strategy);

      if (err==Z_OK)
         zi->ci.stream_initialised = 1;
   }
#    ifndef NOCRYPT
   zi->ci.crypt_header_size = 0;
   if ((err==Z_OK) && (password != nullptr))
   {
      uchar bufHead[RAND_HEAD_LEN];
      u32 sizeHead;
      zi->ci.encrypt = 1;
      zi->ci.pcrc_32_tab = zip_get_crc_table();
      /*init_keys(password,zi->ci.keys,zi->ci.pcrc_32_tab);*/

      sizeHead=crypthead(password,bufHead,RAND_HEAD_LEN,zi->ci.keys,zi->ci.pcrc_32_tab,crcForCrypting);
      zi->ci.crypt_header_size = sizeHead;

      if (ZWRITE(zi->z_filefunc,zi->filestream,bufHead,sizeHead) != sizeHead)
         err = ZIP_ERRNO;
   }
#    endif

   if (err==Z_OK)
      zi->in_opened_file_inzip = 1;
   return err;
}

extern i32 CLASS_DECL_AURA zipOpenNewFileInZip2(
zipFile file,
const char* filename,
const zip_fileinfo* zipfi,
const void * extrafield_local,
u32 size_extrafield_local,
const void * extrafield_global,
u32 size_extrafield_global,
const char* comment,
i32 method,
i32 level,
i32 raw)
{
   return zipOpenNewFileInZip3 (file, filename, zipfi,
                                extrafield_local, size_extrafield_local,
                                extrafield_global, size_extrafield_global,
                                comment, method, level, raw,
                                -MAX_WBITS, DEF_MEM_LEVEL, Z_DEFAULT_STRATEGY,
                                nullptr, 0);
}

extern i32 CLASS_DECL_AURA zipOpenNewFileInZip (
zipFile file,
const char* filename,
const zip_fileinfo* zipfi,
const void * extrafield_local,
u32 size_extrafield_local,
const void * extrafield_global,
u32 size_extrafield_global,
const char* comment,
i32 method,
i32 level)
{
   return zipOpenNewFileInZip2 (file, filename, zipfi,
                                extrafield_local, size_extrafield_local,
                                extrafield_global, size_extrafield_global,
                                comment, method, level, 0);
}

static i32 zipFlushWriteBuffer(
zip_internal* zi)
{
   i32 err=ZIP_OK;

   if (zi->ci.encrypt != 0)
   {
#ifndef NOCRYPT
      u32 i;
      i32 t;
      for (i=0; i<zi->ci.pos_in_buffered_data; i++)
         zi->ci.buffered_data[i] = zencode(zi->ci.keys, zi->ci.pcrc_32_tab,
                                           zi->ci.buffered_data[i],t);
#endif
   }
   if (ZWRITE(zi->z_filefunc,zi->filestream,zi->ci.buffered_data,zi->ci.pos_in_buffered_data)
         !=zi->ci.pos_in_buffered_data)
      err = ZIP_ERRNO;
   zi->ci.pos_in_buffered_data = 0;
   return err;
}

extern i32 CLASS_DECL_AURA zipWriteInFileInZip (
zipFile file,
const void * buf,
u32 len)
{
   zip_internal* zi;
   i32 err=ZIP_OK;

   if (file == nullptr)
      return ZIP_PARAMERROR;
   zi = (zip_internal*)file;

   if (zi->in_opened_file_inzip == 0)
      return ZIP_PARAMERROR;

   zi->ci.stream.next_in = (u8 *)buf;
   zi->ci.stream.avail_in = len;
   zi->ci.crc32 = (u32) crc32(zi->ci.crc32, (const u8 *) buf,len);

   while ((err==ZIP_OK) && (zi->ci.stream.avail_in>0))
   {
      if (zi->ci.stream.avail_out == 0)
      {
         if (zipFlushWriteBuffer(zi) == ZIP_ERRNO)
            err = ZIP_ERRNO;
         zi->ci.stream.avail_out = (u32)Z_BUFSIZE;
         zi->ci.stream.next_out = zi->ci.buffered_data;
      }


      if(err != ZIP_OK)
         break;

      if ((zi->ci.method == Z_DEFLATED) && (!zi->ci.raw))
      {
         uptr uTotalOutBefore = zi->ci.stream.total_out;
         err=deflate(&zi->ci.stream,  Z_NO_FLUSH);
         zi->ci.pos_in_buffered_data += (u32)(zi->ci.stream.total_out - uTotalOutBefore) ;

      }
      else
      {
         uptr copy_this,i;
         if (zi->ci.stream.avail_in < zi->ci.stream.avail_out)
            copy_this = zi->ci.stream.avail_in;
         else
            copy_this = zi->ci.stream.avail_out;
         for (i=0; i<copy_this; i++)
            *(((char*)zi->ci.stream.next_out)+i) =
            *(((const char*)zi->ci.stream.next_in)+i);
         {
            zi->ci.stream.avail_in -= (uInt) copy_this;
            zi->ci.stream.avail_out-= (uInt) copy_this;
            zi->ci.stream.next_in+= copy_this;
            zi->ci.stream.next_out+= copy_this;
            zi->ci.stream.total_in+= (uLong) copy_this;
            zi->ci.stream.total_out+= (uLong) copy_this;
            zi->ci.pos_in_buffered_data += copy_this;
         }
      }
   }

   return err;
}

extern i32 CLASS_DECL_AURA zipCloseFileInZipRaw (
zipFile file,
uptr uncompressed_size,
uptr crc32)
{
   zip_internal* zi;
   uptr compressed_size;
   i32 err=ZIP_OK;

   if (file == nullptr)
      return ZIP_PARAMERROR;
   zi = (zip_internal*)file;

   if (zi->in_opened_file_inzip == 0)
      return ZIP_PARAMERROR;
   zi->ci.stream.avail_in = 0;

   if ((zi->ci.method == Z_DEFLATED) && (!zi->ci.raw))
      while (err==ZIP_OK)
      {
         uptr uTotalOutBefore;
         if (zi->ci.stream.avail_out == 0)
         {
            if (zipFlushWriteBuffer(zi) == ZIP_ERRNO)
               err = ZIP_ERRNO;
            zi->ci.stream.avail_out = (u32)Z_BUFSIZE;
            zi->ci.stream.next_out = zi->ci.buffered_data;
         }
         uTotalOutBefore = zi->ci.stream.total_out;
         err=deflate(&zi->ci.stream,  Z_FINISH);
         zi->ci.pos_in_buffered_data += (u32)(zi->ci.stream.total_out - uTotalOutBefore) ;
      }

   if (err==Z_STREAM_END)
      err=ZIP_OK; /* this is normal */

   if ((zi->ci.pos_in_buffered_data>0) && (err==ZIP_OK))
      if (zipFlushWriteBuffer(zi)==ZIP_ERRNO)
         err = ZIP_ERRNO;

   if ((zi->ci.method == Z_DEFLATED) && (!zi->ci.raw))
   {
      err=deflateEnd(&zi->ci.stream);
      zi->ci.stream_initialised = 0;
   }

   if (!zi->ci.raw)
   {
      crc32 = (uptr)zi->ci.crc32;
      uncompressed_size = (uptr)zi->ci.stream.total_in;
   }
   compressed_size = (uptr)zi->ci.stream.total_out;
#    ifndef NOCRYPT
   compressed_size += zi->ci.crypt_header_size;
#    endif

   ziplocal_putValue_inmemory(zi->ci.central_header+16,crc32,4); /*crc*/
   ziplocal_putValue_inmemory(zi->ci.central_header+20,
                              compressed_size,4); /*compr size*/
   if (zi->ci.stream.data_type == Z_ASCII)
      ziplocal_putValue_inmemory(zi->ci.central_header+36,(uptr)Z_ASCII,2);
   ziplocal_putValue_inmemory(zi->ci.central_header+24,
                              uncompressed_size,4); /*uncompr size*/

   if (err==ZIP_OK)
      err = add_data_in_datablock(&zi->central_dir,zi->ci.central_header,
                                  (uptr)zi->ci.size_centralheader);
   free(zi->ci.central_header);

   if (err==ZIP_OK)
   {
      long cur_pos_inzip = ZTELL(zi->z_filefunc,zi->filestream);
      if (ZSEEK(zi->z_filefunc,zi->filestream,
                zi->ci.pos_local_header + 14,ZLIB_FILEFUNC_SEEK_SET)!=0)
         err = ZIP_ERRNO;

      if (err==ZIP_OK)
         err = ziplocal_putValue(&zi->z_filefunc,zi->filestream,crc32,4); /* crc 32, unknown */

      if (err==ZIP_OK) /* compressed size, unknown */
         err = ziplocal_putValue(&zi->z_filefunc,zi->filestream,compressed_size,4);

      if (err==ZIP_OK) /* uncompressed size, unknown */
         err = ziplocal_putValue(&zi->z_filefunc,zi->filestream,uncompressed_size,4);

      if (ZSEEK(zi->z_filefunc,zi->filestream,
                cur_pos_inzip,ZLIB_FILEFUNC_SEEK_SET)!=0)
         err = ZIP_ERRNO;
   }

   zi->number_entry ++;
   zi->in_opened_file_inzip = 0;

   return err;
}

extern i32 CLASS_DECL_AURA zipCloseFileInZip (
zipFile file)
{
   return zipCloseFileInZipRaw (file,0,0);
}

extern i32 CLASS_DECL_AURA zipClose (
zipFile file,
const char* global_comment)
{
   zip_internal* zi;
   i32 err = 0;
   uptr size_centraldir = 0;
   uptr centraldir_pos_inzip ;
   u32 size_global_comment;
   if (file == nullptr)
      return ZIP_PARAMERROR;
   zi = (zip_internal*)file;

   if (zi->in_opened_file_inzip == 1)
   {
      err = zipCloseFileInZip (file);
   }

   if (global_comment==nullptr)
      size_global_comment = 0;
   else
      size_global_comment = (u32) strlen(global_comment);


   centraldir_pos_inzip = ZTELL(zi->z_filefunc,zi->filestream);
   if (err==ZIP_OK)
   {
      linkedlist_datablock_internal* ldi = zi->central_dir.first_block ;
      while (ldi!=nullptr)
      {
         if ((err==ZIP_OK) && (ldi->filled_in_this_block>0))
            if (ZWRITE(zi->z_filefunc,zi->filestream,
                       ldi->data,ldi->filled_in_this_block)
                  !=ldi->filled_in_this_block )
               err = ZIP_ERRNO;

         size_centraldir += ldi->filled_in_this_block;
         ldi = ldi->next_datablock;
      }
   }
   free_datablock(zi->central_dir.first_block);

   if (err==ZIP_OK) /* Magic End */
      err = ziplocal_putValue(&zi->z_filefunc,zi->filestream,(uptr)ENDHEADERMAGIC,4);

   if (err==ZIP_OK) /* number of this disk */
      err = ziplocal_putValue(&zi->z_filefunc,zi->filestream,(uptr)0,2);

   if (err==ZIP_OK) /* number of the disk with the start of the central directory */
      err = ziplocal_putValue(&zi->z_filefunc,zi->filestream,(uptr)0,2);

   if (err==ZIP_OK) /* total number of entries in the central dir on this disk */
      err = ziplocal_putValue(&zi->z_filefunc,zi->filestream,(uptr)zi->number_entry,2);

   if (err==ZIP_OK) /* total number of entries in the central dir */
      err = ziplocal_putValue(&zi->z_filefunc,zi->filestream,(uptr)zi->number_entry,2);

   if (err==ZIP_OK) /* size of the central directory */
      err = ziplocal_putValue(&zi->z_filefunc,zi->filestream,(uptr)size_centraldir,4);

   if (err==ZIP_OK) /* offset of start of central directory with respect to the
                            starting disk number */
      err = ziplocal_putValue(&zi->z_filefunc,zi->filestream,
                              (uptr)(centraldir_pos_inzip - zi->add_position_when_writting_offset),4);

   if (err==ZIP_OK) /* zipfile comment length */
      err = ziplocal_putValue(&zi->z_filefunc,zi->filestream,(uptr)size_global_comment,2);

   if ((err==ZIP_OK) && (size_global_comment>0))
      if (ZWRITE(zi->z_filefunc,zi->filestream,
                 global_comment,size_global_comment) != size_global_comment)
         err = ZIP_ERRNO;

   if (ZCLOSE(zi->z_filefunc,zi->filestream) != 0)
      if (err == ZIP_OK)
         err = ZIP_ERRNO;

   TRYFREE(zi);

   return err;
}
