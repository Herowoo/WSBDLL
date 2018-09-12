using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.Globalization;
using Newtonsoft.Json;

namespace TestForm
{
    public partial class HID : Form
    {
        IntPtr hdv;
        
        //string atr = null;
        public HID()
        {
            InitializeComponent();
        }

        private void btn_conn_Click(object sender, EventArgs e)
        {
            hdv = HFunction.OpenDevice(0);
          
        }

        private void btn_poweron_Click(object sender, EventArgs e)
        {
            StringBuilder atr_1 = new StringBuilder(100);
            StringBuilder atr_2 = new StringBuilder(100);
            int slot_xkp = 1;
            int slot_psam = 3;

            int status_xkp = HFunction.PowerOn(hdv, slot_xkp, atr_1);
            MessageBox.Show("用户卡返回atr: " + atr_1.ToString());
            int status_psam = HFunction.PowerOn(hdv, slot_psam, atr_2);
            MessageBox.Show("PSAM卡返回atr: " + atr_2.ToString());
            if (status_psam == 0)
            {
                MessageBox.Show("PSAM复位成功");
            }
            else
                MessageBox.Show("PSAM卡复位失败");

            if (status_xkp == 0)
            {
                MessageBox.Show("用户卡复位成功");
            }
            else
                MessageBox.Show("用户卡复位失败");
        }

        private void btn_close_Click(object sender, EventArgs e)
        {
            int status_close = HFunction.CloseDevice(hdv);
            MessageBox.Show(status_close.ToString());
        }

        private void btn_readcard_Click(object sender, EventArgs e)
        {
            //string kh = null;
            //string klb = null;
            //string gfbb = null;
            //string fkjgmc = null;
            //string fkjgdm = null;
            //string fkjgzs = null;
            //string fksj = null;
            //string aqm = null;
            //string xpxlh = null;
            //string yycsdm = null;

            //byte[] klb = new byte[10];
            //byte[] gfbb = new byte[10];
            //byte[] fkjgmc = new byte[20];
            //byte[] fkjgdm = new byte[30];
            //byte[] fkjgzs = new byte[100];
            //byte[] fksj = new byte[10];
            //byte[] kh = new byte[30];
            //byte[] aqm = new byte[10];
            //byte[] xpxlh = new byte[10];
            //byte[] yycsdm  = new byte[10];
            StringBuilder atr_1 = new StringBuilder(100);
            StringBuilder atr_2 = new StringBuilder(100);
            int slot_xkp = 1;
            int slot_psam = 3;

            int status_xkp = HFunction.PowerOn(hdv, slot_xkp, atr_1);
            int status_psam = HFunction.PowerOn(hdv, slot_psam, atr_2);

            StringBuilder klb = new StringBuilder(1000);
            StringBuilder gfbb = new StringBuilder(1000);
            StringBuilder fkjgmc = new StringBuilder(1000);
            StringBuilder fkjgdm = new StringBuilder(1000);
            StringBuilder fkjgzs = new StringBuilder(1000);
            StringBuilder fksj = new StringBuilder(1000);
            StringBuilder kh = new StringBuilder(1000);
            StringBuilder aqm = new StringBuilder(1000);
            StringBuilder xpxlh = new StringBuilder(1000);
            StringBuilder yycsdm = new StringBuilder(1000);

            int status = HFunction.iR_DDF1EF05Info(hdv,klb,gfbb,fkjgmc,fkjgdm,fkjgzs,fksj,kh,aqm,xpxlh,yycsdm);

            txt_kh.Text = kh.ToString();
            txt_aqm.Text = aqm.ToString();
            txt_fkjgdm.Text = fkjgdm.ToString();
            txt_fkjgmc.Text = fkjgmc.ToString();
            txt_fkjgzs.Text = fkjgzs.ToString();
            txt_fksj.Text = fksj.ToString();
            txt_gfbb.Text = gfbb.ToString();
            txt_klb.Text = klb.ToString();
            txt_xpxlh.Text = xpxlh.ToString();
            txt_yycsdm.Text = yycsdm.ToString();
        }
        public static byte[] ConvertStringToByte(string data)
        {
            byte[] bData = null;
            string sData = data;
            if (sData.Length > 0)
            {
                bData = new byte[sData.Length / 2];
                for (int nJ = 0; nJ < sData.Length; nJ += 2)
                    bData[nJ / 2] = byte.Parse(sData.Substring(nJ, 2), NumberStyles.AllowHexSpecifier);
            }
            
            return bData;
        }
        public static char[] ConverStringToChar(string data)
        {
            char[] array = null;
            string _data = data;
            if (_data.Length>0)
            {
                array = new char[_data.Length / 2];
                for (int i = 0; i < _data.Length; i+=2)
                {
                    string temp = _data.Substring(i, 2);
                    int value = Convert.ToInt32(temp,16);
                    array[i / 2] = (char)value;
                }
            }
            return array;

        }
        private void btn_sendApdu_Click(object sender, EventArgs e)
        {
            const int slot = 1;
            string sbd_pbyc = txt_pbyc.Text.Trim();
            
            char[] array = ConverStringToChar(sbd_pbyc);//Encoding.ASCII.GetBytes(sbd_pbyc);
            //array[0] = 
            //array[1] = Convert.ToChar(0x02);
            //array[2] = Convert.ToChar(0x01);
            //array[3] = Convert.ToChar(0x01);
            //array[4] = Convert.ToChar(0x00);
            //array[5] = Convert.ToChar(0x00);
            int len_comm = array.Length;
            StringBuilder sbd_pbyr = new StringBuilder(1000);
            int len_pbyr = 0;
            int status = HFunction.SendAPDU(hdv, slot, array, len_comm, sbd_pbyr, ref len_pbyr);
            if (status==0)
            {
                MessageBox.Show("指令发送成功！");
            }
            else
                MessageBox.Show("指令发送失败，错误码："+status.ToString());
            rtb_pbyr.Text = sbd_pbyr.ToString();
        }

