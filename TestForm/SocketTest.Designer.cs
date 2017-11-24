namespace TestForm
{
    partial class SocketTest
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.btn_send = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.txt_IPaddr = new System.Windows.Forms.TextBox();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.txt_port = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.rtb_value = new System.Windows.Forms.RichTextBox();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.rtb_review = new System.Windows.Forms.RichTextBox();
            this.btn_close = new System.Windows.Forms.Button();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.SuspendLayout();
            // 
            // btn_send
            // 
            this.btn_send.Location = new System.Drawing.Point(433, 289);
            this.btn_send.Name = "btn_send";
            this.btn_send.Size = new System.Drawing.Size(75, 23);
            this.btn_send.TabIndex = 0;
            this.btn_send.Text = "发送";
            this.btn_send.UseVisualStyleBackColor = true;
            this.btn_send.Click += new System.EventHandler(this.btn_send_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 25);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(59, 12);
            this.label1.TabIndex = 1;
            this.label1.Text = "服务器IP:";
            // 
            // txt_IPaddr
            // 
            this.txt_IPaddr.Location = new System.Drawing.Point(86, 20);
            this.txt_IPaddr.Name = "txt_IPaddr";
            this.txt_IPaddr.Size = new System.Drawing.Size(178, 21);
            this.txt_IPaddr.TabIndex = 2;
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.txt_port);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.txt_IPaddr);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Location = new System.Drawing.Point(23, 16);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(501, 61);
            this.groupBox1.TabIndex = 3;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "参数设置";
            // 
            // txt_port
            // 
            this.txt_port.Location = new System.Drawing.Point(347, 20);
            this.txt_port.Name = "txt_port";
            this.txt_port.Size = new System.Drawing.Size(121, 21);
            this.txt_port.TabIndex = 2;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(291, 23);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(41, 12);
            this.label2.TabIndex = 1;
            this.label2.Text = "端口：";
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.rtb_value);
            this.groupBox2.Location = new System.Drawing.Point(23, 83);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(501, 100);
            this.groupBox2.TabIndex = 4;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "传参内容";
            // 
            // rtb_value
            // 
            this.rtb_value.Location = new System.Drawing.Point(7, 21);
            this.rtb_value.Name = "rtb_value";
            this.rtb_value.Size = new System.Drawing.Size(488, 73);
            this.rtb_value.TabIndex = 0;
            this.rtb_value.Text = "";
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.rtb_review);
            this.groupBox3.Location = new System.Drawing.Point(23, 190);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(495, 81);
            this.groupBox3.TabIndex = 5;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "返回值";
            // 
            // rtb_review
            // 
            this.rtb_review.Location = new System.Drawing.Point(7, 20);
            this.rtb_review.Name = "rtb_review";
            this.rtb_review.Size = new System.Drawing.Size(488, 54);
            this.rtb_review.TabIndex = 0;
            this.rtb_review.Text = "";
            // 
            // btn_close
            // 
            this.btn_close.Location = new System.Drawing.Point(37, 289);
            this.btn_close.Name = "btn_close";
            this.btn_close.Size = new System.Drawing.Size(75, 23);
            this.btn_close.TabIndex = 6;
            this.btn_close.Text = "关闭";
            this.btn_close.UseVisualStyleBackColor = true;
            // 
            // SocketTest
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(536, 333);
            this.Controls.Add(this.btn_close);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.btn_send);
            this.Name = "SocketTest";
            this.Text = "SocketTest";
            this.Load += new System.EventHandler(this.SocketTest_Load);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox3.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button btn_send;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox txt_IPaddr;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.TextBox txt_port;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.RichTextBox rtb_value;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.RichTextBox rtb_review;
        private System.Windows.Forms.Button btn_close;
    }
}