/**
 *   PROJECT - HTML Reader Class Library
 *
 *   LiteHTMLEntityResolver.h - Defines LiteHTMLEntityResolver
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
 *   Mar 21, 2004         First release version.
 */
#pragma once



/**
 * LiteHTMLEntityResolver
 * This is a utility class that helps in resolving the character 
 * and numeric entity references.
 *
 * @version 1.0 (Mar 17, 2004)
 * @author Gurmeet S. Kochar
 */
class CLASS_DECL_AXIS LiteHTMLEntityResolver :
   virtual public ::object
{
public:
   
   
   class CharEntityRefs :
      public string_map < char, char >
   {
   public:
      
      CharEntityRefs();

   };

   CharEntityRefs m_CharEntityRefs;


// Constructors
   LiteHTMLEntityResolver();

// Operations
   /**
    * Resolves a character or numeric entity object.
    *
    * @lparam rStr - entity to resolve
    * @lparam ch - payload that will receive the result
    *
    * @return number of TCHARs used to resolve entity object
    * @since 1.0
    * @author Gurmeet S. Kochar
    */
   i32 resolveEntity(const ::string & pszEntity, string & strChar);


};
