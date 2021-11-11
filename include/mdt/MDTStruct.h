//////////////////////////////////////////////////////////////////////////////
/// @file       MDTStruct.h
/// @brief      数据消息结构体定义文件
//////////////////////////////////////////////////////////////////////////////
#ifndef MDT_STRUCT_H_
#define MDT_STRUCT_H_

#include <iostream>
#include "MDTDataType.h"

#pragma pack(8)

/// 买卖档位信息，含价、量、笔数3个信息
struct  _BuySellLevelInfo3
{
    double              Price;                  ///< 价格,3位小数
    unsigned long long  Volume;                 ///< 量
    unsigned int        TotalOrderNo;           ///< 委托笔数
};
typedef struct _BuySellLevelInfo3 BuySellLevelInfo3;

/// 深交所 买卖档位信息，含价、量、笔数3个信息
struct _SZSE_BuySellLevelInfo3
{
    double              Price;                  ///< 价格,6位小数
    double              Volume;                 ///< 量，2位小数
    unsigned long long  TotalOrderNo;           ///< 委托笔数
};
typedef struct _SZSE_BuySellLevelInfo3 SZSE_BuySellLevelInfo3;

/// 买卖档位信息，含价、量信息
struct  _BuySellLevelInfo
{
    double              Price;                  ///< 价格,3位小数
    unsigned long long  Volume;                 ///< 量
};
typedef struct  _BuySellLevelInfo BuySellLevelInfo;

#if 0
/// 大商所 买卖档位信息，含价、量、推导量3个信息
struct  DCE_BuySellLevelInfo3
{
    double              Price;                  ///< 价格,3位小数
    unsigned long long  Volume;                 ///< 量
    unsigned long long  ImplyQty;               ///< 推导量
};
/// 大商所 买卖委托档位信息
struct  DCE_BuySellOrdeLevelInfo
{
    unsigned int        TotalOrderNo;           ///< 委托笔数
};
/// 大商所 分价成交量行情信息
struct  DCE_PriceLevelInfo
{
    double              Price;               ///< 价格
    unsigned long long  PriceBOQty;          ///< 买开数量
    unsigned long long  PriceBEQty;          ///< 买平数量
    unsigned long long  PriceSOQty;          ///< 卖开数量
    unsigned long long  PriceSEQty;          ///< 卖平数量
};
#endif

/// 深交所买卖档位信息
struct _SZSE_BuySellLevelInfo
{
    double              Price;                  ///< 价格
    double              Volume;                 ///< 量
};
typedef struct _SZSE_BuySellLevelInfo SZSE_BuySellLevelInfo;

#define LEVEL_ONE           1       ///< 一档行情
#define LEVEL_FIVE          5       ///< 五档行情
#define LEVEL_TEN           10      ///< 十档行情
#define SETTLE_LEN          10      ///< 结算组代码长度
#define ORDER_LEVEL_FIFTY   50      ///< 50笔委托
#define OTC_ELEMENT_LEN     3       ///< 开盘、交易、收盘竞价参数个数

/// 上交所L1静态数据
struct SSEL1_Static
{
    unsigned long long	   MDTTime;		                 	    ///< 数据接收时间: 从1970/1/1开始的微秒数
    int                 Time;                               ///< 数据生成时间，标识接口中本记录更新时间HHMMSSMMM
    char                Symbol[SYMBOL_LEN];                 ///< 证券代码,
    char                ISINCode[40];                       ///< ISIN代码,
    char                SecurityName[SECURITY_NAME_LEN];    ///< 证券名称,
    char                SecurityEN[SECURITY_EN_LEN];        ///< 英文证券名称,
    char                SymbolUnderlying[SYMBOL_LEN];       ///< 基础证券代码,
    char                MarketType[6];                      ///< 市场种类, ‘ASHR’表示A股市场；‘BSHR’表示B股市场；‘CSHR‘表示国际版市场。
    char                CFICode[6];                         ///< 证券类别, ‘ES’表示股票；‘EU’表示基金；‘D’表示债券；‘RWS’表示权证；‘FF’表示期货。
    char                SecuritySubType[6];                 ///< 证券子类别, 自定义详细证券类别
    char                Currency[5];                        ///< 币种, CNY = 人民币，HKD = 港币
    double              ParValue;                           ///< 面值.债券当前面值，单位元，其他产品取0.000
    long long           TradableNo;                         ///< 可流通未上市数量, 预留
    int                 EndDate;                            ///< 最后交易日期. 对于国债预发行产品，为最后交易日期，格式为YYYYMMDD
    int                 ListingDate;                        ///< 上市日期, 在上交所首日交易日期，YYYYMMDD
    unsigned int        SetNo;                              ///< 产品集编号, 取值范围从1到999,。用来表明产品的一种分组方式，用于在多主机间记性负载均衡分配。该值在一个交易日内不会变化。
    unsigned int        BuyVolumeUnit;                      ///< 买数量单位, 买订单的申报数量必须是该字段的整数倍。
    unsigned int        SellVolumeUnit;                     ///< 卖数量单位, 卖订单的申报数量必须是该字段的整数倍。
    unsigned int        DeclareVolumeFloor;                 ///< 申报量下限, 申报数量下限
    unsigned int        DeclareVolumeCeiling;               ///< 申报量上限, 申报数量上限
    double              PreClosePrice;                      ///< 昨收价, 3位小数；前收盘价格（如有除权除息，为除权除息后的收盘价）；对于货币市场基金实时申赎，取值为0.010
    double              TickSize;                           ///< 最小报价单位, 申报价格的最小变动单位
    char                UpDownLimitType;                    ///< 涨跌幅限制类型, ‘N’表示交易规则3.4.13规定的有涨跌幅限制类型或者权证管理办法第22条规定；‘R'表示交易规则3.4.15和3.4.16规定的无涨跌幅限制类型；’S‘表示回购涨跌幅控制类型。
    double              PriceUpLimit;                       ///< 涨幅价格, 对于N类型涨跌幅限制的产品，该字段当日不会更改，基于前收盘价（已首日上市交易产品为发行价）计算；对于R类型五涨跌幅限制的产品，该字段取开盘时基于参考价格计算的上限价格。
    double              PriceDownLimit;                     ///< 跌幅价格, 计算方式参考涨幅上限价格
    double              XRRatio;                            ///< 除权比例, 每股送股比例；对于国债预发行产品，为保证金比例。
    double              XDAmount;                           ///< 除息金额, 每股分红金额
    char                CrdBuyUnderlying;                   ///< 融资标的标志, ’T‘表示是融资标的证券；’F‘或空表示不是融资标的证券。
    char                CrdSellUnderlying;                  ///< 融券标的标志, ’T‘表示是融拳标的证券；’F‘或空表示不是融券标的证券。
    char                SecurityStatus[20];                 ///< 该字段为20位字符串，每位表示允许对应的业务，无定义则填空格。
                                                            ///< 第0位对应：‘N’表示首日上市。
                                                            ///< 第1位对应：‘D’表示除权。
                                                            ///< 第2位对应：‘R’表示除息。
                                                            ///< 第3位对应：’D’表示国内主板正常交易产品，’S’表示股票风险警示产品，’P’表示退市整理产品，’T’表示退市转让产品，’U’表示优先股产品。
                                                            ///< 第4位对应：’S’表示债券风险警示类。第4位未来改为不启用，此改动暂未实施，具体以交易所通知为准。
                                                            ///< 第5位对应：’L’表示债券投资者适当性要求类。
    int                 TradeDate;                          ///< 市场日期,交易日
    //2.8.2 新加字段
    char                GageUnderlying;                    ///< 担保品标的标志 , ’T‘表示是担保品标的；’F‘或空表示非担保品标的。
    double              CrdBuyBalance;                     ///< 融资余额
    unsigned long long  CrdSellMargin;                     ///< 融券余量
    //3.0 科创板增加字段
    unsigned long long  MktOrdCeiling;                     ///< 市价申报数量上限
    unsigned long long  MktOrdFloor;                       ///< 市价申报数量下限

    //3.2 沪伦通
    unsigned long long          OutstandingShare;               ///市场流通总量
    double                      CumulativeChgVolume;            ///累计变更数量
    char                        CDRSecurityName[201];           ///CDR证券全称
    double                      CDRConvertBase;                 ///CDR证券转换基数
    double                      UnderlyingConvertBase;          ///基础证券转换数
    char                        NameUnderlying[101];             ///基础证券简称
    char                        DepositoryCode[13];             ///存托机构代码
    char                        DepositoryName[41];             ///存托机构简称
    char                        InitialDay[9];                  ///初始流动性生成起始日
    char                        TerminationDay[9];              ///初始流动性生成终止日
    char                        GDRSecurityName[201];           ///GDR证券全称
    long long                   ListingGDRSharesNo;             ///本次上市对应的GDR份额数
    unsigned long long          ListingUnderlyingStockNo;       ///本次上市的基础股票数
    char                        NewSharesListingDate[9];        ///新增股份的上市日期
    char                        NewSharesReason[201];           ///新增股份的产生原因
    char                        GDRSwitchRatio[51];             ///GDR转换比例
    char                        CountryRegisterID[3];           ///公司注册地代码
    char                        MarketSegmentCode[5];           ///板块代码（大）
    char                        MarketSectorCode[5];            ///板块代码（小）
    char                        SEDOL[8];                       ///SEDOL代码
    double                      PreOpenPrice;                   ///开盘价
    double                      PreCloseBuyPrice01;             ///收盘买一价
    double                      SybUndPreClosePrice;            ///收盘价
    double                      PreCloseSellPrice01;            ///收盘卖一价
    unsigned long long          PreTotalVolume;                 ///成交数量（股）
    double                      PreTotalAmount;                 ///成交金额
    unsigned long long          PreTotalNo;                     ///成交笔数
    double                      PreHighPrice;                   ///日内最高价（自动交易）
    double                      PreLowPrice;                    ///日内最低价（自动交易）
    double                      PreNonAutoHighPrice;            ///日内最高价（非自动交易）
    double                      PreNonAutoLowPrice;             ///日内最低价（非自动交易)
    double                      YearHighPrice;                  ///近一年来最高价（自动交易）
    int                         DateYearHighPrice;              ///近一年来最高价出现的日期（自动交易）
    double                      YearLowPrice;                   ///近一年来最低价（自动交易）
    int                         DateYearLowPrice;               ///近一年来最低价出现的日期（自动交易）
    double                      YearNonAutoHighPrice;           ///近一年来最高价（非自动交易）
    int                         DateYearNonAutoHighPrice;       ///近一年来最高价出现的日期（非自动交易）
    double                      YearNonAutoLowPrice;            ///近一年来最低价（非自动交易）
    int                         DateYearNonAutoLowPrice;        ///近一年来最低价出现的日期（非自动交易）
    double                      PreAveragePrice;                ///均价
};

