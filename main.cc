#include <iostream>
#include <memory>
#include <ranges>

#include "book/order_book.h"
#include "dat/reader.h"
#include "mdt/MDTStruct.h"
#include "fmt/format.h"
#include "types.h"
#include "utils.h"

static std::string TARGET = "600111";

class A
{
public:
    A();

    void process(const std::shared_ptr<Item> &item);

private:
    std::shared_ptr<x2h::book::OrderBook> book_ptr_;
    int64_t last_msg_time_{};

    void process_sse_order(SSEL2_Order *order_ptr);

    void process_sse_trade(SSEL2_Transaction *trade_ptr);

    void print_order_book() const;
};

A::A()
{
    Symbol symbol{1, TARGET.c_str(), x2h::type::data::Exchange::SH};
    book_ptr_ = std::make_shared<x2h::book::OrderBook>(symbol);
}

inline void A::print_order_book() const
{
    std::string msg;

    auto ask = book_ptr_->get_ask_book();
    auto bid = book_ptr_->get_bid_book();

    fmt::print("bid1:{}, asks:{}\n", bid.size(), ask.size());
    std::vector<std::string> ask_msgs;

    int i = 0;
    for (auto &it: ask) {
        if (i >= 10) break;
        ++i;
        ask_msgs.push_back(fmt::format(
                "{0:^6} | ask | {1:^7} | {2}\n",
                TARGET, it.first, it.second
        ));
    }

    for (auto &ask_msg: std::ranges::reverse_view(ask_msgs)) {
        msg += ask_msg;
    }

    i = 0;
    msg += fmt::format("-------{}--------\n", last_msg_time_);

    for (const auto &item: bid) {
        if (i >= 10) break;
        ++i;
        msg += fmt::format(
                "{0:^6} | bid | {1:^7} | {2}\n",
                TARGET, item.first, item.second
        );
    }

    fmt::print("{}\n", msg);
}

inline void A::process_sse_order(SSEL2_Order *order_ptr)
{
    std::string symbol(order_ptr->Symbol);
    if (symbol != TARGET) return;

#if 0
    auto msg = fmt::format(
            FMT_STRING("[Order] Symbol:{0}, Time:{1}, RecTime:{2}, Side:{3}, Type:{4}, OrderID:{5:^8}, RecNo:{6:^8}, Price:{7:^7}, Quantity:{8:^7}"),
            order_ptr->Symbol, order_ptr->Time,
            x2h::util::convert_ts_to_time((int64_t)order_ptr->MDTTime, x2h::util::Microseconds()),
            order_ptr->OrderCode, order_ptr->OrderType, order_ptr->RecID,
            order_ptr->RecNO, order_ptr->OrderPrice, order_ptr->Balance);
    fmt::print("{}\n", msg);
#endif

    x2h::type::data::Order order{};
    strcpy(order.ticker, order_ptr->Symbol);
    order.rec_time = static_cast<int64_t>(order_ptr->MDTTime);
    order.time = order_ptr->Time;
    order.channel_no = order_ptr->SetID;
    order.order_id = order_ptr->RecID;
    order.origin_order_id = order_ptr->OrderID;
    order.price = order_ptr->OrderPrice;
    order.qty = static_cast<int64_t>(order_ptr->Balance);
    order.side = *order_ptr->OrderCode;
    order.ord_type = order_ptr->OrderType;
    order.business_no = order_ptr->RecNO;

    last_msg_time_ = order.time;
    book_ptr_->on_order(order);

    if (order.time % MILLISECONDS >= 9'30'00'000) {
//        print_order_book();
    }
#if 0
    auto msg = fmt::format(FMT_STRING("[Order] Time:{},Symbol:{},OrderID:{},Side:{},Price:{},Qty:{}"),
                           order_ptr->Time, order_ptr->Symbol, order_ptr->OrderID, order_ptr->OrderType,
                           order_ptr->OrderPrice, order_ptr->Balance);
    fmt::print("{}\n", msg);
#endif
}

