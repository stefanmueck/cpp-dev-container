#include <cstdint>
#include <iostream>
#include <string>

#include "BashCommand/BashCommand.h"
#include "ValueRange/ValueRange.h"
#include "VlanId/VlanId.h"

int main()
{
    {
        // VlanId<int> id; // static assertion -> not a range type
        VlanId vid_0(0);
        VlanId vid_1(vid_0);
        VlanId vid_3 = vid_0;
        VlanId vid_4 = VlanId(2);

        try
        {
            VlanId vid_5(5000U); // should throw
        }
        catch (std::out_of_range& e)
        {
            std::cout << e.what() << std::endl;
        }

        auto id = vid_0.value();

        if (vid_0 == vid_1) {}

        if (vid_0 != vid_1) {}

        if (vid_0 < vid_1) {}

        if (vid_0 == VlanId(1)) {}

        if (vid_0 != VlanId(1)) {}

        if (vid_0 < VlanId(1)) {}
    }

    { // execute command with combined good/fail handling
        BashCommand::ls("-l")
            /* .withArgument("/path/does/not/exist") */
            .execute()
            .ifGood([](const auto& cmd) {
                std::cout << cmd.stdout() << std::endl;
                std::cout << "4: "
                          << "Command " << cmd.command() << " succeeded" << std::endl;
            })
            .ifFailed([](const auto& cmd) {
                std::cout << "4: "
                          << "Command " << cmd.command() << " failed with code " << cmd.exitCode()
                          << std::endl;
            });
    }

    return 0;
}