/// 上交所L1实时行情
struct SSEL1_Quotation
{
    unsigned long long	   	MDTTime;		                 	///< 数据接收时间: 从1970/1/1开始的微秒数
    long long           	Reserved;                    		///< 保留
    int                 	Time;                               ///< 数据生成时间,时间戳143025表示 14:30:25
    char                Symbol[SYMBOL_LEN];                 ///< 证券代码,期权合约的产品代码;唯一标示
    char                SecurityName[SECURITY_NAME_LEN];    ///< 证券简称,UTF-8编码
    double              OpenPrice;                          ///< 开盘价
    double              HighPrice;                          ///< 最高价
    double              LowPrice;                           ///< 最低价
    double              LastPrice;                          ///< 现价
    unsigned long long  TotalNo;                            ///< 成交笔数
    unsigned long long  TotalVolume;                        ///< 成交总量,股票：股;权证：份;债券：手
    double              TotalAmount;                        ///< 成交总额,（元）
    double              PreClosePrice;                      ///< 昨收价
    double              ClosePrice;                         ///< 今收盘价
    union
    {
        BuySellLevelInfo    SellLevel[LEVEL_FIVE];      ///< 五档卖行情
        struct
        {
            double              SellPrice01;            ///< 申卖价1
            unsigned long long  SellVolume01;           ///< 申卖量1
            double              SellPrice02;            ///< 申卖价2
            unsigned long long  SellVolume02;           ///< 申卖量2
            double              SellPrice03;            ///< 申卖价3
            unsigned long long  SellVolume03;           ///< 申卖量3
            double              SellPrice04;            ///< 申卖价4
            unsigned long long  SellVolume04;           ///< 申卖量4
            double              SellPrice05;            ///< 申卖价5
            unsigned long long  SellVolume05;           ///< 申卖量5
        };
    };
    union
    {
        BuySellLevelInfo    BuyLevel[LEVEL_FIVE];        ///< 五档买行情
        struct
        {
            double              BuyPrice01;             ///< 申买价1
            unsigned long long  BuyVolume01;            ///< 申买量1
            double              BuyPrice02;             ///< 申买价2
            unsigned long long  BuyVolume02;            ///< 申买量2
            double              BuyPrice03;             ///< 申买价3
            unsigned long long  BuyVolume03;            ///< 申买量3
            double              BuyPrice04;             ///< 申买价4
            unsigned long long  BuyVolume04;            ///< 申买量4
            double              BuyPrice05;             ///< 申买价5
            unsigned long long  BuyVolume05;            ///< 申买量5
        };
    };
    double              NAV;                                ///< 基金T-1日累计净值,四位小数
    double              IOPV;                               ///< ETF净值估值
    char                SecurityPhaseTag[PHRASE_TAG_LEN];   ///< 该字段为8位字符串，左起每位表示特定的含义，无定义则填空格。
                                                            ///< 第1位：‘S’表示启动（开市前）时段，‘C’表示集合竞价时段，‘T’表示连续交易时段，‘E’表示闭市时段，‘P’表示产品停牌，‘M’表示可恢复交易的熔断时段（盘中集合竞价），‘N’表示不可恢复交易的熔断时段（暂停交易至闭市），‘U’表示收盘集合竞价时段。
                                                            ///< 第2位：‘0’表示此产品不可正常交易，‘1’表示此产品可正常交易，无意义填空格。
                                                            ///< 第3位：‘0’表示未上市，‘1’表示已上市。
                                                            ///< 第4位：‘0’表示此产品在当前时段不接受进行新订单申报，‘1’ 表示此产品在当前时段可接受进行新订单申报。无意义填空格。
    int                 SecurityType;                       ///< 证券类别代码，1表示指数行情数据； 2表示股票（ A、 B 股）行情数据；3表示债券行情数据；4表示基金行情数据；
};

/// 上交所指数通数据
struct SSE_IndexPress
{
    unsigned long long	   	MDTTime;		                 	///< 数据接收时间: 从1970/1/1开始的微秒数
    long long           	Reserved;                    		///< 保留
    int                 TradeDate;                          ///< 交易日,日期的格式为“YYYYMMDD”
    int                 ActionDay;                          ///< 业务发生日,行情文件所代表的自然日期（北京时间），内容为被用于计算的那天的自然日期（北京时间） 日期的格式为“ YYYYMMDD”
    int                 Time;                               ///< 数据生成时间，行情文件的更新时间戳（北京时间），格式为“HHMMSS”
    char                Symbol[SYMBOL_LEN];                 ///< 指数代码
    char                SecurityName[40];                   ///< 指数简称
    char                MarketType[6];                      ///< 市场代码 0：全球；1：上证所； 2：深交所； 3：沪深；4：香港； 5：亚太；
    double              LastPrice;                          ///< 最新价,当日开盘值，当前交易日开盘指数值。 初始值为 0.0000。 当值为 0.0000时，说明指数未开盘
    double              OpenPrice;                          ///< 开盘价
    double              HighPrice;                          ///< 最高价
    double              LowPrice;                           ///< 最低价
    double              ClosePrice;                         ///< 今收盘价,当前交易日收盘值。初始值为 0.0000。当值不为 0.0000时，说明指数已收盘
    double              PreClosePrice;                      ///< 昨收价
    double              PriceUpdown1;                       ///< 涨跌 LastPrice-PreClosePrice
    double              UpDownRate;                         ///< 涨跌幅
    unsigned long long  TotalVolume;                        ///< 成交总量,单位：股
    double              TotalAmount;                        ///< 成交金额,（万元）
    double              ExchangeRate;                       ///< 汇率，该汇率在盘中时为0.00000000，收盘后，该汇率值为该指数收盘时计算指数所使用的汇率
    char                Currency[5];                        ///< 币种, 0：人民币； 1：港币； 2：美元； 3：台币； 4：日元
    int                 DisplayNum;                         ///< 指数展示序号,展示指数的顺序按指数展示序号进行排列
    double              ClosePrice2;                        ///< 当日收盘值2，若该指数为全球指数，该收盘值为当日亚太区收盘值。初始值为0.0000。当值不为0.0000时，说明指数亚太区已收盘
    double              ClosePrice3;                        ///< 当日收盘值3，若该指数为全球指数，该收盘值为当日欧洲区收盘值。初始值为0.0000。当值不为0.0000时，说明指数欧洲区已收盘
};

/// 上交所L2静态数据
struct SSEL2_Static
{
    unsigned long long	   	MDTTime;		                 	///< 数据接收时间: 从1970/1/1开始的微秒数
    long long           	Reserved;                    		///< 保留
    int                 Time;                               ///< 数据生成时间，标识接口中本记录更新时间HHMMSSMMM
    char                Symbol[SYMBOL_LEN];                 ///< 证券代码, 
    char                ISINCode[40];                       ///< ISIN代码,
    char                SecurityName[SECURITY_NAME_LEN];    ///< 证券名称,
    char                SecurityEN[SECURITY_EN_LEN];        ///< 英文证券名称, 
    char                SymbolUnderlying[SYMBOL_LEN];       ///< 基础证券代码, 
    char                MarketType[6];                      ///< 市场种类, ‘ASHR’表示A股市场；‘BSHR’表示B股市场；‘CSHR‘表示国际版市场。
    char                CFICode[6];                         ///< 证券类别, ’ES'表示股票；‘EU’表示基金；‘D’表示债券；‘RWS’表示权证；‘FF’表示期货。
    char                SecuritySubType[6];                 ///< 证券子类别, 自定义详细证券类别
    char                Currency[5];                        ///< 币种, CNY = 人民币，HKD = 港币
    double              ParValue;                           ///< 面值,债券当前面值，单位元，其他产品取0.000
    long long           TradableNo;                         ///< 可流通未上市数量, 预留
    int                 EndDate;                            ///< 最后交易日期,对于国债预发行产品，为最后交易日期，格式为YYYYMMDD
    int                 ListingDate;                        ///< 上市日期, 在上交所首日交易日期，YYYYMMDD
    unsigned int        SetNo;                              ///< 产品集编号, 取值范围从1到999,。用来表明产品的一种分组方式，用于在多主机间记性负载均衡分配。该值在一个交易日内不会变化。
    unsigned int        BuyVolumeUnit;                      ///< 买数量单位, 买订单的申报数量必须是该字段的整数倍。
    unsigned int        SellVolumeUnit;                     ///< 卖数量单位, 卖订单的申报数量必须是该字段的整数倍。
    unsigned int        DeclareVolumeFloor;                 ///< 申报量下限, 申报数量下限
    unsigned int        DeclareVolumeCeiling;               ///< 申报量上限, 申报数量上限
    double              PreClosePrice;                      ///< 昨收价, 3位小数；前收盘价格（如有除权除息，为除权除息后的收盘价）；对于货币市场基金实时申赎，取值为0.010
    double              TickSize;                           ///< 最小报价单位, 申报价格的最小变动单位
    char                UpDownLimitType;                    ///< 涨跌幅限制类型, ‘N’表示交易规则3.4.13规定的有涨跌幅限制类型或者权证管理办法第22条规定；‘R'表示交易规则3.4.15和3.4.16规定的无涨跌幅限制类型；’S‘表示回购涨跌幅控制类型。
    double              PriceUpLimit;                       ///< 涨幅价格, 对于N类型涨跌幅限制的产品，该字段当日不会更改，基于前收盘价（已首日上市交易产品为发行价）计算；对于R类型五涨跌幅限制的产品，该字段取开盘时基于参考价格计算的上限价格。
    double              PriceDownLimit;                     ///< 跌幅价格, 计算方式参考涨幅上限价格
    double              XRRatio;                            ///< 除权比例, 每股送股比例；对于国债预发行产品，为保证金比例。
    double              XDAmount;                           ///< 除息金额, 每股分红金额
    char                CrdBuyUnderlying;                   ///< 融资标的标志, ’T‘表示是融资标的证券；’F‘或空表示不是融资标的证券。
    char                CrdSellUnderlying;                  ///< 融券标的标志, ’T‘表示是融拳标的证券；’F‘或空表示不是融券标的证券。
    char                SecurityStatus[20];                 ///< 产品状态标识, 第0位对应：‘N’表示首日上市；第1位对应：‘D’表示除权；第2位对应：‘R'表示除息；第3位对应：‘D‘表示国内主板正常交易产品，‘S’表示风险警示产品，‘P’表示退市整理产品。
    unsigned int        SampleNo;                           ///< 样本数量, 指数当前的样本数量
    double              SampleAvgPrice;                     ///< 样本均价, 指数当前样本的均价,市价总值/发行股本,若该指标不统计则输出 N/A
    double              TradeAmount;                        ///< 成交金额, 指数当前样本的当日成交金额（单位：亿元）
    double              AvgCapital;                         ///< 平均股本, 指数当前样本的平均股本,（算术平均，单位：亿股）,若该指标不统计则输出 N/A
    double              TotalMarketValue;                   ///< 总市值, 指数当前样本的总市值汇总 （算术和， 单位： 万亿元）,若该指标不统计则输出 N/A
    double              MarketValueRatio;                   ///< 占比%, 指数当前样本的总市值占上证综指全样本的总市值,百分比,若该指标不统计则输出 N/A
    double              StaticPERatio;                      ///< 静态市盈率, 指数当前样本的静态市盈率。公式：合计（人民币收盘价*发行量） /合计（每股收益*发行量）,若该指标未统计则输出 N/A
    char                IndexLevelStatus[20];               ///< 指数级别标识, 前 5 位为指数排序数值，最后一位即指数级别信息：
                                                            ///< 1 为重点指数
                                                            ///< 2 为全貌指数
                                                            ///< 其他可根据需要扩展。
    int                 TradeDate;                          ///< 市场日期,交易日 YYYYMMDD
    //2.8.2 新加字段
    char                GageUnderlying;                    ///< 担保品标的标志 , ’T‘表示是担保品标的；’F‘或空表示非担保品标的。
    double              CrdBuyBalance;                      ///< 融资余额
    unsigned long long  CrdSellMargin;                      ///< 融券余量
    //3.0 科创板增加字段
    unsigned long long  MktOrdCeiling;                     ///< 市价申报数量上限
    unsigned long long  MktOrdFloor;                       ///< 市价申报数量下限

