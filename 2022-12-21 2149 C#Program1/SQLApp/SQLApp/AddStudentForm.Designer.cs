namespace SQLApp
{
    partial class AddStudentForm
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
            this.panel1 = new System.Windows.Forms.Panel();
            this.groupCombo = new System.Windows.Forms.ComboBox();
            this.facultyCombo = new System.Windows.Forms.ComboBox();
            this.surnameStudent = new System.Windows.Forms.TextBox();
            this.nameStudent = new System.Windows.Forms.TextBox();
            this.addButton = new System.Windows.Forms.Button();
            this.numberStudent = new System.Windows.Forms.TextBox();
            this.panel2 = new System.Windows.Forms.Panel();
            this.closeButton = new System.Windows.Forms.Label();
            this.panel = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.panel1.SuspendLayout();
            this.panel2.SuspendLayout();
            this.SuspendLayout();
            // 
            // panel1
            // 
            this.panel1.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(104)))), ((int)(((byte)(156)))), ((int)(((byte)(210)))));
            this.panel1.Controls.Add(this.label5);
            this.panel1.Controls.Add(this.label4);
            this.panel1.Controls.Add(this.label3);
            this.panel1.Controls.Add(this.label2);
            this.panel1.Controls.Add(this.label1);
            this.panel1.Controls.Add(this.groupCombo);
            this.panel1.Controls.Add(this.facultyCombo);
            this.panel1.Controls.Add(this.surnameStudent);
            this.panel1.Controls.Add(this.nameStudent);
            this.panel1.Controls.Add(this.addButton);
            this.panel1.Controls.Add(this.numberStudent);
            this.panel1.Controls.Add(this.panel2);
            this.panel1.Location = new System.Drawing.Point(1, -25);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(601, 421);
            this.panel1.TabIndex = 2;
            // 
            // groupCombo
            // 
            this.groupCombo.FormattingEnabled = true;
            this.groupCombo.Location = new System.Drawing.Point(321, 238);
            this.groupCombo.Name = "groupCombo";
            this.groupCombo.Size = new System.Drawing.Size(227, 21);
            this.groupCombo.TabIndex = 13;
            this.groupCombo.Enter += new System.EventHandler(this.group_Enter);
            // 
            // facultyCombo
            // 
            this.facultyCombo.FormattingEnabled = true;
            this.facultyCombo.Location = new System.Drawing.Point(321, 168);
            this.facultyCombo.Name = "facultyCombo";
            this.facultyCombo.Size = new System.Drawing.Size(227, 21);
            this.facultyCombo.TabIndex = 12;
            this.facultyCombo.Enter += new System.EventHandler(this.facultyCombo_Enter);
            // 
            // surnameStudent
            // 
            this.surnameStudent.Location = new System.Drawing.Point(188, 302);
            this.surnameStudent.Multiline = true;
            this.surnameStudent.Name = "surnameStudent";
            this.surnameStudent.Size = new System.Drawing.Size(227, 31);
            this.surnameStudent.TabIndex = 11;
            // 
            // nameStudent
            // 
            this.nameStudent.Location = new System.Drawing.Point(53, 238);
            this.nameStudent.Multiline = true;
            this.nameStudent.Name = "nameStudent";
            this.nameStudent.Size = new System.Drawing.Size(227, 31);
            this.nameStudent.TabIndex = 8;
            // 
            // addButton
            // 
            this.addButton.Cursor = System.Windows.Forms.Cursors.Hand;
            this.addButton.Font = new System.Drawing.Font("Times New Roman", 15F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.addButton.Location = new System.Drawing.Point(201, 354);
            this.addButton.Name = "addButton";
            this.addButton.Size = new System.Drawing.Size(201, 42);
            this.addButton.TabIndex = 5;
            this.addButton.Text = "Добавить";
            this.addButton.UseVisualStyleBackColor = true;
            this.addButton.Click += new System.EventHandler(this.addButton_Click);
            // 
            // numberStudent
            // 
            this.numberStudent.Location = new System.Drawing.Point(53, 168);
            this.numberStudent.Multiline = true;
            this.numberStudent.Name = "numberStudent";
            this.numberStudent.Size = new System.Drawing.Size(227, 31);
            this.numberStudent.TabIndex = 2;
            // 
            // panel2
            // 
            this.panel2.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(65)))), ((int)(((byte)(136)))), ((int)(((byte)(210)))));
            this.panel2.Controls.Add(this.closeButton);
            this.panel2.Controls.Add(this.panel);
            this.panel2.Dock = System.Windows.Forms.DockStyle.Top;
            this.panel2.Location = new System.Drawing.Point(0, 0);
            this.panel2.Name = "panel2";
            this.panel2.Size = new System.Drawing.Size(601, 130);
            this.panel2.TabIndex = 0;
            // 
            // closeButton
            // 
            this.closeButton.AutoSize = true;
            this.closeButton.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(65)))), ((int)(((byte)(136)))), ((int)(((byte)(210)))));
            this.closeButton.Cursor = System.Windows.Forms.Cursors.Hand;
            this.closeButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 24F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.closeButton.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(239)))), ((int)(((byte)(239)))), ((int)(((byte)(239)))));
            this.closeButton.Location = new System.Drawing.Point(565, 24);
            this.closeButton.Name = "closeButton";
            this.closeButton.Size = new System.Drawing.Size(39, 37);
            this.closeButton.TabIndex = 1;
            this.closeButton.Text = "X";
            this.closeButton.Click += new System.EventHandler(this.closeButton_Click);
            this.closeButton.MouseDown += new System.Windows.Forms.MouseEventHandler(this.closeButton_MouseDown);
            this.closeButton.MouseLeave += new System.EventHandler(this.closeButton_MouseLeave);
            this.closeButton.MouseHover += new System.EventHandler(this.closeButton_MouseHover);
            // 
            // panel
            // 
            this.panel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel.Font = new System.Drawing.Font("Times New Roman", 20.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.panel.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(239)))), ((int)(((byte)(239)))), ((int)(((byte)(239)))));
            this.panel.Location = new System.Drawing.Point(0, 0);
            this.panel.Name = "panel";
            this.panel.Size = new System.Drawing.Size(601, 130);
            this.panel.TabIndex = 0;
            this.panel.Text = "Добавление студента";
            this.panel.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.panel.MouseDown += new System.Windows.Forms.MouseEventHandler(this.panel_MouseDown);
            this.panel.MouseMove += new System.Windows.Forms.MouseEventHandler(this.panel_MouseMove);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(53, 149);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(96, 13);
            this.label1.TabIndex = 14;
            this.label1.Text = "Student ID number";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(56, 219);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(35, 13);
            this.label2.TabIndex = 15;
            this.label2.Text = "Name";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(321, 149);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(41, 13);
            this.label3.TabIndex = 16;
            this.label3.Text = "Faculty";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(321, 219);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(36, 13);
            this.label4.TabIndex = 17;
            this.label4.Text = "Group";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(188, 283);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(49, 13);
            this.label5.TabIndex = 18;
            this.label5.Text = "Surname";
            // 
            // AddStudentForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(604, 398);
            this.Controls.Add(this.panel1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            this.Name = "AddStudentForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "AddStudentForm";
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            this.panel2.ResumeLayout(false);
            this.panel2.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.TextBox nameStudent;
        private System.Windows.Forms.Button addButton;
        private System.Windows.Forms.TextBox numberStudent;
        private System.Windows.Forms.Panel panel2;
        private System.Windows.Forms.Label closeButton;
        private System.Windows.Forms.Label panel;
        private System.Windows.Forms.TextBox surnameStudent;
        private System.Windows.Forms.ComboBox groupCombo;
        private System.Windows.Forms.ComboBox facultyCombo;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
    }
}