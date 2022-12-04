#ifndef BLUEPRINT_DEMO_H
#define BLUEPRINT_DEMO_H

#include <plano_api.h>
#include <internal/imgui_stdlib.h> // For 3-arg text box
using plano::types::PinType;
namespace node_defs
{
namespace blueprint_demo
{
namespace InputActionFire
{

    void Initialize(Properties& Properties)
    {
        return;
    }

    void DrawAndEdit(Properties& Properties)
    {
        return;
    }


    plano::api::NodeDescription ConstructDefinition(void)
    {
        plano::api::NodeDescription node;
        node.Type = "InputAction Fire";
        node.Color = ImColor(255, 128, 128);

        node.Outputs.push_back(plano::api::PinDescription("Pressed",PinType::Flow));
        node.Outputs.push_back(plano::api::PinDescription("Released",PinType::Flow));

        node.InitializeDefaultProperties = Initialize;
        node.DrawAndEditProperties = DrawAndEdit;
        return node;
    }

} // end namespace InputActionFire

namespace OutputAction
{
    void Initialize(Properties& Properties)
    {
        return;
    }

    void DrawAndEdit(Properties& Properties)
    {
        return;
    }


    plano::api::NodeDescription ConstructDefinition(void)
    {
        plano::api::NodeDescription node;
        node.Type = "OutputAction";

        node.Inputs.push_back(plano::api::PinDescription("Sample",PinType::Float));
        node.Inputs.push_back(plano::api::PinDescription("Condition",PinType::Bool));

        node.Outputs.push_back(plano::api::PinDescription("Event",PinType::Delegate));

        node.InitializeDefaultProperties = Initialize;
        node.DrawAndEditProperties = DrawAndEdit;
        return node;
    }
} // end namespace OutputAction

namespace Branch
{
    void Initialize(Properties& p)
    {
        p.pint["buttonvalue"] ;
    }

    void DrawAndEdit(Properties& p)
    {
        auto input = p.pstring["button"];
        if (ImGui::SmallButton("More")) {
            p.pint["buttonValue"]++;
        }
        ImGui::SameLine();
        ImGui::Text("%i",p.pint["buttonValue"]);
        
    }


    plano::api::NodeDescription ConstructDefinition(void)
    {
        plano::api::NodeDescription node;
        node.Type = "Branch";

        node.Inputs.push_back(plano::api::PinDescription("",PinType::Flow));
        node.Inputs.push_back(plano::api::PinDescription("Condition",PinType::Delegate));

        node.Outputs.push_back(plano::api::PinDescription("True",PinType::Flow));
        node.Outputs.push_back(plano::api::PinDescription("False",PinType::Flow));

        node.InitializeDefaultProperties = Initialize;
        node.DrawAndEditProperties = DrawAndEdit;
        return node;
    }
} // end namespace Branch


namespace DoN
{
    void Initialize(Properties& Properties)
    {
        return;
    }

    void DrawAndEdit(Properties& Properties)
    {
        return;
    }


    plano::api::NodeDescription ConstructDefinition(void)
    {
        plano::api::NodeDescription node;
        node.Type = "DoN";

        node.Inputs.push_back(plano::api::PinDescription("Enter",PinType::Flow));
        node.Inputs.push_back(plano::api::PinDescription("N",PinType::Int));
        node.Inputs.push_back(plano::api::PinDescription("Reset",PinType::Flow));

        node.Outputs.push_back(plano::api::PinDescription("Exit",PinType::Flow));
        node.Outputs.push_back(plano::api::PinDescription("Counter",PinType::Int));

        node.InitializeDefaultProperties = Initialize;
        node.DrawAndEditProperties = DrawAndEdit;
        return node;
    }
} // end namespace DoN


namespace SetTimer
{
    void Initialize(Properties& Properties)
    {
        return;
    }

    void DrawAndEdit(Properties& Properties)
    {
        return;
    }


    plano::api::NodeDescription ConstructDefinition(void)
    {
        plano::api::NodeDescription node;
        node.Type = "SetTimer";
        node.Color = ImColor(128, 195, 248);

        node.Inputs.push_back(plano::api::PinDescription("",PinType::Flow));
        node.Inputs.push_back(plano::api::PinDescription("Object", PinType::Object));
        node.Inputs.push_back(plano::api::PinDescription("Function Name",PinType::Function));
        node.Inputs.push_back(plano::api::PinDescription("Time",PinType::Float));

        node.Inputs.push_back(plano::api::PinDescription("Looping",PinType::Bool));
        node.Outputs.push_back(plano::api::PinDescription("",PinType::Flow));

        node.InitializeDefaultProperties = Initialize;
        node.DrawAndEditProperties = DrawAndEdit;
        return node;
    }
} // end namespace SetTimer

namespace SingleLineTraceByChannel
{
    void Initialize(Properties& Properties)
    {
        return;
    }

    void DrawAndEdit(Properties& Properties)
    {
        return;
    }


    plano::api::NodeDescription ConstructDefinition(void)
    {
        plano::api::NodeDescription node;
        node.Type = "SingleLineTraceByChannel";
        node.Color = ImColor(255, 128, 64);

        node.Inputs.push_back(plano::api::PinDescription("",PinType::Flow));
        node.Inputs.push_back(plano::api::PinDescription("Start",PinType::Flow));
        node.Inputs.push_back(plano::api::PinDescription("End",PinType::Int));
        node.Inputs.push_back(plano::api::PinDescription("Trace Channel",PinType::Float));
        node.Inputs.push_back(plano::api::PinDescription("Trace Complex",PinType::Bool));
        node.Inputs.push_back(plano::api::PinDescription("Actors to Ignore",PinType::Int));
        node.Inputs.push_back(plano::api::PinDescription("Draw Debug Type",PinType::Bool));
        node.Inputs.push_back(plano::api::PinDescription("Ignore Self",PinType::Bool));

        node.Outputs.push_back(plano::api::PinDescription("",PinType::Flow));
        node.Outputs.push_back(plano::api::PinDescription("Out Hit",PinType::Float));
        node.Outputs.push_back(plano::api::PinDescription("Return Value",PinType::Bool));

        node.InitializeDefaultProperties = Initialize;
        node.DrawAndEditProperties = DrawAndEdit;
        return node;
    }
} // end namespace SingleLineTraceByChannel

namespace PrintString
{
    void Initialize(Properties& Properties)
    {
        return;
    }

    void DrawAndEdit(Properties& Properties)
    {
        return;
    }


    plano::api::NodeDescription ConstructDefinition(void)
    {
        plano::api::NodeDescription node;
        node.Type = "PrintString";

        node.Inputs.push_back(plano::api::PinDescription("",PinType::Flow));
        node.Inputs.push_back(plano::api::PinDescription("In String",PinType::String));

        node.Outputs.push_back(plano::api::PinDescription("",PinType::Flow));

        node.InitializeDefaultProperties = Initialize;
        node.DrawAndEditProperties = DrawAndEdit;
        return node;
    }
} // end namespace PrintString



} // end namespace blueprint_demo
} // end namespace node_defs

#endif // BLUEPRINT_DEMO_H
