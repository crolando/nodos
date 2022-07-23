#ifndef IMPORT_ANIMIAL_H
#define IMPORT_ANIMIAL_H

#include <plano_api.h>
#include <internal/imgui_stdlib.h> // For 3-arg text box

namespace node_defs
{
namespace import_animal
{
void Initialize(Properties& Properties)
{
    Properties.set_attr("input","enter text here");
}

void DrawAndEdit(Properties& Properties)
{
    ax::NodeEditor::EnableShortcuts(ImGui::GetIO().WantTextInput);
    auto input = Properties.get_attr("input").get_string();
    // The input widgets require some guidance on their widths, or else they're very large. (note matching pop at the end).
    ImGui::PushItemWidth(200);
    ImGui::InputTextWithHint("File Address", "enter text here", &input);
    Properties.set_attr("input",input);
    ImGui::PopItemWidth();
}


turnkey::api::NodeDescription ConstructDefinition(void)
{
    turnkey::api::NodeDescription node;
    node.Type = "Import Animal";

    turnkey::api::PinDescription out1;
    out1.DataType = "Animal_DataType";
    out1.Label = "Animal";
    node.Outputs.push_back(out1);

    node.InitializeDefaultProperties = Initialize;
    node.DrawAndEditProperties = DrawAndEdit;
    return node;
}


} // end namespace import_animal
} // end namespace node_defs
#endif //IMPORT_ANIMIAL_H
