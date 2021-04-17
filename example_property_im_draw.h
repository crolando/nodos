#ifndef EXAMPLE_PROPERTY_IM_DRAW_H
#define EXAMPLE_PROPERTY_IM_DRAW_H

#include <nodos.h>
#include <imgui.h>


void im_draw_basic_widgets (attr_table& Properties) {

    // Basic Widgets Demo  ==============================================================================================
    ImGui::Text("Basic Widget Demo");

    // This is a crutch for now to get the default properties in the node because we don't have property serialization.
    // This should be avaialbe outside this function because node instantiation would populate the default attributes.
    if (! Properties.has_attr("button")) {
        Properties.set_attr("button",0L);
    }

    // Widget Demo from imgui_demo.cpp...
    // Normal Button
    auto button = Properties.get_attr("button").get_integer();
    if (ImGui::Button("Button")) {
        button++;
        Properties.set_attr("button",button);
    }
    ImGui::SameLine();
    ImGui::Text("Times Clicked: %u", button);

    // Checkbox
    static bool check = true;
    ImGui::Checkbox("checkbox", &check);

    // Radio buttons
    static int e = 0;
    ImGui::RadioButton("radio a", &e, 0); ImGui::SameLine();
    ImGui::RadioButton("radio b", &e, 1); ImGui::SameLine();
    ImGui::RadioButton("radio c", &e, 2);

    // Color buttons, demonstrate using PushID() to add unique identifier in the ID stack, and changing style.
    for (int i = 0; i < 7; i++)
    {
        if (i > 0)
            ImGui::SameLine();
        ImGui::PushID(i);
        ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(i / 7.0f, 0.6f, 0.6f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(i / 7.0f, 0.7f, 0.7f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(i / 7.0f, 0.8f, 0.8f));
        ImGui::Button("Click");
        ImGui::PopStyleColor(3);
        ImGui::PopID();
    }

    // Use AlignTextToFramePadding() to align text baseline to the baseline of framed elements (otherwise a Text+SameLine+Button sequence will have the text a little too high by default)
    ImGui::AlignTextToFramePadding();
    ImGui::Text("Hold to repeat:");
    ImGui::SameLine();

    // Arrow buttons with Repeater
    static int counter = 0;
    float spacing = ImGui::GetStyle().ItemInnerSpacing.x;
    ImGui::PushButtonRepeat(true);
    if (ImGui::ArrowButton("##left", ImGuiDir_Left)) { counter--; }
    ImGui::SameLine(0.0f, spacing);
    if (ImGui::ArrowButton("##right", ImGuiDir_Right)) { counter++; }
    ImGui::PopButtonRepeat();
    ImGui::SameLine();
    ImGui::Text("%d", counter);

    // The input widgets also require you to manually disable the editor shortcuts so the view doesn't fly around.
    // (note that this is a per-frame setting, so it disables it for all text boxes.  I left it here so you could find it!)
    ed::EnableShortcuts(ImGui::GetIO().WantTextInput);
    // The input widgets require some guidance on their widths, or else they're very large. (note matching pop at the end).
    ImGui::PushItemWidth(200);
    static char str1[128] = "";
    ImGui::InputTextWithHint("input text (w/ hint)", "enter text here", str1, IM_ARRAYSIZE(str1));

    static float f0 = 0.001f;
    ImGui::InputFloat("input float", &f0, 0.01f, 1.0f, "%.3f");

    static float f1 = 1.00f, f2 = 0.0067f;
    ImGui::DragFloat("drag float", &f1, 0.005f);
    ImGui::DragFloat("drag small float", &f2, 0.0001f, 0.0f, 0.0f, "%.06f ns");
    ImGui::PopItemWidth();
}

#endif // EXAMPLE_PROPERTY_IM_DRAW_H
