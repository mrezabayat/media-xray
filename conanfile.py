from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMakeDeps


class MediaXrayConan(ConanFile):
    name = "media-xray"
    version = "0.0.1"
    package_type = "application"

    settings = "os", "arch", "compiler", "build_type"

    requires = (
        "cxxopts/3.2.0",
        "gtest/1.14.0",
    )

    def layout(self):
        self.folders.build = "build"
        self.folders.generators = "build/generators"

    def generate(self):
        tc = CMakeToolchain(self)
        tc.cache_variables["CMAKE_EXPORT_COMPILE_COMMANDS"] = "ON"
        tc.generate()

        deps = CMakeDeps(self)
        deps.generate()
