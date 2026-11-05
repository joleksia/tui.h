/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 *  tui.h - Text User Interface single-header library 
 *
 *      - made by: Jakub "joleksia" Oleksiak
 *      - version: 1.0
 *      - licence: lgpl-3
 * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#if defined (__cplusplus)
# pragma once
#endif
#
#if !defined (_tui_h_)
# define _tui_h_ 1
#
# define TUI_VERSION "1.0"
#
# /* Define platform macros */
# if defined (__linux__)
#  define TUI_PLATFORM "linux"
#  define TUI_PLATFORM_LINUX 1
#
# elif defined (__APPLE__) || defined (__MACH__)
#  define TUI_PLATFORM "apple"
#  define TUI_PLATFORM_APPLE 1
#
# elif defined (__CYGWIN__) || defined (_WIN32)
#  define TUI_PLATFORM "win32"
#  define TUI_PLATFORM_WIN32 1
#
# elif defined (__FreeBSD__) || defined (__NetBSD__) || defined (__bsdi__) || defined (__DragonFly__) || defined (__MidnightBSD__)
#  define TUI_PLATFORM "bsd"
#  define TUI_PLATFORM_BSD 1
#
# else
#  error /* No valid platform found */
# endif
#
# include <stddef.h>
# include <stdint.h>

typedef struct _tui_h *tui_t;

enum tui_key_e {
    
    TUI_KEY_ARROW_UP    = ('\x1b' << 24) | ('[' << 16) | ('A' << 8) | (0 << 0),
    TUI_KEY_ARROW_DOWN  = ('\x1b' << 24) | ('[' << 16) | ('B' << 8) | (0 << 0),
    TUI_KEY_ARROW_RIGHT = ('\x1b' << 24) | ('[' << 16) | ('C' << 8) | (0 << 0),
    TUI_KEY_ARROW_LEFT  = ('\x1b' << 24) | ('[' << 16) | ('D' << 8) | (0 << 0),
    
    TUI_KEY_HOME        = ('\x1b' << 24) | ('[' << 16) | ('1' << 8) | ('~' << 0),
    TUI_KEY_INSERT      = ('\x1b' << 24) | ('[' << 16) | ('2' << 8) | ('~' << 0),
    TUI_KEY_DELETE      = ('\x1b' << 24) | ('[' << 16) | ('3' << 8) | ('~' << 0),
    TUI_KEY_END         = ('\x1b' << 24) | ('[' << 16) | ('4' << 8) | ('~' << 0),
    TUI_KEY_PAGEUP      = ('\x1b' << 24) | ('[' << 16) | ('5' << 8) | ('~' << 0),
    TUI_KEY_PAGEDOWN    = ('\x1b' << 24) | ('[' << 16) | ('6' << 8) | ('~' << 0),
    
    TUI_KEY_F1          = ('\x1b' << 24) | ('O' << 16) | ('P' << 8) | (0 << 0),
    TUI_KEY_F2          = ('\x1b' << 24) | ('O' << 16) | ('Q' << 8) | (0 << 0),
    TUI_KEY_F3          = ('\x1b' << 24) | ('O' << 16) | ('R' << 8) | (0 << 0),
    TUI_KEY_F4          = ('\x1b' << 24) | ('O' << 16) | ('S' << 8) | (0 << 0),
    TUI_KEY_F5          = ('\x1b' << 24) | ('[' << 16) | ('1' << 8) | ('5' << 0),
    TUI_KEY_F6          = ('\x1b' << 24) | ('[' << 16) | ('1' << 8) | ('7' << 0),
    TUI_KEY_F7          = ('\x1b' << 24) | ('[' << 16) | ('1' << 8) | ('8' << 0),
    TUI_KEY_F8          = ('\x1b' << 24) | ('[' << 16) | ('1' << 8) | ('9' << 0),
    TUI_KEY_F9          = ('\x1b' << 24) | ('[' << 16) | ('2' << 8) | ('0' << 0),
    TUI_KEY_F10         = ('\x1b' << 24) | ('[' << 16) | ('2' << 8) | ('1' << 0),

};

/* tui.h */

int tui_init(tui_t *);

int tui_free(tui_t);

int tui_read(tui_t, void *);

int tui_write(tui_t, const void *, const size_t);

/* ... */

#endif /* _tui_h_ */
#
#if defined (TUI_IMPLEMENTATION)
# if !defined (_tui_impl_h_)
#  define _tui_impl_h_ 1
#
#  include <errno.h>
#  include <stdio.h>
#  include <stdlib.h>
#
#  if defined (TUI_PLATFORM_LINUX) || \
      defined (TUI_PLATFORM_APPLE) || \
      defined (TUI_PLATFORM_BSD)
#   undef unix
#   include <unistd.h>
#   include <termios.h>
#   include <sys/ioctl.h>
#
#  elif defined (TUI_PLATFORM_WIN32)
#   /* includes here... */
#
#  endif

struct _tui_h_unix;

struct _tui_h {

    /* platform-independent */

    struct {
        int (*init) (struct _tui_h *);
        int (*free) (struct _tui_h *);
        int (*read) (struct _tui_h *, void *);
        int (*write) (struct _tui_h *, const void *, const size_t);
    } api;

    /* platform-dependent */

    struct
    _tui_h_unix *unix;

    /* ... */

};

#  if defined (TUI_PLATFORM_LINUX) || \
      defined (TUI_PLATFORM_APPLE) || \
      defined (TUI_PLATFORM_BSD)

struct _tui_h_unix {

    /* standard file descriptor duplicated */
    int fd_stdin,
        fd_stdout,
        fd_stderr;

