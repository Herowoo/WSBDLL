using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Net;
using System.Net.Sockets;

namespace TestForm
{
    public partial class SocketTest : Form
    {
        public SocketTest()
        {
            InitializeComponent();
        }

        private void btn_send_Click(object sender, EventArgs e)
        {
            string IPaddr = txt_IPaddr.Text.Trim();             
            int port = Int32.Parse(txt_port.Text.Trim());
            string value = rtb_value.Text.Trim();
            string recive = null;
            IPAddress ip = IPAddress.Parse(IPaddr);
            IPEndPoint endpoint = new IPEndPoint(ip, port);
            byte[] data = new byte[1024];
            Socket socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            try
            {
                socket.Connect(endpoint);
            }
            catch (SocketException a)
            {
                MessageBox.Show("Fail to connect server");
                MessageBox.Show(a.ToString());
                return;
            }

            int recv = socket.Receive(data);
            data = Encoding.ASCII.GetBytes(value);
            socket.Send(data, data.Length, SocketFlags.None);
            recive = Encoding.ASCII.GetString(data, 0, recv);
            rtb_review.Text = recive;
            
        }

        private void SocketTest_Load(object sender, EventArgs e)
        {

        }
    }
}
