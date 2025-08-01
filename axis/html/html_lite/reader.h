/**

   HISTORY:

   Version 1.0            Gurmeet S. Kochar (GSK)
   Mar 26, 2004         First release version.
 */
#pragma once

class lite_html_reader;   // forward declaration
class lite_html_tag;   // forward declaration


////#include "acme/prototype/prototype/object.h"


/**
 ILiteHTMLReaderEvents
 This class presents an interface that must be implemented
 by all those classes that want to handle the notifications
 sent by the lite_html_reader while parsing an HTML document.
 The order of happenings handled by the ILiteHTMLReaderEvents
 handler is determined by the order of information within
 the document being parsed. It's important to note that the
 interface includes a series of methods that the lite_html_reader
 invokes during the parsing operation. The reader passes the
 appropriate information to the method's parameters. To perform
 some type of processing for a method, you simply add code to
 the method in your own ILiteHTMLReaderEvents implementation.

 @version 1.0 (Mar 06, 2004)
 @author Gurmeet S. Kochar
 */
class CLASS_DECL_AXIS ILiteHTMLReaderEvents
{
public:

   virtual void BeginParse(uptr dwAppData, bool &bAbort);

   virtual void StartTag(lite_html_tag *pTag, uptr dwAppData, bool &bAbort);

   virtual void EndTag(lite_html_tag *pTag, uptr dwAppData, bool &bAbort);

   virtual void Characters(const string &rText, uptr dwAppData, bool &bAbort);

   virtual void Comment(const string &rComment, uptr dwAppData, bool &bAbort);

   virtual void EndParse(uptr dwAppData, bool bIsAborted);

   virtual ~ILiteHTMLReaderEvents();

};

/**
 lite_html_reader
  This class allows you to parse HTML text in a simple, and fast
  way by handling happenings that it generates as it finds specific
  symbols in the text. This class is similar to the SAX (Simple
  API for XML) implementation, which is an XML DOM parser. Like
  SAX, the lite_html_reader class reads a department of HTML text,
  generates an happening, and moves on to the next department. This
  results in low memory consumption.

  @version 1.0 (Mar 26, 2004)
  @author Gurmeet S. Kochar

  @todo add support for multiple happening handlers.
  @todo add support for tag validation, a ___new interface, that
        validator classes must implement, so reader can then
        make a call, such as isValidTag(...), to validate tag
        information and act accordingly.
  @todo add more reader options (ReaderOptionsEnum). Until now,
        there is only one.
 */
