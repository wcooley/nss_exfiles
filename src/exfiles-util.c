#include <errno.h>
#include <fcntl.h>
#include <nss.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "exfiles-util.h"
#include "nss_exfiles.h"
#include "config.h"

/*
 * Open or rewind a file, checking for errors, setting close-on-exec, etc.
 * This is intended to be used in the setXXent functions and handles almost
 * all error handling for them.
 */
int
exfiles_open_file(char *fname, FILE **ex_file_ptr) {

    enum nss_status status  = NSS_STATUS_SUCCESS;
    char err_msg[128]       = "exfiles_open_file: Failed to open file '%s'";
    FILE *ex_file          = *ex_file_ptr;

    exfiles_trace_msg("Entering exfiles_open_file");

    /* File isn't already open */
    if (NULL == ex_file) {
        ex_file = fopen(fname, "r");

        *ex_file_ptr = ex_file;

        /* Error opening file */
        if (NULL == ex_file) {
            if (EAGAIN == errno) {
                status = NSS_STATUS_TRYAGAIN;
            }
            else {
                sprintf(err_msg, fname);
                perror(err_msg);
                status = NSS_STATUS_UNAVAIL;
            }
        }
        /* Success opening file */
        else {
            /* Ensure the file has "close on exec" */
            int result;
            result = exfiles_set_close_on_exec(ex_file);

            if (0 != result) {
                ex_file = NULL;
                status = NSS_STATUS_UNAVAIL;
            }
        }
    }
    else {
        rewind(ex_file);
    }

    return status;

}

/*
 * Sets the close-on-exec flag on the file handle
 */
int
exfiles_set_close_on_exec(FILE *stream)
{
    int result, flags, status;

    result = flags = fcntl(fileno(stream), F_GETFD, 0);
    if (0 <= result) {
        flags |= FD_CLOEXEC;
        result = fcntl(fileno(stream), F_SETFD, flags);
        status = 0;
    }
    else {
        /* error with fcntl */
        fclose(stream);
        stream = NULL;
        status = -1;
    }

    return status;

}

char *
qualify_file_path(char *inpath, char **outpath)
{
    int len = 0;

    /* Starts with slash, so must be already qualified */
    if (inpath[0] == '/')
        len = strlen(inpath) + 1;
    else
        len = strlen(inpath) + strlen(EXFILES_BASE) + 2;
                                                /* +1 for "/", +1 for '\0' */

    (*outpath) = calloc(1, len);
    if (NULL == *outpath) return NULL;

    if (inpath[0] == '/') {
        strncpy(*outpath, &inpath[0], strlen(inpath)+1);
    }
    else {
        strncpy(*outpath, EXFILES_BASE, strlen(EXFILES_BASE+1));
        strncat(*outpath, "/", 1);
        strncat(*outpath, &inpath[0], strlen(inpath)+1);
    }

    return *outpath;
}

/*
 * Compile-time tracing messages
 * FIXME Take varargs for full power
 */

#ifdef ENABLE_TRACE
void exfiles_trace_msg(char *msg) {
    if (getenv("NSS_EXFILES_TRACE"))
        fprintf(stderr, "TRACE: %s\n", msg);
}
#else
void exfiles_trace_msg(char *msg) {}
#endif /* TRACE */
