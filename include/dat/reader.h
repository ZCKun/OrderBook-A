//
// Created by x2h1z on 2021/11/8.
//

#ifndef ORDERBOOK_READER_H
#define ORDERBOOK_READER_H

#include <functional>
#include <memory>
#include <string>
#include "mdt/MDTDataType.h"
#include "types.h"

#pragma pack(1)
struct Header
{
    short TotalLen;
    int DataType;
    short DataLen;
};
#pragma pack()

struct Item
{
    MsgType DataType;
    void *Data;

    ~Item()
    {
        //if (Data != nullptr) {
        //    std::free(Data);
        //}
    }
};

using DatCallback = std::function<void(const std::shared_ptr<Item>)>;

class DatReader
{
private:
    std::string dat_filepath_;
    DatCallback callback_;

    void bytes_stream_read();

    void memory_map_read();

public:
    DatReader(std::string filepath, DatCallback callback);

    void read();
};

#endif //ORDERBOOK_READER_H
