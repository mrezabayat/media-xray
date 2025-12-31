#include <gtest/gtest.h>

#include "version.h"

TEST(VersionString, IsNotEmpty) {
    EXPECT_FALSE(media_xray::version_string().empty());
}
