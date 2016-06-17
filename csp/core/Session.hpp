#ifndef _SESSION_HPP_
#define _SESSION_HPP_ 1

#pragma GCC diagnostic ignored "-Wwrite-strings"
#pragma GCC diagnostic ignored "-Wunused-result"

#include <sstream>
#include <string>
#include <string.h>
#include <algorithm>
#include <sys/stat.h>

class Session
{
public:
    std::string id;

    Session(std::string id)
    {
        this->id = id;

        // assure session directory exists
        struct stat sb;

        if (stat("sessions", &sb) != 0 || !S_ISDIR(sb.st_mode))
        {
            const int dir_err = mkdir("sessions", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
            if (-1 == dir_err)
            {
                printf("Error creating 'sessions' directory!\n");
                exit(1);
            }
        }
   	}

    void save(std::string id, void *ptr, uint32_t size)
    {
        id = "sessions/" + id;

        FILE *fp = fopen(id.c_str(), "wb");
        fwrite(&size, 4, 1, fp);
        fwrite(ptr, size, 1, fp);
        fclose(fp);
    }

    void load(std::string id, void *out_ptr, uint32_t *size)
    {
        id = "sessions/" + id;
        FILE *fp = fopen(id.c_str(), "rb");
        if (!fp)
        {
            return;
        }

        fread(size, 4, 1, fp);

        // create buffer and fill it
        fread(out_ptr, *size, 1, fp);
        fclose(fp);
    }

    void load(std::string id, void *out_ptr)
    {
        uint32_t *size = new uint32_t;
        this->load(id, out_ptr, size);
    }

    bool remove(std::string id)
    {
        id = "sessions/" + id;
        if (!remove(id.c_str()))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};

#endif
