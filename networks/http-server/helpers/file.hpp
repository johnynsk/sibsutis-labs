#pragma once
#include <string>

using namespace std;

namespace garcon {
    string getMimeType(filesystem::path path)
    {
        string mimetype;

        FILE *p;
        char buffer[128];
        string command = string(string("file --mime-type '") + string(path) + "'");
        p = popen(command.c_str(), "r");
        fgets(buffer, 128, p);
        pclose(p);

        mimetype = string(buffer);
        mimetype.erase(0, mimetype.find(": ") + 2);
        mimetype.erase(mimetype.size() - 1, 1);

        return mimetype;
    }

    string listForDirectory(filesystem::path path)
    {
        stringstream listing;

        FILE *p;
        char buffer[1024];
        string command = string(string("ls -la '") + string(path) + "'");
        p = popen(command.c_str(), "r");
        size_t bytes;

        while (!feof(p))
        {
            bytes = fread(buffer, sizeof(char), 1024, p);
            listing << buffer;
        }

        pclose(p);

        return listing.str();
    }
}