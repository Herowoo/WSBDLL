namespace TestForm
{
    partial class FormCheckCard
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
            this.cob_checktype = new System.Windows.Forms.ComboBox();
            this.cob_tiptype = new System.Windows.Forms.ComboBox();
            this.btn_open = new System.Windows.Forms.Button();
            this.btn_checkcard = new System.Windows.Forms.Button();
            this.btn_close = new System.Windows.Forms.Button();
            this.lab_tip = new System.Windows.Forms.Label();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.label3 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.button1 = new System.Windows.Forms.Button();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.lbl_lianjie_zt = new System.Windows.Forms.Label();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.rtb_log = new System.Windows.Forms.RichTextBox();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.SuspendLayout();
            // 
            // cob_checktype
            // 
            this.cob_checktype.FormattingEnabled = true;
            this.cob_checktype.Location = new System.Drawing.Point(88, 25);
            this.cob_checktype.Name = "cob_checktype";
            this.cob_checktype.Size = new System.Drawing.Size(95, 20);
            this.cob_checktype.TabIndex = 0;
            this.cob_checktype.SelectedIndexChanged += new System.EventHandler(this.cob_checktype_SelectedIndexChanged);
            // 
            // cob_tiptype
            // 
            this.cob_tiptype.FormattingEnabled = true;
            this.cob_tiptype.Location = new System.Drawing.Point(339, 25);
            this.cob_tiptype.Name = "cob_tiptype";
            this.cob_tiptype.Size = new System.Drawing.Size(95, 20);
            this.cob_tiptype.TabIndex = 0;
            // 
            // btn_open
            // 
            this.btn_open.Location = new System.Drawing.Point(27, 20);
            this.btn_open.Name = "btn_open";
            this.btn_open.Size = new System.Drawing.Size(77, 23);
            this.btn_open.TabIndex = 1;
            this.btn_open.Text = "连接读卡器";
            this.btn_open.UseVisualStyleBackColor = true;
            this.btn_open.Click += new System.EventHandler(this.btn_open_Click);
            // 
            // btn_checkcard
            // 
            this.btn_checkcard.Location = new System.Drawing.Point(27, 420);
            this.btn_checkcard.Name = "btn_checkcard";
            this.btn_checkcard.Size = new System.Drawing.Size(77, 23);
            this.btn_checkcard.TabIndex = 1;
            this.btn_checkcard.Text = "开始验卡";
            this.btn_checkcard.UseVisualStyleBackColor = true;
            this.btn_checkcard.Click += new System.EventHandler(this.btn_checkcard_Click);
            // 
            // btn_close
            // 
            this.btn_close.Location = new System.Drawing.Point(339, 420);
            this.btn_close.Name = "btn_close";
            this.btn_close.Size = new System.Drawing.Size(77, 23);
            this.btn_close.TabIndex = 1;
            this.btn_close.Text = "停止验卡";
            this.btn_close.UseVisualStyleBackColor = true;
            this.btn_close.Click += new System.EventHandler(this.btn_close_Click);
            // 
            // lab_tip
            // 
            this.lab_tip.AutoSize = true;
            this.lab_tip.ForeColor = System.Drawing.Color.DarkRed;
            this.lab_tip.Location = new System.Drawing.Point(112, 427);
            this.lab_tip.Name = "lab_tip";
            this.lab_tip.Size = new System.Drawing.Size(0, 12);
            this.lab_tip.TabIndex = 2;
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.label3);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.cob_checktype);
            this.groupBox1.Controls.Add(this.cob_tiptype);
            this.groupBox1.Location = new System.Drawing.Point(21, 76);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(464, 63);
            this.groupBox1.TabIndex = 3;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "设置";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(268, 28);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(65, 12);
            this.label3.TabIndex = 1;
            this.label3.Text = "提示方式：";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(17, 28);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(65, 12);
            this.label2.TabIndex = 1;
            this.label2.Text = "验卡方式：";
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(339, 20);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(77, 23);
            this.button1.TabIndex = 4;
            this.button1.Text = "关闭读卡器";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.lbl_lianjie_zt);
            this.groupBox2.Controls.Add(this.button1);
            this.groupBox2.Controls.Add(this.btn_open);
            this.groupBox2.Location = new System.Drawing.Point(21, 12);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(464, 59);
            this.groupBox2.TabIndex = 5;
            this.groupBox2.TabStop = false;
            // 
            // lbl_lianjie_zt
            // 
            this.lbl_lianjie_zt.AutoSize = true;
            this.lbl_lianjie_zt.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.lbl_lianjie_zt.Location = new System.Drawing.Point(118, 24);
            this.lbl_lianjie_zt.Name = "lbl_lianjie_zt";
            this.lbl_lianjie_zt.Size = new System.Drawing.Size(0, 12);
            this.lbl_lianjie_zt.TabIndex = 5;
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.rtb_log);
            this.groupBox3.Controls.Add(this.btn_checkcard);
            this.groupBox3.Controls.Add(this.btn_close);
            this.groupBox3.Controls.Add(this.lab_tip);
            this.groupBox3.Location = new System.Drawing.Point(21, 145);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(464, 460);
            this.groupBox3.TabIndex = 6;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "验卡操作";
            // 
            // rtb_log
            // 
            this.rtb_log.Location = new System.Drawing.Point(19, 20);
            this.rtb_log.Name = "rtb_log";
            this.rtb_log.ReadOnly = true;
            this.rtb_log.Size = new System.Drawing.Size(429, 385);
            this.rtb_log.TabIndex = 7;
            this.rtb_log.Text = "";
            this.rtb_log.TextChanged += new System.EventHandler(this.richTextBox1_TextChanged);
            // 
            // FormCheckCard
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(506, 617);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.Name = "FormCheckCard";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "二合一验卡";
            this.Load += new System.EventHandler(this.FormCheckCard_Load);
            this.KeyDown += new System.Windows.Forms.KeyEventHandler(this.FormCheckCard_KeyDown);
            this.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.FormCheckCard_KeyPress);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.ComboBox cob_checktype;
        private System.Windows.Forms.ComboBox cob_tiptype;
        private System.Windows.Forms.Button btn_open;
        private System.Windows.Forms.Button btn_checkcard;
        private System.Windows.Forms.Button btn_close;
        private System.Windows.Forms.Label lab_tip;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.RichTextBox rtb_log;
        private System.Windows.Forms.Label lbl_lianjie_zt;
    }
}