#include <cstdint>
#include <functional>
#include <optional>
#include <string>

class BashCommand
{
  public:
    using Function = std::function<void(const BashCommand&)>;
    using Argument = std::optional<std::string>;
    using Command = std::string;
    using StdOut = std::string;
    using ExitCode = std::int32_t;

    static constexpr std::optional<std::string> NoArg{std::nullopt};

    static BashCommand command(const Command& command, const Argument& arguments = NoArg);
    static BashCommand ps(const Argument& arguments = std::nullopt);
    static BashCommand ls(const Argument& arguments = std::nullopt);

    BashCommand& withArgument(const Argument& arg);
    BashCommand& withPipe(const Command& cmd);
    BashCommand& withRedirect(const std::string& outputFile);

    BashCommand& ifGood(const Function& func);
    BashCommand& ifFailed(const Function& func);

    bool isGood() const;
    ExitCode exitCode() const;
    const StdOut& stdout() const;
    const Command& command() const;

    BashCommand& execute();

  private:
    static constexpr ExitCode DefaultExitCode{-1};

    Command m_command;
    StdOut m_stdout;
    ExitCode m_exitCode;

    explicit BashCommand(const Command& command)
        : m_command(command)
        , m_stdout()
        , m_exitCode(DefaultExitCode)
    {}
};