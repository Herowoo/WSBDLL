namespace TestForm
{
    partial class Form1
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要修改
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.button1 = new System.Windows.Forms.Button();
            this.lbl_openStatus = new System.Windows.Forms.Label();
            this.richTextBox1 = new System.Windows.Forms.RichTextBox();
            this.txt_opFare = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.txt_JYDate = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.lbl_SetValueStatus = new System.Windows.Forms.Label();
            this.btn_SetCapValue = new System.Windows.Forms.Button();
            this.btn_openCOM = new System.Windows.Forms.Button();
            this.btn_cloaseCOM = new System.Windows.Forms.Button();
            this.lbl_closeStatus = new System.Windows.Forms.Label();
            this.btn_queryCard = new System.Windows.Forms.Button();
            this.lbl_querystatus = new System.Windows.Forms.Label();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.btn_modPWD = new System.Windows.Forms.Button();
            this.txt_newPWD = new System.Windows.Forms.TextBox();
            this.txt_oldPWD = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.btn_getTAC = new System.Windows.Forms.Button();
            this.txt_tac = new System.Windows.Forms.TextBox();
            this.button2 = new System.Windows.Forms.Button();
            this.txt_redix = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            this.btn_Terminfo = new System.Windows.Forms.Button();
            this.txt_TermInfo = new System.Windows.Forms.TextBox();
            this.btn_WN = new System.Windows.Forms.Button();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.SuspendLayout();
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(525, 44);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 23);
            this.button1.TabIndex = 0;
            this.button1.Text = "读卡";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // lbl_openStatus
            // 
            this.lbl_openStatus.AutoSize = true;
            this.lbl_openStatus.Location = new System.Drawing.Point(132, 49);
            this.lbl_openStatus.Name = "lbl_openStatus";
            this.lbl_openStatus.Size = new System.Drawing.Size(0, 12);
            this.lbl_openStatus.TabIndex = 1;
            // 
            // richTextBox1
            // 
            this.richTextBox1.Location = new System.Drawing.Point(41, 86);
            this.richTextBox1.Name = "richTextBox1";
            this.richTextBox1.Size = new System.Drawing.Size(565, 144);
            this.richTextBox1.TabIndex = 2;
            this.richTextBox1.Text = "";
            // 
            // txt_opFare
            // 
            this.txt_opFare.Location = new System.Drawing.Point(124, 40);
            this.txt_opFare.Name = "txt_opFare";
            this.txt_opFare.Size = new System.Drawing.Size(100, 21);
            this.txt_opFare.TabIndex = 3;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(53, 49);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(53, 12);
            this.label2.TabIndex = 4;
            this.label2.Text = "扣款金额";
            // 
            // txt_JYDate
            // 
            this.txt_JYDate.Location = new System.Drawing.Point(347, 40);
            this.txt_JYDate.Name = "txt_JYDate";
            this.txt_JYDate.Size = new System.Drawing.Size(120, 21);
            this.txt_JYDate.TabIndex = 3;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(276, 49);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(53, 12);
            this.label3.TabIndex = 4;
            this.label3.Text = "交易时间";
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.lbl_SetValueStatus);
            this.groupBox1.Controls.Add(this.btn_SetCapValue);
            this.groupBox1.Controls.Add(this.txt_JYDate);
            this.groupBox1.Controls.Add(this.label3);
            this.groupBox1.Controls.Add(this.txt_opFare);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Location = new System.Drawing.Point(41, 236);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(565, 89);
            this.groupBox1.TabIndex = 5;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "扣款";
            // 
            // lbl_SetValueStatus
            // 
            this.lbl_SetValueStatus.AutoSize = true;
            this.lbl_SetValueStatus.ForeColor = System.Drawing.Color.Red;
            this.lbl_SetValueStatus.Location = new System.Drawing.Point(318, 99);
            this.lbl_SetValueStatus.Name = "lbl_SetValueStatus";
            this.lbl_SetValueStatus.Size = new System.Drawing.Size(0, 12);
            this.lbl_SetValueStatus.TabIndex = 6;
            // 
            // btn_SetCapValue
            // 
            this.btn_SetCapValue.Location = new System.Drawing.Point(484, 38);
            this.btn_SetCapValue.Name = "btn_SetCapValue";
            this.btn_SetCapValue.Size = new System.Drawing.Size(75, 23);
            this.btn_SetCapValue.TabIndex = 5;
            this.btn_SetCapValue.Text = "扣款";
            this.btn_SetCapValue.UseVisualStyleBackColor = true;
            this.btn_SetCapValue.Click += new System.EventHandler(this.button2_Click);
            // 
            // btn_openCOM
            // 
            this.btn_openCOM.Location = new System.Drawing.Point(41, 44);
            this.btn_openCOM.Name = "btn_openCOM";
            this.btn_openCOM.Size = new System.Drawing.Size(75, 23);
            this.btn_openCOM.TabIndex = 6;
            this.btn_openCOM.Text = "连接读卡器";
            this.btn_openCOM.UseVisualStyleBackColor = true;
            this.btn_openCOM.Click += new System.EventHandler(this.btn_openCOM_Click);
            // 
            // btn_cloaseCOM
            // 
            this.btn_cloaseCOM.Location = new System.Drawing.Point(512, 606);
            this.btn_cloaseCOM.Name = "btn_cloaseCOM";
            this.btn_cloaseCOM.Size = new System.Drawing.Size(75, 23);
            this.btn_cloaseCOM.TabIndex = 7;
            this.btn_cloaseCOM.Text = "关闭读卡器";
            this.btn_cloaseCOM.UseVisualStyleBackColor = true;
            this.btn_cloaseCOM.Click += new System.EventHandler(this.btn_cloaseCOM_Click);
            // 
            // lbl_closeStatus
            // 
            this.lbl_closeStatus.AutoSize = true;
            this.lbl_closeStatus.Location = new System.Drawing.Point(123, 404);
            this.lbl_closeStatus.Name = "lbl_closeStatus";
            this.lbl_closeStatus.Size = new System.Drawing.Size(0, 12);
            this.lbl_closeStatus.TabIndex = 8;
            // 
            // btn_queryCard
            // 
            this.btn_queryCard.Location = new System.Drawing.Point(259, 44);
            this.btn_queryCard.Name = "btn_queryCard";
            this.btn_queryCard.Size = new System.Drawing.Size(75, 23);
            this.btn_queryCard.TabIndex = 9;
            this.btn_queryCard.Text = "寻卡";
            this.btn_queryCard.UseVisualStyleBackColor = true;
            this.btn_queryCard.Click += new System.EventHandler(this.btn_queryCard_Click);
            // 
            // lbl_querystatus
            // 
            this.lbl_querystatus.AutoSize = true;
            this.lbl_querystatus.Location = new System.Drawing.Point(361, 49);
            this.lbl_querystatus.Name = "lbl_querystatus";
            this.lbl_querystatus.Size = new System.Drawing.Size(0, 12);
            this.lbl_querystatus.TabIndex = 10;
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.btn_modPWD);
            this.groupBox2.Controls.Add(this.txt_newPWD);
            this.groupBox2.Controls.Add(this.txt_oldPWD);
            this.groupBox2.Controls.Add(this.label4);
            this.groupBox2.Controls.Add(this.label1);
            this.groupBox2.Location = new System.Drawing.Point(41, 331);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(565, 92);
            this.groupBox2.TabIndex = 11;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "修改密码";
            // 
            // btn_modPWD
            // 
            this.btn_modPWD.Location = new System.Drawing.Point(484, 43);
            this.btn_modPWD.Name = "btn_modPWD";
            this.btn_modPWD.Size = new System.Drawing.Size(75, 23);
            this.btn_modPWD.TabIndex = 5;
            this.btn_modPWD.Text = "确认";
            this.btn_modPWD.UseVisualStyleBackColor = true;
            this.btn_modPWD.Click += new System.EventHandler(this.btn_modPWD_Click);
            // 
            // txt_newPWD
            // 
            this.txt_newPWD.Location = new System.Drawing.Point(347, 43);
            this.txt_newPWD.Name = "txt_newPWD";
            this.txt_newPWD.Size = new System.Drawing.Size(100, 21);
            this.txt_newPWD.TabIndex = 0;
            // 
            // txt_oldPWD
            // 
            this.txt_oldPWD.Location = new System.Drawing.Point(124, 43);
            this.txt_oldPWD.Name = "txt_oldPWD";
            this.txt_oldPWD.Size = new System.Drawing.Size(100, 21);
            this.txt_oldPWD.TabIndex = 0;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(276, 52);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(53, 12);
            this.label4.TabIndex = 4;
            this.label4.Text = "新密码：";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(53, 52);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(53, 12);
            this.label1.TabIndex = 4;
            this.label1.Text = "旧密码：";
            // 
            // btn_getTAC
            // 
            this.btn_getTAC.Location = new System.Drawing.Point(57, 571);
            this.btn_getTAC.Name = "btn_getTAC";
            this.btn_getTAC.Size = new System.Drawing.Size(75, 23);
            this.btn_getTAC.TabIndex = 0;
            this.btn_getTAC.Text = "获取tac值";
            this.btn_getTAC.UseVisualStyleBackColor = true;
            this.btn_getTAC.Click += new System.EventHandler(this.btn_getTAC_Click);
            // 
            // txt_tac
            // 
            this.txt_tac.Location = new System.Drawing.Point(165, 573);
            this.txt_tac.Name = "txt_tac";
            this.txt_tac.Size = new System.Drawing.Size(100, 21);
            this.txt_tac.TabIndex = 12;
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(462, 520);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(138, 23);
            this.button2.TabIndex = 13;
            this.button2.Text = "扣款，返回字符串TAC";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click_1);
            // 
            // txt_redix
            // 
            this.txt_redix.Location = new System.Drawing.Point(374, 522);
            this.txt_redix.Name = "txt_redix";
            this.txt_redix.Size = new System.Drawing.Size(67, 21);
            this.txt_redix.TabIndex = 14;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(317, 525);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(29, 12);
            this.label5.TabIndex = 15;
            this.label5.Text = "进制";
            this.label5.Click += new System.EventHandler(this.label5_Click);
            // 
            // btn_Terminfo
            // 
            this.btn_Terminfo.Location = new System.Drawing.Point(57, 437);
            this.btn_Terminfo.Name = "btn_Terminfo";
            this.btn_Terminfo.Size = new System.Drawing.Size(75, 23);
            this.btn_Terminfo.TabIndex = 16;
            this.btn_Terminfo.Text = "TermInfo";
            this.btn_Terminfo.UseVisualStyleBackColor = true;
            this.btn_Terminfo.Click += new System.EventHandler(this.btn_Terminfo_Click);
            // 
            // txt_TermInfo
            // 
            this.txt_TermInfo.Location = new System.Drawing.Point(165, 439);
            this.txt_TermInfo.Name = "txt_TermInfo";
            this.txt_TermInfo.Size = new System.Drawing.Size(100, 21);
            this.txt_TermInfo.TabIndex = 17;
            // 
            // btn_WN
            // 
            this.btn_WN.Location = new System.Drawing.Point(57, 493);
            this.btn_WN.Name = "btn_WN";
            this.btn_WN.Size = new System.Drawing.Size(75, 23);
            this.btn_WN.TabIndex = 18;
            this.btn_WN.Text = "万能button";
            this.btn_WN.UseVisualStyleBackColor = true;
            this.btn_WN.Click += new System.EventHandler(this.btn_WN_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(623, 660);
            this.Controls.Add(this.btn_WN);
            this.Controls.Add(this.txt_TermInfo);
            this.Controls.Add(this.btn_Terminfo);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.txt_redix);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.txt_tac);
            this.Controls.Add(this.btn_getTAC);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.lbl_querystatus);
            this.Controls.Add(this.btn_queryCard);
            this.Controls.Add(this.lbl_closeStatus);
            this.Controls.Add(this.btn_cloaseCOM);
            this.Controls.Add(this.btn_openCOM);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.richTextBox1);
            this.Controls.Add(this.lbl_openStatus);
            this.Controls.Add(this.button1);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Label lbl_openStatus;
        private System.Windows.Forms.RichTextBox richTextBox1;
        private System.Windows.Forms.TextBox txt_opFare;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox txt_JYDate;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Button btn_SetCapValue;
        private System.Windows.Forms.Label lbl_SetValueStatus;
        private System.Windows.Forms.Button btn_openCOM;
        private System.Windows.Forms.Button btn_cloaseCOM;
        private System.Windows.Forms.Label lbl_closeStatus;
        private System.Windows.Forms.Button btn_queryCard;
        private System.Windows.Forms.Label lbl_querystatus;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Button btn_modPWD;
        private System.Windows.Forms.TextBox txt_newPWD;
        private System.Windows.Forms.TextBox txt_oldPWD;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button btn_getTAC;
        private System.Windows.Forms.TextBox txt_tac;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.TextBox txt_redix;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Button btn_Terminfo;
        private System.Windows.Forms.TextBox txt_TermInfo;
        private System.Windows.Forms.Button btn_WN;
    }
}

