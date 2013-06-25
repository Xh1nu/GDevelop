/** \file
 *  Game Develop
 *  2008-2013 Florian Rival (Florian.Rival@gmail.com)
 */

#include "GDL/BuiltinExtensions/SceneExtension.h"
#include "GDL/ExtensionBase.h"
#include "GDCore/Events/EventsCodeGenerator.h"
#include "GDCore/Events/EventsCodeGenerationContext.h"
#include "GDCore/Events/EventsCodeNameMangler.h"
#include "GDCore/Events/ExpressionsCodeGeneration.h"
#include "GDL/Scene.h"
#include "GDL/Project.h"

SceneExtension::SceneExtension()
{
    SetExtensionInformation("BuiltinScene",
                          _("Scene management features"),
                          _("Built-in extension allowing to manipulate scenes"),
                          "Florian Rival",
                          "Freeware");
    #if defined(GD_IDE_ONLY)

    AddExpression("Random", _("Random value"), _("Random value"), _("Random"), "res/actions/position.png")
        .AddParameter("expression", _("Maximum value"))
        .codeExtraInformation.SetFunctionName("GDpriv::CommonInstructions::Random").SetIncludeFile("GDL/BuiltinExtensions/CommonInstructionsTools.h");


    AddCondition("DepartScene",
                   _("At the beginning of the scene"),
                   _("Is true only when scene just begins."),
                   _("At the beginning of the scene"),
                   _("Scene"),
                   "res/conditions/depart24.png",
                   "res/conditions/depart.png")
        .AddCodeOnlyParameter("currentScene", "")
        .codeExtraInformation.SetFunctionName("SceneJustBegins").SetIncludeFile("GDL/BuiltinExtensions/RuntimeSceneTools.h");



    AddAction("Scene",
                   _("Go to a scene"),
                   _("Change and start the specified scene."),
                   _("Go to scene _PARAM1_"),
                   _("Scene"),
                   "res/actions/goscene24.png",
                   "res/actions/goscene.png")
        .AddCodeOnlyParameter("currentScene", "")
        .AddParameter("string", _("Name of the scene"), "",false)
        .codeExtraInformation.SetFunctionName("ChangeScene").SetIncludeFile("GDL/BuiltinExtensions/RuntimeSceneTools.h");

    AddAction("Quit",
                   _("Quit the game"),
                   _("Quit the game"),
                   _("Quit the game"),
                   _("Scene"),
                   "res/actions/quit24.png",
                   "res/actions/quit.png")
        .AddCodeOnlyParameter("currentScene", "")
        .codeExtraInformation.SetFunctionName("StopGame").SetIncludeFile("GDL/BuiltinExtensions/RuntimeSceneTools.h");

    AddAction("SceneBackground",
                   _("Change background color"),
                   _("Change the background color of the scene."),
                   _("Set background color to _PARAM1_"),
                   _("Scene"),
                   "res/actions/background24.png",
                   "res/actions/background.png")
        .AddCodeOnlyParameter("currentScene", "")
        .AddParameter("color", _("Color"), "",false)
        .codeExtraInformation.SetFunctionName("ChangeSceneBackground").SetIncludeFile("GDL/BuiltinExtensions/RuntimeSceneTools.h");

    AddAction("DisableInputWhenFocusIsLost",
                   _("Disable input when focus is lost"),
                   _("Set if the keyboard and mouse buttons must be taken into account even\nif the window is not active."),
                   _("Disable input when focus is lost: _PARAM1_"),
                   _("Scene"),
                   "res/actions/window24.png",
                   "res/actions/window.png")
        .AddCodeOnlyParameter("currentScene", "")
        .AddParameter("yesorno", _("Deactivate input when focus is lost"))
        .codeExtraInformation.SetFunctionName("DisableInputWhenFocusIsLost").SetIncludeFile("GDL/BuiltinExtensions/RuntimeSceneTools.h");

    {
        class CodeGenerator : public gd::InstructionMetadata::ExtraInformation::CustomCodeGenerator
        {
            virtual std::string GenerateCode(gd::Instruction & instruction, gd::EventsCodeGenerator & codeGenerator, gd::EventsCodeGenerationContext & context)
            {
                std::string value1Code;
                {
                    gd::CallbacksForGeneratingExpressionCode callbacks(value1Code, codeGenerator, context);
                    gd::ExpressionParser parser(instruction.GetParameters()[0].GetPlainString());
                    if (!parser.ParseMathExpression(codeGenerator.GetPlatform(), codeGenerator.GetProject(), codeGenerator.GetLayout(), callbacks) || value1Code.empty()) value1Code = "0";
                }

                std::string value2Code;
                {
                    gd::CallbacksForGeneratingExpressionCode callbacks(value2Code, codeGenerator, context);
                    gd::ExpressionParser parser(instruction.GetParameters()[2].GetPlainString());
                    if (!parser.ParseMathExpression(codeGenerator.GetPlatform(), codeGenerator.GetProject(), codeGenerator.GetLayout(), callbacks) || value2Code.empty()) value2Code = "0";
                }

                if ( instruction.GetParameters()[1].GetPlainString() == "=" || instruction.GetParameters()[1].GetPlainString().empty() )
                    return "conditionTrue = ("+value1Code+" == "+value2Code+");\n";
                else if ( instruction.GetParameters()[1].GetPlainString() == ">")
                    return "conditionTrue = ("+value1Code+" > "+value2Code+");\n";
                else if ( instruction.GetParameters()[1].GetPlainString() == "<")
                    return "conditionTrue = ("+value1Code+" < "+value2Code+");\n";
                else if ( instruction.GetParameters()[1].GetPlainString() == "<=")
                    return "conditionTrue = ("+value1Code+" <= "+value2Code+");\n";
                else if ( instruction.GetParameters()[1].GetPlainString() == ">=")
                    return "conditionTrue = ("+value1Code+" >= "+value2Code+");\n";
                else if ( instruction.GetParameters()[1].GetPlainString() == "!=")
                    return "conditionTrue = ("+value1Code+" != "+value2Code+");\n";

                return "";
            };
        };
        gd::InstructionMetadata::ExtraInformation::CustomCodeGenerator * codeGenerator = new CodeGenerator; //Need for code to compile

        AddCondition("Egal",
                   _("Compare two expressions"),
                   _("Test the two expression"),
                   _("_PARAM0_ _PARAM2_ _PARAM1_"),
                   _("Other"),
                   "res/conditions/egal24.png",
                   "res/conditions/egal.png")
        .AddParameter("expression", _("Expression 1"), "",false)
        .AddParameter("relationalOperator", _("Sign of the test"), "",false)
        .AddParameter("expression", _("Expression 2"), "",false)
        .codeExtraInformation.SetCustomCodeGenerator(boost::shared_ptr<gd::InstructionMetadata::ExtraInformation::CustomCodeGenerator>(codeGenerator));
    }

    #endif
}

