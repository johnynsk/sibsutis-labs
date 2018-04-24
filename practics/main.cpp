#include "mainwindow.h"
#include <QApplication>
#include <iostream>

void print_usage(char *argv[])
{
    std::string basename(argv[0]);
    basename = basename.substr(basename.find_last_of("\\") + 1);
    std::cout << "Usage: \n" << basename << " to use GUI or \n"
        << basename << " --dechex 10 # returns A\n"
        << basename << " --hexdec A # return 10\n"
        << basename << " --gui # opens graphic user interface\n"
        << basename << " --sum HEX_A HEX_B # returns HEX_A + HEX_B. Supports negative values\n\n";
}

int main(int argc, char *argv[])
{
    if (argc > 1) {
        if (argv[1] == "--dechex") {
            if (argc != 4) {
                print_usage(argv);
                return 1;
            }
            std::cout << HexSummator::dechex(QString::fromStdString(argv[2]).toLongLong()) << "\n";
            return 0;
        }

        if (argv[1] == "--hexdec") {
            if (argc != 3) {
                print_usage(argv);
                return 1;
            }
            std::cout << HexSummator::hexdec(std::string(argv[2])) << "\n";
            return 0;
        }

        if (argv[1] == "--sum") {
            if (argc != 4) {
                print_usage(argv);
                return 1;
            }
            std::cout << HexSummator::add(std::string(argv[2]), std::string(argv[3])) << "\n";
            return 0;
        }

        if (argv[1] != "--gui") {
            print_usage(argv);
            return 1;
        }
    }

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
