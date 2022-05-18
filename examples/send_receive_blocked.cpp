/*
// Copyright (c) 2022 Intel Corporation
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
*/

#include "mctp_wrapper.hpp"

#include <boost/asio.hpp>
#include <iostream>
#include <phosphor-logging/log.hpp>

int main(int argc, char* argv[])
{
    uint8_t eid = 10;
    using namespace mctpw;
    boost::asio::io_context io;

    boost::asio::signal_set signals(io, SIGINT, SIGTERM);
    signals.async_wait(
        [&io](const boost::system::error_code&, const int&) { io.stop(); });

    MCTPConfiguration config(mctpw::MessageType::pldm,
                             mctpw::BindingType::mctpOverSmBus);
    MCTPWrapper mctpWrapper(io, config, nullptr, nullptr);

    boost::asio::spawn(io, [&mctpWrapper,
                            eid](boost::asio::yield_context yield) {
        mctpWrapper.detectMctpEndpoints(yield);
        std::cout << "Before sendReceiveBlocked Method" << std::endl;
        std::vector<uint8_t> request = {1, 143, 0, 3, 0, 0, 0, 0, 1, 0};
        auto rcvStatus = mctpWrapper.sendReceiveBlocked(eid, request, std::chrono::milliseconds(100));
        if (rcvStatus.first)
        {
            std::cout << "Method " << rcvStatus.first.message() << '\n';
        }
        else
        {
            std::cout << "Blocked Response ";
            for (int n : rcvStatus.second)
            {
                std::cout << n << ' ';
            }
            std::cout << '\n';
        }
    });

    io.run();
    return 0;
}
