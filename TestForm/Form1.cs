using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.Reflection;
using System.Reflection.Emit;
using Newtonsoft.Json;
using System.IO;

namespace TestForm
{
    public partial class Form1 : Form
    {
        int id;
        long psamid;
        int psamjyno;
        int _tac;
        CUSTOMERINFO cust_info = new CUSTOMERINFO();

        public Form1()
        {
            InitializeComponent();
            
        }

        //[DllImport("kernel32.dll")]
        //static extern IntPtr LoadLibrary(string lpFileName);
        //[DllImport("kernel32.dll")]
        //static extern IntPtr GetProcAddress(IntPtr hModule, string lpProcName);
        //[DllImport("kernel32", EntryPoint = "FreeLibrary", SetLastError = true)]
        //static extern bool FreeLibrary(IntPtr hModule);
        //private IntPtr hModule = IntPtr.Zero;
        //private IntPtr farProc = IntPtr.Zero;
        struct mycustinfo
        {

            public int zhuangtai { get; set; }
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
        }
        private void button1_Click(object sender, EventArgs e)
        {

            int status_getinfo = CFunction.CapGetNBCardInfo(ref cust_info);

            mycustinfo mycust = new mycustinfo();
            mycust.zhuangtai = status_getinfo;
            mycust.CardClass = cust_info.CardClass;
            mycust.CustomerID = cust_info.CustomerID;
            mycust.CardSN = cust_info.CardSN;
            mycust.Status = cust_info.Status;
            mycust.SubType = cust_info.SubType;
            mycust.Ye = cust_info.Ye;
            mycust.OpCount = cust_info.OpCount;
            mycust.Name = cust_info.Name;
            mycust.ValidDate = cust_info.ValidDate;
            mycust.CardASN = cust_info.CardASN;
            richTextBox1.Text = JsonConvert.SerializeObject(mycust);
            //switch (get_status)
            //{
            //    case -1801:
            //        MessageBox.Show("加载DLL失败");
            //        break;
            //    case -1701:
            //        MessageBox.Show("找不到程序入口");
            //        break;
            //    case 463:
            //        MessageBox.Show("非正常卡");
            //        break;
            //    case 404:
            //        MessageBox.Show("验证接口连接异常");
            //        break;
            //    default:
            //        MessageBox.Show("正常卡");
            //        break;
            //}
        }
        struct CardInfo_Set
        {
            public int _opfare { get; set; }
            public int _objno { get; set; }
            public string _jydate { get; set; }
            public long _psamid { get; set; }
            public int _psamjyno { get; set; }
            public long _tac { get; set; }

        }
        struct CardInfo_Set_Str
        {
            //目标钱包,1-主钱包，11-14公共扩展钱包
            public int objNo { get; set; }
            //将要扣费的卡的UID
            public int UID { get; set; }
            //扣款金额（单位：分）
            public int opFare { get; set; }
            //扣款时间，YYYY-MM-DD HH:MM:SS
            public string jyDT { get; set; }
            //PSAM卡号，64位长整型
            public long psamID { get; set; }
            //PSAM卡脱机交易序号
            public int psamJyNo { get; set; }
            //交易验证码
            public string tac { get; set; }
        }
        //扣款（TAC返回字符串），返回json格式信息
        public string CapSetNBCardInfo_Str_Json(int objno, int opfare, string jydate, int redix)
        {
            int _objno = objno;
            int _opfare = opfare;
            string _jydate = jydate;
            int _redix = redix;

            long _psamid = 0;
            int _psamjyno = 0;
            StringBuilder _tac = new StringBuilder(20);

            int status_setinfo_str = CFunction.CapSetNBCardInfo_Str(_objno, id, _opfare, _jydate, ref _psamid, ref _psamjyno, _tac, _redix);
            if (status_setinfo_str == 0)
            {
                CardInfo_Set_Str cardstr = new CardInfo_Set_Str();
                cardstr.jyDT = _jydate;
                cardstr.objNo = _objno;
                cardstr.opFare = _opfare;
                cardstr.psamID = _psamid;
                cardstr.psamJyNo = _psamjyno;
                cardstr.tac = _tac.ToString();
                cardstr.UID = id;
                string json = JsonConvert.SerializeObject(cardstr);
                return json;
            }
            else
                return null;
        }
        private void button2_Click(object sender, EventArgs e)
        {
            CardInfo_Set cardset = new CardInfo_Set();
            //cardset._opfare = int.Parse(txt_opFare.Text.Trim());
            //cardset._objno = 1;
            //cardset._jydate = txt_JYDate.Text.Trim();
            int _objno = 1;
            int _opfare = int.Parse(txt_opFare.Text.Trim());
            string _jydate = txt_JYDate.Text.Trim();
            long _psamid = 0;
            int _psamjyno = 0;
            long _tac = 0;
            int setValueStatus = CFunction.CapSetNBCardInfo(_objno, id, _opfare, _jydate,ref _psamid,ref _psamjyno,ref _tac);
            cardset._opfare = _opfare;
            cardset._objno = _objno;
            cardset._jydate = _jydate;
            cardset._psamid = _psamid;
            cardset._psamjyno = _psamjyno;
            cardset._tac = _tac;
            MessageBox.Show("扣款状态：" + setValueStatus.ToString());
            richTextBox1.Text = JsonConvert.SerializeObject(cardset);
            lbl_SetValueStatus.Text = "扣款状态：" + setValueStatus.ToString();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            txt_JYDate.Text = System.DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss");
        }

