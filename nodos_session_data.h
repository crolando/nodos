#ifndef NODOS_SESSION_DATA_H
#define NODOS_SESSION_DATA_H
#include <nodos.h>


class node_attribute_value {
    public:
    enum{STRING,INT,DOUBLE} type;

    private:
    std::string s;
    int i;
    double d;

};

struct node_data {
  std::string name = "";
  std::string type = "";
  std::string node_editor_data = "";
  std::map<std::string, node_attribute_value> properties;
};

struct nodos_session_data {
    // Serialization buffer for view position, etc to be consumed by the node editor using load/save callbacks.
    std::string node_editor_blueprint_data;
    // Node serialization buffer
    std::map<int,node_data>   nodes;
};

#endif // NODOS_SESSION_DATA_H
