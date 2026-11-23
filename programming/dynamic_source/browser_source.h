#pragma once

namespace dynamic_source
{
   // Only a leading block is client code. Server blocks and their string
   // literals are never searched for client delimiters.
   inline bool extract_browser_source(string & source, string & browser_source)
   {
      if (source.substr(0, 5) != "<?cpp")
         return false;

      auto separator = source.substr(5, 1);
      if (separator != " " && separator != "\t" && separator != "\r" && separator != "\n")
         throw ::parsing_exception("Expected whitespace after <?cpp");

      auto end = source.find_index("?>", 5);
      if (end < 0)
         throw ::parsing_exception("Unterminated browser C++ block");

      browser_source = source.substr(5, end - 5);
      source = source.substr(end + 2);
      // Preserve recognition of an existing leading <?ss declarations block.
      while (source.substr(0, 1) == "\r" || source.substr(0, 1) == "\n")
         source = source.substr(1);
      return true;
   }
}
