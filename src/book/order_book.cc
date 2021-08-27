#include "book/order_book.h"

namespace x2h
{
    namespace book
    {
        OrderBook::OrderBook(const Symbol& symbol)
            : symbol_(symbol),
            last_order_id_(0),
            last_bid_price_(0),
            last_ask_price_(std::numeric_limits<int64_t>::max()) {}

        OrderBook::~OrderBook() {}

        template<class TOutputStream>
        TOutputStream& operator<<(TOutputStream& stream, const OrderBook& book)
        {
            //const auto& ask_book = book.asks_;
            //const auto& bid_book = book.bids_;

            //std::map<double, int64_t, std::greater<>> ask{};
            //std::map<double, int64_t, std::greater<>> bid{};

            //int count = 10;

            //for (const auto& item : ask_book) {
            //    if (count == 0) break;
            //    double price = item.price;
            //    ask[price] += item.qty;
            //    --count;
            //}

            //count = 10;
            //for (auto it = bid_book.rbegin(); it != bid_book.rend(); it++) {
            //    if (count == 0) break;
            //    double price = it->price;
            //    bid[price] += it->qty;
            //    --count;
            //}

            //std::string msg;

            //for (const auto& item : ask) {
            //    msg += fmt::format(
            //        "{} | ask | {} | {}\n",
            //        book.symbol_.code, item.first, item.second
            //    );
            //}

            //msg += fmt::format("-------{}--------\n", book.last_msg_time_);

            //for (const auto& item : bid) {
            //    msg += fmt::format(
            //        "{} | bid | {} | {}\n",
            //        book.symbol_.code, item.first, item.second
            //    );
            //}

            //stream << msg;
            return stream;
        }

        inline void OrderBook::add_order(type::data::Order& order) noexcept
        {
            if (order.is_buy()) {
                bids_.push_back(order);

                if ((best_bid_.price == 0) || (order.price > best_bid_.price))
                    best_bid_ = order;
            }
            else if (order.is_sell()) {
                asks_.push_back(order);

                if ((best_ask_.price == 0) || (order.price < best_ask_.price))
                    best_ask_ = order;
            }
            else {
                fmt::print("未知Order Side: {}\n", order.side);
            }
        }

        void OrderBook::on_order(const type::data::Order& order)
        {
            type::data::Order new_order(order);
            last_order_id_ = new_order.order_id;
            last_msg_time_ = new_order.time;

            if (trade_supped(new_order)) return;

            if (new_order.exchange == type::data::Exchange::SH && new_order.ord_type == static_cast<char>(type::data::sh::OrderType::DEL)) {
                if (new_order.is_buy()) {
                    bids_.remove_if([&](type::data::Order& o) {
                        return o.order_id == new_order.order_id;
                        });
                }
                else if (new_order.is_sell()) {
                    asks_.remove_if([&](type::data::Order& o) {
                        return o.order_id == new_order.order_id;
                        });
                }
            }
            else {
                if (new_order.qty > 0) {
                    add_order(new_order);
                }
            }
        }

        void OrderBook::match_order(const type::data::Order& order) noexcept
        {
            if (order.is_sell()) {
                match_ask_book();
            }
            else if (order.is_buy()) {
                match_bid_book();
            }
        }

        inline void OrderBook::match_bid_book()
        {
            bid_book_snapshot_ = get_bid_book();
            ask_book_snapshot_ = get_ask_book();

            for (auto bid_it = bid_book_snapshot_.begin(); bid_it != bid_book_snapshot_.end(); ) {

                const auto& bid_price = bid_it->first;
                auto& bid_qty = bid_it->second;

                for (auto ask_it = ask_book_snapshot_.begin(); bid_qty > 0 && ask_it != ask_book_snapshot_.end(); ) {

                    const auto& ask_price = ask_it->first;
                    auto& ask_qty = ask_it->second;

                    if (ask_price <= bid_price) {
                        auto qty = std::min(ask_qty, bid_qty);
                        ask_qty -= qty;
                        bid_qty -= qty;

                    }
                    if (ask_qty == 0) {
                        ask_book_snapshot_.erase(ask_it++);
                    }
                    else {
                        ++ask_it;
                    }
                }

                if (bid_qty == 0) {
                    bid_book_snapshot_.erase(bid_it++);
                }
                else {
                    ++bid_it;
                }
            }
        }

        inline void OrderBook::match_ask_book()
        {
            bid_book_snapshot_ = get_bid_book();
            ask_book_snapshot_ = get_ask_book();

            for (auto ask_it = ask_book_snapshot_.begin(); ask_it != ask_book_snapshot_.end(); ) {

                const auto& ask_price = ask_it->first;
                auto& ask_qty = ask_it->second;

                for (auto bid_it = bid_book_snapshot_.begin(); ask_qty > 0 && bid_it != bid_book_snapshot_.end(); ) {

                    const auto& bid_price = bid_it->first;
                    auto& bid_qty = bid_it->second;

                    if (bid_price >= ask_price) {
                        auto qty = std::min(ask_qty, bid_qty);
                        ask_qty -= qty;
                        bid_qty -= qty;
                    }
                    if (bid_qty == 0) {
                        bid_book_snapshot_.erase(bid_it++);
                    }
                    else {
                        ++bid_it;
                    }
                }

                if (ask_qty == 0) {
                    ask_book_snapshot_.erase(ask_it++);
                }
                else {
                    ++ask_it;
                }
            }
        }