        private void btn_ReadDDF1EF08_Click(object sender, EventArgs e)
        {
            
            StringBuilder sb_YXQ = new StringBuilder(1000);
            StringBuilder sb_DH1 = new StringBuilder(1000);
            StringBuilder sb_DH2 = new StringBuilder(1000);
            StringBuilder sb_ZFFS1 = new StringBuilder(1000);
            StringBuilder sb_ZFFS2 = new StringBuilder(1000);
            StringBuilder sb_ZFFS3 = new StringBuilder(1000);

            int status = HFunction.iR_DDF1EF08Info(hdv, sb_YXQ, sb_DH1, sb_DH2, sb_ZFFS1, sb_ZFFS2, sb_ZFFS3);
            if (status==0)
            {
                txt_KYXQ.Text = sb_YXQ.ToString();
                txt_DH1.Text = sb_DH1.ToString();
                txt_DH2.Text = sb_DH2.ToString();
                txt_ZFFS1.Text = sb_ZFFS1.ToString();
                txt_ZFFS2.Text = sb_ZFFS2.ToString();
                txt_ZFFS3.Text = sb_ZFFS3.ToString();
            }
            else
            {
                MessageBox.Show("读取信息失败，错误码："+status.ToString());
            }
        }

        private void btn_readcard_Click_1(object sender, EventArgs e)
        {
            btn_readcard_Click(sender, e);
        }

        private void btn_WriteDDF1EF08_Click(object sender, EventArgs e)
        {
            //StringBuilder sb_YXQ = new StringBuilder(8 + 1);
            //StringBuilder sb_DH1 = new StringBuilder(20 + 1);
            //StringBuilder sb_DH2 = new StringBuilder(20 + 1);
            //StringBuilder sb_ZFFS1 = new StringBuilder(2 + 1);
            //StringBuilder sb_ZFFS2 = new StringBuilder(2 + 1);
            //StringBuilder sb_ZFFS3 = new StringBuilder(3 + 1);
            //sb_YXQ.Append(txt_KYXQ.Text.Trim());
            //sb_DH1.Append(txt_DH1.Text.Trim());
            //sb_DH2.Append(txt_DH2.Text.Trim());
            //sb_ZFFS1.Append(txt_ZFFS1.Text.Trim());
            //sb_ZFFS2.Append(txt_ZFFS2.Text.Trim());
            //sb_ZFFS3.Append(txt_ZFFS3.Text.Trim());
            string sb_YXQ = txt_KYXQ.Text.Trim();
            string sb_DH1 = txt_DH1.Text.Trim();
            string sb_DH2 = txt_DH2.Text.Trim();
            string sb_ZFFS1 = txt_ZFFS1.Text.Trim();
            string sb_ZFFS2 = txt_ZFFS2.Text.Trim();
            string sb_ZFFS3 = txt_ZFFS3.Text.Trim();
           
            int status = HFunction.iW_DDF1EF08Info(hdv, sb_YXQ, sb_DH1, sb_DH2, sb_ZFFS1, sb_ZFFS2, sb_ZFFS3);
            if (status == 0)
            {
                MessageBox.Show("写卡成功！");
            }
            else
            {
                MessageBox.Show("读取信息失败，错误码：" + status.ToString());
            }
        }

