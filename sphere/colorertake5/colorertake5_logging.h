#pragma once


#define COLORER_FEATURE_LOGLEVEL_QUIET 0
#define COLORER_FEATURE_LOGLEVEL_ERROR 1
#define COLORER_FEATURE_LOGLEVEL_WARN  2
#define COLORER_FEATURE_LOGLEVEL_TRACE 3
#define COLORER_FEATURE_LOGLEVEL_INFO  4
#define COLORER_FEATURE_LOGLEVEL_FULL  4

#define CLR_ERROR if (COLORER_FEATURE_LOGLEVEL >= COLORER_FEATURE_LOGLEVEL_ERROR)   colorer_logger_error
#define CLR_WARN  if (COLORER_FEATURE_LOGLEVEL >= COLORER_FEATURE_LOGLEVEL_WARN)    colorer_logger_warn
#define CLR_TRACE if (COLORER_FEATURE_LOGLEVEL >= COLORER_FEATURE_LOGLEVEL_TRACE)   colorer_logger_trace
#define CLR_INFO  if (COLORER_FEATURE_LOGLEVEL >= COLORER_FEATURE_LOGLEVEL_INFO)    colorer_logger_info


#include <assert.h>

namespace colorertake5
{

void colorer_logger_error(const ::string &cname, const ::string &msg, ...);
void colorer_logger_warn(const ::string &cname, const ::string &msg, ...);
void colorer_logger_trace(const ::string &cname, const ::string &msg, ...);
void colorer_logger_info(const ::string &cname, const ::string &msg, ...);

void colorer_logger(i32 level, const ::string &cname, const ::string &msg, va_list v);

void colorer_logger_set_target(const ::string &logfile);

}

/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is the Colorer Library.
 *
 * The Initial Developer of the Original Code is
 * Cail Lomecb <cail@nm.ru>.
 * Portions created by the Initial Developer are Copyright (C) 1999-2005
 * the Initial Developer.
 *
 * Contributor(s):
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */
