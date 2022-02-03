#ifndef NODE_UTILS_H
#define NODE_UTILS_H

#include <nodos.h>

int GetNextId();
// Seralization can secretly consume IDs, so we need a way to set it.
void SetNextId(int);
void BuildNode(Node* node);
void BuildNodes();

#endif // NODE_UTILS_H
