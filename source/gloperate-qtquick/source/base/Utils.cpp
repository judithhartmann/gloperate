
#include <gloperate-qtquick/base/Utils.h>

#include <glbinding/Binding.h>
#include <glbinding/gl/gl.h>

#include <globjects/globjects.h>

#include <gloperate/base/Environment.h>
#include <gloperate/base/RenderSurface.h>
#include <gloperate/pipeline/Stage.h>

    
namespace gloperate_qtquick
{


void Utils::initContext()
{
    glbinding::Binding::initialize(false);
    globjects::init();
}

void Utils::clearScreen(float red, float green, float blue, float alpha, bool clearDepthBuffer)
{
    gl::glClearColor(red, green, blue, alpha);

    if (clearDepthBuffer) gl::glClear(gl::GL_COLOR_BUFFER_BIT | gl::GL_DEPTH_BUFFER_BIT);
    else                  gl::glClear(gl::GL_COLOR_BUFFER_BIT);
}

gloperate::Stage * Utils::createRenderStage(gloperate::Environment * environment, const std::string & name)
{
    auto component = environment->componentManager()->component<gloperate::Stage>(name);
    if (component) {
        return component->createInstance(environment);
    }

    return new gloperate::Stage(environment);
}


gloperate::Surface * Utils::createSurface(gloperate::Environment * environment, gloperate::Stage * renderStage)
{
    gloperate::RenderSurface * renderSurface = new gloperate::RenderSurface(environment);
    renderSurface->setRenderStage(renderStage);
    return renderSurface;
}


} // namespace gloperate_qtquick