inline void A::process_sse_trade(SSEL2_Transaction *trade_ptr)
{
    std::string symbol(trade_ptr->Symbol);
    if (symbol != TARGET) return;

#if 0
    auto msg = fmt::format(FMT_STRING(
                                   "[Trade] Symbol:{0}, Time:{1}, RecTime:{2}, BuySell:{3}, BuyOrderID:{4:^10}, "
                                   "SellOrderID:{5:^10}, Price:{6:^5}, Quantity:{7:^8}, Amount:{8:^10}, RecID:{9:^7}, "
                                   "RecNo:{10:^7}"),
                           trade_ptr->Symbol, trade_ptr->TradeTime,
                           x2h::util::convert_ts_to_time((int64_t)trade_ptr->MDTTime, x2h::util::Microseconds()),
                           trade_ptr->BuySellFlag, trade_ptr->BuyRecID,
                           trade_ptr->SellRecID, trade_ptr->TradePrice, trade_ptr->TradeVolume, trade_ptr->TradeAmount,
                           trade_ptr->RecID, trade_ptr->RecNO);
    fmt::print("{}\n", msg);
#endif

    x2h::type::data::Trade trade{};
    strcpy(trade.ticker, trade_ptr->Symbol);
    trade.rec_time = static_cast<int64_t>(trade_ptr->MDTTime);
    trade.time = trade_ptr->TradeTime;
    trade.channel_id = trade_ptr->TradeChannel;
    trade.ask_id = trade_ptr->SellRecID;
    trade.bid_id = trade_ptr->BuyRecID;
    trade.memory = trade_ptr->TradeAmount;
    trade.price = trade_ptr->TradePrice;
    trade.qty = static_cast<int64_t>(trade_ptr->TradeVolume);
    trade.trade_flag = trade_ptr->BuySellFlag;
    trade.trade_id = trade_ptr->RecID;
    trade.business_no = trade_ptr->RecNO;

    last_msg_time_ = trade.time;
    book_ptr_->on_trade(trade);

    if (trade.time % MILLISECONDS >= 9'30'00'000) {
         print_order_book();
    }
#if 0
    auto msg = fmt::format(FMT_STRING("[Trader] Time:{},Symbol:{},TradeID:{},AskNo:{},BidNo:{},Price:{},Qty:{}"),
                           trade_ptr->TradeTime, trade_ptr->Symbol, trade_ptr->RecID, trade_ptr->SellRecID,
                           trade_ptr->BuyRecID, trade_ptr->TradePrice, trade_ptr->TradeVolume);
    fmt::print("{}\n", msg);
#endif
}

void A::process(const std::shared_ptr<Item> &item)
{
    switch (item->DataType) {
        default:
        case Msg_Unknown:
            break;
        case Msg_SSEL1_Static:
            break;
        case Msg_SSEL1_Quotation:
            break;
        case Msg_SSE_IndexPress:
            break;
        case Msg_SSEL2_Static:
            break;
        case Msg_SSEL2_Quotation: {
            auto *sse_snapshot = reinterpret_cast<SSEL2_Quotation *>(item->Data);
            std::string symbol_code{sse_snapshot->Symbol};
            if (sse_snapshot->Time % MILLISECONDS < 9'30'00'000 || symbol_code !=  TARGET) break;
            if (sse_snapshot->SellLevelNo == 0 && sse_snapshot->BuyLevelNo == 0) {
                break;
            }
            std::string msg;
            if (sse_snapshot->SellLevelNo > 0) {
                for (const auto &elem: std::ranges::reverse_view(sse_snapshot->SellLevel)) {
                    msg += fmt::format("{0:^} | ask | {1:^7} | {2}\n", symbol_code, elem.Price, elem.Volume);
                }
            }

            msg += fmt::format("------------------{}----------------\n", sse_snapshot->Time);

            if (sse_snapshot->BuyLevelNo > 0) {
                for (const auto &elem: sse_snapshot->BuyLevel) {
                    msg += fmt::format("{0:^} | bid | {1:^7} | {2}\n", symbol_code, elem.Price, elem.Volume);
                }
            }
            fmt::print(">>>>>>>>>>>>>>>>>>\n{}<<<<<<<<<<<<<<<<<<<<\n\n", msg);
            break;
        }
        case Msg_SSEL2_Transaction: {
            auto *sse_trade_ptr = reinterpret_cast<SSEL2_Transaction *>(item->Data);
            process_sse_trade(sse_trade_ptr);
            break;
        }
        case Msg_SSEL2_Index:
            break;
        case Msg_SSEL2_Auction:
            break;
        case Msg_SSEL2_Overview:
            break;
        case Msg_SSEL2_Order: {
            auto *sse_order_ptr = reinterpret_cast<SSEL2_Order *>(item->Data);
            process_sse_order(sse_order_ptr);
            break;
        }
        case Msg_SSEIOL1_Static:
            break;
        case Msg_SSEIOL1_Quotation:
            break;
        case Msg_SZSEL1_Static:
            break;
        case Msg_SZSEL1_Quotation:
            break;
        case Msg_SZSEL1_Bulletin:
            break;
        case Msg_SZSEL2_Static:
            break;
        case Msg_SZSEL2_Quotation:
            break;
        case Msg_SZSEL2_Transaction:
            break;
        case Msg_SZSEL2_Index:
            break;
        case Msg_SZSEL2_Order:
            break;
        case Msg_SZSEL2_Status:
            break;
    }

}

int main()
{
    A a{};

    DatReader reader{"/home/x2h1z/Downloads/DATA/dat/202109030705.dat",
                     [&](const std::shared_ptr<Item> &item) { a.process(item); }};
//    DatReader reader{"/home/x2h1z/Downloads/DATA/dat/202111100705.dat",
//                     [&](const std::shared_ptr<Item> &item) { a.process(item); }};
    reader.read();

    return 0;
}
