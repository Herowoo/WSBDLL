using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Timers;
using System.Media;
using System.IO;
using System.Collections;
using System.Diagnostics;

namespace TestForm
{
    public partial class FormCheckCard : Form
    {
        //健康卡设备句柄
        IntPtr hdev;
        //城市通uid
        int uid = 0;
        //城市通寻卡状态
        int s_qcard_xdt = -1;   
        //用户卡复位状态
        int s_poweron1_jkk = -1;   
        //PSAM卡复位状态 
        int s_poweron3_jkk = -1;
        //timer时间间隔,单位毫秒
        const int tick = 2000;
        //new timer
        System.Timers.Timer t1 = new System.Timers.Timer(tick);
        //读卡器连接状态
        bool is_open = false;
        //新建HashTable，存储ATR与status
        //哈希表存值会出现异常，暂时弃用
        //Hashtable ht = new Hashtable();
        //存储上一张卡片ATR
        string ATR;
        //存放上一张卡片读卡状态
        int read_status;
        //验卡时间计数器
        Stopwatch sw = new Stopwatch();
        //验卡总数
        int total_cardnum;
        public FormCheckCard()
        {
            InitializeComponent();
        }

        private void FormCheckCard_Load(object sender, EventArgs e)
        {
            cob_checktype.Items.Add("自动验卡");
            cob_checktype.Items.Add("手动验卡");
            cob_checktype.SelectedIndex = 0;
            cob_checktype.DropDownStyle = ComboBoxStyle.DropDownList;
            cob_tiptype.Items.Add("语音提示");
            cob_tiptype.Items.Add("弹框提示");
            cob_tiptype.Items.Add("文字提示");
            cob_tiptype.SelectedIndex = 0;
            cob_tiptype.DropDownStyle = ComboBoxStyle.DropDownList;
            Control.CheckForIllegalCrossThreadCalls = false;
            total_cardnum = 0;
        }
        //连接读卡器
        private void btn_open_Click(object sender, EventArgs e)
        {
            if (is_open)
            {
                //do nothing
            }
            else
            {
                hdev = HFunction.OpenDevice(0);
                 if (hdev != (IntPtr)0)
                {
                    lbl_lianjie_zt.Text = "读卡器连接失败！";
                    lbl_lianjie_zt.ForeColor = Color.Red;
                }
                else
                {
                    //由于PSAM只需要复位一次,因此在此增加复位PSAM卡功能
                    StringBuilder PSAMATR = new StringBuilder(128);
                    s_poweron3_jkk = CFunction.PowerOn(hdev, 3, PSAMATR);
                    if (s_poweron3_jkk==0)
                    {
                        lbl_lianjie_zt.Text = "读卡器连接成功";
                        lbl_lianjie_zt.ForeColor = Color.Green;
                        is_open = true;
                    }
                    else
                    {
                        lbl_lianjie_zt.Text = "PSAM卡复位失败！";
                        lbl_lianjie_zt.ForeColor = Color.Red;
                    }
                }
            }
        }
        //验证卡片状态
        private bool Verify_ATR(string atr)
        {
            //是否与上一张卡ATR相同
            if (atr.Equals(ATR))
            {
                //读卡状态是否正常
                if (read_status==0)
                {
                    return false;
                }
                //异常卡验卡次数是否超过最大限制
                else if(abnomal_checktick < max_checktick)
                {
                    abnomal_checktick++;
                    return true;
                }
                else
                {
                    abnomal_checktick = 0;
                    return false;
                }

            }
            else
            {
                abnomal_checktick = 0;
                return true;
            }
        }
        //自动寻卡
        private void QueryCard(object source, System.Timers.ElapsedEventArgs e)
        {
            StringBuilder cardatr = new StringBuilder(128);
            s_poweron1_jkk = HFunction.PowerOn(hdev,1,cardatr);
            //int _uid = 0;
            //s_qcard_xdt = CFunction.CapNBQueryCard(ref _uid);
            if (s_poweron1_jkk==0)
            {
                string _atr = cardatr.ToString();
                ReadCard(_atr);
            }
            else
            {
                //do nothing
            }
        }
        
