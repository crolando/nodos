#include <node_utils.h>
#include <nodos_session_data.h>

// Some helpers ===================================================================

// These are used for generating the example ID numbers on the fly.
// Should proabably not be used long term.
static int s_NextId = 1;
int GetNextId()
{
    return s_NextId++;
}

void SetNextId(int Id)
{
    s_NextId = Id;
}


// BuildNode exists because during Spawn**Node(), the Pins are not fully
// constructed since the information is reflective.
// The missing information is specifically:
// 1. What node contains me (pin.Node)
// 2. What pin vector contains me (pin.Kind) - this is normally input or output.
void BuildNode(Node* node)
{
    for (auto& input : node->Inputs)
    {
        input.Node = node;
        input.Kind = PinKind::Input;
    }

    for (auto& output : node->Outputs)
    {
        output.Node = node;
        output.Kind = PinKind::Output;
    }
}