    //3.2 沪伦通
    unsigned long long          OutstandingShare;               ///市场流通总量
    double                      CumulativeChgVolume;            ///累计变更数量
    char                        CDRSecurityName[201];           ///CDR证券全称
    double                      CDRConvertBase;                 ///CDR证券转换基数
    double                      UnderlyingConvertBase;          ///基础证券转换数
    char                        NameUnderlying[101];            ///基础证券简称
    char                        DepositoryCode[13];             ///存托机构代码
    char                        DepositoryName[41];             ///存托机构简称
    char                        InitialDay[9];                  ///初始流动性生成起始日
    char                        TerminationDay[9];              ///初始流动性生成终止日
    char                        GDRSecurityName[201];           ///GDR证券全称
    long long                   ListingGDRSharesNo;             ///本次上市对应的GDR份额数
    unsigned long long          ListingUnderlyingStockNo;       ///本次上市的基础股票数
    char                        NewSharesListingDate[9];        ///新增股份的上市日期
    char                        NewSharesReason[201];           ///新增股份的产生原因
    char                        GDRSwitchRatio[51];             ///GDR转换比例
    char                        CountryRegisterID[3];           ///公司注册地代码
    char                        MarketSegmentCode[5];           ///板块代码（大）
    char                        MarketSectorCode[5];            ///板块代码（小）
    char                        SEDOL[8];                      ///SEDOL代码
    double                      PreOpenPrice;                   ///开盘价
    double                      PreCloseBuyPrice01;            ///收盘买一价
    double                      SybUndPreClosePrice;            ///收盘价
    double                      PreCloseSellPrice01;           ///收盘卖一价
    unsigned long long          PreTotalVolume;                 ///成交数量（股）
    double                      PreTotalAmount;                 ///成交金额
    unsigned long long          PreTotalNo;                     ///成交笔数
    double                      PreHighPrice;                   ///日内最高价（自动交易）
    double                      PreLowPrice;                    ///日内最低价（自动交易）
    double                      PreNonAutoHighPrice;            ///日内最高价（非自动交易）
    double                      PreNonAutoLowPrice;             ///日内最低价（非自动交易
    double                      YearHighPrice;                  ///近一年来最高价（自动交易）
    int                         DateYearHighPrice;              ///近一年来最高价出现的日期（自动交易）
    double                      YearLowPrice;                   ///近一年来最低价（自动交易）
    int                         DateYearLowPrice;               ///近一年来最低价出现的日期（自动交易）
    double                      YearNonAutoHighPrice;           ///近一年来最高价（非自动交易）
    int                         DateYearNonAutoHighPrice;       ///近一年来最高价出现的日期（非自动交易）
    double                      YearNonAutoLowPrice;            ///近一年来最低价（非自动交易）
    int                         DateYearNonAutoLowPrice;        ///近一年来最低价出现的日期（非自动交易）
    double                      PreAveragePrice;                ///均价
    // 3.10 新增中文证券名称
    char                        SecurityNameEx[60];            ///中文证券名称（长）
};
typedef struct SSEL2_Static SSEL2_Static;