class CLASS_DECL_AXIS lite_html_reader :
   virtual public ::object
{
public:



   enum EventMaskEnum
   {
      /** @since 1.0 */
      notifyStartStop      = 0x00000001L,   // raise BeginParse and EndParse?

      /** @since 1.0 */
      notifyTagStart      = 0x00000002L,   // raise StartTag?

      /** @since 1.0 */
      notifyTagEnd      = 0x00000004L,   // raise EndTag?

      /** @since 1.0 */
      notifyCharacters   = 0x00000008L,   // raise Characters?

      /** @since 1.0 */
      notifyComment      = 0x00000010L,   // raise Comment?
   };

   enum ReaderOptionsEnum {
      /** @since 1.0 */
      resolveEntities,   // determines whether entity references should be resolved

      // TODO:
      // TODO: add more reader options
      // TODO:
   };

   /**
    * Determines if character entities are to be resolved
    * Default is true.
    *
    * @since 1.0
    * @author Gurmeet S. Kochar
    */
   bool   m_bResolveEntities;

   /**
    * 32-bit cast-specific data (to be passed to callbacks)
    * Default is 0.
    *
    * @since 1.0
    * @author Gurmeet S. Kochar
    */
   character_count   m_dwAppData;

   /**
    * position of the seek pointer
    * @since 1.0
    * @author Gurmeet S. Kochar
    */
   character_count     m_dwBufPos;

   /**
    * size, in TCHARs, of the buffer
    * @since 1.0
    * @author Gurmeet S. Kochar
    */
   //character_count   m_dwBufLen;

   /**
    * Bit-mask flags to customize happenings notification(s)
    * Default is the ORed result of all EventMaskEnum flags.
    *
    * @since 1.0
    * @author Gurmeet S. Kochar
    */
   EventMaskEnum   m_happeningMask;

   /**
    * Pointer to an ILiteHTMLReaderEvents based happening handling object
    * Default is nullptr
    *
    * @since 1.0
    * @author Gurmeet S. Kochar
    */
   ILiteHTMLReaderEvents *    m_pEventHandler;

   ::html::html *             m_phtml;

   ::axis::session *          m_psession;

   /**
    * Pointer to an array of characters being parsed
    * @since 1.0
    * @author Gurmeet S. Kochar
    */
   string m_strBuffer;


// Construction/Destruction

   lite_html_reader();


   /**
    * Returns an happening mask which signifies the notification
    * messages a lite_html_reader will send while parsing HTML
    * text.
    *
    * @return happening mask
    * @since 1.0
    * @author Gurmeet S. Kochar
    */
   EventMaskEnum getEventMask() const
      { return (m_happeningMask); }

   /**
    * Sets a ___new happening mask.
    *
    * @lparam dwNewEventMask - ___new happening mask
    *
    * @return previous happening mask
    * @since 1.0
    * @author Gurmeet S. Kochar
    */
   EventMaskEnum setEventMask(unsigned int dwNewEventMask);

   /**
    * Changes the current happening mask by adding and removing
    * flags specified by addFlags and eraseFlags, respectively.
    *
    * @lparam addFlags - flags to add in the current happening mask
    * @lparam eraseFlags - flags to erase from the current happening mask
    *
    * @return previous happening mask
    * @since 1.0
    * @author Gurmeet S. Kochar
    */
   EventMaskEnum setEventMask(unsigned int addFlags, unsigned int eraseFlags);

   /**
    * Returns a 32-bit application-specific data
    * previously set by a call to setAppData()
    *
    * @return 32-bit application-specific data
    * @since 1.0
    * @author Gurmeet S. Kochar
    */
   character_count getAppData() const
      { return (m_dwAppData); }

   /**
    * Allows you to store 32-bit application-specific
    * data that will be passed to happening handlers on each call
    *
    * @lparam dwNewAppData - System-specific data
    *
    * @return previously associated data
    * @since 1.0
    * @author Gurmeet S. Kochar
    */
   character_count setAppData(unsigned int dwNewAppData);

   /**
    * Returns a pointer to an happening handler registered with
    * a lite_html_reader by a previous call to setEventHandler().
    *
    * @return pointer to a ILiteHTMLReaderEvents
    * @since 1.0
    * @author Gurmeet S. Kochar
    */
   ILiteHTMLReaderEvents* getEventHandler() const
      { return (m_pEventHandler); }

   /**
    * Registers an happening handler with a lite_html_reader. If no
    * happening handler is registered with the reader, all happenings
    * raised by the reader will be ignored. An application can
    * machine the happening handler even when the parsing process
    * is in progress.
    *
    * @lparam pNewHandler - pointer to an happening handler.
    *        This parameter can be nullptr also.
    *
    * @return pointer to the previous happening handler
    * @since 1.0
    * @author Gurmeet S. Kochar
    */
   ILiteHTMLReaderEvents* setEventHandler(ILiteHTMLReaderEvents* pNewHandler);

   // returns the current value for the specified option
   bool getBoolOption(ReaderOptionsEnum option, bool& bCurVal) const;
   // sets a ___new value for the specified option
   bool setBoolOption(ReaderOptionsEnum option, bool bNewVal);


   // parses an HTML document from the specified string
   character_count read_form_document(const ::scoped_string & scopedstr);

// Helpers
   /** Parsing Helpers */

   // parses an HTML document, and returns the
   // number of characters successfully parsed
   virtual character_count parseDocument();

   // parses an HTML comment from the buffer starting from
   // the current buffer position and returns true on sucess
   virtual bool parseComment(string &rComment);

   // parses an HTML tag from the buffer starting from
   // the current buffer position and returns true on success
   virtual bool parseTag(lite_html_tag &rTag, bool &bIsOpeningTag, bool &bIsClosingTag);

   /**
    * @since 1.0
    * @author Gurmeet S. Kochar
    */
   virtual void NormalizeCharacters(string &rCharacters)
   {
      //rCharacters.replace("\r\n", "");
      //rCharacters.erase('\n');
      //rCharacters.replace('\r', ' ');
      //rCharacters.replace('\t', ' ');
//      UNUSED_ALWAYS(rCharacters);
   }

   /** buffer Manipulation Helpers */

   /**
    * Resets the buffer position back to the beginning
    *
    * @since 1.0
    * @author Gurmeet S. Kochar
    */
   void ResetSeekPointer()
      { m_dwBufPos = 0L; }

   /**
    * Reads the next character and advances the buffer position
    *
    * @return character read
    * @since 1.0
    * @author Gurmeet S. Kochar
    */
   char ReadChar()
   {

      if(m_dwBufPos >= m_strBuffer.size())
         return 0;

      return m_strBuffer[m_dwBufPos++];

   }

   /**
    * Moves the buffer back by one char
    *
    * @since 1.0
    * @author Gurmeet S. Kochar
    */
   char UngetChar();

   /** Other Helpers */

   /**
    * Determines if the specified happening's notification is to be raised
    *
    * @return true if notification is to be raised, false otherwise.
    *         false is returned also when there is no happening handler
    *         associated with the reader.
    * @since 1.0
    * @author Gurmeet S. Kochar
    */
   bool getEventNotify(unsigned int dwEvent) const ;

   /**
    * Determines if the character specified by ch is
    * a white-space character. White-space characters
    * are defined as ASCII 0x9-0xD,0x20
    *
    * @returns true if character is a white-space,
    *          false otherwise
    * @since 1.0
    * @author Gurmeet S. Kochar
    */
   bool isWhiteSpace(char ch) const;

};