        //状态展示
        private void ShowStatus(int stat)
        {
            //语音提示
            if (cob_tiptype.SelectedIndex == 0)
            {
                //判断音频文件是否存在
                //根目录
                string path = Environment.CurrentDirectory.ToString();
                string wav1_path = path + @"\正常.wav";
                string wav2_path = path + @"\卡片异常.wav";
                if (File.Exists(wav1_path)&&File.Exists(wav2_path))
                {
                    switch (stat)
                    {
                        case 0:
                            new SoundPlayer(".//正常.wav").Play();
                            break;
                        default:
                            new SoundPlayer(".//卡片异常.wav").Play();
                            break;
                    }
                }
                else
                {
                    MessageBox.Show("音频文件丢失");
                    t1.Stop();
                }
            }
            //弹窗提示
            if (cob_tiptype.SelectedIndex == 1)
            {
                switch (stat)
                {
                    case 0:
                        MessageBox.Show("读卡成功！");
                        break;
                    default:
                        MessageBox.Show("卡片异常！");
                        break;
                    
                }
            }
            if (cob_tiptype.SelectedIndex == 2)
            {
                switch (stat)
                {
                    case 0:
                        lab_tip.Text = "读卡成功！";
                        lab_tip.ForeColor = Color.Green;
                        break;
                    default:
                        lab_tip.Text = "卡片异常！";
                        lab_tip.ForeColor = Color.Red;
                        break;
                }
            }
        }
        //读取卡片数据
        private void ReadCard(string atr)
        {
            CUSTOMERINFO custinfo = new CUSTOMERINFO();

            if (Verify_ATR(atr))
            {
                //状态值等于下面三个变量组成的3位二进制的十进制值，例如s_qcard_xdt != 0 ,s_poweron1_jkk = 0,s_poweron3_jkk=0,则status=0b100,即8
                StringBuilder klb = new StringBuilder(128);
                StringBuilder gfbb = new StringBuilder(128);
                StringBuilder fkjgmc = new StringBuilder(128);
                StringBuilder fkjgdm = new StringBuilder(128);
                StringBuilder fkjgzs = new StringBuilder(1024);
                StringBuilder fksj = new StringBuilder(128);
                StringBuilder kh = new StringBuilder(128);
                StringBuilder aqm = new StringBuilder(128);
                StringBuilder xpxlh = new StringBuilder(128);
                StringBuilder yycsdm = new StringBuilder(128);
                int r_jkk = HFunction.iR_DDF1EF05Info(hdev, klb, gfbb, fkjgmc, fkjgdm, fkjgzs, fksj, kh, aqm, xpxlh, yycsdm);
                int r_xdt = CFunction.CapGetNBCardInfo(ref custinfo);
                if ((r_xdt == 0) && (r_jkk == 0))
                {
                    if ((custinfo.Name.Length == 0) && (kh.ToString().Length == 0))
                    {
                        read_status = -3;    //城市通与健康卡均未读到数据
                    }
                    if ((custinfo.Name.Length != 0) && (kh.ToString().Length == 0))
                    {
                        read_status = -2;    //城市通正常,健康卡未读到数据
                    }
                    if ((custinfo.Name.Length == 0) && (kh.ToString().Length != 0))
                    {
                        read_status = -1;    //城市通未读到数据,健康卡正常
                    }
                    if ((custinfo.Name.Length != 0) && (kh.ToString().Length != 0))
                    {
                        read_status = 0;
                    }
                }
                else
                {
                    read_status = -1;
                }
                //更新ATR
                total_cardnum++;
                ATR = atr;
                UpdateLog(custinfo.Name, atr, read_status);
                ShowStatus(read_status);
                ShowLog(custinfo.Name,atr, read_status);
            }
            else
            {
                
            }
        }
       
