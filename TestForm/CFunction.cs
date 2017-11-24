using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.InteropServices;
using System.Reflection;


namespace TestForm
{
    [StructLayout(LayoutKind.Sequential)]
    public struct CUSTOMERINFO
    {
        //public int zhuangtai { get; set; }
        public int CardClass;      //卡类型：4-M1卡，8-CPU卡
        public int CustomerID;     //账号序号
        public int CardSN;         //个人持卡序号
        public int Status;         //卡状态 F1H=正常 F3H=挂失
        public int SubType;        //卡类别
        public int Ye;             //余额	单位：分
        public int OpCount;        /// 消费计数
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 32)]
        public string Name;        //姓名  
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 12)]
        public string ValidDate;   //有效日期，YYYY-MM-DD
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 24)]
        public string CardASN;     //卡应用序列号
        
        internal int GetCardClass()
        {
            return this.CardClass;
        }
        internal string GetName()
        {
            return this.Name;
        }
        internal int GetYe()
        {
            return this.Ye;
        }
        internal int GetCustomerID()
        {
            return CustomerID;
        }
        internal int GetStatus()
        {
            return Status;
        }
        internal int GetSubType()
        {
            return SubType;
        }
        internal int GetOpCount()
        {
            return OpCount;
        }
        internal int GetCardSN()
        {
            return CardSN;
        }
        internal string GetValidDate()
        {
            return ValidDate;
        }
        internal string GetCardASN()
        {
            return CardASN;
        }
    };
    [StructLayout(LayoutKind.Sequential)]
    
    public struct CONSUMEINFO
    {
        public Int64 psamID;     //PSAM卡号，64位长整型
        public int opFare;        //交易金额
        public int opType;        //交易类型
        public int psamJyNo;      //交易序号
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 20)]
        public string jyDT;      //交易日期时间，YYYY-MM-DD HH:MM:SS
    }
    ;

    class CFunction
    {
        const string str_dll = "wsb_rwinterface.dll";
        [DllImport(str_dll, EntryPoint = "CapReadRecords")]
        public static extern int CapReadRecords(IntPtr info);
        /// <summary>
        /// 打开读卡器连接
        /// </summary>
        /// <returns>0：成功；其他：失败</returns>
        [DllImport(str_dll)]
        //[DllImport(str_dll)]

        public static extern int OpenCom();
        /// <summary>
        /// 寻卡
        /// </summary>
        /// <param name="UID">存放有卡时返回的卡唯一序列号，可以用来区分是否同一张卡</param>
        /// <returns>0：成功；其他：失败</returns>
        [DllImport(str_dll)]
        public static extern int CapNBQueryCard(ref int UID);
        /// <summary>
        /// 读取卡信息
        /// </summary>
        /// <param name="info">客户信息</param>
        /// <returns>0：读卡成功；-1001 数据校验失败；－1400： 卡已经超过使用期限；其他：读卡过程出现错误，读卡失败</returns>
        [DllImport(str_dll)]
        public static extern int CapGetNBCardInfo(ref CUSTOMERINFO info);
        /// <summary>
        /// 扣款
        /// </summary>
        /// <param name="objNo">目标钱包,1-主钱包，11-14公共扩展钱包</param>
        /// <param name="UID">将要扣费的卡的UID</param>
        /// <param name="opFare">扣款金额（单位：分）</param>
        /// <param name="jyDT">扣款时间，YYYY-MM-DD HH:MM:SS</param>
        /// <param name="psamID">PSAM卡号，64位长整型</param>
        /// <param name="psamJyNo">PSAM卡脱机交易序号</param>
        /// <param name="tac">交易验证码</param>
        /// <returns>0:写卡成功；1：非法消费额度；2：不是指定的卡；-601：写卡失败；其他：扣款过程中发生错误，扣款失败</returns>
        [DllImport(str_dll)]
        public static extern int CapSetNBCardInfo(int objNo, int UID, int opFare, string jyDT, ref long psamID, ref int psamJyNo, ref long tac);
        /// <summary>
        /// 扣款（加次/日限额功能）
        /// </summary>
        /// <param name="objNo">目标钱包,1-主钱包，11-14公共扩展钱包</param>
        /// <param name="UID">将要扣费的卡的UID</param>
        /// <param name="opFare">扣款金额（单位：分）</param>
        /// <param name="jyDT">扣款时间，YYYY-MM-DD HH:MM:SS</param>
        /// <param name="onceLmt">平台传入次消费额度，单位：元，如为0，则使用卡上额度</param>
        /// <param name="dayLmt">平台传入日消费额度，单位：元，如为0，则使用卡上额度</param>
        /// <param name="psamID">PSAM卡号，64位长整型</param>
        /// <param name="psamJyNo">PSAM卡脱机交易序号</param>
        /// <param name="tac">交易验证码</param>
        /// <returns>0:写卡成功；1：非法消费额度；2：不是指定的卡；-601：写卡失败；-700：超过次日限额失败；-701：超过次限额；-702：超过日限额；其他：扣款过程中发生错误，扣款失败</returns>
        [DllImport(str_dll)]
        public static extern int CapSetNBCardInfo_LMT(int objNo, int UID, int opFare, string jyDT, int onceLmt, int dayLmt,  long psamID,  int psamJyNo,  int tac);
        /// <summary>
        /// 扣款（超限额后验证密码消费）
        /// </summary>
        /// <param name="objNo">目标钱包,1-主钱包，11-14公共扩展钱包</param>
        /// <param name="UID">将要扣费的卡的UID</param>
        /// <param name="opFare">扣款金额（单位：分）</param>
        /// <param name="jyDT">扣款时间，YYYY-MM-DD HH:MM:SS</param>
        /// <param name="onceLmt">>平台传入次消费额度，单位：元，如为0，则使用卡上额度</param>
        /// <param name="dayLmt">平台传入日消费额度，单位：元，如为0，则使用卡上额度</param>
        /// <param name="pwd">消费验证密码</param>
        /// <param name="psamID">SAM卡号，64位长整型</param>
        /// <param name="psamJyNo">PSAM卡脱机交易序号</param>
        /// <param name="tac">交易验证码</param>
        /// <returns>0:写卡成功；1：非法消费额度；2：不是指定的卡；-601：写卡失败；-700：超过次日限额失败；-701：超过次限额；-702：超过日限额；-703：非法调用；-704：密码验证不通过；其他：扣款过程中发生错误，扣款失败</returns>
        [DllImport(str_dll)]
        public static extern int CapSetNBCardInfo_Verify(int objNo, int UID, int opFare, string jyDT, int onceLmt, int dayLmt, string pwd, ref long psamID, ref int psamJyNo, ref int tac);
        /// <summary>
        /// 从一卡通卡上扣除消费额
        /// </summary>
        /// <param name="objNo"></param>
        /// <param name="uid"></param>
        /// <param name="opFare"></param>
        /// <param name="jyDT">扣款时间，YYYY-MM-DD HH:MM:SS</param>
        /// <param name="psamID"></param>
        /// <param name="psamJyNo"></param>
        /// <param name="tac">交易验证码（字符串，预分配20字节）</param>
        /// <param name="redix">进制（10：十进制；16：十六进制；默认为十进制）</param>
        /// <returns>0:写卡成功；1：非法消费额度；2：不是指定的卡；-601：写卡失败；其它：扣款过程中出现错误，扣款失败</returns>
        [DllImport(str_dll)]
        public static extern int CapSetNBCardInfo_Str(int objNo, int uid, int opFare, string jyDT, ref long psamID, ref int psamJyNo, StringBuilder tac, int redix);
        /// <summary>
        /// 更新日累计消费,-705错误后调用
        /// </summary>
        /// <param name="opFare">扣款金额（单位：分）</param>
        /// <param name="jyDT">扣款时间，YYYY-MM-DD HH:MM:SS</param>
        /// <returns>0：写卡成功；-700：获取次日限额失败；-705：更新日累计限额失败；-706：非法调用；其他：扣款过程中发生错误，扣款失败</returns>
        [DllImport(str_dll)]
        public static extern int CapUpdateNBCardStatus(int opFare, string jyDT);
        /// <summary>
        /// 更新卡次、日限额
        /// </summary>
        /// <param name="onceLmt">次限额（单位：元）</param>
        /// <param name="dayLmt">次限额（单位：元）</param>
        /// <returns>0：写卡成功；-700：获取次、日限额失败；-707：更新失败</returns>
        [DllImport(str_dll)]
        public static extern int CapSetNBCardStatus(int onceLmt, int dayLmt);
        /// <summary>
        /// 设置卡上的消费密码
        /// </summary>
        /// <param name="oldPwd">旧密码</param>
        /// <param name="newPwd">新密码</param>
        /// <returns>0：写卡成功；-710：设置密码失败</returns>
        [DllImport(str_dll)]
        public static extern int CapSetCardPwd(StringBuilder oldPwd, StringBuilder newPwd);
        /// <summary>
        /// 充值初始化
        /// </summary>
        /// <param name="objNo">目标钱包，默认1-主钱包，2-补助钱包</param>
        /// <param name="fare">交易金额（单位：分）</param>
        /// <param name="termId">终端机编号</param>
        /// <param name="bFare">交易前余额（单位：分）</param>
        /// <param name="no">钱包当前交易序号</param>
        /// <param name="random">随机数</param>
        /// <param name="mac1">MAC1</param>
        /// <returns>0：成功；其他：失败</returns>
        [DllImport(str_dll)]
        public static extern int CapChargeInit(int objNo, int fare, ref long termId, ref int bFare, ref int no, ref int random, ref int mac1);
        /// <summary>
        /// 充值
        /// </summary>
        /// <param name="dt">交易日期，YYYY-MM-DD HH:MM:SS</param>
        /// <param name="mac2">主机返回的mac2</param>
        /// <param name="tac">交易验证码</param>
        /// <returns>0：成功；其他：失败</returns>
        [DllImport(str_dll)]
        public static extern int CapCharge(string dt, string mac2, string tac);
        /// <summary>
        /// 从一卡通卡上获取最后一次tac
        /// </summary>
        /// <param name="no">消费计数</param>
        /// <param name="tac">返回tac值，16进制字符串</param>
        /// <returns>0：成功；其他：失败</returns>
        [DllImport(str_dll)]
        public static extern int CapGetConsumeTac(int no,StringBuilder tac);
        /// <summary>
        /// 关闭读卡器连接
        /// </summary>
        [DllImport(str_dll)]
        public static extern void CloseCom();

        /*=====================================居民健康卡接口======================================*/
        /// <summary>
        /// 打开设备
        /// </summary>
        /// <param name="port">端口号</param>
        /// <returns>成功返回当前用户卡设备句柄；失败返回ERROR_OPEN_FAILED。</returns>
        [DllImport(str_dll)]
        public static extern IntPtr OpenDevice(int port);
        /// <summary>
        /// 关闭设备
        /// </summary>
        /// <param name="hdev">设备句柄</param>
        /// <returns>成功，返回0，失败返回相应的错误码</returns>
        [DllImport(str_dll)]
        public static extern int CloseDevice(IntPtr hdev);
        /// <summary>
        /// 设备复位
        /// </summary>
        /// <param name="hdev">设备句柄</param>
        /// <param name="slot">卡槽号（新开普用户卡卡槽号为1，PSAM为3）</param>
        /// <param name="ATR">复位信息</param>
        /// <returns>成功，返回0，失败返回相应的错误码。</returns>
        [DllImport(str_dll)]
        public static extern int PowerOn(IntPtr hdev, int slot, StringBuilder ATR);
        /// <summary>
        /// 发送指令
        /// </summary>
        /// <param name="hdev">设备句柄</param>
        /// <param name="bySlot">卡槽号</param>
        /// <param name="pbyC_Command">指令数据</param>
        /// <param name="bylen">指令长度</param>
        /// <param name="pbyR_Command">返回数据</param>
        /// <param name="pnRes">返回长度</param>
        /// <returns></returns>
        [DllImport(str_dll)]
        public static extern int SendAPDU(IntPtr hdev, int bySlot, StringBuilder pbyC_Command, uint bylen, StringBuilder pbyR_Command, ref int pnRes);
        /// <summary>
        /// 6.2.1	读发卡机构基本数据文件接口
        /// </summary>
        /// <param name="hdev"></param>
        /// <param name="KLB"></param>
        /// <param name="GFBB"></param>
        /// <param name="FKJGMC"></param>
        /// <param name="FKJGDM"></param>
        /// <param name="FKJGZS"></param>
        /// <param name="FKSJ"></param>
        /// <param name="KH"></param>
        /// <param name="AQM"></param>
        /// <param name="XPXLH"></param>
        /// <param name="YYCSDM"></param>
        /// <returns>成功，返回0；否则返回错误代码。</returns>
        [DllImport(str_dll)]
        public static extern int iR_DDF1EF05Info(IntPtr hdev, string KLB, string GFBB, string FKJGMC, string FKJGDM, string FKJGZS, string FKSJ, string KH, string AQM, string XPXLH, string YYCSDM);

        //测试BUSFUC
        [DllImport("busFunc.dll")]
        public static extern IntPtr OpenComm(int port);
        [DllImport("busFunc.dll")]
        public static extern int CloseComm(IntPtr hdev);
        [DllImport("busFunc.dll")]
        public static extern int GetTermInfo(IntPtr hdev,StringBuilder info);
    }
}
