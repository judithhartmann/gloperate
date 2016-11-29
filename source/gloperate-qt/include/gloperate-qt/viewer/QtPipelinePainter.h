#include <gloperate/pipeline/PipelinePainter.h>
#include <QWindow>
namespace gloperate
{
	class AbstractPipeline;

}
namespace gloperate_qt
{
	class QtPipelinePainter : public gloperate::PipelinePainter 
	{
	public:
		QtPipelinePainter(
			const std::string & name,
			gloperate::ResourceManager & resourceManager,
			const cpplocate::ModuleInfo & moduleInfo,
			gloperate::AbstractPipeline & pipeline);

		void setWindow(std::shared_ptr<QWindow> window);

	protected:
		std::shared_ptr<QWindow> m_window;
	};

}