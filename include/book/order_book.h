#pragma once

#include <map>
#include <unordered_map>

#include <list>
#include <limits>
#include <cstring>
#include <ctime>
#include "containers/fast_hash.h"
#include "types.h"
#include "symbol.h"

namespace x2h::book
{
    class OrderBook
    {
    private:
        using OrderQueue = std::list<type::data::Order>;

        Symbol symbol_;
        int64_t last_order_id_{};
        int64_t last_msg_time_{};

        /* 最优买卖 Order */
        type::data::Order best_bid_{};
        type::data::Order best_ask_{};

        OrderQueue bids_;
        OrderQueue asks_;

        std::unordered_map<int64_t, int64_t, FastHash> late_orders_;

        std::map<double, int64_t, std::greater<>> bid_book_snapshot_;
        std::map<double, int64_t> ask_book_snapshot_;

    public:
        OrderBook() = default;

        explicit OrderBook(const Symbol &symbol);

        ~OrderBook();

        template<class TOutputStream>
        friend TOutputStream &operator<<(TOutputStream &stream, const OrderBook &book);

        explicit operator bool() const noexcept
        { return !empty(); }

        bool empty() const noexcept
        { return size() == 0; }

        size_t size() const noexcept
        { return bids_.size() + asks_.size(); }

        int64_t last_msg_time() const noexcept
        { return last_msg_time_; }

        const Symbol &symbol() const noexcept
        { return symbol_; }

        /*!
         * @brief 最优买单
         * @return
        */
        const type::data::Order &best_bid() const noexcept
        { return best_bid_; }

        /*!
         * @brief 最优卖单
         * @return
        */
        const type::data::Order &best_ask() const noexcept
        { return best_ask_; }

        /*!
         * @brief 获取买队列
         * @return
        */
        const OrderQueue &get_bid_queue() const noexcept
        { return bids_; }

        /*!
         * @brief 获取卖队列
         * @return
        */
        const OrderQueue &get_ask_queue() const noexcept
        { return asks_; }

        void on_order(const type::data::Order &order);

        void on_trade(const type::data::Trade &order);


        const std::map<double, int64_t> &get_ask_book_snapshot() const noexcept
        {
            return ask_book_snapshot_;
        }

        const std::map<double, int64_t, std::greater<>> &get_bid_book_snapshot() const noexcept
        {
            return bid_book_snapshot_;
        }

        std::map<double, int64_t> get_ask_book() const noexcept
        {
            std::map<double, int64_t> ask{};

            for (const auto &item: asks_) {
                ask[item.price] += item.qty;
            }

            return ask;
        }

        std::map<double, int64_t, std::greater<>> get_bid_book() const noexcept
        {
            std::map<double, int64_t, std::greater<>> bid{};

            for (const auto &item: bids_) {
                bid[item.price] += item.qty;
            }

            return bid;
        }

        // std::string print_order_book(int count_limit) const;
        void match_order(const type::data::Order &order) noexcept;

        void match_bid_book();

        void match_ask_book();

    private:
        bool trade_supped(type::data::Order &order);

        void on_cancel(const type::data::Trade &trade);

        void on_traded(const type::data::Trade &trade);

        void add_order(type::data::Order &order) noexcept;
    };
}