        void OrderBook::on_trade(const type::data::Trade& trade)
        {
            last_msg_time_ = trade.time;

            if (trade.exchange == type::data::Exchange::SZ && trade.trade_flag == '4') {
                on_cancel(trade);
            }
            else {
                on_traded(trade);
            }
        }

        inline void OrderBook::on_cancel(const type::data::Trade& trade)
        {
            int64_t trade_id;

            if (trade.bid_no != 0) {
                trade_id = trade.bid_no;

                if (last_order_id_ >= trade_id) {
                    bids_.remove_if([&](type::data::Order& order) {
                        return order.order_id == trade_id;
                        });
                }
                else {
                    late_orders_[trade_id] = trade.qty;
                    //trade_cache_.push_back(trade);
                }
            }
            else {
                trade_id = trade.ask_no;

                if (last_order_id_ >= trade_id) {
                    asks_.remove_if([&](type::data::Order& order) {
                        return order.order_id == trade_id;
                        });
                }
                else {
                    late_orders_[trade_id] = trade.qty;
                    //trade_cache_.push_back(trade);
                }
            }
        }

        inline void OrderBook::on_traded(const type::data::Trade& trade)
        {
            int64_t trade_id = trade.is_buy() ? trade.bid_no : trade.ask_no;
            if (last_order_id_ < trade_id) {
                late_orders_[trade_id] = trade.qty;
                //trade_cache_.push_back(trade);
            }

            if (last_order_id_ >= trade.bid_no) {
                auto it = bids_.begin();
                while (it != bids_.end()) {
                    auto new_it = it;
                    ++it;

                    if (trade.bid_no == new_it->order_id) {
                        new_it->qty -= trade.qty;
                        //if (new_it->qty < 0) {
                        //    fmt::print("bid:{}-----------------------------------------\n", new_it->qty);
                        //}
                        if (new_it->qty <= 0)
                            bids_.erase(new_it);
                    }
                    else if ((new_it->price > trade.price) && (new_it->time < trade.time)) {
                        bids_.erase(new_it);
                    }
                }
            }

            if (last_order_id_ >= trade.ask_no) {
                auto it = asks_.begin();
                while (it != asks_.end()) {
                    auto new_it = it;
                    ++it;
                    if (trade.ask_no == new_it->order_id) {
                        new_it->qty -= trade.qty;
                        //if (new_it->qty < 0) {
                        //    fmt::print("ask:{}-----------------------------------------\n", new_it->qty);
                        //}
                        if (new_it->qty <= 0)
                            asks_.erase(new_it);
                    }
                    else if ((new_it->price < trade.price) && (new_it->time < trade.time)) {
                        asks_.erase(new_it);
                    }
                }
            }
        }

        inline bool OrderBook::trade_supped(type::data::Order& order)
        {
            auto it = late_orders_.find(order.order_id);
            if (it != late_orders_.end()) {
                const auto& order_id = it->first;
                auto qty = it->second;

                qty = std::min(qty, order.qty);
                order.qty -= qty;

                return order.qty <= 0;
            }

            //auto it = trade_cache_.begin();
            //while (it != trade_cache_.end()) {
            //    auto new_it = it;
            //    ++it;

            //    if (new_it->trade_flag == '4') {
            //        if ((new_it->bid_no == order.order_id) || (new_it->ask_no == order.order_id)) {
            //            trade_cache_.erase(new_it);
            //            return true;
            //        }

            //        if ((order.order_id > new_it->bid_no) && (order.order_id > new_it->ask_no)) {
            //            trade_cache_.erase(new_it);
            //            return false;
            //        }
            //    }
            //    else {
            //        if (new_it->bid_no == order.order_id) {
            //            order.qty -= new_it->qty;
            //            new_it->ask_no = 0;
            //        }
            //        else if (new_it->ask_no == order.order_id) {
            //            order.qty -= new_it->qty;
            //            new_it->ask_no = 0;
            //        }
            //        else {
            //            if (order.order_id > new_it->bid_no) {
            //                new_it->bid_no = 0;
            //            }

            //            if (order.order_id > new_it->ask_no) {
            //                new_it->ask_no = 0;
            //            }
            //        }

            //        if (new_it->ask_no == 0 && new_it->bid_no == 0) {
            //            trade_cache_.erase(new_it);
            //        }

            //        if (order.qty <= 0)
            //            return true;
            //    }
            //}
            return false;
        }

        std::string OrderBook::print_order_book(int count_limit) const {
            std::string msg;

            auto ask = get_ask_book();
            auto bid = get_bid_book();

            fmt::print("bids:{}, asks:{}\n", bid.size(), ask.size());

            for (auto it = ask.rbegin(); it != ask.rend(); it++) {
                msg += fmt::format(
                    "{0:^6} | ask | {1:^7} | {2}\n",
                    symbol_.code, it->first, it->second
                );
            }

            msg += fmt::format("-------{}--------\n", last_msg_time_);

            for (const auto& item : bid) {
                msg += fmt::format(
                    "{0:^6} | bid | {1:^7} | {2}\n",
                    symbol_.code, item.first, item.second
                );
            }

            return msg;
        }
    }
}