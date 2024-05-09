#define CATCH_CONFIG_RUNNER

#include <catch2/catch.hpp>
#include <catch2/trompeloeil.hpp>

int main(int argc, char* argv[])
{
    int result = Catch::Session().run(argc, argv);

    return (result < Catch::MaxExitCode ? result : Catch::MaxExitCode);
}