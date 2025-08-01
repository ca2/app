//
//HISTORY:
//
//Version 1.0            Gurmeet S. Kochar (GSK)
//Mar 18, 2004         First release version.
#pragma once


////#include "acme/exception/exception.h"
#include "acme/prototype/collection/address_array.h"



class LiteHTMLAttributes;   // forward declaration

/**
 * LiteHTMLElemAttr
 *
 * @version 1.0 (Mar 18, 2004)
 * @author Gurmeet S. Kochar
 */
class CLASS_DECL_AXIS LiteHTMLElemAttr
{
public:


   string           m_strName;
   string           m_strValue;


   LiteHTMLElemAttr(const ::scoped_string & scopedstrAttribName = nullptr, const ::scoped_string & scopedstrAttribValue = nullptr)

   {
      Init();
      m_strName = scopedstrAttribName;

      m_strValue = scopedstrAttribValue;

   }


   LiteHTMLElemAttr(const LiteHTMLElemAttr &rSource)
   {

      Init();

      m_strName = rSource.m_strName;
      m_strValue = rSource.m_strValue;

   }


   static void Init();

   string getName() const
   {
      return m_strName;
   }

   string getValue() const
   {
      return m_strValue;
   }

   /**
    * Determines if the attribute value is a named color value
    * @return true if attribute value is a named color, otherwise, false
    * @since 1.0
    * @author Gurmeet S. Kochar
    */
   bool isNamedColorValue(::lite_html_reader * preader) const;

   /**
    * Determines if the attribute value is a named system color value
    * @return true if value is a named system color, false otherwise
    * @since 1.0
    * @author Gurmeet S. Kochar
    */
   bool isSysColorValue(::lite_html_reader * preader) const;

   /**
    * Determines if the attribute value is a color value in
    * hexadecimal format
    * @return true if attribute value is a color value, otherwise, false
    * @since 1.0
    * @author Gurmeet S. Kochar
    */
   bool isHexColorValue() const;

   /**
    * Determines if the attribute value contains a color object
    * @return true, if attribute value is color value, false otherwise.
    * @since 1.0
    * @author Gurmeet S. Kochar
    */
   bool isColorValue(::lite_html_reader * preader) const
   { return (isNamedColorValue(preader) || isHexColorValue()); }

   /**
    * Returns the color value of the attribute
    * @return a ::color::color representing the color
    * @since 1.0
    * @author Gurmeet S. Kochar
    */
   ::color::color getColorValue(::lite_html_reader * preader) const;

   /**
    * Returns the rgb value of the attribute in hexadecimal format
    * @return hexadecimal string representing the color value
    * @since 1.0
    * @author Gurmeet S. Kochar
    */
   string getColorHexValue(::lite_html_reader * preader) const;

   /**
    * Checks to see if the attribute contains a percent value
    * @return true if value is a percent value, otherwise, false
    * @since 1.0
    * @author Gurmeet S. Kochar
    */
   bool isPercentValue() const
   { return (m_strValue.right(1) == "%" ? true : false); }

   /**
    * Returns a percent value of the attribute
    * @return percentage value
    * @since 1.0
    * @author Gurmeet S. Kochar
    */
   unsigned short getPercentValue(unsigned short maximum = USHRT_MAX) const
   {
      ASSERT(maximum > 0);
      if (!isPercentValue())   return (0);
      unsigned short   percentVal = (unsigned short)((short)*this);
      return ((percentVal > maximum ? maximum : percentVal));
   }

   /**
    * Parses a length value from the attribute/value
    * and identifies its length unit also
    *
    * @lparam rUnit - this will receive the type of the length unit
    *
    * return: an integer value of the attribute
    * @since 1.0
    * @author Gurmeet S. Kochar
    */
   enum LengthUnitsEnum { em, ex, px, per, in, cm, mm, point, pc };
   short getLengthValue(LengthUnitsEnum &rUnit) const
   {
      static const char   _szUnits[][4] =
      {
         /** relative length units */
         "em", "ex", "px", "%",
         /** absolute length units */
         "in", "cm", "mm", "p", "pc"
      };

      if (m_strValue.is_empty())
         return (0);

      int i;
      for (i = 0; i < sizeof(_szUnits)/sizeof(_szUnits[0]); i++)
      {
         if (m_strValue.right(::ansi_len(_szUnits[i])). \
               case_insensitive_order(_szUnits[i]) == 0)
         {
            rUnit = (LengthUnitsEnum)i;
            break;
         }
      }
      if (i == sizeof(_szUnits)/sizeof(_szUnits[0]))
         return (0);
      return (*this);
   }

// Operators
public:
   /**
    * Converts attribute value to bool
    * @return true or false
    * @since 1.0
    * @author Gurmeet S. Kochar
    */
   operator bool() const
   {
      if (m_strValue.case_insensitive_equals("true"))
         return (true);
      if (m_strValue.case_insensitive_equals("false"))
         return (false);
      return (((short)*this ? true : false));
   }

