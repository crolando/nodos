#include <nodos.h>
#ifndef NODE_H
#define NODE_H
namespace nodos {

struct PinDescription {
    std::string Label;
    std::string DataType;
};

// Please fill out this form and then register it.
struct NodeDescription {
    std::string Type;
    std::vector<PinDescription> Inputs;
    std::vector<PinDescription> Outputs;

    // In this section we ask you give us function pointers.
    // Please define functions of the type required, then
    // add them to the forms.  These will be called
    // when the graph or user needs your node to do things.

    // Please provide a function of type
    // void function_name(attr_table&);
    // We will call it when a new node is created.
    // In your function, please add default key value pairs
    // into the attribute table.
    void (*InitializeDefaultProperties)(attr_table&);

    // Please provide a function of type
    // void function_name(attr_table&);
    // This is your IMGUI draw callback.  Your job is to read and
    // write properties values using IMGUI widgets.
    void (*DrawAndEditProperties)(attr_table&);

    // (For offline-update pattern) The system would like you to "execute" your node    
    void (*Execute)(attr_table&,const std::vector<Link>& Inputs, const std::vector<Link>& Outputs);

    // (For offline-update pattern) The system wants you to kill the execution of your node.
    void (*KillExecution)(void);
};


}
#endif // NODE_H