/// 上交所L2实时行情
struct SSEL2_Quotation
{
    unsigned long long	   	MDTTime;		                 	///< 数据接收时间: 从1970/1/1开始的微秒数
    long long           	Reserved;                    		///< 保留
    int                 Time;                   ///< 数据生成时间, 最新订单时间（毫秒）;143025001 表示 14:30:25.001
    char                Symbol[SYMBOL_LEN];     ///< 证券代码, 
    double              PreClosePrice;          ///< 昨收价, 
    double              OpenPrice;              ///< 开盘价, 
    double              HighPrice;              ///< 最高价, 
    double              LowPrice;               ///< 最低价, 
    double              LastPrice;              ///< 现价, 
    double              ClosePrice;             ///< 今收盘价, 
    char                TradeStatus[6];         ///< 当前产品状态,
    char                SecurityPhaseTag[PHRASE_TAG_LEN];   ///< 当前品种交易状态
                                                            ///< 该字段为8位字符串，左起每位表示特定的含义，无定义则填空格。
                                                            ///< 第1位：‘S’表示启动（开市前）时段，‘C’表示集合竞价时段，‘T’表示连续交易时段，‘E’表示闭市时段，‘P’表示产品停牌，‘M’表示可恢复交易的熔断时段（盘中集合竞价），‘N’表示不可恢复交易的熔断时段（暂停交易至闭市），‘U’表示收盘集合竞价时段。
                                                            ///< 第2位：‘0’表示此产品不可正常交易，‘1’表示此产品可正常交易，无意义填空格。
                                                            ///< 第3位：‘0’表示未上市，‘1’表示已上市。
                                                            ///< 第4位：‘0’表示此产品在当前时段不接受进行新订单申报，‘1’ 表示此产品在当前时段可接受进行新订单申报。无意义填空格。
    unsigned long long  TotalNo;                ///< 成交笔数, 
    unsigned long long  TotalVolume;            ///< 成交总量, 股票：股;权证：份;债券：手
    double              TotalAmount;            ///< 成交总额, （元）
    unsigned long long  TotalBuyOrderVolume;    ///< 委托买入总量, 股票：股;权证：份;债券：手
    double              WtAvgBuyPrice;          ///< 加权平均委买价, （元）
    double              BondWtAvgBuyPrice;      ///< 债券加权平均委买价, （元）
    unsigned long long  TotalSellOrderVolume;   ///< 委托卖出总量, 
    double              WtAvgSellPrice;         ///< 加权平均委卖价, （元）
    double              BondWtAvgSellPrice;     ///< 债券加权平均委卖价, 
    double              IOPV;                   ///< ETF 净值估值, 
    int                 ETFBuyNo;               ///< ETF 申购笔数, 
    long long           ETFBuyVolume;           ///< ETF 申购量, 
    double              ETFBuyAmount;           ///< ETF 申购额, 
    int                 ETFSellNo;              ///< ETF 赎回笔数, 
    long long           ETFSellVolume;          ///< ETF 赎回量, 
    double              ETFSellAmount;          ///< ETF 赎回额, 
    double              YTM;                    ///< 债券到期收益率, 
    long long           TotalWarrantExecVol;    ///< 权证执行的总数量, 
    double              WarrantDownLimit;       ///< 权证跌停价格, （元）
    double              WarrantUpLimit;         ///< 权证涨停价格, （元）
    int                 WithdrawBuyNo;          ///< 买入撤单笔数, 
    long long           WithdrawBuyVolume;      ///< 买入撤单量, 
    double              WithdrawBuyAmount;      ///< 买入撤单额, 
    int                 WithdrawSellNo;         ///< 卖出撤单笔数, 
    long long           WithdrawSellVolume;     ///< 卖出撤单量, 
    double              WithdrawSellAmount;     ///< 卖出撤单额, 
    int                 TotalBuyNo;             ///< 买入总笔数, 
    int                 TotalSellNo;            ///< 卖出总笔数, 
    int                 MaxBuyDuration;         ///< 买入成交最大等待时间, 
    int                 MaxSellDuration;        ///< 卖出成交最大等待时间, 
    int                 BuyOrderNo;             ///< 买方委托价位数, 
    int                 SellOrderNo;            ///< 卖方委托价位数, 
    unsigned int        SellLevelNo;            ///< 卖盘价位数量, 10档行情，不足时补空
    union
    {
        BuySellLevelInfo3    SellLevel[LEVEL_TEN];          ///< 十档卖行情
        struct
        {
            double              SellPrice01;            ///< 申卖价, 
            unsigned long long  SellVolume01;           ///< 申卖量, 
            unsigned int        TotalSellOrderNo01;     ///< 卖出总委托笔数, 
            double              SellPrice02;            ///< 申卖价, 
            unsigned long long  SellVolume02;           ///< 申卖量, 
            unsigned int        TotalSellOrderNo02;     ///< 卖出总委托笔数, 
            double              SellPrice03;            ///< 申卖价, 
            unsigned long long  SellVolume03;           ///< 申卖量, 
            unsigned int        TotalSellOrderNo03;     ///< 卖出总委托笔数, 
            double              SellPrice04;            ///< 申卖价, 
            unsigned long long  SellVolume04;           ///< 申卖量, 
            unsigned int        TotalSellOrderNo04;     ///< 卖出总委托笔数, 
            double              SellPrice05;            ///< 申卖价, 
            unsigned long long  SellVolume05;           ///< 申卖量, 
            unsigned int        TotalSellOrderNo05;     ///< 卖出总委托笔数, 
            double              SellPrice06;            ///< 申卖价, 
            unsigned long long  SellVolume06;           ///< 申卖量, 
            unsigned int        TotalSellOrderNo06;     ///< 卖出总委托笔数, 
            double              SellPrice07;            ///< 申卖价, 
            unsigned long long  SellVolume07;           ///< 申卖量, 
            unsigned int        TotalSellOrderNo07;     ///< 卖出总委托笔数, 
            double              SellPrice08;            ///< 申卖价, 
            unsigned long long  SellVolume08;           ///< 申卖量, 
            unsigned int        TotalSellOrderNo08;     ///< 卖出总委托笔数, 
            double              SellPrice09;            ///< 申卖价, 
            unsigned long long  SellVolume09;           ///< 申卖量, 
            unsigned int        TotalSellOrderNo09;     ///< 卖出总委托笔数, 
            double              SellPrice10;            ///< 申卖价, 
            unsigned long long  SellVolume10;           ///< 申卖量, 
            unsigned int        TotalSellOrderNo10;     ///< 卖出总委托笔数, 
        };
    };
    unsigned int        SellLevelQueueNo01;                 ///< 卖一档揭示委托笔数, 为 0 表示不揭示
    unsigned int        SellLevelQueue[ORDER_LEVEL_FIFTY];  ///< 卖1档队列,
    unsigned int        BuyLevelNo;                         ///< 买盘价位数量, 10档行情，不足时补空
    union
    {
        BuySellLevelInfo3    BuyLevel[LEVEL_TEN];           ///< 十档买行情
        struct
        {
            double              BuyPrice01;                 ///< 申买价, 
            unsigned long long  BuyVolume01;                ///< 申买量, 股票：股;权证：份;债券：手
            unsigned int        TotalBuyOrderNo01;          ///< 买入总委托笔数, 
            double              BuyPrice02;                 ///< 申买价, 
            unsigned long long  BuyVolume02;                ///< 申买量, 
            unsigned int        TotalBuyOrderNo02;          ///< 买入总委托笔数, 
            double              BuyPrice03;                 ///< 申买价, 
            unsigned long long  BuyVolume03;                ///< 申买量, 
            unsigned int        TotalBuyOrderNo03;          ///< 买入总委托笔数, 
            double              BuyPrice04;                 ///< 申买价, 
            unsigned long long  BuyVolume04;                ///< 申买量, 
            unsigned int        TotalBuyOrderNo04;          ///< 买入总委托笔数, 
            double              BuyPrice05;                 ///< 申买价, 
            unsigned long long  BuyVolume05;                ///< 申买量, 
            unsigned int        TotalBuyOrderNo05;          ///< 买入总委托笔数, 
            double              BuyPrice06;                 ///< 申买价, 
            unsigned long long  BuyVolume06;                ///< 申买量, 
            unsigned int        TotalBuyOrderNo06;          ///< 买入总委托笔数, 
            double              BuyPrice07;                 ///< 申买价, 
            unsigned long long  BuyVolume07;                ///< 申买量, 
            unsigned int        TotalBuyOrderNo07;          ///< 买入总委托笔数, 
            double              BuyPrice08;                 ///< 申买价, 
            unsigned long long  BuyVolume08;                ///< 申买量, 
            unsigned int        TotalBuyOrderNo08;          ///< 买入总委托笔数, 
            double              BuyPrice09;                 ///< 申买价, 
            unsigned long long  BuyVolume09;                ///< 申买量, 
            unsigned int        TotalBuyOrderNo09;          ///< 买入总委托笔数, 
            double              BuyPrice10;                 ///< 申买价, 
            unsigned long long  BuyVolume10;                ///< 申买量, 
            unsigned int        TotalBuyOrderNo10;          ///< 买入总委托笔数, 
        };
    };
    unsigned int        BuyLevelQueueNo01;                  ///< 买一档揭示委托笔数, 为 0 表示不揭示
    unsigned int        BuyLevelQueue[ORDER_LEVEL_FIFTY];   ///< 买1档队列
};

/// 上交所L2指数行情
struct SSEL2_Index
{
    unsigned long long	   	MDTTime;		       	///< 数据接收时间: 从1970/1/1开始的微秒数
    long long           	Reserved;               ///< 保留
    int                 Time;                   ///< 数据生成时间(毫秒), 143025000 表示 14:30:25000
    int                 TradeTime;              ///< 成交时间(毫秒),
    char                Symbol[SYMBOL_LEN];     ///< 证券代码, 
    double              PreClosePrice;          ///< 昨收价, 
    double              OpenPrice;              ///< 开盘价, 
    double              TotalAmount;            ///< 成交总额, 
    double              HighPrice;              ///< 最高价, 
    double              LowPrice;               ///< 最低价, 
    double              LastPrice;              ///< 现价, 
    unsigned long long  TotalVolume;            ///< 成交总量, 手
    double              ClosePrice;             ///< 今收盘价, 
};
typedef struct SSEL2_Index SSEL2_Index;

/// 上交所L2逐笔成交
struct SSEL2_Transaction
{
    unsigned long long	   	MDTTime;		       	///< 数据接收时间: 从1970/1/1开始的微秒数
    long long           	Reserved;              	///< 保留
    int                 TradeTime;              ///< 成交时间(毫秒), 14302506 表示14:30:25.06
    unsigned int        RecID;                  ///< 成交序号, 从 1 开始，按 TradeChannel连续
    int                 TradeChannel;           ///< 成交通道, 
    char                Symbol[SYMBOL_LEN];     ///< 证券代码, 
    double              TradePrice;             ///< 成交价格, 
    unsigned int        TradeVolume;            ///< 成交数量, 股票：股;权证：份;债券：手
    double              TradeAmount;            ///< 成交金额, 
    long long           BuyRecID;               ///< 买方订单号, 
    long long           SellRecID;              ///< 卖方订单号, 
    char                BuySellFlag;            ///< 内外盘标志, B – 外盘,主动买;S – 内盘,主动卖;N – 未知
    long long           RecNO;                  ///< 业务序号
};
typedef struct SSEL2_Transaction SSEL2_Transaction;

/// 上交所L2逐笔委托
struct SSEL2_Order
{
    unsigned long long         MDTTime;                   ///< 数据接收时间: 从1970/1/1开始的微秒数
    long long               Reserved;                  ///< 保留
    unsigned int        RecID;                    ///< 委托序号
    int                    SetID;                    ///< 频道代码
    char                Symbol[SYMBOL_LEN];        ///< 证券代码
    int                    Time;                    ///< 委托时间
    char                OrderType;                ///< 订单类别
    long long            OrderID;                ///< 原始订单号
    double                OrderPrice;                ///< 委托价格
    double                Balance;                ///< 剩余委托量
    char                OrderCode[10];            ///< 委托买卖方向
    long long            RecNO;                    ///< 业务序号
};
typedef struct SSEL2_Order SSEL2_Order;

/// 上交所L2虚拟集合竞价
struct SSEL2_Auction
{
    unsigned long long	MDTTime;		       	///< 数据接收时间: 从1970/1/1开始的微秒数
    long long        	Reserved;              	///< 保留
    int            	Time;                   ///< 数据生成时间, 143025001 表示 14:30:25.001
    char            	Symbol[SYMBOL_LEN];     	///< 证券代码,
    double   			OpenPrice;              ///< 虚拟开盘参考价,
    long long        	AuctionVolume;          ///< 虚拟匹配量,
    long long        	LeaveVolume;            ///< 虚拟未匹配量,
    char            	Side;                 	///< 买卖方向, 0=无未匹配量，买卖两边的未匹配量都为 0;1=买方有未匹配量，卖方未匹配量=0;2=卖方有未匹配量，买方未匹配量=0
};
typedef struct SSEL2_Auction SSEL2_Auction;

/// 上交所L2市场总览
struct SSEL2_Overview
{
    unsigned long long	   	MDTTime;		      	///< 数据接收时间: 从1970/1/1开始的微秒数
    long long          	Reserved;              	///< 保留
    int                 	Time;                   ///< 数据生成时间, 143025001 表示 14:30:25.001
    char                	Symbol[SYMBOL_LEN];     	///< 证券代码,
    int                 	MarketTime;             ///< 市场时间, 百分之一秒
    int                 	TradeDate;              ///< 市场日期,
};
typedef struct SSEL2_Overview SSEL2_Overview;

