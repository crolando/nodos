#include <node_utils.h>
#include <imgui.h> // for ImColor()
#include "utilities/builders.h"
#include <nodos_session_data.h>


Node* SpawnInputActionNode(std::vector<Node> &s_Nodes)
{
    s_Nodes.emplace_back(GetNextId(), "InputAction Fire", ImColor(255, 128, 128));
    s_Nodes.back().Outputs.emplace_back(GetNextId(), "", PinType::Delegate);
    s_Nodes.back().Outputs.emplace_back(GetNextId(), "Pressed", PinType::Flow);
    s_Nodes.back().Outputs.emplace_back(GetNextId(), "Released", PinType::Flow);

    BuildNode(&s_Nodes.back());

    return &s_Nodes.back();
}

Node* SpawnBranchNode(std::vector<Node> &s_Nodes)
{
    s_Nodes.emplace_back(GetNextId(), "Branch");
    s_Nodes.back().Inputs.emplace_back(GetNextId(), "", PinType::Flow);
    s_Nodes.back().Inputs.emplace_back(GetNextId(), "Condition", PinType::Bool);
    s_Nodes.back().Outputs.emplace_back(GetNextId(), "True", PinType::Flow);
    s_Nodes.back().Outputs.emplace_back(GetNextId(), "False", PinType::Flow);

    BuildNode(&s_Nodes.back());

    return &s_Nodes.back();
}

Node* SpawnDoNNode(std::vector<Node> &s_Nodes)
{
    s_Nodes.emplace_back(GetNextId(), "Do N");
    s_Nodes.back().Inputs.emplace_back(GetNextId(), "Enter", PinType::Flow);
    s_Nodes.back().Inputs.emplace_back(GetNextId(), "N", PinType::Int);
    s_Nodes.back().Inputs.emplace_back(GetNextId(), "Reset", PinType::Flow);
    s_Nodes.back().Outputs.emplace_back(GetNextId(), "Exit", PinType::Flow);
    s_Nodes.back().Outputs.emplace_back(GetNextId(), "Counter", PinType::Int);

    BuildNode(&s_Nodes.back());

    return &s_Nodes.back();
}

Node* SpawnOutputActionNode(std::vector<Node> &s_Nodes)
{
    s_Nodes.emplace_back(GetNextId(), "OutputAction");
    s_Nodes.back().Inputs.emplace_back(GetNextId(), "Sample", PinType::Float);
    s_Nodes.back().Outputs.emplace_back(GetNextId(), "Condition", PinType::Bool);
    s_Nodes.back().Inputs.emplace_back(GetNextId(), "Event", PinType::Delegate);

    BuildNode(&s_Nodes.back());

    return &s_Nodes.back();
}

Node* SpawnPrintStringNode(std::vector<Node> &s_Nodes)
{
    s_Nodes.emplace_back(GetNextId(), "Print String");
    s_Nodes.back().Inputs.emplace_back(GetNextId(), "", PinType::Flow);
    s_Nodes.back().Inputs.emplace_back(GetNextId(), "In String", PinType::String);
    s_Nodes.back().Outputs.emplace_back(GetNextId(), "", PinType::Flow);

    BuildNode(&s_Nodes.back());

    return &s_Nodes.back();
}

Node* SpawnMessageNode(std::vector<Node> &s_Nodes)
{
    s_Nodes.emplace_back(GetNextId(), "", ImColor(128, 195, 248));
    s_Nodes.back().Type = NodeType::Simple;
    s_Nodes.back().Outputs.emplace_back(GetNextId(), "Message", PinType::String);

    BuildNode(&s_Nodes.back());

    return &s_Nodes.back();
}

Node* SpawnSetTimerNode(std::vector<Node> &s_Nodes)
{
    s_Nodes.emplace_back(GetNextId(), "Set Timer", ImColor(128, 195, 248));
    s_Nodes.back().Inputs.emplace_back(GetNextId(), "", PinType::Flow);
    s_Nodes.back().Inputs.emplace_back(GetNextId(), "Object", PinType::Object);
    s_Nodes.back().Inputs.emplace_back(GetNextId(), "Function Name", PinType::Function);
    s_Nodes.back().Inputs.emplace_back(GetNextId(), "Time", PinType::Float);
    s_Nodes.back().Inputs.emplace_back(GetNextId(), "Looping", PinType::Bool);
    s_Nodes.back().Outputs.emplace_back(GetNextId(), "", PinType::Flow);

    BuildNode(&s_Nodes.back());

    return &s_Nodes.back();
}

Node* SpawnLessNode(std::vector<Node> &s_Nodes)
{
    s_Nodes.emplace_back(GetNextId(), "<", ImColor(128, 195, 248));
    s_Nodes.back().Type = NodeType::Simple;
    s_Nodes.back().Inputs.emplace_back(GetNextId(), "", PinType::Float);
    s_Nodes.back().Inputs.emplace_back(GetNextId(), "", PinType::Float);
    s_Nodes.back().Outputs.emplace_back(GetNextId(), "", PinType::Float);

    BuildNode(&s_Nodes.back());

    return &s_Nodes.back();
}

