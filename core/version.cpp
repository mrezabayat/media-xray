#include "version.h"

namespace media_xray {
std::string version_string() {
  const std::string hash =
      MEDIAXRAY_GIT_HASH[0] == '\0' ? "unknown" : MEDIAXRAY_GIT_HASH;
  return std::string("MediaXray ") + MEDIAXRAY_VERSION + " (git " + hash + ")";
}
} // namespace media_xray