/// 上交所个股期权静态数据
struct SSEIOL1_Static
{
    unsigned long long	   	MDTTime;		                 	///< 数据接收时间: 从1970/1/1开始的微秒数
    long long           	Reserved;                    		///< 保留
    char                Symbol[SYMBOL_LEN];                 ///< 证券代码（合约代码）, 合约期权产品代码，8位字符;唯一标示
    char                ContractID[19];                    ///< 合约交易代码 , 合约交易代码17位，按以下顺序编写：1、第1至第6位为数字，取标的证券代码，如工商银行601398，取“601398”；2、第7位为C(Call)或者P(Put)，分别表示认购期权或者认沽期权；3、第8、9位表示到期年份；4、第10、11位表示到期月份；5、第12位期初设为“M”，表示月份合约。当合约首次调整后，“M”修改为 “A”，以表示该合约被调整过一次，如发生第二次调整，则“A”修改为“B”、“M”修改为 “A”，以此类推；6、第13至17位表示期权行权价格.留两位备用
    char                SecurityName[SECURITY_NAME_LEN];    ///< 期权合约简称（证券名称） , 
    char                SymbolUnderlying[SYMBOL_LEN];       ///< 基础证券代码, 
    char                NameUnderlying[SECURITY_NAME_LEN];  ///< 基础证券名称 , 
    char                UnderlyingType[5];                 ///< 标的证券类型 , EBS – ETF， ASH – A股 
    char                OptionType;                         ///< 行权类型, 若为欧式期权，则本字段为“E”；若为美式期权，则本字段为“A” 
    char                CallOrPut;                          ///< 认购认沽 , 认购，则本字段为“C”；若为认沽，则本字段为“P” 
    long long           ContractMultiplierUnit;             ///< 合约单位 , 经过除权除息调整后的合约单位, 一定是整数 
    double              ExercisePrice;                      ///< 期权行权价 , 经过除权除息调整后的期权行权价，右对齐，精确到厘;行权价格调整采取四舍五入方式，股票保留两位小数，ETF保留三位小数。
    int                 StartDate;                          ///< 首个交易日 , 期权首个交易日,YYYYMMDD (年*10000+月*100+日)
    int                 EndDate;                            ///< 最后交易日 , 期权最后交易日/行权日，YYYYMMDD 
    int                 ExerciseDate;                       ///< 期权行权日 , 期权行权日，YYYYMMDD 
    int                 DeliveryDate;                       ///< 行权交割日, 行权交割日，默认为行权日的下一个交易日，YYYYMMDD
    int                 ExpireDate;                         ///< 期权到期日 , 期权到期日，YYYYMMDD 
    char                Version;                            ///< 合约版本号 , 期权合约的版本号。新挂合约是’1’ 
    unsigned int        TotalLongPosition;                  ///< 合约未平仓数 , 单位是 （张） 此值为日终持仓轧差对冲之后持仓数据。
    double              PreClosePrice;                      ///< 昨收价, 昨日收盘价，如遇除权除息则为调整后的收盘价格（上市首日的文件中，填写参考价格），右对齐，精确到厘 
    double              PreSettlePrice;                     ///< 昨结算, 昨日结算价，右对齐，单位：元 
    double              PreClosePriceUnderlying;            ///< 标的昨收价, 期权标的证券除权除息调整后的前收盘价格，右对齐，单位：元 
    char                UpDownLimitType;                    ///< 涨跌幅限制类型 , ‘N’表示交易规则3.4.13规定的有涨跌幅限制类型或者权证管理办法第22条规定 ‘R’表示交易规则3.4.15和3.4.16规定的无涨跌幅限制类型 
    double              PriceUpLimit;                       ///< 涨幅价格, 当日期权涨停价格，精确到厘 
    double              PriceDownLimit;                     ///< 跌幅价格, 当日期权跌停价格，精确到厘 
    double              MarginUnit;                         ///< 单位保证金 , 当日持有一张合约所需要的保证金数 量，精确到分 
    double              MarginRatioParam1;                  ///< 保证金计算参数一 , 保证金计算参数，单位：% 
    double              MarginRatioParam2;                  ///< 保证金计算参数二 , 保证金计算参数，单位：% 
    unsigned int        RoundLot;                           ///< 整手数 , 一手等于几张合约 
    long long           LmtOrdFloor;                        ///< 限价申报下限 , 单笔限价申报的申报张数下限。 
    long long           LmtOrdCeiling;                      ///< 限价申报上限 , 单笔限价申报的申报张数上限。 
    long long           MktOrdFloor;                        ///< 市价申报下限 , 单笔市价申报的申报张数下限。 
    long long           MktOrdCeiling;                      ///< 市价申报上限 , 单笔市价申报的申报张数上限。 
    double              TickSize;                           ///< 最小报价单位, 单位：元（精确到0.1厘）
    char                SecurityStatusFlag[8];              ///< 期权合约状态, 该字段为8位字符串，左起每位表示特定的含义，无定义则填空格。
                                                            ///< 第1位：‘0’表示可开仓，‘1’表示限制卖出开仓（包括备兑开仓）和买入开仓。
                                                            ///< 第2位：‘0’表示未连续停牌，‘1’表示连续停牌。
                                                            ///< 第3位：‘0’表示未临近到期日，‘1’表示距离到期日不足5个交易日。
                                                            ///< 第4位：‘0’表示近期未做调整，‘1’表示最近5个交易日内合约发生过调整。
                                                            ///< 第5位：‘A’表示当日新挂牌的合约，‘E’表示存续的合约，‘D’表示当日摘牌的合约。
                                                            ///< 第6位：‘1’表示合约只能进行跨式和宽跨式的组合策略，‘0’表示可以进行所有的组合策略
    int                 AutoSplitDate;                      ///< 该日期表示垂直价差组合策略到期解除的日期，YYYYMMDD； 对于E-2后波动加挂的合约，此字段仍为E-2日。到期日调整时，此字段信息自动同步调整。
    int                 TradeDate;                         	///< 市场日期,交易日
};
typedef struct SSEIOL1_Static SSEIOL1_Static;

/// 上交所个股期权实时行情
struct SSEIOL1_Quotation
{
    unsigned long long	   	MDTTime;		      	///< 数据接收时间: 从1970/1/1开始的微秒数
    long long           	Reserved;             	///< 保留
    int                 Time;                   ///< 数据生成时间, 143025001表示 14:30:25.001;如果期权合约的产品代码为“00000000”，则表示行情时间，格式为HHMMSSMMM;有成交时才会变化
    char                Symbol[SYMBOL_LEN];     ///< 合约代码（证券代码）, 期权合约的产品代码;唯一标示
    double              PreSettlePrice;         ///< 昨结算, 4 decimal places
    double              SettlePrice;            ///< 结算价, 4 decimal places
    double              OpenPrice;              ///< 开盘价, 4 decimal places
    double              HighPrice;              ///< 最高价 , 4 decimal places
    double              LowPrice;               ///< 最低价, 4 decimal places
    double              LastPrice;              ///< 现价, 4 decimal places
    double              ClosePrice;             ///< 收盘价
    double              AuctionPrice;           ///< 波动性中断参考价, 4 decimal places
    long long           AuctionVolume;          ///< 波动性中断虚拟匹配量, 
    unsigned long long  TotalPosition;          ///< 持仓量, 单位是 （张），交易时间代表此处总持仓量值为持仓余额轧差之前的数值;收盘后为闭市轧差后的未平仓合约数量。
    unsigned int        SellLevelNo;            ///< 卖盘价位数量, 五档:总是5，空档位用0填充
    union
    {
        BuySellLevelInfo    SellLevel[LEVEL_FIVE];      ///< 五档卖行情
        struct
        {
            double              SellPrice01;            ///< 申卖价, 当10069<5时，补足5  档，即：不知的填充为0
            unsigned long long  SellVolume01;           ///< 申卖量, 当10069<5时，补足5  档，即：不知的填充为0
            double              SellPrice02;            ///< 申卖价, 当10069<5时，补足5  档，即：不知的填充为0
            unsigned long long  SellVolume02;           ///< 申卖量, 当10069<5时，补足5  档，即：不知的填充为0
            double              SellPrice03;            ///< 申卖价, 当10069<5时，补足5  档，即：不知的填充为0
            unsigned long long  SellVolume03;           ///< 申卖量, 当10069<5时，补足5  档，即：不知的填充为0
            double              SellPrice04;            ///< 申卖价, 当10069<5时，补足5  档，即：不知的填充为0
            unsigned long long  SellVolume04;           ///< 申卖量, 当10069<5时，补足5  档，即：不知的填充为0
            double              SellPrice05;            ///< 申卖价, 当10069<5时，补足5  档，即：不知的填充为0
            unsigned long long  SellVolume05;           ///< 申卖量, 当10069<5时，补足5  档，即：不知的填充为0
        };
    };
    unsigned int            BuyLevelNo;                  ///< 买盘价位数量, 五档:总是5，空档位用0填充
    union
    {
        BuySellLevelInfo    BuyLevel[LEVEL_FIVE];        ///< 五档买行情
        struct
        {
            double              BuyPrice01;             ///< 申买价, 当10068<5时，补足5档，即：不知的填充为0
            unsigned long long  BuyVolume01;            ///< 申买量, 当10068<5时，补足5档，即：不知的填充为0
            double              BuyPrice02;             ///< 申买价, 当10068<5时，补足5档，即：不知的填充为0
            unsigned long long  BuyVolume02;            ///< 申买量, 当10068<5时，补足5档，即：不知的填充为0
            double              BuyPrice03;             ///< 申买价, 当10068<5时，补足5档，即：不知的填充为0
            unsigned long long  BuyVolume03;            ///< 申买量, 当10068<5时，补足5档，即：不知的填充为0
            double              BuyPrice04;             ///< 申买价, 当10068<5时，补足5档，即：不知的填充为0
            unsigned long long  BuyVolume04;            ///< 申买量, 当10068<5时，补足5档，即：不知的填充为0
            double              BuyPrice05;             ///< 申买价, 当10068<5时，补足5档，即：不知的填充为0
            unsigned long long  BuyVolume05;            ///< 申买量, 当10068<5时，补足5档，即：不知的填充为0
        };
    };
    unsigned long long  TotalVolume;            ///< 成交总量, Trade volume of this security.如果期权合约的产品代码为“00000000”，则表示行情日期，格式为YYYYMMDD
    double              TotalAmount;            ///< 成交金额, 2 decimal places
    char                SecurityPhaseTag[PHRASE_TAG_LEN];    ///< 该字段为4位字符串，左起每位表示特定的含义，无定义则填空格。
                                                             ///< 第1位：‘S’表示启动（开市前）时段，‘C’表示集合竞价时段，‘T’表示连续交易时段，‘B’表示休市时段，‘E’表示闭市时段，‘V’表示波动性中断，‘P’表示临时停牌、‘U’表示收盘集合竞价。
                                                             ///<        ‘M’表示可恢复交易的熔断（盘中集合竞价），‘N’表示不可恢复交易的熔断（暂停交易至闭市）
                                                             ///< 第2位：‘0’表示未连续停牌，‘1’表示连续停牌。（预留，暂填空格）。
                                                             ///< 第3位：‘0’表示不限制开仓，‘1’表示限制备兑开仓，‘2’表示卖出开仓，‘3’表示限制卖出开仓、备兑开仓，‘4’表示限制买入开仓，‘5’表示限制买入开仓、备兑开仓，‘6’表示限制买入开仓、卖出开仓，‘7’表示限制买入开仓、卖出开仓、备兑开仓。
                                                             ///< 第4位：‘0’表示此产品在当前时段不接受进行新订单申报，‘1’表示此产品在当前时段可接受进行新订单申报。

};
typedef struct SSEIOL1_Quotation SSEIOL1_Quotation;

