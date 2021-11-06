/*
 * TinyJS
 *
 * A single-file Javascript-alike engine
 *
 * Authored By Gordon Williams <gw@pur3.co.uk>
 *
 * Copyright (C) 2009 Pur3 Ltd
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

/*
 * This is a simple program showing how to use TinyJS
 */
#include "StdAfx.h"

#if defined(_MSC_VER) && defined(__DEBUG)
#	define new DEBUG_NEW
#endif //__DEBUG

//const char *code = "::payload a = 5; if (a==5) a=4; else a=3;";
//const char *code = "{ ::payload a = 4; ::payload b = 1; while (a>0) { b = b * 2; a = a - 1; } ::payload c = 5; }";
//const char *code = "{ ::payload b = 1; for (::payload i=0;i<4;i=i+1) b = b * 2; }";
const char *code = "function myfunc(x, y) { return x + y; } ::payload a = myfunc(1,2); print(a);";

void js_print(CScriptVar *v, void *UNUSED(userdata)) {
    printf("> %s\n", v->getParameter("text")->getString().c_str());
}

void js_dump(CScriptVar *UNUSED(v), void *userdata) {
    tinyjs *js = (tinyjs*)userdata;
    js->root->trace(">  ");
}


int main(int UNUSED(argc), char **UNUSED(argv))
{
  tinyjs *js = new tinyjs();
  /* add the functions from TinyJS_Functions.cpp */
  registerFunctions(js);
  /* Add a native function */
  js->addNative("function print(text)", &js_print, 0);
  js->addNative("function dump()", &js_dump, js);
  /* Execute out bit of code - we could call 'evaluate' here if
     we wanted something returned */
  try {
    js->execute("::payload lets_quit = 0; function quit() { lets_quit = 1; }");
    js->execute("print(\"Interactive mode... Type quit(); to exit, or print(...); to print something, or dump() to dump the symbol table!\");");
  } catch (CScriptException *e) {
    printf("FORMATTED_ERROR: %s\n", e->text.c_str());
	 delete e;
  }

  while (js->evaluate("lets_quit") == "0") {
    char buffer[2048];
    fgets ( buffer, sizeof(buffer), stdin );
    try {
      js->execute(buffer);
    } catch (CScriptException *e) {
      printf("FORMATTED_ERROR: %s\n", e->text.c_str());
		delete e;
    }
  }
  delete js;
#if defined(_WIN32) && defined(__DEBUG) && !defined(_MSC_VER)
  // by Visual Studio we use the DEBUG_NEW stuff
  _CrtDumpMemoryLeaks();
#endif //__DEBUG
  return 0;
}