   /**
    * Converts attribute value to unsigned char (uchar)
    * @return the left-most character of attribute value
    * @since 1.0
    * @author Gurmeet S. Kochar
    */
   operator unsigned char() const
   { return ((unsigned char)(m_strValue.length() ? m_strValue[0] : 0)); }

   /**
    * Converts attribute value to double
    * @return 0.00 on failure, otherwise, a numeric value
    * @since 1.0
    * @author Gurmeet S. Kochar
    */
   operator double() const
   { return (::strtod(m_strValue, nullptr)); }

   /**
    * Converts attribute value to signed short
    * @return 0 on failure, otherwise, an integer value
    * @since 1.0
    * @author Gurmeet S. Kochar
    */
   operator short() const
   { return ((short)::atoi(m_strValue)); }

   /**
    * @return attribute value
    * @since 1.0
    * @author Gurmeet S. Kochar
    */
   operator const_char_pointer () const
   { return (m_strValue); }

// Private Operations
private:
   /**
    * Sets the value of an attribute. Takes care of the following:
    *  1. Ignores leading and trailing white-space characters
    *  2. Replaces character entities with appropriate characters.
    *  3. Ignores line feeds (LF).
    *  4. Replaces each carriage-return (CR) or tab with a single space.
    *
    * @lparam pszValue - ___new attribute value

    *
    * @since 1.0
    * @author Gurmeet S. Kochar
    */
   void putValue(::lite_html_reader * preader, const ::scoped_string & scopedstrValue);


// Parsing Helpers
public:
   // parses an attribute/value pair from the given string
   character_count parseFromStr(::lite_html_reader * preader, const ::scoped_string & scopedstrString);


};


/**
 * LiteHTMLAttributes
 *
 * @version 1.0 (Mar 18, 2004)
 * @author Gurmeet S. Kochar
 */
class LiteHTMLAttributes
{
// Construction/Destruction
public:
   LiteHTMLAttributes()
      : m_parrAttrib(nullptr)
   { }

   /**
    * @lparam bCopy - if true, this LiteHTMLAttributes makes a copy
    * of the encapsulated pointer. if false, this constructor takes
    * composite of the encapsulated pointer.
    *
    * @since 1.0
    * @author Gurmeet S. Kochar
    */
   LiteHTMLAttributes(LiteHTMLAttributes &rSource, bool bCopy = false)
      : m_parrAttrib(nullptr)
   {
      if (!bCopy)
      {
         m_parrAttrib = rSource.m_parrAttrib;
         rSource.m_parrAttrib = nullptr;
      }
      else
      {
         const ::collection::count nElemCount = rSource.getCount();
         if (nElemCount)
         {

            if ((m_parrAttrib = ___new  CElemAttrArray()) == nullptr)
            {

               throw ::exception(error_no_memory);

            }

            LiteHTMLElemAttr   *pItem = nullptr;

            m_parrAttrib->set_size(nElemCount);

            /** DEEP COPY BEGIN */
            for (int iElem = 0; iElem < nElemCount; iElem++)
            {
               if ((pItem = __raw_new LiteHTMLElemAttr(rSource[iElem])) == nullptr)
               {
                  eraseAll();
                  throw ::exception(error_no_memory);
                  return;
               }

               (*m_parrAttrib)[iElem] = pItem;
               pItem = nullptr;
            }
            /** DEEP COPY END */
         }
      }
   }

   virtual ~LiteHTMLAttributes()
   { eraseAll(); }

// Initialization
public:
   // parses attribute/value pairs from the given string
   character_count parseFromStr(::lite_html_reader * papp, const ::scoped_string & scopedstrString, character_count iLen);



public:
   /**
    * Returns the ::collection::count of LiteHTMLElemAttr items in this collection
    * @return number of items
    * @since 1.0
    * @author Gurmeet S. Kochar
    */
   ::collection::count getCount() const
   {
      if (m_parrAttrib != nullptr)
         return (m_parrAttrib->get_upper_bound() + 1);
      return (0);
   }

   /**
    * Look up the index of an attribute given its name.
    * If more than one attribute with the same name exist,
    * this will return the index of the first match.
    *
    * @lparam pszAttributeName - name of the attribute

    *
    * @return zero-based index of an attribute, or -1 if not found
    * @since 1.0
    * @author Gurmeet S. Kochar
    */
   int getIndexFromName(const ::scoped_string & scopedstrAttributeName) const

   {
      ASSERT(is_string_ok(scopedstrAttributeName));

      LiteHTMLElemAttr   *pItem = nullptr;
      for (int iElem = 0; iElem < getCount(); iElem++)
      {
         if ((pItem = (*m_parrAttrib)[iElem]) == nullptr)   // just in case
            continue;

         // perform a CASE-INSENSITIVE search
         if (pItem->m_strName.case_insensitive_order(scopedstrAttributeName) == 0)

            return (iElem);
      }
      return (-1);
   }

