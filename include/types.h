#pragma once

#include <list>

namespace x2h::type::data
{
    enum class Exchange : uint8_t
    {
        SH,
        SZ
    };

    struct Order
    {
        /* 股票代码 */
        char ticker[20];
        /* 消息接收时间 */
        int64_t rec_time;
        /* 下单时间 */
        int64_t time;
        /* 频道代码 */
        int32_t channel_no;
        /* 委托序号 */
        int64_t order_id;
        /* 委托价格 */
        double price;
        /* 委托数量 */
        int64_t qty;
        /* '1':买; '2':卖; 'G':借入; 'F':出借 */
        char side;
        /* 订单类别: '1': 市价; '2': 限价; 'U': 本方最优 */
        char ord_type;
        /* 原始订单号. 深证无意义, 上证表示order id */
        int64_t origin_order_id;
        /* 业务序号 */
        int64_t business_no;

        Exchange exchange;

        Order() noexcept = default;

        Order(const Order &) noexcept = default;

        Order(Order &&) noexcept = default;

        ~Order() noexcept = default;

        Order &operator=(const Order &) noexcept = default;

        Order &operator=(Order &&) noexcept = default;

        [[nodiscard]] bool is_buy() const noexcept
        {
            return (exchange == Exchange::SH) ?
                   side == 'B' : side == '1';
        }

        [[nodiscard]] bool is_sell() const noexcept
        {
            return (exchange == Exchange::SH) ?
                   side == 'S' : side == '2';
        }
    };

    struct Trade
    {
        /* 股票代码 */
        char ticker[20];
        /* 消息接收时间 */
        int64_t rec_time;
        /* 成交时间 */
        int64_t time;
        /* 频道代码 */
        int32_t channel_id;
        /* 委托序号 */
        int64_t trade_id;
        /* 成交价格 */
        double price;
        /* 成交量 */
        int64_t qty;
        /* 成交金额(仅适用上交所) */
        double memory;
        /* 买方订单号 */
        int64_t bid_id;
        /* 卖方订单号 */
        int64_t ask_id;
        /* SH: 内外盘标识('B':主动买; 'S':主动卖; 'N':未知) SZ: 成交标识('4':撤; 'F':成交) */
        char trade_flag;
        Exchange exchange;
        /* 业务序号 */
        int64_t business_no;

        [[nodiscard]] bool is_buy() const noexcept
        {
            return ask_id > bid_id;
        }

        [[nodiscard]] bool is_sell() const noexcept
        {
            return bid_id > ask_id;
        }
    };

    namespace sh
    {
        enum class OrderSide : char
        {
            /* 买 */
            BUY = 'B',
            /* 卖 */
            SELL = 'S',
        };

        enum class OrderType : char
        {
            /* 增加(下单) */
            ADD = 'A',
            /* 删除(撤单) */
            DEL = 'D',
        };
    }

    namespace sz
    {
        enum class OrderSide : char
        {
            /* 买 */
            BUY = '1',
            /* 卖 */
            SELL = '2',
            /* 借入 */
            BORROW = 'G',
            /* 出借 */
            LOAN = 'F',
        };

        enum class OrderType : char
        {
            /* 市价 */
            MARKET = '1',
            /* 限价 */
            LIMIT = '2',
            /* 本方最优 */
            BETTER = 'U',
        };
    }
}