/// 集合竞价涨跌幅
struct AuctionUpDown {
    double          LimitUpRate;                     ///< 集合竞价上涨幅度，3位小数
    double          LimitDownRate;                   ///< 集合竞价下跌幅度，3位小数
    double          LimitUpAbsolute;                 ///< 集合竞价上涨限价，4位小数
    double          LimitDownAbsolute;               ///< 集合竞价下跌限价，4位小数
    double          AuctionUpDownRate;               ///< 集合竞价有效范围涨跌幅度，3位小数
    double          AuctionUpDownAbsolute;           ///< 集合竞价有效范围涨跌价格，4位小数
};
typedef struct AuctionUpDown AuctionUpDown;

#if 0
/// 深交所L1实时行情
struct SZSEL1_Quotation
{
    unsigned long long	   MDTTime;		                 	    ///< 数据接收时间: 从1970/1/1开始的微秒数
    long long           Time;                               ///< 数据生成时间YYYYMMDDHHMMSSsss
    char                Symbol[SYMBOL_LEN];                 ///< 证券代码. 证券代码以395打头的记录为成交量统计指标记录
    char                SymbolSource[SYMBOLSOURCE_LEN];     ///< 证券代码源，102 = 深圳证券交易所,103=香港交易所
    double              PreClosePrice;                      ///< 昨收价.
    double              OpenPrice;                          ///< 开盘价.
    double              LastPrice;                          ///< 现价.
    double              HighPrice;                          ///< 最高价. 
    double              LowPrice;                           ///< 最低价.
    double              PriceUpLimit;                       ///< 涨停价.
    double              PriceDownLimit;                     ///< 跌停价.
    double              PriceUpdown1;                       ///< 升跌一
    double              PriceUpdown2;                       ///< 升跌二
    unsigned long long  TotalNo;                            ///< 总成交笔数. 证券代码以395打头的记录为成交量统计指标记录，该字段表示各类别对应的成交笔数
    double              TotalVolume;                        ///< 成交总量. 证券代码以395打头的记录为成交量统计指标记录，该字段表示各类别对应的成交单位数
    double              TotalAmount;                        ///< 成交总额. 证券代码以395打头的记录为成交量统计指标记录，该字段表示各类别对应的成交金额。所有单位均为人民币。
    double              ClosePrice;                         ///< 今收盘价 盘前、盘中赋为0值；盘后，由闭市后发的静态数据：现货证券收盘行情(cashsecurityclosemd.xml)进行填充，按证券代码进行填充。无可取值的代码，则赋0值
    char                SecurityPhaseTag[8];                ///< 当前品种交易状态. 产品所处的交易阶段代码：
                                                            ///<  第 0 位：S=启动(开市前) O=开盘集合竞价 T=连续     B=休市
                                                            ///<  C=收盘集合竞价 E=已闭市 H=临时停牌 A=盘后交易
                                                            ///<  V=波动性中断
                                                            ///<  第 1 位：0=正常状态 1=全天停牌
    double              PERatio1;                           ///< 市盈率1.
    double              PERatio2;                           ///< 市盈率2.
    double              NAV;                                ///< 基金 T-1 日净值
    double              IOPV;                               ///< 基金实时参考净值(包括 ETF的 IOPV)
    double              PremiumRate;                        ///< 权证溢价率
    unsigned int        SampleNo;                           ///< 样本个数
    union
    {
        SZSE_BuySellLevelInfo    SellLevel[LEVEL_FIVE];      ///< 五档卖行情
        struct
        {
            double              SellPrice01;            ///< 申卖价一
            double              SellVolume01;           ///< 申卖量一
            double              SellPrice02;            ///< 申卖价二
            double              SellVolume02;           ///< 申卖量二
            double              SellPrice03;            ///< 申卖价三
            double              SellVolume03;           ///< 申卖量三
            double              SellPrice04;            ///< 申卖价四
            double              SellVolume04;           ///< 申卖量四
            double              SellPrice05;            ///< 申卖价五
            double              SellVolume05;           ///< 申卖量五
        };
    };
    union
    {
        SZSE_BuySellLevelInfo    BuyLevel[LEVEL_FIVE];        ///< 五档买行情
        struct
        {
            double              BuyPrice01;             ///< 申买价一
            double              BuyVolume01;            ///< 申买量一
            double              BuyPrice02;             ///< 申买价二
            double              BuyVolume02;            ///< 申买量二
            double              BuyPrice03;             ///< 申买价三
            double              BuyVolume03;            ///< 申买量三
            double              BuyPrice04;             ///< 申买价四
            double              BuyVolume04;            ///< 申买量四
            double              BuyPrice05;             ///< 申买价五
            double              BuyVolume05;            ///< 申买量五
        };
    };
    double              WtAvgRate;                          ///< 实时加权平均利率    质押式回购产品实时行情增加三个字段
    double              WtAvgRateUpdown;                    ///< 加权平均利率涨跌BP
    double              PreWtAvgRate;                       ///< 昨收盘加权平均利率
};

/// 深交所公告消息头
struct SZSEL1_BulletinHead
{
    unsigned long long	   MDTTime;		                 	    ///< 数据接收时间: 从1970/1/1开始的微秒数
    long long       Time;                               ///< 数据生成时间YYYYMMDDHHMMSSsss
    unsigned int    SetID;                              ///< 频道代码
    char            NewsID[12];                         ///< 公告标识, 空串代表公告摘要, 会重复发送. 通过摘要可确定公告是否有遗漏
    char            Headline[128];                      ///< 公告标题
    char            RawDataFormat[8];                   ///< 二进制数据格式
    unsigned int    RawDataLength;                      ///< 二进制数据长度
};

/// 深交所公告消息
struct SZSEL1_Bulletin
{
    SZSEL1_BulletinHead 	RawHead;                        ///< 公告头
    char                	RawData[1];                     ///< 二进制数据,长度由RawDataLength确定
};
#endif

