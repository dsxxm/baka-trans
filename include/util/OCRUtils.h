#include <string>

namespace OCRUtils {
enum class OCRSource { REMOTE, LOCAL };
std::string recognize(OCRSource source);
} // namespace OCRUtils
