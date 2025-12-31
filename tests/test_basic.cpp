#include <gtest/gtest.h>

#include <sstream>
#include <string>
#include <vector>

#include "cli.h"
#include "version.h"

namespace {
class StreamCapture {
public:
  explicit StreamCapture(std::ostream &stream)
      : stream_(stream), old_(stream.rdbuf(buffer_.rdbuf())) {}

  ~StreamCapture() { stream_.rdbuf(old_); }

  std::string str() const { return buffer_.str(); }

private:
  std::ostream &stream_;
  std::streambuf *old_;
  std::ostringstream buffer_;
};

struct CliResult {
  int code;
  std::string out;
  std::string err;
};

CliResult run_cli_with_output(const std::vector<std::string> &args) {
  std::vector<std::string> storage = args;
  std::vector<char *> argv;
  argv.reserve(storage.size());
  for (auto &arg : storage) {
    argv.push_back(arg.data());
  }

  StreamCapture out(std::cout);
  StreamCapture err(std::cerr);
  int code = media_xray::run_cli(static_cast<int>(argv.size()), argv.data());
  return {code, out.str(), err.str()};
}
} // namespace

TEST(VersionString, IncludesVersion) {
  EXPECT_NE(media_xray::version_string().find(MEDIAXRAY_VERSION),
            std::string::npos);
}

TEST(CliHelp, ListsAnalyzeCommand) {
  CliResult result = run_cli_with_output({"media-xray", "--help"});
  EXPECT_EQ(result.code, 0);
  EXPECT_NE(result.out.find("analyze"), std::string::npos);
}

TEST(CliVersion, PrintsVersionString) {
  CliResult result = run_cli_with_output({"media-xray", "--version"});
  EXPECT_EQ(result.code, 0);
  EXPECT_NE(result.out.find(media_xray::version_string()), std::string::npos);
}

TEST(CliAnalyze, MissingInputIsError) {
  CliResult result = run_cli_with_output({"media-xray", "analyze"});
  EXPECT_NE(result.code, 0);
  EXPECT_NE(result.err.find("missing <input>"), std::string::npos);
}

TEST(CliAnalyze, AcceptsInput) {
  CliResult result = run_cli_with_output({"media-xray", "analyze", "foo"});
  EXPECT_EQ(result.code, 0);
}
