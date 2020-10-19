#include "token.h"
#include "memory.h"

const char *token_name(token_type type) {
  return token_names[type];
}

void token_free(token_t *token) {
  uai_free(token->literal);
  uai_free(token);
}
