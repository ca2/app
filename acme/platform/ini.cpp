//
//  ini.cpp
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 04/04/26.
//  Copyright © 2026 ca2 Software Development. All rights reserved.
//
#include "framework.h"
#include "ini.h"
#include "winprofile_compat_v2.h"

//#ifndef _WIN32

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* ============================================================
   Config
   ============================================================ */

#define WP_MAX_LINE     8192
#define WP_MAX_NAME     1024
#define WP_MAX_VALUE    4096

/* ============================================================
   Helpers
   ============================================================ */

static char *wp_strdup(const char *s) {
    size_t n;
    char *p;
    if (!s) return NULL;
    n = strlen(s);
    p = (char *)malloc(n + 1);
    if (!p) return NULL;
    memcpy(p, s, n + 1);
    return p;
}

static int wp_stricmp(const char *a, const char *b) {
    unsigned char ca, cb;
    while (*a && *b) {
        ca = (unsigned char)tolower((unsigned char)*a);
        cb = (unsigned char)tolower((unsigned char)*b);
        if (ca != cb) return (int)ca - (int)cb;
        ++a;
        ++b;
    }
    ca = (unsigned char)tolower((unsigned char)*a);
    cb = (unsigned char)tolower((unsigned char)*b);
    return (int)ca - (int)cb;
}

static char *wp_ltrim(char *s) {
    while (*s && isspace((unsigned char)*s)) ++s;
    return s;
}

static void wp_rtrim_inplace(char *s) {
    size_t len = strlen(s);
    while (len > 0 && isspace((unsigned char)s[len - 1])) {
        s[len - 1] = '\0';
        --len;
    }
}

static char *wp_trim(char *s) {
    s = wp_ltrim(s);
    wp_rtrim_inplace(s);
    return s;
}

static int wp_is_blank(const char *s) {
    while (*s) {
        if (!isspace((unsigned char)*s)) return 0;
        ++s;
    }
    return 1;
}

static int wp_is_comment_line(const char *s) {
    char buf[WP_MAX_LINE];
    char *t;
    strncpy(buf, s ? s : "", sizeof(buf) - 1);
    buf[sizeof(buf) - 1] = '\0';
    t = wp_trim(buf);
    return (*t == ';' || *t == '#');
}

static int wp_starts_with_space(const char *s) {
    return s && *s && isspace((unsigned char)*s);
}

/* ============================================================
   Dynamic line array
   ============================================================ */

typedef struct {
    char **items;
    size_t count;
    size_t cap;
} WpLines;

static void wp_lines_free(WpLines *a) {
    size_t i;
    if (!a) return;
    for (i = 0; i < a->count; ++i) free(a->items[i]);
    free(a->items);
    a->items = NULL;
    a->count = 0;
    a->cap = 0;
}

static int wp_lines_reserve(WpLines *a, size_t need) {
    char **p;
    size_t newcap;
    if (need <= a->cap) return 1;
    newcap = (a->cap == 0) ? 16 : a->cap;
    while (newcap < need) newcap *= 2;
    p = (char **)realloc(a->items, newcap * sizeof(char *));
    if (!p) return 0;
    a->items = p;
    a->cap = newcap;
    return 1;
}

static int wp_lines_push(WpLines *a, const char *line) {
    if (!wp_lines_reserve(a, a->count + 1)) return 0;
    a->items[a->count] = wp_strdup(line ? line : "");
    if (!a->items[a->count]) return 0;
    ++a->count;
    return 1;
}

static int wp_lines_insert(WpLines *a, size_t pos, const char *line) {
    size_t i;
    if (pos > a->count) pos = a->count;
    if (!wp_lines_reserve(a, a->count + 1)) return 0;
    for (i = a->count; i > pos; --i) {
        a->items[i] = a->items[i - 1];
    }
    a->items[pos] = wp_strdup(line ? line : "");
    if (!a->items[pos]) return 0;
    ++a->count;
    return 1;
}

static void wp_lines_remove_range(WpLines *a, size_t start, size_t end) {
    size_t i, n;
    if (start >= end || start >= a->count) return;
    if (end > a->count) end = a->count;
    for (i = start; i < end; ++i) free(a->items[i]);
    n = end - start;
    for (i = end; i < a->count; ++i) a->items[i - n] = a->items[i];
    a->count -= n;
}