        private void label17_Click(object sender, EventArgs e)
        {

        }

        private void btn_R_DDF1EF06_Click(object sender, EventArgs e)
        {
            StringBuilder sb_lxrxm1 = new StringBuilder(1024);
            StringBuilder sb_lxrgx1 = new StringBuilder(1024);
            StringBuilder sb_lxrdh1 = new StringBuilder(1024);
            StringBuilder sb_lxrxm2 = new StringBuilder(1024);
            StringBuilder sb_lxrgx2 = new StringBuilder(1024);
            StringBuilder sb_lxrdh2 = new StringBuilder(1024);
            StringBuilder sb_lxrxm3 = new StringBuilder(1024);
            StringBuilder sb_lxrgx3 = new StringBuilder(1024);
            StringBuilder sb_lxrdh3 = new StringBuilder(1024);
            int status = HFunction.iR_DF01EF06Info(hdv, sb_lxrxm1, sb_lxrgx1, sb_lxrdh1, sb_lxrxm2, sb_lxrgx2, sb_lxrdh2, sb_lxrxm3, sb_lxrgx3, sb_lxrdh3);
            if (status == 0)
            {
                txt_lxrxm1.Text = sb_lxrxm1.ToString();
                txt_lxrgx1.Text = sb_lxrgx1.ToString();
                txt_lxrdh1.Text = sb_lxrdh1.ToString();
                txt_lxrxm2.Text = sb_lxrxm2.ToString();
                txt_lxrgx2.Text = sb_lxrgx2.ToString();
                txt_lxrdh2.Text = sb_lxrdh2.ToString();
            }
            else
            {
                MessageBox.Show("读取信息失败，错误码：" + status.ToString());
            }
        }

        private void btn_W_DDF1EF06_Click(object sender, EventArgs e)
        {
            StringBuilder sb_lxrxm1 = new StringBuilder(30 + 1);
            StringBuilder sb_lxrgx1 = new StringBuilder(2 + 1);
            StringBuilder sb_lxrdh1 = new StringBuilder(20 + 1);
            StringBuilder sb_lxrxm2 = new StringBuilder(30 + 1);
            StringBuilder sb_lxrgx2 = new StringBuilder(2 + 1);
            StringBuilder sb_lxrdh2 = new StringBuilder(20 + 1);
            StringBuilder sb_lxrxm3 = new StringBuilder(30 + 1);
            StringBuilder sb_lxrgx3 = new StringBuilder(2 + 1);
            StringBuilder sb_lxrdh3 = new StringBuilder(20 + 1);
            sb_lxrxm1.Append(txt_lxrxm1.Text.Trim());
            sb_lxrgx1.Append(txt_lxrgx1.Text.Trim());
            sb_lxrdh1.Append(txt_lxrdh1.Text.Trim());
            sb_lxrxm2.Append(txt_lxrxm2.Text.Trim());
            sb_lxrgx2.Append(txt_lxrgx2.Text.Trim());
            sb_lxrdh2.Append(txt_lxrdh2.Text.Trim());

            int status = HFunction.iW_DF01EF06Info(hdv, sb_lxrxm1, sb_lxrgx1, sb_lxrdh1, sb_lxrxm2, sb_lxrgx2, sb_lxrdh2, sb_lxrxm3, sb_lxrgx3, sb_lxrdh3);
            if (status == 0)
            {
                MessageBox.Show("写卡成功");
            }
            else
                MessageBox.Show("写卡失败，错误码：" + status.ToString());
        }

        private void btn_verifyPin_Click(object sender, EventArgs e)
        {
            string _pin = txt_szPin.Text.Trim();
            byte[] _retryPin = new byte[1];
            _retryPin.SetValue(byte.Parse(txt_pinRetry.Text.Trim()), 0);
            int ret = HFunction.VerifyPin(hdv, ref _pin, _retryPin);
            if (ret==0)
            {
                MessageBox.Show("PIN验证成功");
            }
            else
                MessageBox.Show(ret.ToString());
        }

