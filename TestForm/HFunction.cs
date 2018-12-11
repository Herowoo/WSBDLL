using System;
using System.Text;
using System.Runtime.InteropServices;

namespace TestForm
{
    class HFunction
    {
       
        const string str_dll = "wsb_rwinterface.dll";
        [DllImport(str_dll,EntryPoint = "OpenDevice")]
        public static extern IntPtr OpenDevice(int port);
        [DllImport(str_dll, EntryPoint = "CloseDevice")]
        public static extern int CloseDevice(IntPtr hDev);
        [DllImport(str_dll, EntryPoint = "PowerOn",CallingConvention =CallingConvention.StdCall)]
        public static extern int PowerOn(IntPtr dDev, int slot,StringBuilder ATR);
        [DllImport(str_dll, EntryPoint = "iR_DDF1EF05Info",CallingConvention =CallingConvention.StdCall)]

        public static extern int iR_DDF1EF05Info(IntPtr hDev, StringBuilder KLB, StringBuilder GFBB, StringBuilder FKJGMC, StringBuilder FKJGDM, StringBuilder FKJGDZS, StringBuilder FKSJ, StringBuilder KH, StringBuilder AQM, StringBuilder XPXLH, StringBuilder YYCSDM);

        [DllImport(str_dll, CallingConvention = CallingConvention.StdCall)]
        public static extern int SendAPDU(IntPtr hDev, short bySlot, char[] pbyC_Command, int bylen, StringBuilder pbyR_Command, ref int pnRes);
        [DllImport(str_dll, EntryPoint = "iR_DDF1EF06Info")]
        public static extern int iR_DDF1EF06Info(IntPtr hdev, StringBuilder XM, StringBuilder XB, StringBuilder MZ, StringBuilder CSRQ, StringBuilder SFZH);

        //读照片文件
        [DllImport(str_dll, EntryPoint = "iR_DDF1EF07Info")]
        public static extern int iR_DDF1EF07Info(IntPtr hdev, ref byte ZHAOPIAN);
        //读有效期等文件接口
        [DllImport(str_dll, EntryPoint = "iR_DDF1EF08Info")]
        public static extern int iR_DDF1EF08Info(IntPtr hdev, StringBuilder KYXQ, StringBuilder BRDH1, StringBuilder BRDH2, StringBuilder YLFYZFFS1, StringBuilder YLFYZFFS2, StringBuilder YLFYZFFS3);
        //写有效期等文件接口
        [DllImport(str_dll, EntryPoint = "iW_DDF1EF08Info")]
        public static extern int iW_DDF1EF08Info(IntPtr hdev, string KYXQ, string BRDH1, string BRDH2, string YLFYZFFS1, string YLFYZFFS2, string YLFYZFFS3);

