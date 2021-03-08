#ifndef EXAMPLE_NODE_SPAWNER_H
#define EXAMPLE_NODE_SPAWNER_H

#include <nodos.h>

Node* SpawnInputActionNode(std::vector<Node> &s_Nodes);
Node* SpawnBranchNode(std::vector<Node> &s_Nodes);
Node* SpawnDoNNode(std::vector<Node> &s_Nodes);
Node* SpawnOutputActionNode(std::vector<Node> &s_Nodes);
Node* SpawnPrintStringNode(std::vector<Node> &s_Nodes);
Node* SpawnMessageNode(std::vector<Node> &s_Nodes);
Node* SpawnSetTimerNode(std::vector<Node> &s_Nodes);
Node* SpawnLessNode(std::vector<Node> &s_Nodes);
Node* SpawnWeirdNode(std::vector<Node> &s_Nodes);
Node* SpawnTraceByChannelNode(std::vector<Node> &s_Nodes);
Node* SpawnTreeSequenceNode(std::vector<Node> &s_Nodes);
Node* SpawnTreeTaskNode(std::vector<Node> &s_Nodes);
Node* SpawnTreeTask2Node(std::vector<Node> &s_Nodes);
Node* SpawnComment(std::vector<Node> &s_Nodes);
Node* SpawnHoudiniTransformNode(std::vector<Node> &s_Nodes);
Node* SpawnHoudiniGroupNode(std::vector<Node> &s_Nodes);

#endif // EXAMPLE_NODE_SPAWNER_H