static int wp_read_all_lines(const char *filename, WpLines *out) {
    FILE *fp;
    char buf[WP_MAX_LINE];
    memset(out, 0, sizeof(*out));

    fp = fopen(filename, "rb");
    if (!fp) return 1; /* treat missing file as empty */

    while (fgets(buf, sizeof(buf), fp)) {
        size_t len = strlen(buf);
        while (len > 0 && (buf[len - 1] == '\n' || buf[len - 1] == '\r')) {
            buf[len - 1] = '\0';
            --len;
        }
        if (!wp_lines_push(out, buf)) {
            fclose(fp);
            wp_lines_free(out);
            return 0;
        }
    }

    fclose(fp);
    return 1;
}

static int wp_write_all_lines(const char *filename, const WpLines *a) {
    FILE *fp;
    size_t i;
    fp = fopen(filename, "wb");
    if (!fp) return 0;
    for (i = 0; i < a->count; ++i) {
        if (fputs(a->items[i], fp) == EOF || fputc('\n', fp) == EOF) {
            fclose(fp);
            return 0;
        }
    }
    if (fclose(fp) != 0) return 0;
    return 1;
}

/* ============================================================
   Parsing: sections
   ============================================================ */

static int wp_parse_section_name(const char *line, char *out, size_t outsz) {
    char buf[WP_MAX_LINE];
    char *t, *start, *end;
    size_t len;

    if (!line) return 0;

    strncpy(buf, line, sizeof(buf) - 1);
    buf[sizeof(buf) - 1] = '\0';
    t = wp_trim(buf);

    if (*t != '[') return 0;
    start = t + 1;
    end = strchr(start, ']');
    if (!end) return 0;

    len = (size_t)(end - start);
    if (len >= outsz) len = outsz - 1;
    memcpy(out, start, len);
    out[len] = '\0';
    wp_trim(out);
    return 1;
}

/* ============================================================
   Parsing: escaped / quoted values
   ============================================================ */

static void wp_append_char(char *dst, size_t dstsz, size_t *di, char c) {
    if (*di + 1 < dstsz) {
        dst[*di] = c;
        ++(*di);
        dst[*di] = '\0';
    }
}

static void wp_unescape_string(const char *src, char *dst, size_t dstsz) {
    size_t i = 0;
    size_t di = 0;
    dst[0] = '\0';

    while (src[i]) {
        if (src[i] == '\\') {
            ++i;
            switch (src[i]) {
                case 'n':  wp_append_char(dst, dstsz, &di, '\n'); break;
                case 'r':  wp_append_char(dst, dstsz, &di, '\r'); break;
                case 't':  wp_append_char(dst, dstsz, &di, '\t'); break;
                case '\\': wp_append_char(dst, dstsz, &di, '\\'); break;
                case '"':  wp_append_char(dst, dstsz, &di, '"'); break;
                case ';':  wp_append_char(dst, dstsz, &di, ';'); break;
                case '#':  wp_append_char(dst, dstsz, &di, '#'); break;
                case '=':  wp_append_char(dst, dstsz, &di, '='); break;
                case '\0':
                    return;
                default:
                    wp_append_char(dst, dstsz, &di, src[i]);
                    break;
            }
            if (src[i]) ++i;
        } else {
            wp_append_char(dst, dstsz, &di, src[i]);
            ++i;
        }
    }
}

static void wp_escape_string(const char *src, char *dst, size_t dstsz) {
    size_t i = 0, di = 0;
    dst[0] = '\0';

    while (src[i]) {
        char c = src[i++];
        switch (c) {
            case '\n':
                if (di + 2 < dstsz) { dst[di++]='\\'; dst[di++]='n'; }
                break;
            case '\r':
                if (di + 2 < dstsz) { dst[di++]='\\'; dst[di++]='r'; }
                break;
            case '\t':
                if (di + 2 < dstsz) { dst[di++]='\\'; dst[di++]='t'; }
                break;
            case '\\':
                if (di + 2 < dstsz) { dst[di++]='\\'; dst[di++]='\\'; }
                break;
            case '"':
                if (di + 2 < dstsz) { dst[di++]='\\'; dst[di++]='"'; }
                break;
            default:
                if (di + 1 < dstsz) dst[di++] = c;
                break;
        }
    }
    dst[di] = '\0';
}

