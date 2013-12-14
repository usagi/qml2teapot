#include "gl_teapot_plugin.h"
#include "gl_teapot.h"

#include <qqml.h>

void gl_teapot_plugin::registerTypes(const char *uri)
{
    // @uri net.WonderRabbitProject.tmp
    qmlRegisterType<gl_teapot>(uri, 1, 0, "GLTeapot");
}