        //开始验卡
        private void btn_checkcard_Click(object sender, EventArgs e)
        {
            //判断读卡器是否连接
            if (!is_open)
            {
                //do nothing
                MessageBox.Show("请先连接读卡器");
            }
            else
            {
                sw.Start();
                rtb_log.Clear();
                //自动验卡
                if (cob_checktype.SelectedIndex == 0)
                {
                    //判断自动验卡是否启动
                    if (!t1.Enabled)
                    {
                        t1.Elapsed += new System.Timers.ElapsedEventHandler(QueryCard);
                        t1.AutoReset = true;
                        t1.Enabled = true;
                    }
                }
                //手动验卡
                if (cob_checktype.SelectedIndex == 1)
                {
                    StringBuilder cardatr = new StringBuilder(128);
                    s_poweron1_jkk = HFunction.PowerOn(hdev, 1, cardatr);
                    //int _uid = 0;
                    //s_qcard_xdt = CFunction.CapNBQueryCard(ref _uid);
                    if (s_poweron1_jkk == 0)
                    {
                        string _atr = cardatr.ToString();
                        ReadCard(_atr);
                    }
                    else
                    {
                        //do nothing
                        
                    }
                }
            }
            
        }
        StringBuilder _log = new StringBuilder();

        /// <summary>
        /// 在richtextbox中显示验卡日志
        /// </summary>
        private void ShowLog(string name,string atr,int card_status)
        {
            //读卡状态
            string _zhuangtai;  
            //当前时间
            string _now = DateTime.Now.ToString("HH:mm:ss")+": ";
            if (card_status == 0)
            {
                _zhuangtai = "正常";
            }
            else
                _zhuangtai = "异常！ 返回： " + card_status.ToString();
            string _str = _now + "姓名:" + name +",ATR:"+atr+",状态："+ _zhuangtai +"\r\n" ;
            _log.Append(_str);
            rtb_log.Text = _log.ToString();
        }
        private void UpdateLog(string name,string atr,int card_status)
        {
            string _now = DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss") + ": ";
            string _str = _now + "姓名:" + name + ",ATR:" + atr + ",状态：" + card_status;
            string path = Environment.CurrentDirectory.ToString()+@"\CheckLog\";
            string file_path = Environment.CurrentDirectory.ToString() + @"\CheckLog\" + DateTime.Now.ToString("yyyy-MM-dd") + ".log";
            if (!Directory.Exists(path))
            {
                Directory.CreateDirectory(path);
            }
            if (!File.Exists(file_path))
            {
                File.Create(file_path);
            }
            File.AppendAllText(file_path, _str + Environment.NewLine);

        }
        //设置异常卡片的最大重新验证次数
        const int max_checktick = 3;
        //异常卡片验证次数
        int abnomal_checktick = 0;
        //停止验卡
        private void btn_close_Click(object sender, EventArgs e)
        {
            if (t1.Enabled)
            {
                t1.Close();
                sw.Stop();
                string tongji = "本次共验卡" + total_cardnum.ToString() + "张，用时" + TransMilliseconds(sw.Elapsed) +"\r\n";
                _log.Append(tongji);
                rtb_log.Text = _log.ToString();
                total_cardnum = 0;
            }
        }
        private string TransMilliseconds(TimeSpan ts)
        {
          
            string usual_time = ts.Hours + "小时" + ts.Minutes + "分" + ts.Seconds + "秒";
            return usual_time;
        }
        //关闭读卡器
        private void button1_Click(object sender, EventArgs e)
        {
            if (is_open)
            {
                HFunction.CloseDevice(hdev);
                is_open = false;
                lbl_lianjie_zt.Text = "读卡器连接已关闭";
                lbl_lianjie_zt.ForeColor = Color.Black;
            }
        }

        private void FormCheckCard_KeyPress(object sender, KeyPressEventArgs e)
        {
          
        }

        private void FormCheckCard_KeyDown(object sender, KeyEventArgs e)
        {
            
        }
        //根据验卡方式改变 停止验卡按钮可用状态
        private void cob_checktype_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (cob_checktype.SelectedIndex==1)
            {
                btn_close.Enabled = false;
                t1.Stop();
            }
            if (cob_checktype.SelectedIndex==0)
            {
                btn_close.Enabled = true;
            }
        }

        private void richTextBox1_TextChanged(object sender, EventArgs e)
        {
            rtb_log.SelectionStart = rtb_log.Text.Length;
            rtb_log.ScrollToCaret();
        }

        private void btn_pause_Click(object sender, EventArgs e)
        {
            if (t1.Enabled)
            {
                t1.Close();
                MessageBox.Show("验卡已暂停");
            }
        }
    }
}
