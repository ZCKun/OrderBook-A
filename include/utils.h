#pragma once

#include <ctime>
#include <string>
#include <random>
#include <climits>
#include <fstream>
#include <filesystem>
#include <unordered_map>
#include <vector>
#include <thread>

#include "fmt/format.h"

#ifdef __APPLE__
#include "spdlog/spdlog.h"
#include "spdlog/async.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/rotating_file_sink.h"
#else

#endif

#define MILLISECONDS 1'00'00'00'000
#define MICROSECONDS 1'00'00'00'000'000
#define NANOSECONDS 1'00'00'00'000'000'000

#define DOUBLE_EQ(a, b) fabs(a - b) < 1e-6

namespace x2h
{
    namespace log
    {

        enum Level : uint8_t
        {
            DBG = 0,
            INF,
            WRN,
            ERR,
            OFF
        };
    }

    using logLevel = log::Level;

    namespace util
    {

        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_int_distribution<> ms_dis(5, 20);

        inline int get_rand_ms()
        {
            return ms_dis(gen);
        }

        inline int count_digit(long long n)
        {
            int count = 0;
            while (n != 0) {
                n = n / 10;
                ++count;
            }
            return count;
        }

        template<typename T>
        inline int64_t now_time()
        {
            return std::chrono::duration_cast<T>(
                    std::chrono::system_clock::now().time_since_epoch()
            ).count();
        }

        inline void tokenize(std::string const &str, const char delim,
                             std::unordered_map<std::string, int> &out)
        {
            size_t start;
            size_t end = 0;

            while ((start = str.find_first_not_of(delim, end)) != std::string::npos) {
                end = str.find(delim, start);
                out[str.substr(start, end - start)] = 0;
            }
        }

        inline std::unordered_map<std::string, int>
        read_list(const std::string &fp)
        {
            std::unordered_map<std::string, int> list_{};
            if (!fp.empty()) {
                std::ifstream is(fp);

                if (is.is_open()) {
                    std::string line;
                    std::getline(is, line);
                    if (!line.empty()) {
                        util::tokenize(line, ',', list_);
                    }
                } else {
                    auto msg = fmt::format("文件 {} 打开失败", fp);
                    fmt::print("{}\n", msg);
                }
            }

            return list_;
        }

        template<typename T>
        inline int64_t file_last_write_time(const std::string &file_path)
        {
            if (!std::filesystem::exists(file_path))
                return -1;
            auto t = std::filesystem::last_write_time(file_path);
            auto elapse = std::chrono::duration_cast<T>(
                    std::filesystem::file_time_type::clock::now().time_since_epoch() -
                    std::chrono::system_clock::now().time_since_epoch()).count();
            auto a = std::chrono::duration_cast<T>(t.time_since_epoch()).count();

            return a - elapse;
        }

        /*!
         * (价格 - 昨收价) / 昨收价 * 100
         * @brief 计算给定价格当前所处的涨跌幅度百分比
         * @param price 需要计算的价格
         * @param pre_close_price 昨收价
         * @return 涨跌幅度百分比
        */
        inline double upper_limit_percent(double price, double pre_close_price)
        {
            return (price - pre_close_price) / pre_close_price * 100.0;
        }

        /*!
         * (幅度百分比 / 100 + 1) * 昨收价
         * @brief 根据给定涨跌幅度百分比计算对应价格
         * @param percent 需要计算的涨跌幅度百分比
         * @param pre_close_price 昨收价
         * @return
        */
        inline double price_from_percent(double percent, double pre_close_price)
        {
            return (percent / 100.0 + 1.0) * pre_close_price;
        }

        /*!
         * @brief 上证股票涨停价计算
         * @param pre_close_price 昨收价
         * @return
        */
        inline double sh_upper_limit_price(double pre_close_price)
        {
            return std::round(pre_close_price * 1.1 * 100.0) / 100.0;
        }

        /*!
         * @brief 上证股票跌停价计算
         * @param pre_close_price 昨收价
         * @return
        */
        inline double sh_lower_limit_price(double pre_close_price)
        {
            return pre_close_price * .9;
        }

        /*!
         * @brief 深证股票验证
         * @param head 股票头两个字符组成的字符串
         * @return
        */
        inline bool is_sz(const std::string &head)
        {
            return head == "30" || head == "00";
        }