Node* SpawnWeirdNode(std::vector<Node> &s_Nodes)
{
    s_Nodes.emplace_back(GetNextId(), "o.O", ImColor(128, 195, 248));
    s_Nodes.back().Type = NodeType::Simple;
    s_Nodes.back().Inputs.emplace_back(GetNextId(), "", PinType::Float);
    s_Nodes.back().Outputs.emplace_back(GetNextId(), "", PinType::Float);
    s_Nodes.back().Outputs.emplace_back(GetNextId(), "", PinType::Float);

    BuildNode(&s_Nodes.back());

    return &s_Nodes.back();
}

Node* SpawnTraceByChannelNode(std::vector<Node> &s_Nodes)
{
    s_Nodes.emplace_back(GetNextId(), "Single Line Trace by Channel", ImColor(255, 128, 64));
    s_Nodes.back().Inputs.emplace_back(GetNextId(), "", PinType::Flow);
    s_Nodes.back().Inputs.emplace_back(GetNextId(), "Start", PinType::Flow);
    s_Nodes.back().Inputs.emplace_back(GetNextId(), "End", PinType::Int);
    s_Nodes.back().Inputs.emplace_back(GetNextId(), "Trace Channel", PinType::Float);
    s_Nodes.back().Inputs.emplace_back(GetNextId(), "Trace Complex", PinType::Bool);
    s_Nodes.back().Inputs.emplace_back(GetNextId(), "Actors to Ignore", PinType::Int);
    s_Nodes.back().Inputs.emplace_back(GetNextId(), "Draw Debug Type", PinType::Bool);
    s_Nodes.back().Inputs.emplace_back(GetNextId(), "Ignore Self", PinType::Bool);
    s_Nodes.back().Outputs.emplace_back(GetNextId(), "", PinType::Flow);
    s_Nodes.back().Outputs.emplace_back(GetNextId(), "Out Hit", PinType::Float);
    s_Nodes.back().Outputs.emplace_back(GetNextId(), "Return Value", PinType::Bool);

    BuildNode(&s_Nodes.back());

    return &s_Nodes.back();
}

Node* SpawnTreeSequenceNode(std::vector<Node> &s_Nodes)
{
    s_Nodes.emplace_back(GetNextId(), "Sequence");
    s_Nodes.back().Type = NodeType::Tree;
    s_Nodes.back().Inputs.emplace_back(GetNextId(), "", PinType::Flow);
    s_Nodes.back().Outputs.emplace_back(GetNextId(), "", PinType::Flow);

    BuildNode(&s_Nodes.back());

    return &s_Nodes.back();
}

Node* SpawnTreeTaskNode(std::vector<Node> &s_Nodes)
{
    s_Nodes.emplace_back(GetNextId(), "Move To");
    s_Nodes.back().Type = NodeType::Tree;
    s_Nodes.back().Inputs.emplace_back(GetNextId(), "", PinType::Flow);

    BuildNode(&s_Nodes.back());

    return &s_Nodes.back();
}

Node* SpawnTreeTask2Node(std::vector<Node> &s_Nodes)
{
    s_Nodes.emplace_back(GetNextId(), "Random Wait");
    s_Nodes.back().Type = NodeType::Tree;
    s_Nodes.back().Inputs.emplace_back(GetNextId(), "", PinType::Flow);

    BuildNode(&s_Nodes.back());

    return &s_Nodes.back();
}

Node* SpawnComment(std::vector<Node> &s_Nodes)
{
    s_Nodes.emplace_back(GetNextId(), "Test Comment");
    s_Nodes.back().Type = NodeType::Comment;
    s_Nodes.back().Size = ImVec2(300, 200);

    return &s_Nodes.back();
}

Node* SpawnHoudiniTransformNode(std::vector<Node> &s_Nodes)
{
    s_Nodes.emplace_back(GetNextId(), "Transform");
    s_Nodes.back().Type = NodeType::Houdini;
    s_Nodes.back().Inputs.emplace_back(GetNextId(), "", PinType::Flow);
    s_Nodes.back().Outputs.emplace_back(GetNextId(), "", PinType::Flow);

    BuildNode(&s_Nodes.back());

    return &s_Nodes.back();
}

Node* SpawnHoudiniGroupNode(std::vector<Node> &s_Nodes)
{
    s_Nodes.emplace_back(GetNextId(), "Group");
    s_Nodes.back().Type = NodeType::Houdini;
    s_Nodes.back().Inputs.emplace_back(GetNextId(), "", PinType::Flow);
    s_Nodes.back().Inputs.emplace_back(GetNextId(), "", PinType::Flow);
    s_Nodes.back().Outputs.emplace_back(GetNextId(), "", PinType::Flow);

    BuildNode(&s_Nodes.back());

    return &s_Nodes.back();
}
