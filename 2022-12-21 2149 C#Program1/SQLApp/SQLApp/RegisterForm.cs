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
    public partial class RegisterForm : Form
    {
        public RegisterForm()
        {
            InitializeComponent();

            userName.Text = "Введите имя";
            userName.ForeColor = Color.Gray;
            userSurname.Text = "Введите фамилию";
            userSurname.ForeColor = Color.Gray;
        }

        private void closeButton_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        Point lastPoint;

        private void panel_MouseDown(object sender, MouseEventArgs e)
        {
            lastPoint = new Point(e.X, e.Y);
        }

        private void panel_MouseMove(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                this.Left += e.X - lastPoint.X;
                this.Top += e.Y - lastPoint.Y;
            }
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

        private void buttonRegistr_Click(object sender, EventArgs e)
        {
            String loginUser = loginField.Text;
            String passUser = passField.Text;
            String repeatPassUser = repeatPassField.Text;
            String usName = userName.Text;
            String usSurname = userSurname.Text;

            if (passUser == repeatPassUser)
            {
                if (loginUser.Length > 0 && passUser.Length > 0 && repeatPassUser.Length > 0
                    && usName != "" && usSurname != "")
                {
                    this.loginField.BackColor = Color.White;
                    this.passField.BackColor = Color.White;
                    this.repeatPassField.BackColor = Color.White;
                    this.userName.BackColor = Color.White;
                    this.userSurname.BackColor = Color.White;

                    DB db = new DB(loginUser, passUser, usName, usSurname);
                    db.registration();
                }
                else
                {
                    this.loginField.BackColor = Color.FromArgb(243, 0, 33);
                    this.passField.BackColor = Color.FromArgb(243, 0, 33);
                    this.repeatPassField.BackColor = Color.FromArgb(243, 0, 33);
                    this.userName.BackColor = Color.FromArgb(243, 0, 33);
                    this.userSurname.BackColor = Color.FromArgb(243, 0, 33);
                }
            }
            else
            {
                this.passField.BackColor = Color.FromArgb(120, 219, 226);
                this.repeatPassField.BackColor = Color.FromArgb(120, 219, 226);
            }
        }

        private void userName_Enter(object sender, EventArgs e)
        {
            if (userName.Text == "Введите имя")
            {
                userName.Text = "";
                userName.ForeColor = Color.Black;
            }
        }

        private void userName_Leave(object sender, EventArgs e)
        {
            if (userName.Text == "")
            {
                userName.Text = "Введите имя";
                userName.ForeColor = Color.Gray;
            }
        }

        private void userSurname_Enter(object sender, EventArgs e)
        {
            if (userSurname.Text == "Введите фамилию")
            {
                userSurname.Text = "";
                userSurname.ForeColor = Color.Black;
            }
        }

        private void userSurname_Leave(object sender, EventArgs e)
        {
            if (userSurname.Text == "")
            {
                userSurname.Text = "Введите фамилию";
                userSurname.ForeColor = Color.Gray;
            }
        }
    }
}
