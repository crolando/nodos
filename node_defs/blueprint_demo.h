#ifndef BLUEPRINT_DEMO_H
#define BLUEPRINT_DEMO_H

#include <node_turnkey_api.h>
#include <imgui_stdlib.h> // For 3-arg text box

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


    turnkey::api::NodeDescription ConstructDefinition(void)
    {
        turnkey::api::NodeDescription node;
        node.Type = "InputAction Fire";

        node.Outputs.push_back(turnkey::api::PinDescription("Pressed","Flow"));
        node.Outputs.push_back(turnkey::api::PinDescription("Released","Flow"));

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


    turnkey::api::NodeDescription ConstructDefinition(void)
    {
        turnkey::api::NodeDescription node;
        node.Type = "OutputAction";

        node.Inputs.push_back(turnkey::api::PinDescription("Sample","Float"));
        node.Inputs.push_back(turnkey::api::PinDescription("Condition","Bool"));

        node.Outputs.push_back(turnkey::api::PinDescription("Event","Delegate"));

        node.InitializeDefaultProperties = Initialize;
        node.DrawAndEditProperties = DrawAndEdit;
        return node;
    }
} // end namespace OutputAction

namespace Branch
{
    void Initialize(Properties& Properties)
    {
        Properties.set_attr("button","Hello");
    }

    void DrawAndEdit(Properties& Properties)
    {
        auto input = Properties.get_attr("button").get_string();
        ImGui::SmallButton(input.c_str());
        Properties.set_attr("input",input);
    }


    turnkey::api::NodeDescription ConstructDefinition(void)
    {
        turnkey::api::NodeDescription node;
        node.Type = "Branch";

        node.Inputs.push_back(turnkey::api::PinDescription("","Flow"));
        node.Inputs.push_back(turnkey::api::PinDescription("Condition","Delegate"));

        node.Outputs.push_back(turnkey::api::PinDescription("True","Flow"));
        node.Outputs.push_back(turnkey::api::PinDescription("False","Flow"));

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


    turnkey::api::NodeDescription ConstructDefinition(void)
    {
        turnkey::api::NodeDescription node;
        node.Type = "DoN";

        node.Inputs.push_back(turnkey::api::PinDescription("Enter","Flow"));
        node.Inputs.push_back(turnkey::api::PinDescription("N","Int"));
        node.Inputs.push_back(turnkey::api::PinDescription("Reset","Flow"));

        node.Outputs.push_back(turnkey::api::PinDescription("Exit","Flow"));
        node.Outputs.push_back(turnkey::api::PinDescription("Counter","Int"));

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


    turnkey::api::NodeDescription ConstructDefinition(void)
    {
        turnkey::api::NodeDescription node;
        node.Type = "SetTimer";

        node.Inputs.push_back(turnkey::api::PinDescription("","Flow"));
        node.Inputs.push_back(turnkey::api::PinDescription("Object","Object"));
        node.Inputs.push_back(turnkey::api::PinDescription("Function Name","Function"));
        node.Inputs.push_back(turnkey::api::PinDescription("Time","Float"));

        node.Inputs.push_back(turnkey::api::PinDescription("Looping","Bool"));
        node.Outputs.push_back(turnkey::api::PinDescription("","Flow"));

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


    turnkey::api::NodeDescription ConstructDefinition(void)
    {
        turnkey::api::NodeDescription node;
        node.Type = "SingleLineTraceByChannel";

        node.Inputs.push_back(turnkey::api::PinDescription("","Flow"));
        node.Inputs.push_back(turnkey::api::PinDescription("Start","Flow"));
        node.Inputs.push_back(turnkey::api::PinDescription("End","Int"));
        node.Inputs.push_back(turnkey::api::PinDescription("Trace Channel","Float"));
        node.Inputs.push_back(turnkey::api::PinDescription("Trace Complex","Bool"));
        node.Inputs.push_back(turnkey::api::PinDescription("Actors to Ignore","Int"));
        node.Inputs.push_back(turnkey::api::PinDescription("Draw Debug Type","Bool"));
        node.Inputs.push_back(turnkey::api::PinDescription("Ignore Self","Bool"));

        node.Outputs.push_back(turnkey::api::PinDescription("","Flow"));
        node.Outputs.push_back(turnkey::api::PinDescription("Out Hit","Float"));
        node.Outputs.push_back(turnkey::api::PinDescription("Return Value","Bool"));

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


    turnkey::api::NodeDescription ConstructDefinition(void)
    {
        turnkey::api::NodeDescription node;
        node.Type = "PrintString";

        node.Inputs.push_back(turnkey::api::PinDescription("","Flow"));
        node.Inputs.push_back(turnkey::api::PinDescription("In String","String"));

        node.Outputs.push_back(turnkey::api::PinDescription("","Flow"));

        node.InitializeDefaultProperties = Initialize;
        node.DrawAndEditProperties = DrawAndEdit;
        return node;
    }
} // end namespace PrintString



} // end namespace blueprint_demo
} // end namespace node_defs

#endif // BLUEPRINT_DEMO_H
