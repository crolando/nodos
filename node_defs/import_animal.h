#include <node.h>
#ifndef IMPORT_ANIMIAL_H
#define IMPORT_ANIMIAL_H

namespace node_defs
{
namespace import_animal
{
using namespace nodos;

void Initialize(attr_table&)
{

}

void DrawAndEdit(attr_table&)
{

}

void Execute(attr_table&, const std::vector<Link>& Inputs, const std::vector<Link>& Outputs)
{

}

NodeDescription ConstructDefinition(){
    NodeDescription node;
    node.Type = "Import Animal";

    PinDescription out1;
    out1.DataType = "Animal_DataType";
    out1.Label = "Animal_Label";
    node.Outputs.push_back(out1);

    node.InitializeDefaultProperties = Initialize;
    node.DrawAndEditProperties = DrawAndEdit;
    node.Execute = Execute;

    return node;
}


} // end namespace import_animal
} // end namespace node_defs
#endif //IMPORT_ANIMIAL_H
