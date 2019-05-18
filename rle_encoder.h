#ifndef RLE_ENCODER_H
#define RLE_ENCODER_H

#include <boost/filesystem/path.hpp>
#include <string>

class RLE_Encoder
{
public:
    RLE_Encoder();
    ~RLE_Encoder();

    std::string decompress(boost::filesystem::path path);
    std::string compress(std::string compressed);
};

#endif // RLE_ENCODER_H
