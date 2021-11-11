//////////////////////////////////////////////////////////////////////////////
/// @file       MDTDataType.h
/// @brief      MDT数据格式定义
//////////////////////////////////////////////////////////////////////////////
#ifndef MDT_DATA_TYPE_H_
#define MDT_DATA_TYPE_H_

#ifndef NULL
#ifdef __cplusplus
#define NULL    0
#else
#define NULL    ((void *)0)
#endif
#endif

/// 消息类型定义，值为unsigned int值
enum MsgType
{
    Msg_Unknown = 0x00000000,       ///< 错误的消息类型

    Msg_SSEL1_Static = 0x00101000,       ///< 上交所L1静态数据
    Msg_SSEL1_Quotation = 0x00101001,       ///< 上交所L1实时行情
    Msg_SSE_IndexPress = 0x0010100D,       ///< 上交所指数通行情

    Msg_SSEL2_Static = 0x00102000,       ///< 上交所L2静态数据 
    Msg_SSEL2_Quotation = 0x00102001,       ///< 上交所L2实时行情 
    Msg_SSEL2_Transaction = 0x00102002,       ///< 上交所L2逐笔成交 
    Msg_SSEL2_Index = 0x00102003,       ///< 上交所L2指数行情 
    Msg_SSEL2_Auction = 0x00102004,       ///< 上交所L2虚拟集合竞价 
    Msg_SSEL2_Overview = 0x00102005,       ///< 上交所L2市场总览
    Msg_SSEL2_Order = 0x00102006,       ///< 上交所L2逐笔委托

    Msg_SSEIOL1_Static = 0x00103000,       ///< 上交所个股期权静态数据
    Msg_SSEIOL1_Quotation = 0x00103001,       ///< 上交所个股期权实时行情

    Msg_SZSEL1_Static = 0x00201000,       ///< 深交所L1静态数据
    Msg_SZSEL1_Quotation = 0x00201001,       ///< 深交所L1实时行情
    Msg_SZSEL1_Bulletin = 0x0020100C,       ///< 深交所L1公告

    Msg_SZSEL2_Static = 0x00202000,       ///< 深交所L2静态数据 
    Msg_SZSEL2_Quotation = 0x00202001,       ///< 深交所L2实时行情 
    Msg_SZSEL2_Transaction = 0x00202002,       ///< 深交所L2逐笔成交 
    Msg_SZSEL2_Index = 0x00202003,       ///< 深交所L2指数行情
    Msg_SZSEL2_Order = 0x00202006,       ///< 深交所L2逐笔委托 
    Msg_SZSEL2_Status = 0x00202007,       ///< 深交所L2证券状态

    //Msg_UpLimited				= 0xf0000000,			//曾涨停
    //Msg_UpLimitTouched			= 0xf0000001,			//曾触及涨停
};

/// 返回值含义列表
enum RetCode
{
    Ret_Error = -1,   ///< 失败
    Ret_Success = 0,    ///< 成功
    Ret_NoAddress = 1,    ///< 请先设置行情服务器地址
    Ret_NoPermission = 2,    ///< 没有权限，请联系客服
    Ret_ParamInvalid = 3,    ///< 参数无效
    Ret_AccountError = 4,    ///< 帐号或密码错误
    Ret_AccountOutDate = 5,    ///< 帐号不在有效期内
    Ret_ConnectFail = 6,    ///< 连接失败
    Ret_LoginRepeat = 7,    ///< 帐号重复登录
    Ret_OutTime = 8,    ///< 超时
    Ret_CloseConnect = 9,    ///< 连接断开
    Ret_OutLimit = 10,   ///< 代码订阅数超出上限
    Ret_LowVersion = 11,   ///< 版本过低
    Ret_NoSubInnerMsg = 12,   ///< 不能订阅或退订内部通讯消息
};

/// 数据结构字段长度定义
#define SYMBOL_LEN          40      ///< 代码长度
#define SECURITY_NAME_LEN   40      ///< 证券名称长度
#define SECURITY_EN_LEN     24      ///< 英文证券简称
#define MARKET_TAG_LEN      10      ///< 市场标志长度
#define TIMEOUT_DEFAULT     3       ///< 默认设置超时时长
#define SYMBOLSOURCE_LEN    5       ///< 代码源长度
#define PHRASE_TAG_LEN      8       ///< 当前品种交易状态长度
#define SETTLE_GROUP_ID_LEN 10      ///< 结算组代码长度
#define USER_NAME_LEN       50      ///< 用户名长度
#define USER_PWD_LEN        16      ///< 密码长度

#endif // MDT_DATA_TYPE_H_