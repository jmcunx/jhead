/*
 * Copyright (c) 2007 ... 2020 2021
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

#ifndef JHEAD_H_REV

#define JHEAD_H_REV "$Id: jhead.h,v 3.2 2020/06/14 20:08:01 jmccue Exp $"

#define PROG_NAME      "jhead"
#define JHEAD_MSG_SIZE 256
#define ARG_JHEAD      "ARG_JHEAD"

#define HEAD_LINES_DEFAULT 10L
#define HEAD_LINES_START   1L

/*** Structures ***/
struct s_file_info
{
  FILE *fp;
  char *fname;
} ;

typedef struct
{
  char *prog_name;
  char arg_switch;
  char response_switch;
  char msg[JHEAD_MSG_SIZE];
  int  num_files;
  int  force;                  /* TRUE or FALSE, defaults to FALSE */
  int  verbose;                /* TRUE or FALSE, defaults to TRUE  */
  int  show_ln;                /* TRUE or FALSE, defaults to FALSE */
  long int  start_line;        /* Start at this line number        */
  long int  show_lines;        /* Lines to display                 */
  struct s_file_info out;
  struct s_file_info err;
}  work_area;

/*** Prototypes ***/
void process_arg(int, char **, work_area *);
void init(work_area *, int, char **);
int  show_rev(work_area *);
int  show_brief_help(work_area *);
void get_prog_name(char **, char *);
void close_out(struct s_file_info *);
void init_finfo(struct s_file_info *);

#endif /* JHEAD_H_REV */

/* END: jhead.h */
