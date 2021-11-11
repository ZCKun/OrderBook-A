#include "dat/reader.h"

DatReader::DatReader(std::string filepath, DatCallback callback)
        : dat_filepath_(std::move(filepath)),
          callback_(std::move(callback))
{}

void DatReader::bytes_stream_read()
{
    std::FILE* file_ptr = std::fopen(dat_filepath_.c_str(), "rb");

    void* head_buf = std::malloc(8);
    void* msg_buf = std::malloc(4096);
    std::shared_ptr<Item> item = std::make_shared<Item>();

    while (std::fread(head_buf, 1, sizeof(head_buf), file_ptr) > 0) {
        auto* head = (Header*)head_buf;

        item->DataType = (MsgType)head->DataType;
        fread(msg_buf, 1, head->DataLen, file_ptr);
        item->Data = msg_buf;

        callback_(item);
    }

    std::free(head_buf);
    head_buf = nullptr;
    std::free(msg_buf);
    msg_buf = nullptr;

    std::fclose(file_ptr);
}

void DatReader::memory_map_read()
{
    //boost::interprocess::file_mapping mapping(dat_filepath_.c_str(), boost::interprocess::read_only);
    //boost::interprocess::mapped_region region(mapping, boost::interprocess::read_only);

    //const char* addr = (const char*)region.get_address();
    //const size_t size = region.get_size();
    //const size_t total_size = reinterpret_cast<size_t>(addr) + size;

    //while (reinterpret_cast<size_t>(addr) <= total_size) {
    //    auto header = (Header*)addr;

    //    // auto item = new Item;
    //    auto item = std::make_shared<Item>();
    //    item->DataType = (MsgType)header->DataType;
    //    item->Data = header + 1;

    //    addr += header->DataLen;

    //    addr += sizeof(Header); // +8
    //    callback_(item);
    //
    //}
}

void DatReader::read()
{
    bytes_stream_read();
}