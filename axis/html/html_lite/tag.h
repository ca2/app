/**
 *   PROJECT - HTML Reader Class Library
 *
 *   lite_html_tag.h - Defines lite_html_tag
 *
 *   Written By Gurmeet S. Kochar <gomzygotit@hotmail.com>
 *   Copyright (ca) 2004. 
 *
 *   This code may be used in compiled form in any way you desire 
 *   (including commercial use). The code may be redistributed 
 *   unmodified by any means PROVIDING it is not sold for profit 
 *   without the authors written consent, and providing that this 
 *   notice and the authors name and all copyright notices remains 
 *   intact. However, this file and the accompanying source code may 
 *   not be hosted on a website or bulletin board without the authors 
 *   written permission.
 *
 *   This file is provided "AS IS" with no expressed or implied warranty.
 *   The author accepts no liability for any damage/loss of business that
 *   this product may cause.
 *
 *   Although it is not necessary, but if you use this code in any of 
 *   your application (commercial or non-commercial), please INFORM me 
 *   so that I may know how useful this library is. This will encourage 
 *   me to keep updating it.
 *
 *   HISTORY:
 *
 *   Version 1.0            Gurmeet S. Kochar (GSK)
 *   Mar 18, 2004         First release version.
 */
#pragma once


/**
 * lite_html_tag
 *
 * @version 1.0 (March 18, 2004)
 * @author Gurmeet S. Kochar
 */
class CLASS_DECL_AXIS lite_html_tag
{
// Construction/Destruction
public:
   lite_html_tag()
      : m_pcollAttr(nullptr)
   { }

   /**
    * @lparam bCopy - if true, this lite_html_tag makes a copy of the 
    * LiteHTMLAttributes pointer. if false, this constructor takes 
    * composite of the encapsulated LiteHTMLAttributes pointer.
    *
    * @since 1.0
    * @author Gurmeet S. Kochar
    */
   lite_html_tag(lite_html_tag &rSource, bool bCopy = false);

   virtual ~lite_html_tag();

// Attributes
public:
   /**
    * @return name of the tag
    * @since 1.0
    * @author Gurmeet S. Kochar
    */
   string getTagName() const
      { return (m_strTagName); }

   /**
    * @return pointer to the attribute collection
    * @since 1.0
    * @author Gurmeet S. Kochar
    */
   const LiteHTMLAttributes* getAttributes() const
      { return (m_pcollAttr);  }

// Parsing Helpers
public:
   // parses tag information from the given string
   UINT parseFromStr(
      lite_html_reader * preader,
      const string & strString, 
      strsize iPos,
      bool &bIsOpeningTag, 
      bool &bIsClosingTag, 
      bool bParseAttrib = true);

// Data Members
private:
   /**
    * collection of LiteHTMLElemAttr objects
    * @since 1.0
    */
   LiteHTMLAttributes   *m_pcollAttr;

   /**
    * tag name of the element
    * @since 1.0
    */
   string            m_strTagName;
};

