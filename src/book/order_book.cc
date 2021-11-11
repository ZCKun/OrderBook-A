#include "book/order_book.h"

namespace x2h::book
{
    OrderBook::OrderBook(const Symbol &symbol)
            : symbol_(symbol)
    {}

    OrderBook::~OrderBook() = default;

    template<class TOutputStream>
    TOutputStream &operator<<(TOutputStream &stream, const OrderBook &book)
    {
        return stream;
    }

    /*!
     * @brief 添加新 Order 到对应队列
    */
    inline void OrderBook::add_order(type::data::Order &order) noexcept
    {
        if (order.is_buy()) {
            bids_.push_back(order);

            if ((best_bid_.price == 0) || (order.price > best_bid_.price))
                best_bid_ = order;
        } else if (order.is_sell()) {
            asks_.push_back(order);

            if ((best_ask_.price == 0) || (order.price < best_ask_.price))
                best_ask_ = order;
        } else {
            printf("未知Order Side: %c\n", order.side);
        }
    }

    /*!
     * @brief 新的 Order 消息
    */
    void OrderBook::on_order(const type::data::Order &order)
    {
        type::data::Order new_order(order);
        last_msg_time_ = new_order.time;

        if (order.exchange == type::data::Exchange::SH) {
            last_order_id_ = new_order.origin_order_id;
            //! 上证的撤单会通过 Order 回报
            if (new_order.ord_type == static_cast<char>(type::data::sh::OrderType::DEL)) {
                if (new_order.is_buy()) {
                    bids_.remove_if([&](type::data::Order &o) {
                        return o.origin_order_id == new_order.origin_order_id;
                    });
                } else if (new_order.is_sell()) {
                    asks_.remove_if([&](type::data::Order &o) {
                        return o.origin_order_id == new_order.origin_order_id;
                    });
                }
                return;
            }
        } else {
            last_order_id_ = new_order.order_id;
            //! 检查当前 Order 是否是延迟的
            if (trade_supped(new_order)) return;
        }

        match_order(order);
        if (new_order.qty > 0) {
            add_order(new_order);
        }
    }

    /*!
     * @brief 新的 Trade 消息
    */
    void OrderBook::on_trade(const type::data::Trade &trade)
    {
        last_msg_time_ = trade.time;

        if (trade.exchange == type::data::Exchange::SZ && trade.trade_flag == '4') {
            on_cancel(trade);
        } else {
            on_traded(trade);
        }
    }

    /*!
     * @brief 处理撤单
    */
    inline void OrderBook::on_cancel(const type::data::Trade &trade)
    {
        int64_t trade_id;

        if (trade.bid_id != 0) {
            trade_id = trade.bid_id;

            if (last_order_id_ >= trade_id) {
                bids_.remove_if([&](type::data::Order &order) {
                    return order.order_id == trade_id;
                });
            } else {
                late_orders_[trade_id] = trade.qty;
            }
        } else {
            trade_id = trade.ask_id;

            if (last_order_id_ >= trade_id) {
                asks_.remove_if([&](type::data::Order &order) {
                    return order.order_id == trade_id;
                });
            } else {
                late_orders_[trade_id] = trade.qty;
            }
        }
    }

