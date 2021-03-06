#include <experimental/filesystem>
#include <filesystem>

// With Visual Studio compiler, filesystem is still "experimental"
namespace fs = std::experimental::filesystem;

namespace imgui_ext {

	const struct file {
		std::string alias;
		fs::path path;
	};

	class file_browser_modal final {

		//static inline const int modal_flags;

		const char* m_title;

		bool m_oldVisibility;

		int m_selection;

		fs::path m_currentPath;
		bool m_currentPathIsDir;

		std::vector<file> m_filesInScope;

	public:

		file_browser_modal(const char* title);

		const bool render(const bool isVisible, std::string& outPath);

	};

};