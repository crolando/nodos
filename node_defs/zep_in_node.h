#pragma once
#ifndef ZEP_IN_NODE_H
#define ZEP_IN_NODE_H

#include <node_turnkey_api.h>
#include <imgui_stdlib.h> // For 3-arg text box

namespace node_defs
{
    namespace zep_in_node
    {
        static bool zep_started = false; // zep_init cannot be called before the first frame.
        static Zep::NVec2i zep_size = Zep::NVec2i(640, 480);

        void Initialize(Properties& Properties)
        {
            Properties.set_attr("input", "enter text here");
            
        }

        void DrawAndEdit(Properties& Properties)
        {
            // 4. Zep window.
            if (!zep_started) {
                zep_init(Zep::NVec2f(1.0f, 1.0f));
                zep_load(Zep::ZepPath(APP_ROOT) / "main.cpp");
                // Set editing mode to "Not VIM"
                zep_get_editor().SetGlobalMode(Zep::ZepMode_Standard::StaticName());
                zep_started = true;
            }

            ImGui::PushItemWidth(640);

            // Required for CTRL+P and flashing cursor.
            zep_update();
            zep_show(zep_size);

            //ax::NodeEditor::EnableShortcuts(ImGui::GetIO().WantTextInput);
            //auto input = Properties.get_attr("input").get_string();
            //// The input widgets require some guidance on their widths, or else they're very large. (note matching pop at the end).
            
            //ImGui::InputTextWithHint("File Address", "enter text here", &input);
            //Properties.set_attr("input", input);
            //ImGui::PopItemWidth();
        }


        turnkey::api::NodeDescription ConstructDefinition(void)
        {
            turnkey::api::NodeDescription node;
            node.Type = "Zep in Node";

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
