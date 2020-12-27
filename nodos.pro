QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    nodos.cpp \
    ../imgui-node-editor/examples/blueprints-example/utilities/builders.cpp \
    ../imgui-node-editor/examples/blueprints-example/utilities/drawing.cpp \
    ../imgui-node-editor/examples/blueprints-example/utilities/widgets.cpp \
    ../imgui-node-editor/crude_json.cpp \
    ../imgui-node-editor/imgui_canvas.cpp \
    ../imgui-node-editor/imgui_node_editor.cpp \
    ../imgui-node-editor/imgui_node_editor_api.cpp \
    ../imgui-node-editor/external/imgui/imgui.cpp \
    ../imgui-node-editor/external/imgui/imgui_demo.cpp \
    ../imgui-node-editor/external/imgui/imgui_draw.cpp \
    ../imgui-node-editor/external/imgui/imgui_widgets.cpp \
    ../qtimgui/ImGuiRenderer.cpp \
    ../qtimgui/QtImGui.cpp \
    ../qt-imgui-nodes/NodosWidget.cpp \
    ../qt-imgui-nodes/main.cpp \
    ../qt-imgui-nodes/mainwindow.cpp \
    ../qt-imgui-nodes/texture_manager.cpp

HEADERS += \
    ../qt-imgui-nodes/application.h \
    ../imgui-node-editor/examples/blueprints-example/utilities/builders.h \
    ../imgui-node-editor/examples/blueprints-example/utilities/drawing..h \
    ../imgui-node-editor/examples/blueprints-example/utilities/widgets.h \
    ../imgui-node-editor/NodeEditor/Include/imgui_node_editor.h \
    ../imgui-node-editor/NodeEditor/Source/crude_json.h \
    ../imgui-node-editor/NodeEditor/Source/imgui_bezier_math.h \
    ../imgui-node-editor/NodeEditor/Source/imgui_bezier_math.inl \
    ../imgui-node-editor/NodeEditor/Source/imgui_canvas.h \
    ../imgui-node-editor/NodeEditor/Source/imgui_extra_math.h \
    ../imgui-node-editor/NodeEditor/Source/imgui_extra_math.inl \
    ../imgui-node-editor/NodeEditor/Source/imgui_node_editor_internal.h \
    ../imgui-node-editor/NodeEditor/Source/imgui_node_editor_internal.inl \
    ../imgui-node-editor/external/imgui/imgui.h \
    ../qtimgui/ImGuiRenderer.h \
    ../qtimgui/QtImGui.h \
    ../qt-imgui-nodes/texture_manager.h \
    ../qt-imgui-nodes/NodosWidget.h \
    ../qt-imgui-nodes/mainwindow.h

FORMS += \
    ../qt-imgui-nodes/mainwindow.ui

INCLUDEPATH += \
    ../qt-imgui-nodes \
    ../imgui-node-editor \
    ../imgui-node-editor/external/imgui \
    ../qtimgui \
    ../imgui-node-editor/examples/application/include \
    ../imgui-node-editor/examples/Common/Application/Include \
    ../imgui-node-editor/examples/blueprints-example/utilities \
    ../imgui-node-editor/examples/blueprints-example


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