/// 深交所L2静态数据
struct SZSEL2_Static
{
    unsigned long long	   MDTTime;		                 	///< 数据接收时间: 从1970/1/1开始的微秒数
    char            Symbol[SYMBOL_LEN];                 	///< 证券代码，8个字符
    char            SecurityName[40];                   	///< 证券名称，可能包含中文字符，表示最多 40个 UTF-8 字符
    char            SymbolSource[SYMBOLSOURCE_LEN];     	///< 证券代码源，102 = 深圳证券交易所
    char            SecurityEN[40];                     	///< 证券英文简称
    char            ISINCode[12];                       	///< ISIN 代码
    char            SymbolUnderlying[20];               	///< 基础证券代码
    char            UnderlyingSecurityIDSource[4];      	///< 基础证券代码源
    int             SecurityType;                       	///< 证券类别代码，1主板 A股； 2中小板股票；3创业板股票；4主板 B股；5国债 （含地方债）；6企业债；
                                                        ///< 7公司债；8可转债；9私募债；10可交换私募债；11证券公司次级债；12质押式回购；13资产支持证券；
                                                        ///< 14本市场股票ETF；15跨市场ETF；16跨境ETF；17本市场实物债券ETF；18现金债券ETF；19黄金ETF；20货币ETF；
                                                        ///< 21（预留）杠杆ETF;22(预留)商品期货ETF；23标准LOF;24分级子基金；25封闭式基金；26仅申赎基金；28权证；
                                                        ///< 29个股期权；30ETF期权；33优先股；34证券公司短期债；35可交换公司债
    char            SecurityStatusTag[20];              	///< 证券状态标识，该字段为20位字符串（后六位备用），
                                                        ///< 每位表示特定的含义，“1”表示位数有业务意义，“0”表示该位数无业务意义。第1位对应：“1”表示停牌；
                                                        ///< 第2位对应：“1”表示除权；第3位对应：“1”表示除息；第4位对应：“1”表示ST;第5位对应：“1”表示*ST;
                                                        ///< 第6位对应：“1”表示上市首日；第7位对应：“1”表示公司再融资；第8位对应：“1”表示恢复上市首日；
                                                        ///< 第9位对应：“1”表示网络投票；第10位对应：“1”表示退市整理期；第12位对应：“1”表示增发股份上市；
                                                        ///< 第13位对应：“1”表示合约调整；第14位对应：“1”表示暂停上市后协议转让。
    double          PreClosePrice;                      	///< 昨日收盘价，4位或5位小数
    int             ListingDate;                        	///< 上市日期
    char            Currency[5];                        	///< 币种，CNY = 人民币，HKD = 港币
    double          ParValue;                           	///< 每股面值，4位小数
    double          IssuedVolume;                       	///< 总发行量，2位小数
    double          OutstandingShare;                   	///< 流通股数，2位小数
    char            IndustryType[5];                    	///< 行业种类
    double          PreYearEPS;                         	///< 上年每股利润，4位小数
    double          YearEPS;                            	///< 本年每股利润，4位小数
    char            OfferingFlag;                       	///< 收购（转股、行权）标志，股票：要约收购；债券、优先股：转股回售；Y=是，N=否
    double          NAV;                                	///< 基金T-1日累计净值，4位小数
    double          CouponRate;                         	///< 票面利率，4位小数
    double          IssuePrice;                         	///< 贴现发行价，4位小数
    double          Interest;                           	///< 每百元应计利息，8位小数，优先股：0.0000 表示浮动股息率
    int             InterestAccrualDate;                	///< 起息日
    int             MaturityDate;                       ///< 到期交割日
    double          ConversionPrice;                    ///< 行权价格，4位小数
    double          ConversionRatio;                    ///< 行权比例，4位小数
    int             ConversionBeginDate;                ///< 行权开始日
    int             ConversionEndDate;                  ///< 行权结束日
    char            CallOrPut;                          ///< 认购认沽，C = Call，P = Put
    char            WarrantClearingType;                ///< 权证结算方式，S = 证券结算，C = 现金结算
    double          ClearingPrice;                      ///< 结算价格，适用于权证，4位小数
    char            OptionType;                         ///< 行权类型，A = 美式，E = 欧式，B = 百慕大式
    int             EndDate;                           ///< 最后交易日
    int             ExpirationDays;                     ///< 购回期限
    char            DayTrading;                         	///< 回转交易标志，是否支持当日回，转交易：Y=支持，N=不支持
    char            GageFlag;                           ///< 保证金证券标志，是否可作为融资，融券可充抵保证，金证券：Y=是，N=否
    double          GageRate;                           ///< 担保品折算率，2位小数
    char            CrdBuyUnderlying;                   ///< 融资标的标志，Y=是，N=否
    char            CrdSellUnderlying;                  ///< 融券标的标志，Y=是，N=否
    char            CrdPriceCheckType[2];               ///< 提价检查方式，0=不检查，1=不低于最近成交价，2=不低于昨收价，3=不低于最高叫买，4=不低于最低叫卖
    char            PledgeFlag;                         ///< 质押入库标志，是否可质押入库:Y=是，N=否
    double          ContractMultiplier;                 ///< 债券折合回购标准券比例，4位小数
    char            RegularShare[8];                    ///< 对应回购标准券
    char            QualificationFlag;                  ///< 投资者适当性管理标志，是否需要对该证券作投资者适当性管理，Y=是，N=否
    char            MarketMakerFlag;                    ///< 做市商标志，标识是否有做市商，Y=是，N=否
    double          RoundLot;                           ///< 整手数(2位有效小数)，对于某一证券申报的委托，其委托数量字段必须为该证券数量单位的整数倍
    double          TickSize;                           ///< 最小报价单位，4位小数
    double          BuyQtyUpperLimit;                   ///< 买数量上限，2位小数
    double          SellQtyUpperLimit;                  ///< 卖数量上限，2位小数
    double          BuyVolumeUnit;                      ///< 买数量单位，每笔买委托的委托数量必须是买数量单位的整数倍，2位小数
    double          SellVolumeUnit;                     ///< 卖数量单位，每笔卖委托的委托数量必须是卖数量单位的整数倍，2位小数
    union {
        AuctionUpDown OTC[OTC_ELEMENT_LEN];
        struct
        {
            double          LimitUpRateO;                     ///< 开盘集合竞价上涨幅度，3位小数
            double          LimitDownRateO;                   ///< 开盘集合竞价下跌幅度，3位小数
            double          LimitUpAbsoluteO;                 ///< 开盘集合竞价上涨限价，4位小数
            double          LimitDownAbsoluteO;               ///< 开盘集合竞价下跌限价，4位小数
            double          AuctionUpDownRateO;               ///< 开盘集合竞价有效范围涨跌幅度，3位小数
            double          AuctionUpDownAbsoluteO;           ///< 开盘集合竞价有效范围涨跌价格，4位小数
            double          LimitUpRateT;                     ///< 连续竞价上涨幅度，3位小数
            double          LimitDownRateT;                   ///< 连续竞价下跌幅度，3位小数
            double          LimitUpAbsoluteT;                 ///< 连续竞价上涨限价，4位小数
            double          LimitDownAbsoluteT;               ///< 连续竞价下跌限价，4位小数
            double          AuctionUpDownRateT;               ///< 连续竞价有效范围涨跌幅度，3位小数
            double          AuctionUpDownAbsoluteT;           ///< 连续竞价有效范围涨跌价格，4位小数
            double          LimitUpRateC;                     ///< 收盘集合竞价上涨幅度，3位小数
            double          LimitDownRateC;                   ///< 收盘集合竞价下跌幅度，3位小数
            double          LimitUpAbsoluteC;                 ///< 收盘集合竞价上涨限价，4位小数
            double          LimitDownAbsoluteC;               ///< 收盘集合竞价下跌限价，4位小数
            double          AuctionUpDownRateC;               ///< 收盘集合竞价有效范围涨跌幅度，3位小数
            double          AuctionUpDownAbsoluteC;           ///< 收盘集合竞价有效范围涨跌价格，4位小数
        };
    };
    int             TradeDate;                          ///< 市场日期,交易日
    char            QualificationClass[2];              ///< 投资者适当性管理分类

    char            Attribute[2];                       ///< 股票属性
    char            NoProfit;                           ///< 是否尚未盈利 Y=是，未盈利 N=否，已盈利
    char            WeightedVotingRights;               ///< 是否存在投票权差异 Y=存在差异 N=无差异
    //QTS 3.7 新增创业板
    char            SecurityNameEx[40];                 ///< 证券简称(扩)，若无与证券简称内容一致
    char            IsRegistration;                     ///< 是否注册制
    char            IsVIE;                              ///< 是否具有协议控制架构
    double          MktBuyQtyUpLimit;                   ///< 市价买数量上限
    double          MktSellQtyUpLimit;                  ///< 市价卖数量上限
    double          MktBuyQtyUnit;                      ///< 市价买数量单位
    double          MktSellQtyUnit;                     ///< 市价卖数量单位
    double          FixedPriceBuyQtyUpLimit;            ///< 定价买数量上限
    double          FixedPriceSellQtyUpLimit;           ///< 定价卖数量上限
    double          FixedPriceBuyQtyUnit;               ///< 定价买数量单位
    double          FixedPriceSellQtyUnit;              ///< 定价卖数量单位
};
typedef struct SZSEL2_Static SZSEL2_Static;
//typedef SZSEL2_Static SZSEL1_Static;

/// 深交所L2证券状态
struct SZSEL2_Status
{
    unsigned long long	   MDTTime;		                ///< 数据接收时间: 从1970/1/1开始的微秒数
    char        Symbol[SYMBOL_LEN];                 	///< 证券代码
    char        SymbolSource[SYMBOLSOURCE_LEN];     	///< 证券代码源，102=深圳证券交易所，103=香港交易所
    long long   Time;                               	///< 数据生成时间YYYYMMDDHHMMSSMMM
    char        FinancialStatus[8];                 	///< A=上市公司早间披露提示,
                                                    ///< B=上市公司午间披露提示,
                                                    ///< 每个字节揭示一种状态，最多可同时揭示八种状态
    char        CrdBuyStatus;                       ///< 适用于融资标的证券。1= 开放,0=暂停，空格无意义
    char        CrdSellStatus;                      ///< 适用于融券标的证券。1= 开放,0=暂停，空格无意义
    char        SubscribeStatus;                    ///< 适用于 ETF， LOF 等开放式基金，对于黄金 ETF 是指现金申购。1= 是,0= 否，空格无意义
    char        RedemptionStatus;                   ///< 适用于 ETF， LOF 等开放式基金，对于黄金 ETF 是指现金赎回开关。1= 是,0= 否，空格无意义
    char        PurchasingStatus;                   ///< 适用于网上发行认购代。1= 是,0= 否，空格无意义
    char        StockDiviStatus;                    ///< 适用于处于转股回售期的可转债。1= 是,0= 否，空格无意义
    char        PutableStatus;                      ///< 适用于处于转股回售期的可转债。1= 是,0= 否，空格无意义
    char        ExerciseStatus;                     ///< 适用于处于行权期的权证。1= 是,0=否，空格无意义
    char        GoldPurchase;                       ///< 适用于黄金ETF实物申购。1= 是,0= 否，空格无意义
    char        GoldRedemption;                     ///< 适用于黄金ETF实物赎回。1= 是,0= 否，空格无意义
    char        AcceptedStatus;                     ///< 适用于处于要约收购期的股票。1= 是,0= 否，空格无意义
    char        ReleaseStatus;                      ///< 适用于处于要约收购期的股票。1= 是,0= 否，空格无意义
    char        CancStockDiviStatus;                ///< 适用于处于转股回售期的可转债。1= 是,0= 否，空格无意义
    char        CancPutableStatus;                  ///< 适用于处于转股回售期的可转债。1= 是,0= 否，空格无意义
    char        PledgeStatus;                       ///< 适用于质押式回购可质押入库证券。1= 是,0= 否，空格无意义
    char        RemovePledge;                       ///< 适用于质押式回购可质押入库证券。1= 是,0= 否，空格无意义
    char        VoteStatus;                         ///< 适用于优先股。1= 是,0= 否，空格无意义
    char        StockPledgeRepo;                    ///< 适用于可开展股票质押式回购业务的证券。1= 是,0= 否，空格无意义
    char        DivideStatus;                       ///< 适用于分级基金。1= 是,0= 否，空格无意义
    char        MergerStatus;                       ///< 适用于分级基金。1= 是,0= 否，空格无意义
};
typedef struct SZSEL2_Status SZSEL2_Status;

