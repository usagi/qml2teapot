#pragma once
#include <QQmlExtensionPlugin>

class gl_teapot_plugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface")
    
public:
    void registerTypes(const char* uri);
};
