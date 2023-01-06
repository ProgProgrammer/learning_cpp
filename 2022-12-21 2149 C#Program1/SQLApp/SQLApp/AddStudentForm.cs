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
        private List<string[]> list_faculties = new List<string[]>();
        private List<string[]> data_groups;
        public AddStudentForm()
        {
            InitializeComponent();
            comboBoxes();
        }

        private void comboBoxes()
        {
            DB db = new DB("admin", "12345");

            data_groups = db.getFacultiesGroups();

            for (int i = 0; i < data_groups.Count; i++)
            {
                this.list_faculties.Add(new string[2]);
                this.list_faculties[i][0] = this.data_groups[i][0];
                this.list_faculties[i][1] = this.data_groups[i][1];
            }

            for (int i = 0; i < this.list_faculties.Count; i++)
            {
                for (int a = i + 1; a < this.list_faculties.Count; a++)
                {
                    if (this.list_faculties[i][1] == this.list_faculties[a][1])
                    {
                        this.list_faculties.RemoveAt(a);
                    }
                }
            }

            for (int i = 0; i < list_faculties.Count(); i++)
            {
                facultyCombo.Items.Add(list_faculties[i][1]);
            }
        }

        private void facultyCombo_Enter(object sender, EventArgs e)
        {
            this.groupCombo.Text = "";
        }

        private void group_Enter(object sender, EventArgs e)
        {
            this.groupCombo.Items.Clear();
            string faculty = facultyCombo.Text;

            for (int i = 0; i < data_groups.Count; i++)
            {
                if (data_groups[i][1] == faculty)
                {
                    this.groupCombo.Items.Add(this.data_groups[i][3]);
                }
            }
        }

        public struct InfoStudent
        {
            public String number_student;
            public String name_student;
            public String surname_student;
            public String faculty_combo;
            public String group_combo;
        }

        private void addButton_Click(object sender, EventArgs e)
        {
            InfoStudent infoStudent = new InfoStudent();
            infoStudent.number_student = this.numberStudent.Text;
            infoStudent.name_student = this.nameStudent.Text;
            infoStudent.surname_student = this.surnameStudent.Text;
            String faculty_combo = this.facultyCombo.Text;
            String group_combo = this.groupCombo.Text;

            if (infoStudent.number_student.Length >= 8 && infoStudent.name_student.Length > 1
                && infoStudent.surname_student.Length > 1 && faculty_combo.Length > 10
                && group_combo.Length > 3)
            {
                this.numberStudent.BackColor = Color.White;
                this.nameStudent.BackColor = Color.White;
                this.surnameStudent.BackColor = Color.White;
                this.facultyCombo.BackColor = Color.White;
                this.groupCombo.BackColor = Color.White;

                DB db = new DB("admin", "12345");

                for (int i = 0; i < list_faculties.Count; i++)
                {
                    if (list_faculties[i][1] == faculty_combo)
                    {
                        infoStudent.faculty_combo = list_faculties[i][0];
                        break;
                    }
                }

                for (int i = 0; i < data_groups.Count; i++)
                {
                    if (data_groups[i][3] == group_combo)
                    {
                        infoStudent.group_combo = data_groups[i][2];
                        break;
                    }
                }

                db.registrationStudent(infoStudent);

                /*if (db.registrationStudent(infoStudent))
                {
                    this.Hide();  // скрывает окно
                }*/
            }


            if (infoStudent.number_student.Length >= 8)
            {
                this.numberStudent.BackColor = Color.White;
            }
            
            if (infoStudent.name_student.Length > 1)
            {
                this.nameStudent.BackColor = Color.White;
            }
            
            if (infoStudent.surname_student.Length > 1)
            {
                this.surnameStudent.BackColor = Color.White;
            }
            
            if (faculty_combo.Length > 10)
            {
                this.facultyCombo.BackColor = Color.White;
            }
            
            if (group_combo.Length > 3)
            {
                this.groupCombo.BackColor = Color.White;
            }


            if (infoStudent.number_student.Length < 8)
            {
                this.numberStudent.BackColor = Color.FromArgb(243, 0, 33);
            }
            
            if (infoStudent.name_student.Length < 2)
            {
                this.nameStudent.BackColor = Color.FromArgb(243, 0, 33);
            }
            
            if (infoStudent.surname_student.Length < 2)
            {
                this.surnameStudent.BackColor = Color.FromArgb(243, 0, 33);
            }
            
            if (faculty_combo.Length <= 10)
            {
                this.facultyCombo.BackColor = Color.FromArgb(243, 0, 33);
            }
            
            if (group_combo.Length <= 2)
            {
                this.groupCombo.BackColor = Color.FromArgb(243, 0, 33);
            }
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
    }
}