static int wp_needs_quotes(const char *s) {
    if (!s || !*s) return 1;
    if (isspace((unsigned char)s[0])) return 1;
    while (*s) {
        if (*s == ';' || *s == '#' || *s == '=' || *s == '"')
            return 1;
        ++s;
    }
    return 0;
}

static void wp_encode_value(const char *value, char *dst, size_t dstsz) {
    char esc[WP_MAX_VALUE * 2];
    wp_escape_string(value ? value : "", esc, sizeof(esc));

    if (wp_needs_quotes(value ? value : "")) {
        snprintf(dst, dstsz, "\"%s\"", esc);
    } else {
        snprintf(dst, dstsz, "%s", esc);
    }
}

/*
Parses:
  key = value ; comment
  key="hello\nworld" # comment
Preserves:
  prefix spacing around key and '='
  inline comment suffix (returned separately)

Returns 1 if line is key/value.
*/
static int wp_parse_key_value_line_ex(
    const char *line,
    char *out_key, size_t keysz,
    char *out_value, size_t valsz,
    char *out_inline_comment, size_t commentsz
) {
    const char *p;
    const char *eq;
    char keybuf[WP_MAX_NAME];
    char valbuf[WP_MAX_VALUE];
    size_t klen = 0, vlen = 0;
    int in_quotes = 0;
    int escaped = 0;
    const char *comment_start = NULL;

    out_key[0] = '\0';
    out_value[0] = '\0';
    if (out_inline_comment && commentsz > 0) out_inline_comment[0] = '\0';

    if (!line) return 0;

    p = line;
    while (*p && isspace((unsigned char)*p)) ++p;
    if (*p == '\0' || *p == ';' || *p == '#') return 0;

    eq = strchr(p, '=');
    if (!eq) return 0;

    /* key */
    while (p < eq && klen + 1 < sizeof(keybuf)) {
        keybuf[klen++] = *p++;
    }
    keybuf[klen] = '\0';
    {
        char *tk = wp_trim(keybuf);
        memmove(keybuf, tk, strlen(tk) + 1);
    }

    /* value */
    p = eq + 1;
    while (*p && isspace((unsigned char)*p)) ++p;

    if (*p == '"') {
        in_quotes = 1;
        ++p;
    }

    while (*p) {
        if (escaped) {
            if (vlen + 2 < sizeof(valbuf)) {
                valbuf[vlen++] = '\\';
                valbuf[vlen++] = *p;
            }
            escaped = 0;
            ++p;
            continue;
        }

        if (*p == '\\') {
            escaped = 1;
            ++p;
            continue;
        }

        if (in_quotes) {
            if (*p == '"') {
                ++p;
                break;
            }
            if (vlen + 1 < sizeof(valbuf)) valbuf[vlen++] = *p;
            ++p;
        } else {
            if (*p == ';' || *p == '#') {
                comment_start = p;
                break;
            }
            if (vlen + 1 < sizeof(valbuf)) valbuf[vlen++] = *p;
            ++p;
        }
    }

    valbuf[vlen] = '\0';
    wp_rtrim_inplace(valbuf);

    /* after quoted value, allow spaces then inline comment */
    if (!comment_start) {
        while (*p && isspace((unsigned char)*p)) ++p;
        if (*p == ';' || *p == '#') comment_start = p;
    }

    if (comment_start && out_inline_comment && commentsz > 0) {
        strncpy(out_inline_comment, comment_start, commentsz - 1);
        out_inline_comment[commentsz - 1] = '\0';
    }

    wp_unescape_string(valbuf, out_value, valsz);

    strncpy(out_key, keybuf, keysz - 1);
    out_key[keysz - 1] = '\0';

    return 1;
}

/* ============================================================
   Section/key location
   ============================================================ */

typedef struct {
    int found_section;
    size_t section_start;
    size_t section_end;      /* one past last line in section */

    int found_key;
    size_t key_line;

    size_t key_block_start;  /* includes immediately preceding comments */
} WpLocation;

