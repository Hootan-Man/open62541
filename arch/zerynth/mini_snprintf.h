#ifndef __MINI_PRINTF_H__
#define __MINI_PRINTF_H__

#include <stddef.h>

int mini_snprintf(char* buf, size_t size, const char* fmt, ...);

#endif


// this is the link to the repository that I used to have a minimal snprintf() 
// https://github.com/tatetian/mini-snprintf
// thanks tatetian