        private void btn_getCSN_Click(object sender, EventArgs e)
        {
            StringBuilder _CSN = new StringBuilder(100);
            int status = HFunction.IReader_GetDeviceCSN(hdv, _CSN);
            if (status==0)
            {
                txt_DeviceCSN.Text = _CSN.ToString();
            }
            else
                MessageBox.Show("获取失败，错误码： "+status);
        }

        private void btn_R_SAM_Click(object sender, EventArgs e)
        {
            StringBuilder _CSN = new StringBuilder(100);
            int status = HFunction.iReader_SAM_Public(hdv, _CSN);
            if (status == 0)
            {
                txt_SAMinfo.Text = _CSN.ToString();
            }
            else
                MessageBox.Show("获取失败，错误码： " + status);
        }
        struct DF02EF05
        {
            public int status { get; set; }
            //ABO血型代码
            public string ABOXX { get; set; }
            //RH血型代码
            public string RHXX { get; set; }
            //哮喘标志
            public string XCBZ { get; set; }
            //心脏病标志
            public string XZBBZ { get; set; }
            //心脑血管病标志
            public string XNXGBBZ { get; set; }
            //癫痫病标志
            public string DXBBZ { get; set; }
            //凝血紊乱标志
            public string NXWLBZ { get; set; }
            //糖尿病标志
            public string TNBBZ { get; set; }
            //青光眼标志
            public string QGYBZ { get; set; }
            //透析标志
            public string TXBZ { get; set; }
            //器官移植标志
            public string QGYZBZ { get; set; }
            //器官缺失标志
            public string QGQSBZ { get; set; }
            //可装卸义肢标志
            public string KZXYZBZ { get; set; }
            //心脏起搏器标志
            public string XZQBQBZ { get; set; }
            //其他医学警示名称
            public string QTYXJSMC { get; set; }
        }
        private  void btn_df02ef05_Click(object sender, EventArgs e)
        {
            StringBuilder _ABOXX = new StringBuilder(1000);
            StringBuilder _RHXX = new StringBuilder(1000);
            StringBuilder _XCBZ = new StringBuilder(1000);
            StringBuilder _XZBBZ = new StringBuilder(1000);
            StringBuilder _XNXGBBZ = new StringBuilder(1000);
            StringBuilder _DXBBZ = new StringBuilder(1000);
            StringBuilder _NXWLBZ = new StringBuilder(1000);
            StringBuilder _TNBBZ = new StringBuilder(1000);
            StringBuilder _QGYBZ = new StringBuilder(1000);
            StringBuilder _TXBZ = new StringBuilder(1000);
            StringBuilder _QGYZBZ = new StringBuilder(1000);
            StringBuilder _QGQSBZ = new StringBuilder(1000);
            StringBuilder _KZXYZBZ = new StringBuilder(1000);
            StringBuilder _XZQBQBZ = new StringBuilder(1000);
            StringBuilder _QTYXJSMC = new StringBuilder(1000);
            int status_R_DF02EF05 = HFunction.iR_DF02EF05Info(hdv, _ABOXX, _RHXX, _XCBZ, _XZBBZ, _XNXGBBZ, _DXBBZ, _NXWLBZ, _TNBBZ, _QGYBZ, _TXBZ, _QGYZBZ, _QGQSBZ, _KZXYZBZ, _XZQBQBZ, _QTYXJSMC);
            DF02EF05 df02ef05 = new DF02EF05();
            df02ef05.ABOXX = _ABOXX.ToString();
            df02ef05.RHXX = _RHXX.ToString();
            df02ef05.XCBZ = _XCBZ.ToString();
            df02ef05.XZBBZ = _XZBBZ.ToString();
            df02ef05.XNXGBBZ = _XNXGBBZ.ToString();
            df02ef05.DXBBZ = _DXBBZ.ToString();
            df02ef05.NXWLBZ = _NXWLBZ.ToString();
            df02ef05.TNBBZ = _TNBBZ.ToString();
            df02ef05.QGYBZ = _QGYBZ.ToString();
            df02ef05.TXBZ = _TXBZ.ToString();
            df02ef05.QGYZBZ = _QGYZBZ.ToString();
            df02ef05.QGQSBZ = _QGQSBZ.ToString();
            df02ef05.KZXYZBZ = _KZXYZBZ.ToString();
            df02ef05.XZQBQBZ = _XZQBQBZ.ToString();
            df02ef05.QTYXJSMC = _QTYXJSMC.ToString();
            df02ef05.status = status_R_DF02EF05;

            rtb_df02ef05.Text = JsonConvert.SerializeObject(df02ef05);
        }
    }
}