static WpLocation wp_find_section_and_key(
    const WpLines *lines,
    const char *section,
    const char *key
) {
    WpLocation loc;
    size_t i;
    int in_target = 0;
    char sec[WP_MAX_NAME];
    char k[WP_MAX_NAME], v[WP_MAX_VALUE], c[WP_MAX_VALUE];

    memset(&loc, 0, sizeof(loc));
    loc.section_start = (size_t)-1;
    loc.section_end   = lines->count;
    loc.key_line      = (size_t)-1;
    loc.key_block_start = (size_t)-1;

    for (i = 0; i < lines->count; ++i) {
        if (wp_parse_section_name(lines->items[i], sec, sizeof(sec))) {
            if (in_target) {
                loc.section_end = i;
                break;
            }
            if (wp_stricmp(sec, section) == 0) {
                loc.found_section = 1;
                loc.section_start = i;
                in_target = 1;
            }
            continue;
        }

        if (in_target && key) {
            if (wp_parse_key_value_line_ex(lines->items[i], k, sizeof(k), v, sizeof(v), c, sizeof(c))) {
                if (wp_stricmp(k, key) == 0) {
                    size_t start = i;
                    while (start > loc.section_start + 1) {
                        const char *prev = lines->items[start - 1];
                        if (wp_is_comment_line(prev) || wp_is_blank(prev)) {
                            --start;
                        } else {
                            break;
                        }
                    }
                    loc.found_key = 1;
                    loc.key_line = i;
                    loc.key_block_start = start;
                }
            }
        }
    }

    if (in_target && loc.section_end == lines->count) {
        loc.section_end = lines->count;
    }

    return loc;
}

/* ============================================================
   Win32-style multi-string helpers
   ============================================================ */

static DWORD wp_copy_cstr(char *dst, DWORD nSize, const char *src) {
    size_t len;
    if (!dst || nSize == 0) return 0;
    if (!src) src = "";
    strncpy(dst, src, nSize - 1);
    dst[nSize - 1] = '\0';
    len = strlen(dst);
    return (DWORD)len;
}

static DWORD wp_multisz_append(char *dst, DWORD nSize, DWORD used, const char *s) {
    size_t len;
    if (!dst || nSize == 0) return 0;
    if (!s) s = "";
    len = strlen(s);

    if (used >= nSize) return nSize;

    while (*s && used + 1 < nSize) {
        dst[used++] = *s++;
    }

    if (used < nSize) dst[used++] = '\0';
    if (used < nSize) dst[used] = '\0';
    else dst[nSize - 1] = '\0';

    return used;
}

/* ============================================================
   Public API
   ============================================================ */