    /*!
     * @brief 处理成交
    */
    inline void OrderBook::on_traded(const type::data::Trade &trade)
    {
        int64_t traded_id = trade.is_buy() ? trade.bid_id : trade.ask_id;
        if (last_order_id_ < traded_id) {
            late_orders_[traded_id] = trade.qty;
        }

        //! 按时间、价格、order_id来删减 Order
        /*if (last_order_id_ >= trade.bid_id)*/ {
            auto it = bids_.begin();
            if (trade.exchange == type::data::Exchange::SH) {
                while (it != bids_.end()) {
                    auto new_it = it;
                    ++it;

                    auto qty1 = new_it->qty;
                    if (trade.bid_id == new_it->origin_order_id) {
                        if (trade.business_no < new_it->business_no) continue;
                        new_it->qty -= trade.qty;
                        if (new_it->qty <= 0)
                            bids_.erase(new_it);
                    } else if ((new_it->price >= trade.price && new_it->time < trade.time)) {
                        bids_.erase(new_it);
                    }
                }
            } else {
                while (it != bids_.end()) {
                    auto new_it = it;
                    ++it;

                    if (trade.bid_id == new_it->order_id) {
                        new_it->qty -= trade.qty;
                        if (new_it->qty <= 0)
                            bids_.erase(new_it);
                    } else if ((new_it->price > trade.price) && (new_it->time < trade.time)) {
                        bids_.erase(new_it);
                    }
                }
            }
        }

        /*if (last_order_id_ >= trade.ask_id)*/ {
            auto it = asks_.begin();
            if (trade.exchange == type::data::Exchange::SH) {
                while (it != asks_.end()) {
                    auto new_it = it;
                    ++it;

                    auto qty1 = new_it->qty;
                    if (trade.ask_id == new_it->origin_order_id) {
                        if (trade.business_no < new_it->business_no) continue;
                        new_it->qty -= trade.qty;
                        if (new_it->qty <= 0)
                            asks_.erase(new_it);
                    } else if ((new_it->price <= trade.price) && (new_it->time < trade.time)) {
                        asks_.erase(new_it);
                    }
                }
            } else {
                while (it != asks_.end()) {
                    auto new_it = it;
                    ++it;

                    if (trade.ask_id == new_it->order_id) {
                        new_it->qty -= trade.qty;
                        if (new_it->qty <= 0)
                            asks_.erase(new_it);
                    } else if ((new_it->price < trade.price) && (new_it->time < trade.time)) {
                        asks_.erase(new_it);
                    }
                }
            }
        }
    }

    /*!
     * @brief 处理迟到的 Order
     * @param order
     * @return 当前 order 是否已被处理
    */
    inline bool OrderBook::trade_supped(type::data::Order &order)
    {
        auto it = late_orders_.find(order.order_id);
        if (it != late_orders_.end()) {
            const auto &order_id = it->first;
            auto qty = it->second;

            qty = std::min(qty, order.qty);
            order.qty -= qty;

            return order.qty <= 0;
        }

        return false;
    }

    /*!
     * @brief 撮合 Order
     * @param order 最新 Order
     * @return
    */
    void OrderBook::match_order(const type::data::Order &order) noexcept
    {
        if (order.is_sell()) {
            match_ask_book();
        } else if (order.is_buy()) {
            match_bid_book();
        }
    }

    inline void OrderBook::match_bid_book()
    {
        //! sorted
        bid_book_snapshot_ = get_bid_book();
        ask_book_snapshot_ = get_ask_book();

        for (auto bid_it = bid_book_snapshot_.begin(); bid_it != bid_book_snapshot_.end();) {

            const auto &bid_price = bid_it->first;
            auto &bid_qty = bid_it->second;

            for (auto ask_it = ask_book_snapshot_.begin(); bid_qty > 0 && ask_it != ask_book_snapshot_.end();) {

                const auto &ask_price = ask_it->first;
                auto &ask_qty = ask_it->second;

                if (ask_price <= bid_price) {
                    auto qty = std::min(ask_qty, bid_qty);
                    ask_qty -= qty;
                    bid_qty -= qty;

                }
                if (ask_qty == 0) {
                    ask_book_snapshot_.erase(ask_it++);
                } else {
                    ++ask_it;
                }
            }

            if (bid_qty == 0) {
                bid_book_snapshot_.erase(bid_it++);
            } else {
                ++bid_it;
            }
        }
    }

    inline void OrderBook::match_ask_book()
    {
        bid_book_snapshot_ = get_bid_book();
        ask_book_snapshot_ = get_ask_book();

        for (auto ask_it = ask_book_snapshot_.begin(); ask_it != ask_book_snapshot_.end();) {

            const auto &ask_price = ask_it->first;
            auto &ask_qty = ask_it->second;

            for (auto bid_it = bid_book_snapshot_.begin(); ask_qty > 0 && bid_it != bid_book_snapshot_.end();) {

                const auto &bid_price = bid_it->first;
                auto &bid_qty = bid_it->second;

                if (bid_price >= ask_price) {
                    auto qty = std::min(ask_qty, bid_qty);
                    ask_qty -= qty;
                    bid_qty -= qty;
                }
                if (bid_qty == 0) {
                    bid_book_snapshot_.erase(bid_it++);
                } else {
                    ++bid_it;
                }
            }

            if (ask_qty == 0) {
                ask_book_snapshot_.erase(ask_it++);
            } else {
                ++ask_it;
            }
        }
    }

#if 0
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
#endif
}
