using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;
using static System.Windows.Forms.VisualStyles.VisualStyleElement.StartPanel;

namespace SQLApp
{
    public partial class AddStudentForm : Form
    {
        private string num_student = "№ зачетной книжки";
        private string name_student = "Имя студента";
        private string surname_student = "Фамилия студента";
        private List<string> list_faculties = new List<string>();
        private List<string[]> data_groups;
        public AddStudentForm()
        {
            InitializeComponent();
            comboBoxes();

            numberStudent.Text = num_student;
            numberStudent.ForeColor = Color.Gray;
            nameStudent.Text = name_student;
            nameStudent.ForeColor = Color.Gray;
            surnameStudent.Text = surname_student;
            surnameStudent.ForeColor = Color.Gray;
            facultyCombo.Text = "Факультет";
            facultyCombo.ForeColor = Color.Gray;
            groupCombo.Text = "Группа";
            groupCombo.ForeColor = Color.Gray;
        }

        /*private void addItems(System.Windows.Forms.ComboBox combox, ref List<string[]> data)
        {
            foreach (string s in data)
            {
                combox.Items.Add(s);
            }
        }*/

        private void comboBoxes()
        {
            DB db = new DB("admin", "12345");

            data_groups = db.getFacultiesGroups();

            for (int i = 0; i < data_groups.Count; i++)
            {
                list_faculties.Add(data_groups[i][0]);
            }

            for (int i = 0; i < list_faculties.Count; i++)
            {
                for (int a = i + 1; a < list_faculties.Count; a++)
                {
                    if (list_faculties[i][0] == list_faculties[a][0])
                    {
                        list_faculties.RemoveAt(a);
                    }
                }
            }

            foreach (string s in list_faculties)
            {
                facultyCombo.Items.Add(s);
            }
        }

        private void facultyCombo_Leave(object sender, EventArgs e)
        {
            groupCombo.Text = "";
        }

        private void group_Enter(object sender, EventArgs e)
        {
            groupCombo.Items.Clear();
            string faculty = facultyCombo.Text;

            for (int i = 0; i < data_groups.Count; i++)
            {
                if (data_groups[i][0] == faculty)
                {
                    groupCombo.Items.Add(data_groups[i][1]);
                }
            }
        }

        private void addButton_Click(object sender, EventArgs e)
        {

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

        private void numberStudent_Enter(object sender, EventArgs e)
        {
            if (numberStudent.Text == num_student)
            {
                numberStudent.Text = "";
                numberStudent.ForeColor = Color.Black;
            }
        }

        private void numberStudent_Leave(object sender, EventArgs e)
        {
            if (numberStudent.Text == "")
            {
                numberStudent.Text = num_student;
                numberStudent.ForeColor = Color.Gray;
            }
        }

        private void nameStudent_Enter(object sender, EventArgs e)
        {
            if (nameStudent.Text == name_student)
            {
                nameStudent.Text = "";
                nameStudent.ForeColor = Color.Black;
            }
        }

        private void nameStudent_Leave(object sender, EventArgs e)
        {
            if (nameStudent.Text == "")
            {
                nameStudent.Text = name_student;
                nameStudent.ForeColor = Color.Gray;
            }
        }

        private void surnameStudent_Enter(object sender, EventArgs e)
        {
            if (surnameStudent.Text == name_student)
            {
                surnameStudent.Text = "";
                surnameStudent.ForeColor = Color.Black;
            }
        }

        private void surnameStudent_Leave(object sender, EventArgs e)
        {
            if (surnameStudent.Text == "")
            {
                surnameStudent.Text = name_student;
                surnameStudent.ForeColor = Color.Gray;
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
    }
}
