#ifndef _MAKESHIFT_GLERROR_HPP_
#define _MAKESHIFT_GLERROR_HPP_

void _check_gl_error(const char *file, int line);

#define check_gl_error() _check_gl_error(__FILE__,__LINE__)

#endif
