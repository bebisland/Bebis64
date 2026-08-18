#include "result.h"
#include <stddef.h>

Result result_ok(void)
{
	Result r;
	r.code = RESULT_OK;
	r.message = NULL;
	return r;
}

Result result_err(ResultCode code, const char *message)
{
	Result r;
	r.code = code;
	r.message = message;
	return r;
}
