#include "BashCommand.h"
#include <array>
#include <cstdio>
#include <optional>
#include <sstream>
#include <utility>

BashCommand BashCommand::command(const Command& command, const Argument& arguments)
{
    auto runner = BashCommand(command);
    runner.withArgument(arguments.value_or(""));
    return runner;
}

BashCommand BashCommand::ps(const Argument& arguments)
{
    return command("ps", arguments);
}

BashCommand BashCommand::ls(const Argument& arguments)
{
    return command("ls", arguments);
}

BashCommand& BashCommand::withArgument(const Argument& arg)
{
    if (arg)
    {
        m_command += " " + arg.value();
    }
    return *this;
}

BashCommand& BashCommand::withPipe(const Command& cmd)
{
    m_command += " | " + cmd;
    return *this;
}

BashCommand& BashCommand::withRedirect(const std::string& outputFile)
{
    m_command += " > " + outputFile;
    return *this;
}

BashCommand& BashCommand::ifGood(const Function& func)
{
    if (isGood())
    {
        func(*this);
    }
    return *this;
}

BashCommand& BashCommand::ifFailed(const Function& func)
{
    if (not isGood())
    {
        func(*this);
    }
    return *this;
}

bool BashCommand::isGood() const
{
    return (m_exitCode == 0);
}

BashCommand::ExitCode BashCommand::exitCode() const
{
    return m_exitCode;
}

const BashCommand::StdOut& BashCommand::stdout() const
{
    return m_stdout;
}

const BashCommand::Command& BashCommand::command() const
{
    return m_command;
}

BashCommand& BashCommand::execute()
{
    constexpr std::uint32_t BufferSize{128};
    std::array<char, BufferSize> buffer{};
    std::string result;

    FILE* pipe = popen(m_command.c_str(), "r"); // NOLINT(cert-env33-c)
    if (pipe == nullptr)
    {
        m_stdout = "Pipe failed!";
        m_exitCode = DefaultExitCode;
    }
    else
    {
        while (std::fgets(buffer.data(), buffer.size(), pipe) != nullptr)
        {
            result += buffer.data();
        }

        std::int32_t status = pclose(pipe);
        if (WIFEXITED(status))
        {
            m_exitCode = WEXITSTATUS(status);
            m_stdout = result;
        }
        else
        {
            m_exitCode = DefaultExitCode;
        }
    }
    return *this;
}