BOOL WritePrivateProfileStringA(
    const char *lpAppName,
    const char *lpKeyName,
    const char *lpString,
    const char *lpFileName
) {
    WpLines lines;
    WpLocation loc;
    char newline[WP_MAX_LINE];
    char encoded[WP_MAX_VALUE * 2];
    char k[WP_MAX_NAME], v[WP_MAX_VALUE], comment[WP_MAX_VALUE];

    if (!lpAppName || !lpFileName) return FALSE;

    if (!wp_read_all_lines(lpFileName, &lines)) return FALSE;

    loc = wp_find_section_and_key(&lines, lpAppName, lpKeyName);

    /* delete section */
    if (lpKeyName == NULL) {
        if (loc.found_section) {
            wp_lines_remove_range(&lines, loc.section_start, loc.section_end);
            if (loc.section_start < lines.count && wp_is_blank(lines.items[loc.section_start])) {
                wp_lines_remove_range(&lines, loc.section_start, loc.section_start + 1);
            }
        }
        if (!wp_write_all_lines(lpFileName, &lines)) {
            wp_lines_free(&lines);
            return FALSE;
        }
        wp_lines_free(&lines);
        return TRUE;
    }

    /* delete key */
    if (lpString == NULL) {
        if (loc.found_key) {
            /* delete only the actual key line, preserve surrounding comments */
            wp_lines_remove_range(&lines, loc.key_line, loc.key_line + 1);
        }
        if (!wp_write_all_lines(lpFileName, &lines)) {
            wp_lines_free(&lines);
            return FALSE;
        }
        wp_lines_free(&lines);
        return TRUE;
    }

    wp_encode_value(lpString, encoded, sizeof(encoded));

    /* replace existing key, preserving inline comment */
    if (loc.found_key) {
        comment[0] = '\0';
        if (wp_parse_key_value_line_ex(lines.items[loc.key_line], k, sizeof(k), v, sizeof(v), comment, sizeof(comment))) {
            if (comment[0]) {
                snprintf(newline, sizeof(newline), "%s=%s %s", lpKeyName, encoded, comment);
            } else {
                snprintf(newline, sizeof(newline), "%s=%s", lpKeyName, encoded);
            }
        } else {
            snprintf(newline, sizeof(newline), "%s=%s", lpKeyName, encoded);
        }

        free(lines.items[loc.key_line]);
        lines.items[loc.key_line] = wp_strdup(newline);
        if (!lines.items[loc.key_line]) {
            wp_lines_free(&lines);
            return FALSE;
        }
    }
    /* append key to existing section */
    else if (loc.found_section) {
        snprintf(newline, sizeof(newline), "%s=%s", lpKeyName, encoded);
        if (!wp_lines_insert(&lines, loc.section_end, newline)) {
            wp_lines_free(&lines);
            return FALSE;
        }
    }
    /* create section + key */
    else {
        if (lines.count > 0 && !wp_is_blank(lines.items[lines.count - 1])) {
            if (!wp_lines_push(&lines, "")) {
                wp_lines_free(&lines);
                return FALSE;
            }
        }

        snprintf(newline, sizeof(newline), "[%s]", lpAppName);
        if (!wp_lines_push(&lines, newline)) {
            wp_lines_free(&lines);
            return FALSE;
        }

        snprintf(newline, sizeof(newline), "%s=%s", lpKeyName, encoded);
        if (!wp_lines_push(&lines, newline)) {
            wp_lines_free(&lines);
            return FALSE;
        }
    }

    if (!wp_write_all_lines(lpFileName, &lines)) {
        wp_lines_free(&lines);
        return FALSE;
    }

    wp_lines_free(&lines);
    return TRUE;
}

DWORD GetPrivateProfileStringA(
    const char *lpAppName,
    const char *lpKeyName,
    const char *lpDefault,
    char *lpReturnedString,
    DWORD nSize,
    const char *lpFileName
) {
    WpLines lines;
    size_t i;
    int in_target = 0;
    char sec[WP_MAX_NAME];
    char key[WP_MAX_NAME], val[WP_MAX_VALUE], comment[WP_MAX_VALUE];
    DWORD used = 0;

    if (!lpReturnedString || nSize == 0) return 0;
    lpReturnedString[0] = '\0';

    if (!lpFileName) {
        return wp_copy_cstr(lpReturnedString, nSize, lpDefault ? lpDefault : "");
    }

    if (!wp_read_all_lines(lpFileName, &lines)) {
        return wp_copy_cstr(lpReturnedString, nSize, lpDefault ? lpDefault : "");
    }

    /* Win32-ish enumeration: app==NULL -> section names */
    if (lpAppName == NULL && lpKeyName == NULL) {
        for (i = 0; i < lines.count; ++i) {
            if (wp_parse_section_name(lines.items[i], sec, sizeof(sec))) {
                used = wp_multisz_append(lpReturnedString, nSize, used, sec);
                if (used >= nSize) break;
            }
        }
        if (used == 0 && nSize >= 2) {
            lpReturnedString[0] = '\0';
            lpReturnedString[1] = '\0';
            used = 1;
        } else if (used < nSize) {
            lpReturnedString[used] = '\0';
        } else {
            lpReturnedString[nSize - 1] = '\0';
        }
        wp_lines_free(&lines);
        return used ? (used - 1) : 0;
    }

    /* Win32-ish enumeration: key==NULL -> keys in section */
    if (lpAppName != NULL && lpKeyName == NULL) {
        for (i = 0; i < lines.count; ++i) {
            if (wp_parse_section_name(lines.items[i], sec, sizeof(sec))) {
                in_target = (wp_stricmp(sec, lpAppName) == 0);
                continue;
            }

            if (!in_target) continue;

            if (wp_parse_key_value_line_ex(lines.items[i], key, sizeof(key), val, sizeof(val), comment, sizeof(comment))) {
                used = wp_multisz_append(lpReturnedString, nSize, used, key);
                if (used >= nSize) break;
            }
        }

        if (used == 0 && nSize >= 2) {
            lpReturnedString[0] = '\0';
            lpReturnedString[1] = '\0';
            used = 1;
        } else if (used < nSize) {
            lpReturnedString[used] = '\0';
        } else {
            lpReturnedString[nSize - 1] = '\0';
        }

        wp_lines_free(&lines);
        return used ? (used - 1) : 0;
    }

    /* normal key lookup */
    if (!lpAppName || !lpKeyName) {
        wp_lines_free(&lines);
        return wp_copy_cstr(lpReturnedString, nSize, lpDefault ? lpDefault : "");
    }

    for (i = 0; i < lines.count; ++i) {
        if (wp_parse_section_name(lines.items[i], sec, sizeof(sec))) {
            in_target = (wp_stricmp(sec, lpAppName) == 0);
            continue;
        }

        if (!in_target) continue;

        if (wp_parse_key_value_line_ex(lines.items[i], key, sizeof(key), val, sizeof(val), comment, sizeof(comment))) {
            if (wp_stricmp(key, lpKeyName) == 0) {
                wp_lines_free(&lines);
                return wp_copy_cstr(lpReturnedString, nSize, val);
            }
        }
    }

    wp_lines_free(&lines);
    return wp_copy_cstr(lpReturnedString, nSize, lpDefault ? lpDefault : "");
}

