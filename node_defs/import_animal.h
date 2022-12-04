#ifndef IMPORT_ANIMIAL_H
#define IMPORT_ANIMIAL_H

#include <plano_api.h>
#include <internal/imgui_stdlib.h> // For 3-arg text box

namespace node_defs
{
namespace import_animal
{
void Initialize(Properties& p)
{
    p.pstring["input"] = "enter text here";
}

void DrawAndEdit(Properties& p)
{
    ax::NodeEditor::EnableShortcuts(ImGui::GetIO().WantTextInput);
    
    // The input widgets require some guidance on their widths, or else they're very large. (note matching pop at the end).
    ImGui::PushItemWidth(200);
    ImGui::InputTextWithHint("File Address", "enter text here", &p.pstring["input"]);
    ImGui::PopItemWidth();
}


plano::api::NodeDescription ConstructDefinition(void)
{
    plano::api::NodeDescription node;
    node.Type = "Import Animal";

    plano::api::PinDescription out1("Animal", plano::types::PinType::String);    
    node.Outputs.push_back(out1);

    node.InitializeDefaultProperties = Initialize;
    node.DrawAndEditProperties = DrawAndEdit;
    return node;
}


} // end namespace import_animal
} // end namespace node_defs
#endif //IMPORT_ANIMIAL_H