/// 深交所L2实时行情
struct SZSEL2_Quotation
{
    unsigned long long	   	MDTTime;		                 	///< 数据接收时间: 从1970/1/1开始的微秒数
    long long          	Time;                               ///< 数据生成时间YYYYMMDDHHMMSSMMM
    char                	Symbol[SYMBOL_LEN];                 	///< 证券代码
    char                	SymbolSource[SYMBOLSOURCE_LEN];     	///< 证券代码源
    double              	PreClosePrice;                      ///< 昨日收盘价,4位小数
    double              	OpenPrice;                          ///< 开盘价,6位小数
    double              	LastPrice;                          ///< 现价,6位小数
    double              	HighPrice;                          ///< 最高价,6位小数
    double              	LowPrice;                           ///< 最低价,6位小数
    double              	PriceUpLimit;                       ///< 涨停价,6位小数
    double              	PriceDownLimit;                     ///< 跌停价,6位小数
    double              	PriceUpdown1;                       ///< 升跌一,6位小数
    double              	PriceUpdown2;                       ///< 升跌二,6位小数
    unsigned long long  	TotalNo;                            ///< 成交笔数
    double              	TotalVolume;                        ///< 成交总量,2位小数
    double              	TotalAmount;                        ///< 成交总金额,4位小数
    double              	ClosePrice;                         ///< 今收盘价，6位小数
    char                	SecurityPhaseTag[PHRASE_TAG_LEN];   	///< 当前品种交易状态：产品所处的交易阶段代码：
                                                            ///< 第 0 位：S=启动（开市前），O=开盘集合竞价， T=连续,B=休市
                                                            ///<          C=收盘集合竞价,E=已闭市,H=临时停牌,A=盘后交易,V=波动性中断;
                                                            ///< 第 1 位：0=正常状态,1=全天停牌"
    double              	PERatio1;                           ///< 市盈率 1,6位小数
    double              	NAV;                                ///< 基金 T-1 日净值,6位小数
    double              	PERatio2;                           ///< 市盈率 2,6位小数
    double              	IOPV;                               ///< 基金实时参考净值,6位小数
    double              	PremiumRate;                        ///< 权证溢价率,6位小数
    double              	TotalSellOrderVolume;               ///< 委托卖出总量（有效竞价范围内）2位小数
    double              	WtAvgSellPrice;                     ///< 加权平均卖出价格（有效竞价范围内）,6位小数
    unsigned int        	SellLevelNo;                        ///< 申卖档位数（价格由低至高）
    union
    {
        SZSE_BuySellLevelInfo3    SellLevel[LEVEL_TEN];      ///< 十档卖行情
        struct
        {
            double              SellPrice01;            ///< 申卖价,6位小数
            double              SellVolume01;           ///< 申卖量，2位小数
            unsigned long long  TotalSellOrderNo01;     ///< 卖价位总委托笔数
            double              SellPrice02;            ///< 申卖价
            double              SellVolume02;           ///< 申卖量
            unsigned long long  TotalSellOrderNo02;     ///< 卖价位总委托笔数
            double              SellPrice03;            ///< 申卖价
            double              SellVolume03;           ///< 申卖量
            unsigned long long  TotalSellOrderNo03;     ///< 卖价位总委托笔数
            double              SellPrice04;            ///< 申卖价
            double              SellVolume04;           ///< 申卖量
            unsigned long long  TotalSellOrderNo04;     ///< 卖价位总委托笔数
            double              SellPrice05;            ///< 申卖价
            double              SellVolume05;           ///< 申卖量
            unsigned long long  TotalSellOrderNo05;     ///< 卖价位总委托笔数
            double              SellPrice06;            ///< 申卖价
            double              SellVolume06;           ///< 申卖量
            unsigned long long  TotalSellOrderNo06;     ///< 卖价位总委托笔数
            double              SellPrice07;            ///< 申卖价
            double              SellVolume07;           ///< 申卖量
            unsigned long long  TotalSellOrderNo07;     ///< 卖价位总委托笔数
            double              SellPrice08;            ///< 申卖价
            double              SellVolume08;           ///< 申卖量
            unsigned long long  TotalSellOrderNo08;     ///< 卖价位总委托笔数
            double              SellPrice09;            ///< 申卖价
            double              SellVolume09;           ///< 申卖量
            unsigned long long  TotalSellOrderNo09;     ///< 卖价位总委托笔数
            double              SellPrice10;            ///< 申卖价
            double              SellVolume10;           ///< 申卖量
            unsigned long long  TotalSellOrderNo10;     ///< 卖价位总委托笔数
        };
    };
    unsigned int        	SellLevelQueueNo01;                 ///< 卖一档揭示委托笔数
    double              	SellLevelQueue[ORDER_LEVEL_FIFTY];  	///< 揭示卖一价前50笔委托，50档，不足补0，2位小数
    double              	TotalBuyOrderVolume;                ///< 委托买入总量（有效竞价范围内），2位小数
    double              	WtAvgBuyPrice;                      ///< 加权平均买入价格（有效竞价范围内）,6位小数
    unsigned int        	BuyLevelNo;                         ///< 申买档位数（价格由高至低）
    union
    {
        SZSE_BuySellLevelInfo3    BuyLevel[LEVEL_TEN];      ///< 十档买行情
        struct
        {
            double              BuyPrice01;             ///< 申买价,6位小数
            double              BuyVolume01;            ///< 申买量,2位小数
            unsigned long long  TotalBuyOrderNo01;      ///< 买价位总委托笔数
            double              BuyPrice02;             ///< 申买价
            double              BuyVolume02;            ///< 申买量
            unsigned long long  TotalBuyOrderNo02;      ///< 买价位总委托笔数
            double              BuyPrice03;             ///< 申买价
            double              BuyVolume03;            ///< 申买量
            unsigned long long  TotalBuyOrderNo03;      ///< 买价位总委托笔数
            double              BuyPrice04;             ///< 申买价
            double              BuyVolume04;            ///< 申买量
            unsigned long long  TotalBuyOrderNo04;      ///< 买价位总委托笔数
            double              BuyPrice05;             ///< 申买价
            double              BuyVolume05;            ///< 申买量
            unsigned long long  TotalBuyOrderNo05;      ///< 买价位总委托笔数
            double              BuyPrice06;             ///< 申买价
            double              BuyVolume06;            ///< 申买量
            unsigned long long  TotalBuyOrderNo06;      ///< 买价位总委托笔数
            double              BuyPrice07;             ///< 申买价
            double              BuyVolume07;            ///< 申买量
            unsigned long long  TotalBuyOrderNo07;      ///< 买价位总委托笔数
            double              BuyPrice08;             ///< 申买价
            double              BuyVolume08;            ///< 申买量
            unsigned long long  TotalBuyOrderNo08;      ///< 买价位总委托笔数
            double              BuyPrice09;             ///< 申买价
            double              BuyVolume09;            ///< 申买量
            unsigned long long  TotalBuyOrderNo09;      ///< 买价位总委托笔数
            double              BuyPrice10;             ///< 申买价
            double              BuyVolume10;            ///< 申买量
            unsigned long long  TotalBuyOrderNo10;      ///< 买价位总委托笔数
        };
    };
    unsigned int        	BuyLevelQueueNo01;                  ///< 买一档揭示委托笔数
    double              	BuyLevelQueue[ORDER_LEVEL_FIFTY];	   	///< 揭示买一价前50笔委托，50档，不足补0，2位小数
    double              	WtAvgRate;                          ///< 实时加权平均利率    质押式回购产品实时行情增加三个字段
    double              	WtAvgRateUpdown;                    ///< 加权平均利率涨跌BP
    double              	PreWtAvgRate;                       ///< 昨收盘加权平均利率
};
typedef struct SZSEL2_Quotation SZSEL2_Quotation;

/// 深交所L2指数行情
struct SZSEL2_Index
{
    unsigned long long	   	MDTTime;		                 	///< 数据接收时间: 从1970/1/1开始的微秒数
    long long           	Time;                               ///< 数据生成时间YYYYMMDDHHMMSSMMM
    char                Symbol[SYMBOL_LEN];                 	///< 证券代码
    char                SymbolSource[SYMBOLSOURCE_LEN];     	///< 102=深圳证券交易所, 103=香港交易所
    double              PreClosePrice;                      ///< 前收盘指数,6位小数
    double              OpenPrice;                          ///< 今开盘指数,6位小数
    double              HighPrice;                          ///< 最高指数,6位小数
    double              LowPrice;                           ///< 最低指数,6位小数
    double              LastPrice;                          ///< 最新指数,6位小数
    double              TotalAmount;                        ///< 参与计算相应指数的成交金额,4位小数
    unsigned long long  	TotalNo;                           	///< 参与计算相应指数的成交笔数
    double              TotalVolume;                        	///< 参与计算相应指数的交易数量，2位小数
    char                SecurityPhaseTag[PHRASE_TAG_LEN];   	///< 当前品种交易状态
    unsigned int        SampleNo;                           	///< 样本个数
};
typedef struct SZSEL2_Index SZSEL2_Index;

/// 深交所L2逐笔委托
struct SZSEL2_Order
{
    unsigned long long	   	MDTTime;		                 	///< 数据接收时间: 从1970/1/1开始的微秒数
    unsigned int        	SetID;                              ///< 频道代码
    unsigned long long  	RecID;                              ///< 消息记录号:从 1 开始计数，同一频道连续
    char                	Symbol[SYMBOL_LEN];                 	///< 证券代码
    char                	SymbolSource[SYMBOLSOURCE_LEN];     	///< 证券代码源
    long long           	Time;                               ///< 委托时间YYYYMMDDHHMMSSMMM
    double              	OrderPrice;                         ///< 委托价格,4位小数
    double              	OrderVolume;                        ///< 委托数量,2位小数
    char                	OrderCode;                          ///< 买卖方向：1=买 2=卖 G=借入 F=出借
    char                	OrderType;                          ///< 订单类别：1=市价 2=限价 U=本方最优

    friend std::ostream& operator<<(std::ostream& os, const SZSEL2_Order* order)
    {
        os << "{" << "mdt_time:" << order->MDTTime << ", set_id:" << order->SetID << ", rec_id:" << order->RecID <<
            ", symbol:\"" << order->Symbol << "\", symbol_source:\"" << order->SymbolSource << "\", time:" << order->Time <<
            ", order_price:" << order->OrderPrice << ", order_volume:" << order->OrderVolume << ", order_code:" <<
            order->OrderCode << ", order_type:" << order->OrderType << "}";
        return os;
    }
};
typedef struct SZSEL2_Order SZSEL2_Order;

/// 深交所L2逐笔成交
struct SZSEL2_Transaction
{
    unsigned long long    MDTTime;		             ///< 数据接收时间: 从1970/1/1开始的微秒数
    unsigned int        	SetID;                              ///< 证券集代号
    unsigned long long  	RecID;                              ///< 消息记录号 从 1 开始计数，同一频道连续
    unsigned long long  	BuyOrderID;                         ///< 买方委托索引
    unsigned long long  	SellOrderID;                        ///< 卖方委托索引
    char                	Symbol[SYMBOL_LEN];                 	///< 证券代码
    char                	SymbolSource[SYMBOLSOURCE_LEN];     	///< 证券代码源
    long long           	TradeTime;                          ///< 成交时间YYYYMMDDHHMMSSMMM
    double              	TradePrice;                         ///< 成交价格,4位小数
    double              	TradeVolume;                        ///< 成交数量,2位小数
    char                	TradeType;                          ///< 成交类别：4=撤销，主动或自动撤单执行报告；F=成交，成交执行报告
};
typedef struct SZSEL2_Transaction SZSEL2_Transaction;

/// 证券代码
struct StockSymbol
{
    char    Symbol[SYMBOL_LEN + MARKET_TAG_LEN];        ///< 查询个股列表返回的股票代码，带市场标志
};

#pragma pack()

#endif // MDT_STRUCT_H_