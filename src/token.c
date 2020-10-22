#include "token.h"
#include "memory.h"

const char *token_name(TOKEN_TYPE type) {
  return token_names[type];
}

void token_free(Token *token) {
  uai_free(token->literal);
  uai_free(token);
}