UINT GetPrivateProfileIntA(
    const char *lpAppName,
    const char *lpKeyName,
    int nDefault,
    const char *lpFileName
) {
    char buf[64];
    char *endptr;
    long v;

    GetPrivateProfileStringA(lpAppName, lpKeyName, "", buf, (DWORD)sizeof(buf), lpFileName);
    if (buf[0] == '\0') return (UINT)nDefault;

    v = strtol(buf, &endptr, 0);
    if (endptr == buf) return (UINT)nDefault;
    return (UINT)v;
}

DWORD GetPrivateProfileSectionA(
    const char *lpAppName,
    char *lpReturnedString,
    DWORD nSize,
    const char *lpFileName
) {
    WpLines lines;
    size_t i;
    int in_target = 0;
    char sec[WP_MAX_NAME];
    char key[WP_MAX_NAME], val[WP_MAX_VALUE], comment[WP_MAX_VALUE];
    char kv[WP_MAX_LINE];
    DWORD used = 0;

    if (!lpReturnedString || nSize == 0) return 0;
    lpReturnedString[0] = '\0';

    if (!lpAppName || !lpFileName) {
        if (nSize >= 2) {
            lpReturnedString[0] = '\0';
            lpReturnedString[1] = '\0';
        }
        return 0;
    }

    if (!wp_read_all_lines(lpFileName, &lines)) {
        if (nSize >= 2) {
            lpReturnedString[0] = '\0';
            lpReturnedString[1] = '\0';
        }
        return 0;
    }

    for (i = 0; i < lines.count; ++i) {
        if (wp_parse_section_name(lines.items[i], sec, sizeof(sec))) {
            if (in_target) break;
            in_target = (wp_stricmp(sec, lpAppName) == 0);
            continue;
        }

        if (!in_target) continue;

        if (wp_parse_key_value_line_ex(lines.items[i], key, sizeof(key), val, sizeof(val), comment, sizeof(comment))) {
            snprintf(kv, sizeof(kv), "%s=%s", key, val);
            used = wp_multisz_append(lpReturnedString, nSize, used, kv);
            if (used >= nSize) break;
        }
    }

    if (used == 0 && nSize >= 2) {
        lpReturnedString[0] = '\0';
        lpReturnedString[1] = '\0';
        used = 1;
    } else if (used < nSize) {
        lpReturnedString[used] = '\0';
    } else {
        lpReturnedString[nSize - 1] = '\0';
    }

    wp_lines_free(&lines);
    return used ? (used - 1) : 0;
}

DWORD GetPrivateProfileSectionNamesA(
    char *lpszReturnBuffer,
    DWORD nSize,
    const char *lpFileName
) {
    return GetPrivateProfileStringA(NULL, NULL, "", lpszReturnBuffer, nSize, lpFileName);
}

#endif /* !_WIN32 */
