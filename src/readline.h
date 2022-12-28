#ifndef READLINE_H
#define READLINE_H

/*
 * Read a line from the keyboard.
 * The caller is responsible for freeing the returned string with kfree()
 */
char *readline(void);

#endif
