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

/* tui.h */

/* {{{ */

typedef void *tui_t;

int tui_init(tui_t *);

int tui_free(tui_t);

int tui_read(tui_t, void *);

int tui_write(tui_t, const void *, const size_t);

int tui_write_cstr(tui_t, const char *);

/* }}} */

/* tui.h: ANSI escape sequences 
 *
 * SOURCES:
 * - https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797
 *
 * XTerm escape sequence specification:
 * - https://invisible-island.net/xterm/ctlseqs/ctlseqs-contents.html
 *
 * XTerm Control Sequence Introducer specification:
 * - https://invisible-island.net/xterm/ctlseqs/ctlseqs.html#h3-Functions-using-CSI-_-ordered-by-the-final-character_s_
 * - https://invisible-island.net/xterm/ctlseqs/ctlseqs.html#h4-Functions-using-CSI-_-ordered-by-the-final-character-lparen-s-rparen:CSI-Pm-m.1CA7
 * - https://invisible-island.net/xterm/ctlseqs/ctlseqs.html#h4-Functions-using-CSI-_-ordered-by-the-final-character-lparen-s-rparen:CSI-?-Pm-h.1D0E
 * - https://invisible-island.net/xterm/ctlseqs/ctlseqs.html#h4-Functions-using-CSI-_-ordered-by-the-final-character-lparen-s-rparen:CSI-?-Pm-l.1D12
 * */

/* {{{ */

/* 'reset' : "\x1b[0m" */
static const char *ANSI_esc_reset = "\x1b[0m";


/* 'arrow_up' : "\x1b[A" */
static const char *ANSI_esc_arror_up = "\x1b[A";


/* 'arrow_down' : "\x1b[B" */
static const char *ANSI_esc_arror_down = "\x1b[B";


/* 'arrow_right' : "\x1b[C" */
static const char *ANSI_esc_arror_right = "\x1b[C";


/* 'arrow_left' : "\x1b[D" */
static const char *ANSI_esc_arror_left = "\x1b[D";


/* 'home' : "\x1b[1~" */
static const char *ANSI_esc_home = "\x1b[1~";


/* 'insert' : "\x1b[2~" */
static const char *ANSI_esc_insert = "\x1b[2~";


/* 'delete' : "\x1b[3~" */
static const char *ANSI_esc_delete = "\x1b[3~";


/* 'end' : "\x1b[4~" */
static const char *ANSI_esc_end = "\x1b[4~";


/* 'page_up' : "\x1b[5~" */
static const char *ANSI_esc_page_up = "\x1b[5~";


/* 'page_down' : "\x1b[6~" */
static const char *ANSI_esc_page_down = "\x1b[6~";


/* 'F1' : "\x1bOP" */
static const char *ANSI_esc_F1 = "\x1bOP";


/* 'F2' : "\x1bOQ" */
static const char *ANSI_esc_F2 = "\x1bOQ";


/* 'F3' : "\x1bOR" */
static const char *ANSI_esc_F3 = "\x1bOR";


/* 'F4' : "\x1bOS" */
static const char *ANSI_esc_F4 = "\x1bOS";


/* 'F5' : "\x1b[15~" */
static const char *ANSI_esc_F5 = "\x1b[15~";


/* 'F6' : "\x1b[16~" */
static const char *ANSI_esc_F6 = "\x1b[16~";


/* 'F7' : "\x1b[17~" */
static const char *ANSI_esc_F7 = "\x1b[17~";


/* 'F8' : "\x1b[18~" */
static const char *ANSI_esc_F8 = "\x1b[18~";


/* 'F9' : "\x1b[19~" */
static const char *ANSI_esc_F9 = "\x1b[19~";


/* 'F10' : "\x1b[20~" */
static const char *ANSI_esc_F10 = "\x1b[20~";


/* 'F11' : "\x1b[21~" */
static const char *ANSI_esc_F11 = "\x1b[21~";


/* 'F12' : "\x1b[22~" */
static const char *ANSI_esc_F12 = "\x1b[22~";


/* 'bold' : 
 * - set     : "\x1b[1m"
 * - resture : "\x1b[21m"
 * */
static const char *ANSI_esc_bold[2] = { "\x1b[1m", "\x1b[22m" };


/* 'faint' :
 * - set     : "\x1b[2m"
 * - resture : "\x1b[22m"
 * */
static const char *ANSI_esc_faint[2] = { "\x1b[2m", "\x1b[22m" };


/* 'italic' :
 * - set     : "\x1b[3m"
 * - resture : "\x1b[23m"
 * */
static const char *ANSI_esc_italic[2] = { "\x1b[3m", "\x1b[23m" };


/* 'underline' :
 * - set     : "\x1b[4m"
 * - resture : "\x1b[24m"
 * */
static const char *ANSI_esc_underline[2] = { "\x1b[4m", "\x1b[24m" };


/* 'blink' :
 * - set     : "\x1b[5m"
 * - resture : "\x1b[25m"
 * */
static const char *ANSI_esc_blink[2] = { "\x1b[5m", "\x1b[25m" };


/* 'inverse' :
 * - set     : "\x1b[7m"
 * - resture : "\x1b[27m"
 * */
static const char *ANSI_esc_inverse[2] = { "\x1b[7m", "\x1b[27m" };


/* 'hidden' :
 * - set     : "\x1b[8m"
 * - resture : "\x1b[28m"
 * */
