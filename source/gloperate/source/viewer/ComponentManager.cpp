
#include <gloperate/viewer/ComponentManager.h>

#include <fstream>

#include <cppexpose/variant/Variant.h>

#include <gloperate/viewer/ViewerContext.h>


namespace gloperate
{


ComponentManager::ComponentManager(ViewerContext * viewerContext)
: cppexpose::Object("components")
, m_viewerContext(viewerContext)
{
    // Register functions
    addFunction("pluginPaths",      this, &ComponentManager::script_pluginPaths);
    addFunction("addPluginPath",    this, &ComponentManager::script_addPluginPath);
    addFunction("removePluginPath", this, &ComponentManager::script_removePluginPath);
    addFunction("scanPlugins",      this, &ComponentManager::script_scanPlugins);
    addFunction("components",       this, &ComponentManager::script_components);
    addFunction("printComponents",  this, &ComponentManager::script_printComponents);
}

ComponentManager::~ComponentManager()
{
}

cppexpose::Variant ComponentManager::script_pluginPaths()
{
    std::vector<std::string> paths = m_viewerContext->componentManager()->pluginPaths();

    cppexpose::Variant lst = cppexpose::Variant::array();
    for (auto path : paths) {
        lst.asArray()->push_back(cppexpose::Variant(path));
    }

    return lst;
}

void ComponentManager::script_addPluginPath(const std::string & path)
{
    m_viewerContext->componentManager()->addPluginPath(path);
}

void ComponentManager::script_removePluginPath(const std::string & path)
{
    m_viewerContext->componentManager()->removePluginPath(path);
}

void ComponentManager::script_scanPlugins(const std::string & identifier)
{
    m_viewerContext->componentManager()->scanPlugins(identifier);
}

cppexpose::Variant ComponentManager::script_components()
{
    cppexpose::Variant lst = cppexpose::Variant::array();

    auto & components = m_viewerContext->componentManager()->components();
    for (auto * component : components) {
        cppexpose::Variant obj = cppexpose::Variant::map();
        cppexpose::VariantMap & map = *obj.asMap();

        map["name"]        = cppexpose::Variant(component->name());
        map["description"] = cppexpose::Variant(component->description());
        map["type"]        = cppexpose::Variant(component->type());
        map["tags"]        = cppexpose::Variant(component->tags());
        map["icon"]        = cppexpose::Variant(component->icon());
        map["annotations"] = cppexpose::Variant(component->annotations());
        map["vendor"]      = cppexpose::Variant(component->vendor());
        map["version"]     = cppexpose::Variant(component->version());

        lst.asArray()->push_back(obj);
    }

    return lst;
}

void ComponentManager::script_printComponents()
{
    m_viewerContext->componentManager()->printComponents();
}


} // namespace gloperate