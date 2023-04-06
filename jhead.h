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

#ifndef JHEAD_H_REV

#define JHEAD_H_REV "INCLUDED"

#define PROG_NAME      "jhead"
#define JHEAD_MSG_SIZE 256
#define ARG_JHEAD      "ARG_JHEAD"

#define HEAD_LINES_DEFAULT 10L
#define HEAD_LINES_START   1L

#ifndef JLIB2_CHAR_NULL
#define NO_JLIB 1
#define JLIB2_INT_NULL   ((int) '\0')
#define JLIB2_CHAR_NULL  ((char) '\0')
#define JLIB2_UCHAR_NULL ((unsigned char) '\0' )
#endif

#ifndef NULL
#define NULL '\0'
#endif
#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

#ifndef SSIZE_T
#define SSIZE_T ssize_t
#endif
#ifndef TAB_CHAR
#define TAB_CHAR 0x09
#endif

/*** messages ***/
#ifdef NO_JLIB
#define ARG_COUNT         'c'  /* Prefix output with line number     */
#define ARG_END           'E'  /* End Line Number                    */
#define ARG_ERR           'e'  /* Output Error File                  */
#define ARG_FORCE         'f'  /* force create files                 */
#define ARG_HELP          'h'  /* Show Help                          */
#define ARG_NUMB          'n'  /* # of lines to print                */
#define ARG_OUT           'o'  /* Output File                        */
#define ARG_QUIET         'q'  /* Quiet Mode                         */
#define ARG_START         'S'  /* start print at line #              */
#define ARG_VERBOSE       'v'  /* Verbose                            */
#define ARG_VERSION       'V'  /* Show Version Information           */
#define FILE_NAME_STDIN   "-"
#define LIT_C80           "::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::"
#define LIT_INFO_01       "\tBuild: %s %s\n"
#define LIT_REV           "Revision"
#define LIT_STDIN         "(standard input)"
#define MSG_ERR_E000      "Try '%s %c%c' for more information\n"
#define MSG_ERR_E002      "ERROR E002: Cannot open '%s' for write, processing aborted\n"
#define MSG_ERR_E006      "ERROR E006: '%s' is an invalid value for %c%c\n"
#define MSG_ERR_E025      "ERROR E025: File %s cannot be created, already exists\n"
#define MSG_WARN_W002     "W002: Open Error Bypass File '%s' : %s\n"
#define SWITCH_CHAR       '-'
#define USG_MSG_ARG_COUNT      "\t%c%c\t\t: prefix output with line number\n"
#define USG_MSG_ARG_END_1      "\t%c%c #\t\t: End display at line '#'\n"
#define USG_MSG_ARG_ERR        "\t%c%c file\t\t: Write errors to file 'file', default stderr\n"
#define USG_MSG_ARG_FORCE      "\t%c%c\t\t: force create of files when found\n"
#define USG_MSG_ARG_HELP       "\t%c%c\t\t: Show brief help and exit\n"
#define USG_MSG_ARG_NUMB       "\t%c%c #\t\t: Display '#' lines, default is to display %ld lines\n"
#define USG_MSG_ARG_OUT        "\t%c%c file\t\t: Write output to file 'file', default stdout\n"
#define USG_MSG_ARG_QUIET_2    "\t%c%c\t\t: do not show file headings.\n"
#define USG_MSG_ARG_START_1    "\t%c%c #\t\t: Start display at line '#', default is line %ld\n"
#define USG_MSG_ARG_VERBOSE_1  "\t%c%c\t\t: Show headings for file being processed\n"
#define USG_MSG_ARG_VERSION    "\t%c%c\t\t: Show revision information and exit\n"
#define USG_MSG_OPTIONS        "Options\n"
#define USG_MSG_USAGE          "usage:\t%s [OPTIONS] [FILES ...]\n"
#endif /* NO_JLIB */

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

#ifdef NO_JLIB
SSIZE_T j2_getline(char **buf, size_t *n, FILE *fp);
char *j2_get_prgname(char *argv_0, char *default_name);
int j2_f_exist(char *file_name);
long int j2_clr_str(char *s, char c, int size);
#endif /* NO_JLIB */

#endif /* JHEAD_H_REV */