        private void btn_openCOM_Click(object sender, EventArgs e)
        {
            int open_status = CFunction.OpenCom();
            lbl_openStatus.Text = open_status.ToString();
        }

        private void btn_cloaseCOM_Click(object sender, EventArgs e)
        {
            CFunction.CloseCom();
        }

        private void btn_queryCard_Click(object sender, EventArgs e)
        {
            int query_status = CFunction.CapNBQueryCard(ref id);
            lbl_querystatus.Text = query_status.ToString();
        }

        private void btn_modPWD_Click(object sender, EventArgs e)
        {
            string old_pwd = txt_oldPWD.Text.Trim();
            string new_pwd = txt_newPWD.Text.Trim();
            StringBuilder old = new StringBuilder(old_pwd);
            StringBuilder xin = new StringBuilder(new_pwd);
            int mod_status = CFunction.CapSetCardPwd(old, xin);
            if (mod_status == 0)
            {
                MessageBox.Show("修改成功，新的密码为：" + new_pwd.ToString());
            }
            else
            {
                MessageBox.Show(mod_status.ToString());
            }
        }

        private void btn_getTAC_Click(object sender, EventArgs e)
        {
            int no = cust_info.GetOpCount();
            //string _tac = null;
            StringBuilder _tac = new StringBuilder();
            int status = CFunction.CapGetConsumeTac(no, _tac);
            txt_tac.Text = _tac.ToString();
            MessageBox.Show(status.ToString());
        }
        private delegate int CapGetConsumeTacEventHandler(int no, ref string tac);
        private string GetCustJosn(CUSTOMERINFO cust)
        {
            
            
            if (cust.GetName().Length==0)
            {
                return null;
            }
            else
            {
                string json = "{";
                json += "\"CardClass\""+":"+"\""+cust.GetCardClass()+"\"" +",";
                json += "\"CustomerID\"" + ":" + "\"" + cust.GetCustomerID() + "\"" + ",";
                json += "\"CardSN\"" + ":" + "\"" + cust.GetCardSN() + "\"" + ",";
                json += "\"Status\"" + ":" + "\"" + cust.GetStatus() + "\"" + ",";
                json += "\"SubType\"" + ":" + "\"" + cust.GetSubType() + "\"" + ",";
                json += "\"Ye\"" + ":" + "\"" + cust.GetYe() + "\"" + ",";
                json += "\"OpCount\"" + ":" + "\"" + cust.GetOpCount() + "\"" + ",";
                json += "\"Name\"" + ":" + "\"" + cust.GetName() + "\"" + ",";
                json += "\"ValidDate\"" + ":" + "\"" + cust.GetValidDate() + "\"" + ",";
                json += "\"CardASN\"" + ":" + "\"" + cust.GetCardASN() + "\"" ;
                json += "}";
                return json;
            }
        }

