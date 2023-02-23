#pragma once
#include "../types.hpp"

#include <boost/program_options.hpp>
#include <iostream>
#include <string>
#include <memory>

namespace helpers
{
    namespace arguments
    {
        using namespace std;
        int parse(int argc, const char *argv[], shared_ptr<endpoint_t> server)
        {
            using namespace boost::program_options;
            options_description desc{"Options"};
            variables_map arguments;

            auto setConfigIp = [server](string ip)
            { server->config.address = ip; };
            auto setConfigPort = [server](int port)
            { server->config.port = port; };
            auto setMessage = [server](string message)
            { server->config.message = message; };

            desc.add_options()("help,h,usage", "Help screen")
                ("ip", value<string>()->default_value("0.0.0.0")->notifier(setConfigIp), "IP Address")
                ("port,p", value<int>()->default_value(9050)->notifier(setConfigPort), "Port")
                ("message,m", value<string>()->notifier(setMessage), "Message");

            try
            {
                store(parse_command_line(argc, argv, desc), arguments);
                notify(arguments);

                if (arguments.count("help"))
                {
                    std::cout << desc << '\n';
                    return 1;
                }
            }
            catch (const boost::program_options::error &ex)
            {
                std::cerr << ex.what() << '\n';
                std::cerr << desc << endl;
                return 1;
            }

            return 0;
        }
    }
}