#include <stdarg.h>
#include <errno.h>
#include "error_procedure.h"

static char *ename[] = {
    /*   0 */ "", 
    /*   1 */ "EPERM", "ENOENT", "ESRCH", "EINTR", "EIO", "ENXIO", 
    /*   7 */ "E2BIG", "ENOEXEC", "EBADF", "ECHILD", 
    /*  11 */ "EAGAIN/EWOULDBLOCK", "ENOMEM", "EACCES", "EFAULT", 
    /*  15 */ "ENOTBLK", "EBUSY", "EEXIST", "EXDEV", "ENODEV", 
    /*  20 */ "ENOTDIR", "EISDIR", "EINVAL", "ENFILE", "EMFILE", 
    /*  25 */ "ENOTTY", "ETXTBSY", "EFBIG", "ENOSPC", "ESPIPE", 
    /*  30 */ "EROFS", "EMLINK", "EPIPE", "EDOM", "ERANGE", 
    /*  35 */ "EDEADLK/EDEADLOCK", "ENAMETOOLONG", "ENOLCK", "ENOSYS", 
    /*  39 */ "ENOTEMPTY", "ELOOP", "", "ENOMSG", "EIDRM", "ECHRNG", 
    /*  45 */ "EL2NSYNC", "EL3HLT", "EL3RST", "ELNRNG", "EUNATCH", 
    /*  50 */ "ENOCSI", "EL2HLT", "EBADE", "EBADR", "EXFULL", "ENOANO", 
    /*  56 */ "EBADRQC", "EBADSLT", "", "EBFONT", "ENOSTR", "ENODATA", 
    /*  62 */ "ETIME", "ENOSR", "ENONET", "ENOPKG", "EREMOTE", 
    /*  67 */ "ENOLINK", "EADV", "ESRMNT", "ECOMM", "EPROTO", 
    /*  72 */ "EMULTIHOP", "EDOTDOT", "EBADMSG", "EOVERFLOW", 
    /*  76 */ "ENOTUNIQ", "EBADFD", "EREMCHG", "ELIBACC", "ELIBBAD", 
    /*  81 */ "ELIBSCN", "ELIBMAX", "ELIBEXEC", "EILSEQ", "ERESTART", 
    /*  86 */ "ESTRPIPE", "EUSERS", "ENOTSOCK", "EDESTADDRREQ", 
    /*  90 */ "EMSGSIZE", "EPROTOTYPE", "ENOPROTOOPT", 
    /*  93 */ "EPROTONOSUPPORT", "ESOCKTNOSUPPORT", 
    /*  95 */ "EOPNOTSUPP/ENOTSUP", "EPFNOSUPPORT", "EAFNOSUPPORT", 
    /*  98 */ "EADDRINUSE", "EADDRNOTAVAIL", "ENETDOWN", "ENETUNREACH", 
    /* 102 */ "ENETRESET", "ECONNABORTED", "ECONNRESET", "ENOBUFS", 
    /* 106 */ "EISCONN", "ENOTCONN", "ESHUTDOWN", "ETOOMANYREFS", 
    /* 110 */ "ETIMEDOUT", "ECONNREFUSED", "EHOSTDOWN", "EHOSTUNREACH", 
    /* 114 */ "EALREADY", "EINPROGRESS", "ESTALE", "EUCLEAN", 
    /* 118 */ "ENOTNAM", "ENAVAIL", "EISNAM", "EREMOTEIO", "EDQUOT", 
    /* 123 */ "ENOMEDIUM", "EMEDIUMTYPE", "ECANCELED", "ENOKEY", 
    /* 127 */ "EKEYEXPIRED", "EKEYREVOKED", "EKEYREJECTED", 
    /* 130 */ "EOWNERDEAD", "ENOTRECOVERABLE", "ERFKILL", "EHWPOISON"
};

#define MAX_ENAME 133

static void terminateProcess() 
{
	exit(EXIT_FAILURE);
}


static void outputError(bool prtErr, int err, bool flushStdout, 
                const char *msg, va_list ap)
{
#define BUF_SIZE 4096
	char buf[BUF_SIZE], userMsg[BUF_SIZE/4], errText[BUF_SIZE/4];

	vsnprintf(userMsg, BUF_SIZE, msg, ap);

	if(prtErr)
		snprintf(errText, BUF_SIZE, " [%s %s]",
				(err > 0 && err <= MAX_ENAME) ?
				ename[err] : "?UNKNOWN?", strerror(err));
	else
		snprintf(errText, BUF_SIZE, ":");

	snprintf(buf, BUF_SIZE, "ERROR%s %s\n", errText, userMsg);

	if(flushStdout)
		fflush(stdout);			/* flush stdout */
	fputs(buf, stderr);
	fflush(stderr);
}


void cmdLineErr(const char *format, ...) 
{
	va_list argList;

	fflush(stdout);

	fprintf(stderr, "Command-line usage error: ");
	va_start(argList, format);
	vfprintf(stderr, format, argList);
	va_end(argList);

	fflush(stderr);
	exit(EXIT_FAILURE);
}


void usageErr(const char *format, ...)
{
	va_list argList;

	fflush(stdout);

	fprintf(stderr, "Usage: ");
	va_start(argList, format);
	vfprintf(stderr, format, argList);
	va_end(argList);

	fflush(stderr);
	exit(EXIT_FAILURE);
}


void errExit(const char *format, ...) 
{
	va_list argList;

	va_start(argList, format);
	outputError(true, errno, true, format, argList);
	va_end(argList);

	terminateProcess();
}


void fatal(const char *format, ...)
{
	va_list argList;

	va_start(argList, format);
	outputError(false, 0, true, format, argList);
	va_end(argList);

	terminateProcess();
}
