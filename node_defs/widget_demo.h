#ifndef WIDGET_DEMO_H
#define WIDGET_DEMO_H

#include <plano_api.h>
#include <internal/imgui_stdlib.h> // For 3-arg text box

#include "imgui_internal.h" // needed for columns hack for tree widget...
using plano::types::PinType;
namespace node_defs
{
namespace widget_demo
{
namespace BasicWidgets
{

void Initialize(Properties& p)
{
    return;
}

void DrawAndEdit(Properties& p)
{
    // Button toggles label
    if (ImGui::Button("Push Me"))
        p.pint["Button"]++;
    ImGui::SameLine();
    if (p.pint["Button"] & 1)
    {
        ImGui::Text("Thanks for clicking me!");
    } else {
        ImGui::Text("You are a great person!");
    }
    
    // Checkbox
    ImGui::Checkbox("Checkbox", &p.pbool["Check"]);
    
    // Radio buttons
    ImGui::RadioButton("radio a", &p.pint["Radio"], 0); ImGui::SameLine();
    ImGui::RadioButton("radio b", &p.pint["Radio"], 1); ImGui::SameLine();
    ImGui::RadioButton("radio c", &p.pint["Radio"], 2);
    
    // Color buttons, demonstrate using PushID() to add unique identifier in the ID stack, and changing style.
    for (int i = 0; i < 3; i++)
    {
        
        ImGui::PushID(i);
        ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(i / 7.0f, 0.6f, 0.6f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(i / 7.0f, 0.7f, 0.7f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(i / 7.0f, 0.8f, 0.8f));
        bool& c = p.pbool["button-" + std::to_string(i)];
        if(ImGui::Button("Click"))
            c =! c;
        ImGui::SameLine();
        ImGui::Text( c ? "Yes" : "No" );
        ImGui::PopStyleColor(3);
        ImGui::PopID();
    }
    
    // Use AlignTextToFramePadding() to align text baseline to the baseline of framed elements (otherwise a Text+SameLine+Button sequence will have the text a little too high by default)
    ImGui::AlignTextToFramePadding();
    ImGui::Text("Hold to repeat:");
    ImGui::SameLine();
    
    // Arrow buttons with Repeater
    float spacing = ImGui::GetStyle().ItemInnerSpacing.x;
    ImGui::PushButtonRepeat(true);
    if (ImGui::ArrowButton("##left", ImGuiDir_Left)) { p.pint["spinner"]--; }
    ImGui::SameLine(0.0f, spacing);
    if (ImGui::ArrowButton("##right", ImGuiDir_Right)) { p.pint["spinner"]++; }
    ImGui::PopButtonRepeat();
    ImGui::SameLine();
    ImGui::Text("%d", p.pint["spinner"]);
    
    // The input widgets also require you to manually disable the editor shortcuts so the view doesn't fly around.
    // (note that this is a per-frame setting, so it disables it for all text boxes.  I left it here so you could find it!)
    ax::NodeEditor::EnableShortcuts(!ImGui::GetIO().WantTextInput);
    // The input widgets require some guidance on their widths, or else they're very large. (note matching pop at the end).
    ImGui::PushItemWidth(200);
    
    //ImGui::InputTextWithHint("input text (w/ hint)", "enter text here", &p.pstring["input"], p.pstring["input"].capacity()+1);
    
    ImGui::InputFloat("input float", &p.pfloat["infloat"], 0.01f, 1.0f, "%.3f");
    
    ImGui::DragFloat("drag float", &p.pfloat["infloat2"], 0.005f);
    ImGui::DragFloat("drag small float", &p.pfloat["infloat3"], 0.0001f, 0.0f, 0.0f, "%.06f ns");
    ImGui::PopItemWidth();
    
    
}
plano::api::NodeDescription ConstructDefinition(void)
{
    plano::api::NodeDescription node;
    node.Type = "BasicWidgets";
    node.Inputs.push_back(plano::api::PinDescription("Enter",PinType::Flow));
    node.Outputs.push_back(plano::api::PinDescription("Exit",PinType::Flow));
    node.InitializeDefaultProperties = Initialize;
    node.DrawAndEditProperties = DrawAndEdit;
    return node;
}
}
}
}
#endif
