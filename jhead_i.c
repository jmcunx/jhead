/*
 * Copyright (c) 2007 ... 2023 2024
 *     John McCue <jmccue@jmcunx.com>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef _MSDOS
#include <sys/param.h>
#endif
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>

#ifdef HAVE_JLIB
#include <j_lib2.h>
#include <j_lib2m.h>
#endif

#include "jhead.h"

/*
 * f_init_fi() - clear file information
 */
void f_init_fi(struct s_file_info *f)
{

  f->fp    = (FILE *) NULL; 
  f->fname = (char *) NULL;

} /* f_init_fi() */
   
/*
 * clear_work()
 */
void clear_work(work_area *w, char *a)

{

  w->prog_name   = j2_get_prgname(a, PROG_NAME);
  w->num_files   = (int) 0;
  w->force       = (int) FALSE;
  w->verbose     = (int) TRUE;
  w->show_ln     = (int) FALSE;
  w->start_line  = HEAD_LINES_START;
  w->show_lines  = HEAD_LINES_DEFAULT;

  memset(w->msg, JLIB2_CHAR_NULL, JHEAD_MSG_SIZE);

  f_init_fi(&(w->out));
  f_init_fi(&(w->err));
  
  w->out.fp = stdout;
  w->err.fp = stderr;
  
} /* clear_work() */

/*
 * init() -- setup for Run
 */
void init(work_area *w, int argc, char **argv)

{

  clear_work(w, argv[0]);

  process_arg(argc, argv, w);

} /* process_arg() */