        //public static extern int iW_DDF1EF08Info(IntPtr hdev, StringBuilder KYXQ, StringBuilder BRDH1, StringBuilder BRDH2, StringBuilder YLFYZFFS1, StringBuilder YLFYZFFS2, StringBuilder YLFYZFFS3);
        //读地址信息文件接口
        [DllImport(str_dll, EntryPoint = "iR_DF01EF05Info")]
        public static extern int iR_DF01EF05Info(IntPtr hdev, StringBuilder DZLB1, StringBuilder DZ1, StringBuilder DZLB2, StringBuilder DZ2);
        //写地址信息文件接口
        [DllImport(str_dll, EntryPoint = "iW_DF01EF05Info")]
        public static extern int iW_DF01EF05Info(IntPtr hdev, StringBuilder DZLB1, StringBuilder DZ1, StringBuilder DZLB2, StringBuilder DZ2);
        //读联系人信息文件接口
        [DllImport(str_dll, EntryPoint = "iR_DF01EF06Info",CallingConvention = CallingConvention.StdCall)]
        public static extern int iR_DF01EF06Info(IntPtr hdev, StringBuilder LXRXM1, StringBuilder LXRGX1, StringBuilder LXRDH1, StringBuilder LXRXM2, StringBuilder LXRGX2, StringBuilder LXRDH2, StringBuilder LXRXM3, StringBuilder LXRGX3, StringBuilder LXRDH3);
        //写联系人信息文件接口
        [DllImport(str_dll, EntryPoint = "iW_DF01EF06Info")]
        public static extern int iW_DF01EF06Info(IntPtr hdev, StringBuilder LXRXM1, StringBuilder LXRGX1, StringBuilder LXRDH1, StringBuilder LXRXM2, StringBuilder LXRGX2, StringBuilder LXRDH2, StringBuilder LXRXM3, StringBuilder LXRGX3, StringBuilder LXRDH3);
        //读职业婚姻信息文件接口
        [DllImport(str_dll, EntryPoint = "iR_DF01EF07Info")]
        public static extern int iR_DF01EF07Info(IntPtr hdev, StringBuilder WHCD, StringBuilder HYZK, StringBuilder ZY);
        //写职业婚姻信息文件接口
        [DllImport(str_dll, EntryPoint = "iW_DF01EF07Info")]
        public static extern int iW_DF01EF07Info(IntPtr hdev, StringBuilder WHCD, StringBuilder HYZK, StringBuilder ZY);
        //读证件记录信息文件接口
        [DllImport(str_dll, EntryPoint = "iR_DF01EF08Info")]
        public static extern int iR_DF01EF08Info(IntPtr hdev, StringBuilder ZJLB, StringBuilder ZJHM, StringBuilder JKDAH, StringBuilder XNHZH);
        //写证件记录信息文件接口
        [DllImport(str_dll, EntryPoint = "iW_DF01EF08Info")]
        public static extern int iW_DF01EF08Info(IntPtr hdev, StringBuilder ZJLB, StringBuilder ZJHM, StringBuilder JKDAH, StringBuilder XNHZH);
        //读临床基本数据文件接口
        [DllImport(str_dll, EntryPoint = "iR_DF02EF05Info")]
        public static extern int iR_DF02EF05Info(IntPtr hdev, StringBuilder ABOXX, StringBuilder RHXX, StringBuilder XCBZ, StringBuilder XZBBZ, StringBuilder XNXGBBZ, StringBuilder DXBBZ, StringBuilder NXWLBZ, StringBuilder TNBBZ, StringBuilder QGYBZ, StringBuilder TXBZ, StringBuilder QGYZBZ, StringBuilder QGQSBZ, StringBuilder KZXYZBZ, StringBuilder XZQBQBZ, StringBuilder QTYXJSMC);
        //写临床基本数据文件接口
        [DllImport(str_dll, EntryPoint = "iW_DF02EF05Info")]
        public static extern int iW_DF02EF05Info(IntPtr hdev, StringBuilder ABOXX, StringBuilder RHXX, StringBuilder XCBZ, StringBuilder XZBBZ, StringBuilder XNXGBBZ, StringBuilder DXBBZ, StringBuilder NXWLBZ, StringBuilder TNBBZ, StringBuilder QGYBZ, StringBuilder TXBZ, StringBuilder QGYZBZ, StringBuilder QGQSBZ, StringBuilder KZXYZBZ, StringBuilder XZQBQBZ, StringBuilder QTYXJSMC);
        //读特殊信息数据文件接口
        [DllImport(str_dll, EntryPoint = "iR_DF02EF06Info")]
        public static extern int iR_DF02EF06Info(IntPtr hdev, StringBuilder JSBBZ);
        //写特殊信息数据文件接口
        [DllImport(str_dll, EntryPoint = "iW_DF02EF06Info")]
        public static extern int iW_DF02EF06Info(IntPtr hdev, StringBuilder JSBBZ);
        //读过敏基本数据文件接口
        [DllImport(str_dll, EntryPoint = "iR_DF02EF07Info")]
        public static extern int iR_DF02EF07Info(IntPtr hdev, int nRecorderNo, StringBuilder GMWZMC, StringBuilder GMWZFY);
        //写过敏基本数据文件接口
        [DllImport(str_dll, EntryPoint = "iW_DF02EF07Info")]
        public static extern int iW_DF02EF07Info(IntPtr hdev,StringBuilder GMWZMC, StringBuilder GMWZFY);
        //读免疫基本数据文件接口
        [DllImport(str_dll, EntryPoint = "iR_DF02EF08Info")]
        public static extern int iR_DF02EF08Info(IntPtr hdev, int nRecorderNo, StringBuilder MYJZMC, StringBuilder MYJZSJ);
        //写免疫基本数据文件接口
        [DllImport(str_dll, EntryPoint = "iW_DF02EF08Info")]
        public static extern int iW_DF02EF08Info(IntPtr hdev, StringBuilder MYJZMC, StringBuilder MYJZSJ);
        //读住院信息索引文件接口
        [DllImport(str_dll, EntryPoint = "iR_DF03EF05Info")]
        public static extern int iR_DF03EF05Info(IntPtr hdev, StringBuilder ZYJLBS1, StringBuilder ZYJLBS2, StringBuilder ZYJLBS3);
        //写住院信息索引文件接口
        [DllImport(str_dll, EntryPoint = "iW_DF03EF05Info")]
        public static extern int iW_DF03EF05Info(IntPtr hdev, int nRecorderNo);
        //擦除住院信息索引文件接口
        [DllImport(str_dll, EntryPoint = "iErase_DF03EF05Info")]
        public static extern int iErase_DF03EF05Info(IntPtr hdev, int nRecorderNo);
        //读门诊信息索引文件接口
        [DllImport(str_dll, EntryPoint = "iR_DF03EF06Info")]
        public static extern int iR_DF03EF06Info(IntPtr hdev, StringBuilder MZJLBS1, StringBuilder MZJLBS2, StringBuilder MZJLBS3, StringBuilder MZJLBS4, StringBuilder MZJLBS5);
        //写住院信息索引文件接口
        [DllImport(str_dll, EntryPoint = "iW_DF03EF06Info")]
        public static extern int iW_DF03EF06Info(IntPtr hdev, int nRecorderNo);
        //擦除住院信息索引文件接口
        [DllImport(str_dll, EntryPoint = "iErase_DF03EF06Info")]
        public static extern int iErase_DF03EF06Info(IntPtr hdev, int nRecorderNo);
        //读住院信息文件接口
        [DllImport(str_dll, EntryPoint = "iR_DF03EEInfo")]
        public static extern int iR_DF03EEInfo(IntPtr hdev, int nRecorderNo, StringBuilder szDate, int nPos, int nLen, int nStyle);
        //写住院信息文件接口
        [DllImport(str_dll, EntryPoint = "iW_DF03EEInfo")]
        public static extern int iW_DF03EEInfo(IntPtr hdev, int nRecorderNo, StringBuilder szDate, int nPos, int nLen, int nStyle);
        //读过门诊信息文件接口
        [DllImport(str_dll, EntryPoint = "iR_DF03EDInfo")]
        public static extern int iR_DF03EDInfo(IntPtr hdev, int nRecorderNo, StringBuilder szDate, int nPos, int nLen, int nStyle);
        //写过门诊信息文件接口
        [DllImport(str_dll, EntryPoint = "iW_DF03EDInfo")]
        public static extern int iW_DF03EDInfo(IntPtr hdev, int nRecorderNo, StringBuilder szDate, int nPos, int nLen, int nStyle);
        //6.3.1	SM3摘要
        [DllImport(str_dll, EntryPoint = "SM3Digest")]
        public static extern int SM3Digest(IntPtr hdev, ref byte pbDate, int nDateLen, ref byte pbHash, ref byte pbHashLen);
        //6.3.2	PIN验证函数
        [DllImport(str_dll, EntryPoint = "VerifyPin")]
        public static extern int VerifyPin(IntPtr hdev, ref string szPin, byte[] pdwRetry);
        //SM2签名函数
        [DllImport(str_dll, EntryPoint = "SM2SignHash")]
        public static extern int SM2SignHash(IntPtr hdev, ref byte pbDate, byte bLen, ref byte pbSingedDate, ref byte pblength);
        //获取设备序列号
        [DllImport(str_dll, EntryPoint = "IReader_GetDeviceCSN",CallingConvention =CallingConvention.StdCall)]
        public static extern int IReader_GetDeviceCSN(IntPtr hdev, StringBuilder info);
        //获取SAM卡号
        [DllImport(str_dll, EntryPoint = "iReader_SAM_Public", CallingConvention = CallingConvention.StdCall)]
        public static extern int iReader_SAM_Public(IntPtr hdev, StringBuilder info);
        //写发卡机构基本数据文件接口
        [DllImport(str_dll, EntryPoint = "iW_DDF1EF05Info", CallingConvention = CallingConvention.StdCall)]
        public static extern int iW_DDF1EF05Info(IntPtr hDev, StringBuilder KLB, StringBuilder GFBB, StringBuilder FKJGMC, StringBuilder FKJGDM, StringBuilder FKJGDZS, StringBuilder FKSJ, StringBuilder KH, StringBuilder AQM, StringBuilder XPXLH, StringBuilder YYCSDM);
        //写持卡人基本信息数据文件接口
        [DllImport(str_dll, EntryPoint = "iW_DDF1EF06Info", CallingConvention = CallingConvention.StdCall)]
        public static extern int iW_DDF1EF06Info(IntPtr hdev, StringBuilder XM, StringBuilder XB, StringBuilder MZ, StringBuilder CSRQ, StringBuilder SFZH);
        //读照片文件接口
        [DllImport(str_dll, EntryPoint = "iR_DDF1EF07Info", CallingConvention = CallingConvention.StdCall)]
        public static extern int iR_DDF1EF07Info(IntPtr hdev, StringBuilder zhaopianPath);
        //写照片文件接口
        [DllImport(str_dll, EntryPoint = "iW_DDF1EF07Info", CallingConvention = CallingConvention.StdCall)]
        public static extern int iW_DDF1EF07Info(IntPtr hdev, StringBuilder zhaopianPath);
        /// <summary>
        /// 获取住院索引号接口
        /// </summary>
        /// <param name="hdev">设备句柄</param>
        /// <returns>如果成功，返回1-3；否则返回-1。返回住院索引号，如果3条住院信息未写满，则返回第一条标记为FF的记录索引号；如果3条住院信息全部写满，则返回入院日期最早的索引号，若两条入院日期一直则取出院日期最早的索引号。</returns>
        [DllImport(str_dll, EntryPoint = "iReader_GetLastEEIndex", CallingConvention = CallingConvention.StdCall)]
        public static extern int iReader_GetLastEEIndex(IntPtr hdev);
        /// <summary>
        /// 获取门诊索引号接口
        /// </summary>
        /// <param name="hdev">设备句柄</param>
        /// <returns>如果成功，返回1-5；否则返回-1。返回门诊记录索引号，如果5条门诊就诊信息未写满，则返回第一条标记为FF的记录索引号；如果5条门诊就诊信息全部写满，则返回就诊日期最早的索引号</returns>
        [DllImport(str_dll, EntryPoint = "iReader_GetLastEDIndex", CallingConvention = CallingConvention.StdCall)]
        public static extern int iReader_GetLastEDIndex(IntPtr hdev);
        /// <summary>
        /// 锁定人员信息初始化
        /// </summary>
        /// <param name="hdev">设备句柄</param>
        /// <returns>成功返回0</returns>
        [DllImport(str_dll, EntryPoint = "LockPersonalInfo", CallingConvention = CallingConvention.StdCall)]
        public static extern int LockPersonalInfo(IntPtr hdev);

    }
}
