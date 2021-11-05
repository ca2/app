/**

   HISTORY:

   Version 1.0            Gurmeet S. Kochar (GSK)
   Mar 26, 2004         First release version.
 */
#pragma once

class lite_html_reader;   // forward declaration
class lite_html_tag;   // forward declaration

/**
 ILiteHTMLReaderEvents
 This class presents an interface that must be implemented
 by all those classes that want to handle the notifications
 sent by the lite_html_reader while parsing an HTML document.
 The order of events handled by the ILiteHTMLReaderEvents
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
  way by handling events that it generates as it finds specific
  symbols in the text. This class is similar to the SAX (Simple
  API for XML) implementation, which is an XML DOM parser. Like
  SAX, the lite_html_reader class reads a department of HTML text,
  generates an event, and moves on to the next department. This
  results in low memory consumption.

  @version 1.0 (Mar 26, 2004)
  @author Gurmeet S. Kochar

  @todo add support for multiple event handlers.
  @todo add support for tag validation, a new interface, that
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
   strsize   m_dwAppData;

   /**
    * position of the seek pointer
    * @since 1.0
    * @author Gurmeet S. Kochar
    */
   strsize     m_dwBufPos;

   /**
    * size, in TCHARs, of the buffer
    * @since 1.0
    * @author Gurmeet S. Kochar
    */
   //strsize   m_dwBufLen;

   /**
    * Bit-mask flags to customize events notification(s)
    * Default is the ORed result of all EventMaskEnum flags.
    *
    * @since 1.0
    * @author Gurmeet S. Kochar
    */
   EventMaskEnum   m_eventMask;

   /**
    * Pointer to an ILiteHTMLReaderEvents based event handling object
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
    * Returns an event mask which signifies the notification
    * messages a lite_html_reader will send while parsing HTML
    * text.
    *
    * @return event mask
    * @since 1.0
    * @author Gurmeet S. Kochar
    */
   EventMaskEnum getEventMask() const
      { return (m_eventMask); }

   /**
    * Sets a new event mask.
    *
    * @lparam dwNewEventMask - new event mask
    *
    * @return previous event mask
    * @since 1.0
    * @author Gurmeet S. Kochar
    */
   EventMaskEnum setEventMask(u32 dwNewEventMask);

   /**
    * Changes the current event mask by adding and removing
    * flags specified by addFlags and eraseFlags, respectively.
    *
    * @lparam addFlags - flags to add in the current event mask
    * @lparam eraseFlags - flags to erase from the current event mask
    *
    * @return previous event mask
    * @since 1.0
    * @author Gurmeet S. Kochar
    */
   EventMaskEnum setEventMask(u32 addFlags, u32 eraseFlags);

   /**
    * Returns a 32-bit application-specific data
    * previously set by a call to setAppData()
    *
    * @return 32-bit application-specific data
    * @since 1.0
    * @author Gurmeet S. Kochar
    */
   strsize getAppData() const
      { return (m_dwAppData); }

   /**
    * Allows you to store 32-bit application-specific
    * data that will be passed to event handlers on each call
    *
    * @lparam dwNewAppData - System-specific data
    *
    * @return previously associated data
    * @since 1.0
    * @author Gurmeet S. Kochar
    */
   strsize setAppData(u32 dwNewAppData);

   /**
    * Returns a pointer to an event handler registered with
    * a lite_html_reader by a previous call to setEventHandler().
    *
    * @return pointer to a ILiteHTMLReaderEvents
    * @since 1.0
    * @author Gurmeet S. Kochar
    */
   ILiteHTMLReaderEvents* getEventHandler() const
      { return (m_pEventHandler); }

   /**
    * Registers an event handler with a lite_html_reader. If no
    * event handler is registered with the reader, all events
    * raised by the reader will be ignored. An application can
    * machine the event handler even when the parsing process
    * is in progress.
    *
    * @lparam pNewHandler - pointer to an event handler.
    *        This parameter can be nullptr also.
    *
    * @return pointer to the previous event handler
    * @since 1.0
    * @author Gurmeet S. Kochar
    */
   ILiteHTMLReaderEvents* setEventHandler(ILiteHTMLReaderEvents* pNewHandler);

   // returns the current value for the specified option
   bool getBoolOption(ReaderOptionsEnum option, bool& bCurVal) const;
   // sets a new value for the specified option
   bool setBoolOption(ReaderOptionsEnum option, bool bNewVal);

// Operations
   // parses an HTML document from the specified string
   strsize read_form_document(const ::string & str);

// Helpers
   /** Parsing Helpers */

   // parses an HTML document, and returns the
   // number of characters successfully parsed
   virtual strsize parseDocument();

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
    * Determines if the specified event's notification is to be raised
    *
    * @return true if notification is to be raised, false otherwise.
    *         false is returned also when there is no event handler
    *         associated with the reader.
    * @since 1.0
    * @author Gurmeet S. Kochar
    */
   bool getEventNotify(u32 dwEvent) const ;

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