        /*!
         * @brief 上证股票验证
         * @param head 股票头两个字符组成的字符串
         * @return
        */
        inline bool is_sh(const std::string &head)
        {
            return head == "60" || head == "68";
        }

        /* code from http://git.musl-libc.org/cgit/musl/tree/src/time/__secs_to_tm.c?h=v0.9.15 */
        /* 2000-03-01 (mod 400 year, immediately after feb29 */
#define LEAPOCH (946684800LL + 86400*(31+29))

#define DAYS_PER_400Y (365*400 + 97)
#define DAYS_PER_100Y (365*100 + 24)
#define DAYS_PER_4Y   (365*4   + 1)

        [[maybe_unused]] inline int secs_to_tm(long long t, struct tm *tm)
        {
            long long days, secs;
            int remdays, remsecs, remyears;
            int qc_cycles, c_cycles, q_cycles;
            int years, months;
            int wday, yday, leap;
            static const char days_in_month[] = {31, 30, 31, 30, 31, 31, 30, 31, 30, 31, 31, 29};

            /* Reject time_t values whose year would overflow int */
            if (t < INT_MIN * 31622400LL || t > INT_MAX * 31622400LL)
                return -1;

            secs = t - LEAPOCH;
            days = secs / 86400;
            remsecs = static_cast<int>(secs % 86400);
            if (remsecs < 0) {
                remsecs += 86400;
                days--;
            }

            wday = static_cast<int>((3 + days) % 7);
            if (wday < 0) wday += 7;

            qc_cycles = static_cast<int>(days / DAYS_PER_400Y);
            remdays = static_cast<int>(days % DAYS_PER_400Y);
            if (remdays < 0) {
                remdays += DAYS_PER_400Y;
                qc_cycles--;
            }

            c_cycles = remdays / DAYS_PER_100Y;
            if (c_cycles == 4) c_cycles--;
            remdays -= c_cycles * DAYS_PER_100Y;

            q_cycles = remdays / DAYS_PER_4Y;
            if (q_cycles == 25) q_cycles--;
            remdays -= q_cycles * DAYS_PER_4Y;

            remyears = remdays / 365;
            if (remyears == 4) remyears--;
            remdays -= remyears * 365;

            leap = !remyears && (q_cycles || !c_cycles);
            yday = remdays + 31 + 28 + leap;
            if (yday >= 365 + leap) yday -= 365 + leap;

            years = remyears + 4 * q_cycles + 100 * c_cycles + 400 * qc_cycles;

            for (months = 0; days_in_month[months] <= remdays; months++)
                remdays -= days_in_month[months];

            if (years + 100 > INT_MAX || years + 100 < INT_MIN)
                return -1;

            tm->tm_year = years + 100;
            tm->tm_mon = months + 2;
            if (tm->tm_mon >= 12) {
                tm->tm_mon -= 12;
                tm->tm_year++;
            }
            tm->tm_mday = remdays + 1;
            tm->tm_wday = wday;
            tm->tm_yday = yday;

            tm->tm_hour = remsecs / 3600;
            tm->tm_min = remsecs / 60 % 60;
            tm->tm_sec = remsecs % 60;

            return 0;
        }

        struct Milliseconds
        {
            static inline std::tuple<int64_t, std::string> parse(int64_t ms)
            {
                int64_t t = ms / 1'000;
                int64_t suffix = ms % 1'000;
                std::string suffix_s;
                if (suffix - 1 == -1) { suffix_s = "000"; }
                else if (suffix - 10 < 0) { suffix_s = fmt::format("00{}", suffix); }
                else if (suffix - 100 < 0) { suffix_s = fmt::format("0{}", suffix); }
                else { suffix_s = std::to_string(suffix); }

                return std::make_tuple(t, suffix_s);
            }
        };

