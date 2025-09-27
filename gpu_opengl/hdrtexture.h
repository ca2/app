#pragma once

#include <string>

/**
 * A texture loaded from a .hdr file.
 */
class HDRTexture {
public:
    HDRTexture(const std::string &path);
    unsigned int getId();
private:
    unsigned int mId;
};