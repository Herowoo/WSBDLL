using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace TestForm
{
    public partial class 修改用户地址 : Form
    {
        IntPtr hdv;

        public 修改用户地址()
        {
            InitializeComponent();
        }

        private void Form2_Load(object sender, EventArgs e)
        {
            comboBox1.Items.Add("城乡一体化示范区尚集镇陈门村居委会7组");
            comboBox1.Items.Add("城乡一体化示范区尚集镇陈门村居委会8组");
            comboBox1.SelectedIndex = 0;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            hdv = HFunction.OpenDevice(0);

        }

        private void button2_Click(object sender, EventArgs e)
        {
            StringBuilder atr_1 = new StringBuilder(100);
            StringBuilder atr_2 = new StringBuilder(100);
            int slot_xkp = 1;
            int slot_psam = 3;

            int status_xkp = HFunction.PowerOn(hdv, slot_xkp, atr_1);
            int status_psam = HFunction.PowerOn(hdv, slot_psam, atr_2);

            if (status_xkp==0&&status_psam==0)
            {
                StringBuilder dzlb1 = new StringBuilder(128);
                StringBuilder dz1 = new StringBuilder(128);
                StringBuilder dzlb2 = new StringBuilder(128);
                StringBuilder dz2 = new StringBuilder(128);

                dzlb1.Append("1");
                dz1.Append(comboBox1.Text);
                dzlb2.Append("");
                dz2.Append("");

                int st = HFunction.iW_DF01EF05Info(hdv, dzlb1, dz1, dzlb2, dz2);
                if (st==0)
                {
                    MessageBox.Show("写入成功！");
                }
                else
                    MessageBox.Show("写入失败，错误码："+st.ToString());
            }
            else
            {
                MessageBox.Show("复位失败！");
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            int status_close = HFunction.CloseDevice(hdv);
            MessageBox.Show(status_close.ToString());
        }
    }
}
