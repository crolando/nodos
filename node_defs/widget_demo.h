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
} // basic widgets
namespace TreeDemo {
void Initialize(Properties& p)
{
    return;
}

void DrawAndEdit(Properties& p)
{
    // Tree widgets "stretch to fill whatever space is available" in their parent.
    // There is a shortcoming with the node: they cannot
    // tell their children how big they are.  So, Tree widgets are not drawn correctly when placed inside nodes.
    // However, there is a hack that works around this.  We can manually instantiate a column of a fixed width in the node,
    // and this provides the information trees need to dispaly correctly.
    int width = 135;
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 0.0f));
    ImGui::Dummy(ImVec2(width, 0));
    ImGui::PopStyleVar();
    
    // Start columns, but use only first one.
    ImGui::BeginColumns("##TreeColumns", 2,
        ImGuiOldColumnFlags_NoBorder |
        ImGuiOldColumnFlags_NoResize |
        ImGuiOldColumnFlags_NoPreserveWidths |
        ImGuiOldColumnFlags_NoForceWithinWindow);

    // Adjust column width to match requested one.
    ImGui::SetColumnWidth(0, width
        + ImGui::GetStyle().WindowPadding.x
        + ImGui::GetStyle().ItemSpacing.x);
    
    // Back to normal ImGui drawing, in our column.
    if (ImGui::CollapsingHeader("Open Header"))
    {
        ImGui::Text("Hello There");
        if (ImGui::TreeNode("Open Tree")) {
            ImGui::Text("Checked: %s", p.pbool["check"] ? "true" : "false");
            ImGui::Checkbox("Option 1", &p.pbool["check"]);
            ImGui::TreePop();
        }
    }
    
    // Tree Column Shutdown
    ImGui::EndColumns();
    
    
    
    return;
} // draw and edit

plano::api::NodeDescription ConstructDefinition(void)
{
    plano::api::NodeDescription node;
    node.Type = "TreeDemo";
    node.Inputs.push_back(plano::api::PinDescription("Enter",PinType::Flow));
    node.Outputs.push_back(plano::api::PinDescription("Exit",PinType::Flow));
    node.InitializeDefaultProperties = Initialize;
    node.DrawAndEditProperties = DrawAndEdit;
    return node;
} // construct defintion

} // tree demo

namespace PlotDemo {

void Initialize(Properties& p)
{
    return;
}

void DrawAndEdit(Properties& p)
{
    // Animate some runtime data
    static float progress = 0.0f, progress_dir = 1.0f;
    progress += progress_dir * 0.4f * ImGui::GetIO().DeltaTime;
    if (progress >= +1.1f) { progress = +1.1f; progress_dir *= -1.0f; }
    if (progress <= -0.1f) { progress = -0.1f; progress_dir *= -1.0f; }

    // We must specify the ProgressBar's width.
    static ImVec2 bar_size = ImVec2(200.0f, 0.0f);
    
    // Progress bar with percent text
    ImGui::ProgressBar(progress, bar_size);
    ImGui::SameLine();
    ImGui::Text("Progress Bar");
    
    // Progress bar with custom text
    float progress_saturated = (progress < 0.0f) ? 0.0f : (progress > 1.0f) ? 1.0f : progress;
    char buf[32];
    snprintf(buf, 32 ,"%d/%d", (int)(progress_saturated * 1753), 1753);
    ImGui::ProgressBar(progress, bar_size, buf);
    
}

plano::api::NodeDescription ConstructDefinition(void)
{
    plano::api::NodeDescription node;
    node.Type = "PlotDemo";
    node.Inputs.push_back(plano::api::PinDescription("Enter",PinType::Flow));
    node.Outputs.push_back(plano::api::PinDescription("Exit",PinType::Flow));
    node.InitializeDefaultProperties = Initialize;
    node.DrawAndEditProperties = DrawAndEdit;
    return node;
} // construct defintion
} // plot demo
} // widget demo
} // node defs
#endif
