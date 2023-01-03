using MySql.Data.MySqlClient;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace SQLApp
{
    public partial class LoginForm : Form
    {
        public LoginForm()
        {
            InitializeComponent();
        }

        private void closeButton_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void closeButton_MouseHover(object sender, EventArgs e)
        {
            this.closeButton.ForeColor = Color.Cyan;
        }

        private void closeButton_MouseDown(object sender, MouseEventArgs e)
        {
            this.closeButton.ForeColor = Color.FromArgb(243, 0, 33);
        }

        private void closeButton_MouseLeave(object sender, EventArgs e)
        {
            this.closeButton.ForeColor = Color.FromArgb(239, 239, 239);
        }

        Point lastPoint;

        private void movePanel_MouseMove(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                this.Left += e.X - lastPoint.X;
                this.Top += e.Y - lastPoint.Y;
            }
        }

        private void downPanel_MouseDown(object sender, MouseEventArgs e)
        {
            lastPoint = new Point(e.X, e.Y);
        }

        private void loginField_KeyDown(object sender, KeyEventArgs e)
        {
            String loginUser = loginField.Text;

            if (loginUser.Length > 0 
                && this.loginField.BackColor == Color.FromArgb(243, 0, 33))
            {
                this.loginField.BackColor = Color.White;
            }
        }

        private void passField_KeyDown(object sender, KeyEventArgs e)
        {
            String passUser = passField.Text;

            if (passUser.Length > 0
                && this.passField.BackColor == Color.FromArgb(243, 0, 33))
            {
                this.passField.BackColor = Color.White;
            }
        }

        private void ButtonLogin_Click(object sender, EventArgs e)
        {
            String loginUser = loginField.Text;
            String passUser = passField.Text;

            if (loginUser.Length > 0 && passUser.Length > 0)
            {
                this.loginField.BackColor = Color.White;
                this.passField.BackColor = Color.White;

                DB db = new DB(loginUser, passUser);

                if (db.authorization())
                {
                    this.Hide();
                    MainForm mainForm = new MainForm();
                    mainForm.Show();
                }
            }
            else
            {
                this.loginField.BackColor = Color.FromArgb(243, 0, 33);
                this.passField.BackColor = Color.FromArgb(243, 0, 33);
            }
        }

        private void registrationLabel_Click(object sender, EventArgs e)
        {
            this.Hide();
            RegisterForm registerForm = new RegisterForm();
            registerForm.Show();
        }

        private void registrationLabel_MouseHover(object sender, EventArgs e)
        {
            this.registrationLabel.ForeColor = Color.Cyan;
        }

        private void registrationLabel_MouseLeave(object sender, EventArgs e)
        {
            this.registrationLabel.ForeColor = Color.White;
        }

        private void registrationLabel_MouseDown(object sender, MouseEventArgs e)
        {
            this.registrationLabel.ForeColor = Color.FromArgb(243, 0, 33);
        }
    }
}