        struct Microseconds
        {
            static inline std::tuple<int64_t, std::string> parse(int64_t ms)
            {
                std::string suffix_s;
                int64_t t = ms / 1'000'000;
                int64_t suffix = ms % 1'000'000;

                if (suffix - 1 == -1) { suffix_s = "000000"; }
                else if (suffix - 10 < 0) { suffix_s = fmt::format("00000{}", suffix); }
                else if (suffix - 100 < 0) { suffix_s = fmt::format("0000{}", suffix); }
                else if (suffix - 1'000 < 0) { suffix_s = fmt::format("000{}", suffix); }
                else if (suffix - 10'000 < 0) { suffix_s = fmt::format("00{}", suffix); }
                else if (suffix - 100'000 < 0) { suffix_s = fmt::format("0{}", suffix); }
                else { suffix_s = std::to_string(suffix); }

                return std::make_tuple(t, suffix_s);
            }
        };

        struct Nanoseconds
        {
            static inline std::tuple<int64_t, std::string> parse(int64_t ms)
            {
                std::string suffix_s;
                int64_t t = ms / 1'000'000'000;
                int64_t suffix = ms % 1'000'000'000;

                if (suffix - 1 == -1) { suffix_s = "000000000"; }
                else if (suffix - 10 < 0) { suffix_s = fmt::format("00000000{}", suffix); }
                else if (suffix - 100 < 0) { suffix_s = fmt::format("0000000{}", suffix); }
                else if (suffix - 1'000 < 0) { suffix_s = fmt::format("000000{}", suffix); }
                else if (suffix - 10'000 < 0) { suffix_s = fmt::format("00000{}", suffix); }
                else if (suffix - 100'000 < 0) { suffix_s = fmt::format("0000{}", suffix); }
                else if (suffix - 1'000'000 < 0) { suffix_s = fmt::format("000{}", suffix); }
                else if (suffix - 10'000'000 < 0) { suffix_s = fmt::format("00{}", suffix); }
                else if (suffix - 100'000'000 < 0) { suffix_s = fmt::format("0{}", suffix); }
                else { suffix_s = std::to_string(suffix); }

                return std::make_tuple(t, suffix_s);
            }
        };


        /*! cpu usage: ~ 10 us
         * @brief 转换微秒级的 unix time 为time
         * @param ms 待转换的 unix time
         * @param save_ns 是否保留纳秒部分
         * @return
        */
        template<typename T>
        inline int64_t convert_ts_to_time(int64_t ms, T p)
        {
            auto[t, suffix_s] = p.parse(ms);

            std::tm tm{};
            if (secs_to_tm(t, &tm) == 0) {
                const char *min_append = (tm.tm_min - 10 < 0) ? "0" : "";
                const char *sec_append = (tm.tm_sec - 10 < 0) ? "0" : "";
                auto time_str = fmt::format("{}{}{}{}{}{}", tm.tm_hour + 8, min_append, tm.tm_min, sec_append,
                                            tm.tm_sec,
                                            suffix_s);
                return std::stoll(time_str);
            }

            return -1;
        }

        inline std::string time_to_str(int64_t time_diff)
        {
            int64_t second_ms = 1'000;
            int64_t minute_ms = second_ms * 60;

            std::string time_diff_str;
            if (time_diff >= minute_ms) {
                double time_diff_min = static_cast<double>(time_diff) / static_cast<double>(minute_ms);
                time_diff_str = fmt::format(
                        FMT_STRING("{:.2f}min"),
                        time_diff_min
                );
            } else if (time_diff >= second_ms) {
                double time_diff_s = static_cast<double>(time_diff) / static_cast<double>(second_ms);
                time_diff_str = fmt::format(
                        FMT_STRING("{:.2f}s"),
                        time_diff_s
                );
            } else {
                time_diff_str = fmt::format(
                        FMT_STRING("{}ms"),
                        time_diff
                );
            }

            return time_diff_str;
        }

        inline bool is_stock_code(const std::string &symbol_code)
        {
            std::string symbol_head(symbol_code.c_str(), 2);
            //return symbol_code.size() == 6 && (symbol_head == "30" || symbol_head == "00");
            //return symbol_code.size() == 6 && (symbol_head == "60" || symbol_head == "68");
            return symbol_code.size() == 6 && (symbol_head == "30" || symbol_head == "00"
                                               || symbol_head == "60" || symbol_head == "68");
        }

        inline int cpu_affinity(uint32_t cpu)
        {
            int status = -1;
#if defined(__linux__)
            cpu_set_t mask;

            CPU_ZERO(&mask);
            CPU_SET(cpu, &mask);
            status = sched_setaffinity(0, sizeof(mask), &mask);
#endif
            return status;
        }

        inline int cpu_affinity_of_thread(std::thread& t, uint32_t core_num)
        {
            int status = -1;
#ifdef __linux__
            cpu_set_t cpu_set;
            CPU_ZERO(&cpu_set);
            CPU_SET(core_num, &cpu_set);
            status = pthread_setaffinity_np(t.native_handle(), sizeof(cpu_set), &cpu_set);
#endif
            return status;
        }

    }
}
