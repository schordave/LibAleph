/*
 * Copyright (c) 2006-2015 David Schor (david@zigwap.com), ZigWap LLC
 * 
 * License: MIT
 */

static char    *a_internal_cp_to_char(a_cp cp, char *buffer);
static a_cp     a_internal_char_to_cp(const char *s);
/*static a_cp   a_internal_to_next(const char **s);*/
static a_cp     a_internal_to_next_cp(const char **s);
static char    *a_internal_to_prev(const char **s);
static a_cp     a_internal_to_prev_cp(const char **s);