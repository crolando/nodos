#ifndef NODOS_SESSION_DATA_H
#define NODOS_SESSION_DATA_H
#include <nodos.h>
#include <node.h>

struct nodos_session_data {
    std::map<std::string, nodos::NodeDescription> NodeRegistry;
    void RegisterNewNode(nodos::NodeDescription NewDescription) {
        NodeRegistry[NewDescription.Type] = NewDescription;
    }
};

#endif // NODOS_SESSION_DATA_H