static const char *ANSI_esc_hidden[2] = { "\x1b[8m", "\x1b[28m" };


/* 'strikethrough' :
 * - set     : "\x1b[9m"
 * - resture : "\x1b[29m"
 * */
static const char *ANSI_esc_strikethrough[2] = { "\x1b[9m", "\x1b[29m" };


/* 'cursor' : 
 * - visible : "\x1b[?25l"
 * - hidden  : "\x1b[?25h"
 * */
static const char *ANSI_esc_cursor[2] = { "\x1b[?25l", "\x1b[?25h" };


/* 'screen' : 
 * - restore : "\x1b[?47l"
 * - save    : "\x1b[?47h"
 * */
static const char *ANSI_esc_screen[2] = { "\x1b[?47l", "\x1b[?57h" };


/* 'alt-buffer' : 
 * - leave : "\x1b[?1049l"
 * - enter : "\x1b[?1049h"
 * */
static const char *ANSI_esc_alt_buffer[2] = { "\x1b[?1049l", "\x1b[?1049h" };


/* 'black' :
 * - foreground : "\x1b[30m"
 * - background : "\x1b[40m"
 * */
static const char *ANSI_esc_black[2] = { "\x1b[30m", "\x1b[40m" };


/* 'red' :
 * - foreground : "\x1b[31m"
 * - background : "\x1b[41m"
 * */
static const char *ANSI_esc_red[2] = { "\x1b[31m", "\x1b[41m" };


/* 'green' :
 * - foreground : "\x1b[32m"
 * - background : "\x1b[42m"
 * */
static const char *ANSI_esc_green[2] = { "\x1b[32m", "\x1b[42m" };


/* 'yellow' :
 * - foreground : "\x1b[33m"
 * - background : "\x1b[43m"
 * */
static const char *ANSI_esc_yellow[2] = { "\x1b[33m", "\x1b[43m" };


/* 'blue' :
 * - foreground : "\x1b[34m"
 * - background : "\x1b[44m"
 * */
static const char *ANSI_esc_blue[2] = { "\x1b[34m", "\x1b[44m" };


/* 'magenta' :
 * - foreground : "\x1b[35m"
 * - background : "\x1b[45m"
 * */
static const char *ANSI_esc_magenta[2] = { "\x1b[35m", "\x1b[45m" };


/* 'cyan' :
 * - foreground : "\x1b[36m"
 * - background : "\x1b[46m"
 * */
static const char *ANSI_esc_cyan[2] = { "\x1b[36m", "\x1b[46m" };


/* 'white' :
 * - foreground : "\x1b[37m"
 * - background : "\x1b[47m"
 * */
static const char *ANSI_esc_white[2] = { "\x1b[37m", "\x1b[47m" };


/* 'default' :
 * - foreground : "\x1b[39m"
 * - background : "\x1b[49m"
 * */
static const char *ANSI_esc_default[2] = { "\x1b[39m", "\x1b[49m" };


/* define custom colors 
 *
 * TODO:
 * Consider redesigning these compile-time functions to run-time functions?
 * */

# if !defined ANSI_esc_color_fg_rgb
#  /* 'Foreground' (RGB) : "\x1b[38:2:(Red):(Green):(Blue)m" */
#  define ANSI_esc_color_fg_rgb(r, g, b) ( "\x1b[38:2:" #r ":" #g ":" #b "m" )
# endif
#
# if !defined ANSI_esc_color_bg_rgb
#  /* 'Background' (RGB) : "\x1b[48:2:(Red):(Green):(Blue)m" */
#  define ANSI_esc_color_bg_rgb(r, g, b) ( "\x1b[48:2:" #r ":" #g ":" #b "m" )
# endif
#
# if !defined ANSI_esc_color_fg_idx
#  /* 'Foreground' (Index) : "\x1b[48:5:(Index)m" */
#  define ANSI_esc_color_fg_idx(idx) ( "\x1b[38:5:" #idx "m" )
# endif
#
# if !defined ANSI_esc_color_bg_idx
#  /* 'Background' (Index) : "\x1b[48:5:(Index)m" */
#  define ANSI_esc_color_bg_idx(idx) ( "\x1b[48:5:" #idx "m" )
# endif

/* }}} */

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
        int (*write_cstr) (struct _tui_h *, const char *);
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

static int __tui_unix_write_cstr(struct _tui_h *, const char *);


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


static int __tui_unix_write_cstr(struct _tui_h *pTui, const char *pStr) {
    /* null-check */
    if (!pTui) { return (-1); }
    if (!pStr) { return (-1); }
    
    /* references */
    struct
    _tui_h_unix *unix = pTui->unix;
    if (!unix) { return (-1); }

    /* get the 'size' of 'pDat' */
    ssize_t size = 0;
    for ( ; pStr[size]; size++);

    /* 'write' 'pStr' to 'fd_stdout' */
    ssize_t nwrite = write(unix->fd_stdout, pStr, size);

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
    tui->api.write_cstr = __tui_unix_write_cstr;

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


int tui_write_cstr(tui_t pTui, const char *pStr) {
    /* references */
    struct
    _tui_h *tui = (struct _tui_h *) pTui;
    if (!tui) { return (0); }

    /* run 'write' */
    return (tui->api.write_cstr(pTui, pStr));
}

# endif /* _tui_impl_h_ */
#endif /* TUI_IMPLEMENTATION */