    struct
    termios t_default,
            t_rawmode;
};


static int __tui_unix_init(struct _tui_h *);

static int __tui_unix_free(struct _tui_h *);

static int __tui_unix_read(struct _tui_h *, void *);

static int __tui_unix_write(struct _tui_h *, const void *, const size_t);


static int __tui_unix_init(struct _tui_h *pTui) {
    /* null-check */
    if (!pTui) { return (-1); }

    /* create 'unix' object */
    struct
    _tui_h_unix *unix = (struct _tui_h_unix *) calloc(1, sizeof(struct _tui_h_unix));
    if (!unix) { return (-1); }

    /* 'dup' standard files  */
    int fd_stdin  = dup(STDIN_FILENO);
    int fd_stdout = dup(STDOUT_FILENO);
    int fd_stderr = dup(STDERR_FILENO);
    unix->fd_stdin  = fd_stdin;
    unix->fd_stdout = fd_stdout;
    unix->fd_stderr = fd_stderr;
    
    /* terminal configuration */
    struct
    termios t_default = { 0 };

    struct
    termios t_rawmode = { 0 };

    tcgetattr(unix->fd_stdin, &t_default);
    tcgetattr(unix->fd_stdin, &t_rawmode);
    
    t_rawmode.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
    t_rawmode.c_oflag &= ~(OPOST);
    t_rawmode.c_cflag |=  (CS8);
    t_rawmode.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
    t_rawmode.c_cc[VMIN]  = 0;
    t_rawmode.c_cc[VTIME] = 1;
    
    tcsetattr(unix->fd_stdin, TCSAFLUSH, &t_rawmode);
    
    unix->t_default = t_default;
    unix->t_rawmode = t_rawmode;

    /* return 'unix' */
    pTui->unix = unix;

    /* success */
    return (0);
}


static int __tui_unix_free(struct _tui_h *pTui) {
    /* null-check */
    if (!pTui) { return (-1); }
    
    /* references */
    struct
    _tui_h_unix *unix = pTui->unix;
    if (!unix) { return (-1); }

    /* terminal configuration */
    tcsetattr(unix->fd_stdin, TCSAFLUSH, &unix->t_default);
    for (size_t i = 0; i < sizeof(struct termios); ((uint8_t *) &unix->t_default)[i++] = 0);
    for (size_t i = 0; i < sizeof(struct termios); ((uint8_t *) &unix->t_rawmode)[i++] = 0);

    /* close file descriptors */
    close(unix->fd_stdin);  unix->fd_stdin  = -1;
    close(unix->fd_stdout); unix->fd_stdout = -1;
    close(unix->fd_stderr); unix->fd_stderr = -1;

    /* release 'unix' */
    free(unix);

    /* success */
    return (0);
}


static int __tui_unix_read(struct _tui_h *pTui, void *pOut) {
    /* null-check */
    if (!pTui) { return (-1); }
    if (!pOut) { return (-1); }
    
    /* references */
    struct
    _tui_h_unix *unix = pTui->unix;
    if (!unix) { return (-1); }

    /* 'read' from 'stdin' */
    ssize_t nread = read(unix->fd_stdin, pOut, 1);
    
    /* return 'nread' */
    return (nread);
}


static int __tui_unix_write(struct _tui_h *pTui, const void *pDat, const size_t size) {
    /* null-check */
    if (!pTui) { return (-1); }
    if (!pDat) { return (-1); }
    
    /* references */
    struct
    _tui_h_unix *unix = pTui->unix;
    if (!unix) { return (-1); }

    /* 'write' 'pDat' to 'fd_stdout' */
    ssize_t nwrite = write(unix->fd_stdout, pDat, size);

    /* return 'nwrite' */
    return (nwrite);
}

/* ... */

#  elif defined (TUI_PLATFORM_WIN32)

/* ... */

#  endif

int tui_init(tui_t *pTui) {
    /* null-check */
    if (!pTui) { return (0); }

    /* create 'result' object */
    struct
    _tui_h *tui = calloc(1, sizeof(struct _tui_h));
    if (!tui) { return (0); }

    /* setup platform-dependent api */

#  if defined (TUI_PLATFORM_LINUX) || \
      defined (TUI_PLATFORM_APPLE) || \
      defined (TUI_PLATFORM_BSD)

    tui->api.init = __tui_unix_init;
    tui->api.free = __tui_unix_free;
    tui->api.read = __tui_unix_read;
    tui->api.write = __tui_unix_write;

#  elif defined (TUI_PLATFORM_WIN32)

    /* ... */

#  endif

    /* return 'tui' */
    *pTui = tui;

    /* run 'init' */
    return (tui->api.init(tui));
}

int tui_free(tui_t pTui) {
    /* references */
    struct
    _tui_h *tui = (struct _tui_h *) pTui;
    if (!tui) { return (0); }

    /* run 'free' */
    tui->api.free(tui);

    /* release */
    free(tui);

    /* success */
    return (0);
}


int tui_read(tui_t pTui, void *pOut) {
    /* references */
    struct
    _tui_h *tui = (struct _tui_h *) pTui;
    if (!tui) { return (0); }

    /* run 'read' */
    return (tui->api.read(pTui, pOut));
}


int tui_write(tui_t pTui, const void *pDat, const size_t size) {
    /* references */
    struct
    _tui_h *tui = (struct _tui_h *) pTui;
    if (!tui) { return (0); }

    /* run 'write' */
    return (tui->api.write(pTui, pDat, size));
}

# endif /* _tui_impl_h_ */
#endif /* TUI_IMPLEMENTATION */
