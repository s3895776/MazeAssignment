#ifndef ENVIRONMENT
#define ENVIRONMENT

typedef char** Env;
Env make_env(const int rows, const int cols);
void delete_env(Env env, int rows, int cols);

#endif //ENVIRONMENT
