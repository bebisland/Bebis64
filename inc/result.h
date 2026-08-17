#ifndef BEBIS64_RESULT_H
#define BEBIS64_RESULT_H

typedef enum {
  RESULT_OK = 0,
  RESULT_ERR_INIT,
  RESULT_ERR_ALLOC,
  RESULT_ERR_FILE,
  RESULT_ERR_NULL
} ResultCode;

typedef struct {
  ResultCode code;
  const char *message;
} Result;

Result result_ok(void);
Result result_err(ResultCode code, const char *message);

#define RESULT_IS_OK(r) ((r).code == RESULT_OK)

#endif // BEBIS64_RESULT_H
