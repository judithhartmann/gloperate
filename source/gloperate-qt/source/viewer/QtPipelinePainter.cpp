#include <gloperate-qt/viewer/QtPipelinePainter.h>

namespace gloperate_qt {
	QtPipelinePainter::QtPipelinePainter(const std::string & name, gloperate::ResourceManager & resourceManager, const cpplocate::ModuleInfo & moduleInfo, gloperate::AbstractPipeline & pipeline)
		:gloperate::PipelinePainter(name, resourceManager, moduleInfo, pipeline)
	{
	}


	void QtPipelinePainter::setWindow(std::shared_ptr<QWindow> window)
	{
		m_window = window;
	}

}