   /**
    * Returns a LiteHTMLElemAttr object given an attribute's index
    *
    * @return LiteHTMLElemAttr containing the name and value of an attribute
    * @since 1.0
    * @author Gurmeet S. Kochar
    */
   LiteHTMLElemAttr operator[](int nIndex) const
   {
      if (!(nIndex >= 0 && nIndex < getCount()))
      {
         ASSERT(false);
         return (LiteHTMLElemAttr());
      }
      return ( *((*m_parrAttrib)[nIndex]) );
   }

   /**
    * Returns a LiteHTMLElemAttr object given an attribute name
    *
    * @return LiteHTMLElemAttr containing the name and value of an attribute
    * @since 1.0
    * @author Gurmeet S. Kochar
    */
   LiteHTMLElemAttr operator[](const ::scoped_string & scopedstrIndex) const

   {
      ASSERT(is_string_ok(scopedstrIndex));

      return ((*this)[getIndexFromName(scopedstrIndex)]);

   }

   /**
    * Returns a LiteHTMLElemAttr object given an attribute's index
    *
    * @return LiteHTMLElemAttr containing the name and value of an attribute
    * @since 1.0
    * @author Gurmeet S. Kochar
    */
   LiteHTMLElemAttr getAttribute(int nIndex) const
   { return ((*this)[nIndex]); }

   /**
    * Returns a LiteHTMLElemAttr object given an attribute name
    *
    * @return LiteHTMLElemAttr containing the name and value of an attribute
    * @since 1.0
    * @author Gurmeet S. Kochar
    */
   LiteHTMLElemAttr getAttribute(const ::scoped_string & scopedstrIndex) const

   {
      ASSERT(is_string_ok(scopedstrIndex));

      return ((*this)[getIndexFromName(scopedstrIndex)]);

   }

   /**
    * Returns the name of an attribute given its index
    *
    * @return name of an attribute
    * @since 1.0
    * @author Gurmeet S. Kochar
    */
   string getName(int nIndex) const
   { return ((*this)[nIndex].m_strName); }

   /**
    * Returns the value of an attribute given its index
    *
    * @return value of an attribute
    * @since 1.0
    * @author Gurmeet S. Kochar
    */
   string getValue(int nIndex) const
   { return ((*this)[nIndex].m_strValue); }

   /**
    * Returns the value of an attribute given its name
    *
    * @return value of an attribute
    * @since 1.0
    * @author Gurmeet S. Kochar
    */
   string getValueFromName(const ::scoped_string & scopedstrAttributeName) const
   {

      return ((*this)[scopedstrAttributeName].m_strValue);


   }



public:
   /**
    * Adds a ___new LiteHTMLElemAttr item to the collection
    *
    * @lparam lpszName - attribute name (serves as the key to the item)

    * @lparam pszValue - attribute value

    * @lparam bReplaceOld - If an item with the same name as specified
    *        by lpszName already exists in the collection, this

    *        parameter is used to determine whether to replace the
    *        existing item or add a ___new one
    *
    * @return pointer to a LiteHTMLElemAttr
    * @since 1.0
    * @author Gurmeet S. Kochar
    */
   LiteHTMLElemAttr* addAttribute(const ::scoped_string & scopedstrName, const ::scoped_string & scopedstrValue);


   /**
    * Removes an LiteHTMLElemAttr item from the collection
    *
    * @lparam lpszName - attribute to erase

    *
    * @return true if successful, false otherwise
    * @since 1.0
    * @author Gurmeet S. Kochar
    */
   bool eraseAttribute(int nIndex)
   {
      if (!(nIndex >= 0 && nIndex < getCount()))
         return (false);
      LiteHTMLElemAttr   *pItem = (*m_parrAttrib)[nIndex];
      ASSERT(pItem != nullptr);
      SAFE_DELETE_POINTER(pItem);
      return (true);
   }

   /**
    * Removes all LiteHTMLElemAttr items from the collection
    * @return true if successful, false otherwise
    * @since 1.0
    * @author Gurmeet S. Kochar
    */
   bool eraseAll()
   {
      LiteHTMLElemAttr   *pItem = nullptr;
      for (int iElem = 0; iElem < getCount(); iElem++)
      {
         pItem = (*m_parrAttrib)[iElem];
         ASSERT(pItem != nullptr);
         SAFE_DELETE_POINTER(pItem);
      }
      SAFE_DELETE_POINTER(m_parrAttrib);
      return (true);
   }

// Data Members
private:
   typedef address_array < LiteHTMLElemAttr * >   CElemAttrArray;
   CElemAttrArray   *m_parrAttrib;   // array of attributes/value pairs
};
