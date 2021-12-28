/*
 * Copyright (c) 2007 ... 2021 2022
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
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#ifdef IS_BSD
#include <err.h>
#endif

#include <j_lib2.h>
#include <j_lib2m.h>

#include "jhead.h"

/*
 * open_in() -- open in file
 */
int open_in(FILE **in, char *fname, FILE *fp_err)

{

  int errsave;

  if (fname == (char *) NULL)
    {
      (*in) = stdin;
      return((int) TRUE);
    }
  if (strcmp(fname, FILE_NAME_STDIN) == 0)
    {
      (*in) = stdin;
      return((int) TRUE);
    }

  (*in) = fopen(fname, "r");
  errsave = errno;

  if ((*in) == (FILE *) NULL)
    {
      fprintf(fp_err, MSG_WARN_W002, fname, strerror(errsave));
      return((int) FALSE);
    }

  return((int) TRUE);

} /* open_in() */

/*
 * close_out() -- close output
 */
void close_out(struct s_file_info *f)
{

  if (f->fname != (char *) NULL)
    {
      fclose(f->fp);
      free(f->fname);
      f->fname = (char *) NULL;
    }

} /* close_out() */

/*
 * show_file_heading() -- Show run stats
 */
void show_file_heading(FILE *fp, char *fname)

{

  fprintf(fp, "%s\n", LIT_C80);

  if (fname == (char *) NULL)
    fprintf(fp, "%s\n", LIT_STDIN);
  else
    {
      if (strcmp(fname, FILE_NAME_STDIN) == 0)
	fprintf(fp, "%s\n", LIT_STDIN);
      else
	fprintf(fp, "%s\n", fname);
    }

  fprintf(fp, "%s\n", LIT_C80);

} /* show_file_heading() */

/*
 * eoj() -- End of Job
 */
void eoj(work_area *w)

{

  close_out(&(w->out));
  close_out(&(w->err));

} /* eoj() */

/*
 * process_a_file()
 */
void process_a_file(work_area *w, char *fname,
                    char **buf,   size_t *bsiz)

{

  long int lines_read = 0L;
  long int shown = 0L;
  FILE *fp;

  if (w->verbose == (int) TRUE)
    show_file_heading(w->out.fp, fname);

  if ( ! open_in(&fp, fname, w->err.fp) )
    return;

  while (j2_getline(buf, bsiz, fp) > (ssize_t) -1)
    {
      lines_read++;
      if (lines_read >= w->start_line)
        {
          shown++;
	  if ( w->show_ln )
	    fprintf(w->out.fp, "%ld: %s", lines_read, (*buf));
	  else
	    fprintf(w->out.fp, "%s", (*buf));
          if (shown >= w->show_lines)
            break;
        }
    }

  if (fname != (char *) NULL)
    {
      if (strcmp(fname, FILE_NAME_STDIN) !=0)
	{
	  if (fp != (FILE *) NULL)
	    fclose(fp);
	}
    }

} /* process_a_file() */

/*
 * process_all()
 */
void process_all(int argc, char **argv, work_area *w)

{
  char *buf = (char *) NULL;
  size_t bsiz = (size_t) 0;
  int i;

  for (i = optind; i < argc; i++)
    process_a_file(w, argv[i], &buf, &bsiz);

  if (i == optind)
    process_a_file(w, FILE_NAME_STDIN, &buf, &bsiz);

  if (buf != (char *) NULL)
    free(buf);

} /* process_all() */

/*
 * main()
 */
int main(int argc, char **argv)

{
  work_area w;

#ifdef OpenBSD
  if(pledge("stdio rpath wpath cpath",NULL) == -1)
    err(1,"pledge\n");
#endif

  init(&w, argc, argv);

  process_all(argc, argv, &w);

  eoj(&w);
  exit(EXIT_SUCCESS);

}  /* main() */