        private void button2_Click_1(object sender, EventArgs e)
        {
            int _objno = 1;
            int _opfare = int.Parse(txt_opFare.Text.Trim());
            string _jydate = txt_JYDate.Text.Trim();
            int _redix = int.Parse(txt_redix.Text.Trim());

            string json = CapSetNBCardInfo_Str_Json(_objno, _opfare, _jydate, _redix);
            richTextBox1.Text = json;
        }

        private void label5_Click(object sender, EventArgs e)
        {

        }

        private void btn_Terminfo_Click(object sender, EventArgs e)
        {
            IntPtr hdv = HFunction.OpenDevice(0);
            StringBuilder atr_1 = new StringBuilder(30);
            StringBuilder atr_2 = new StringBuilder(30);
            int slot_xkp = 1;
            int slot_psam = 3;
            int status_xkp = HFunction.PowerOn(hdv, slot_xkp, atr_1);

            int status_psam = HFunction.PowerOn(hdv, slot_psam, atr_2);
            //===============
            StringBuilder _info = new StringBuilder(100);
            //_hev = CFunction.OpenComm(0);
            int status = CFunction.GetTermInfo(hdv, _info);
            if (status==0)
            {
                txt_TermInfo.Text = _info.ToString();
            }
            else
            {
                MessageBox.Show("获取失败，错误码： " + status);

            }
            //CFunction.CloseComm(_hev);

        }
        struct DDF1EF06
        {
            //成功，返回0；否则返回错误代码。
            public int status { get; set; }
            //姓名
            public string XM { get; set; }
            //性别
            public string XB { get; set; }
            //民族代码
            public string MZ { get; set; }
            //出生日期
            public string CSRQ { get; set; }
            //身份证号 
            public string SFZH { get; set; }
        }
        //读取卡中DDF1EF06中的数据
        public string iR_DDF1EF06Info(IntPtr hdev)
        {
            IntPtr _hdev = hdev;
            StringBuilder _xm = new StringBuilder(31);
            StringBuilder _xb = new StringBuilder(3);
            StringBuilder _mz = new StringBuilder(3);
            StringBuilder _csrq = new StringBuilder(9);
            StringBuilder _sfzh = new StringBuilder(19);

            int status_R_DDF1EF06 = HFunction.iR_DDF1EF06Info(_hdev, _xm, _xb, _mz, _csrq, _sfzh);

            DDF1EF06 df1ef06 = new DDF1EF06();
            df1ef06.XM = _xm.ToString();
            df1ef06.XB = _xb.ToString();
            df1ef06.MZ = _mz.ToString();
            df1ef06.CSRQ = _csrq.ToString();
            df1ef06.SFZH = _sfzh.ToString();
            df1ef06.status = status_R_DDF1EF06;

            return JsonConvert.SerializeObject(df1ef06);
        }
        DDF1EF06 ef06;
        public string ReadPersonInfo()
        {
            IntPtr _hdev = HFunction.OpenDevice(0);
            string json = iR_DDF1EF06Info(_hdev);
            ef06 = JsonConvert.DeserializeObject<DDF1EF06>(json);
            string _name = cust_info.Name;
            string _sfz = ef06.SFZH;
            string result = _name + "@" + "@" + _sfz + "@0@1@0";
            return result;
        }

        private void btn_WN_Click(object sender, EventArgs e)
        {
            try
            {
                int size = Marshal.SizeOf(typeof(CONSUMEINFO)) * 10;
                IntPtr pbuff = Marshal.AllocHGlobal(size);
                CONSUMEINFO[] info = new CONSUMEINFO[10];
                int s = CFunction.CapReadRecords(pbuff);

                if (s==0)
                {
                    string str = "";
                    for (int i = 0; i < 10; i++)
                    {
                        IntPtr pp = new IntPtr(pbuff.ToInt64() + Marshal.SizeOf(typeof(CONSUMEINFO)) * i);
                        info[i] = (CONSUMEINFO)Marshal.PtrToStructure(pp, typeof(CONSUMEINFO));
                        str += JsonConvert.SerializeObject(info[i]);
                    }
                    Marshal.FreeHGlobal(pbuff);
                    richTextBox1.Text = str;
                }
                else
                    MessageBox.Show("调用失败，错误码： "+s.ToString());
            }
            catch (Exception ex)
            {

                throw;
            }
                
        }
    }
}
