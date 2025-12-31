from conan import ConanFile


class MediaXrayConan(ConanFile):
    name = "media-xray"
    version = "0.0.1"
    package_type = "application"

    settings = "os", "arch", "compiler", "build_type"

    requires = (
        "cxxopts/3.2.0",
        "gtest/1.14.0",
    )

    generators = ("CMakeDeps", "CMakeToolchain")

    def layout(self):
        self.folders.build = "build"
        self.folders.generators = "build/generators"
