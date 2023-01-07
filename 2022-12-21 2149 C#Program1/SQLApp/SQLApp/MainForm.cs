using MySqlX.XDevAPI.Relational;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Net;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace SQLApp
{
    public partial class MainForm : Form
    {
        public MainForm()
        {
            InitializeComponent();

            loadDataStudents();
        }

        private void loadDataStudents()
        {
            DB db = new DB("admin", "12345");
            List<string[]> data_students = db.getStudents();
            List<string[]> data_faculty_groups = db.getFacultiesGroups();
            List<string[]> data = new List<string[]>();

            for (int i = 0; i < data_students.Count; ++i)
            {
                data.Add(new string[5]);
                
                for (int a = 0; a < data[i].Length; ++a)
                {
                    data[i][a] = data_students[i][a];
                }
            }

            for (int i = 0; i < data.Count; ++i)
            {
                for (int a = 0; a < data_faculty_groups.Count; ++a)
                {
                    if (data[i][3] == data_faculty_groups[a][0])
                    {
                        data[i][3] = data_faculty_groups[a][1];
                    }

                    if (data[i][4] == data_faculty_groups[a][2])
                    {
                        data[i][4] = data_faculty_groups[a][3];
                    }
                }
            }

            foreach (string[] s in data)
            {
                dataGridView1.Rows.Add(s);
            }
        }

        /*private void loadDataUsers()
        {
            DB db = new DB("admin", "12345");
            List<string[]> data = db.getDataUsers();

            foreach (string[] s in data)
            {
                dataGridView1.Rows.Add(s);
            }
        }*/

        private void closeButton_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        /*private void changeUserToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Hide();
            LoginForm loginForm = new LoginForm();
            loginForm.Show();
        }*/

        private void propertiesToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }

        private void aboutUserToolStripMenuItem1_Click(object sender, EventArgs e)
        {

        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void addToolStripMenuItem_Click(object sender, EventArgs e)
        {
            AddStudentForm addStudentForm = new AddStudentForm();
            addStudentForm.ShowDialog();
        }

        private void changeToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }

        private void deleteToolStripMenuItem_Click(object sender, EventArgs e)
        {
            int column = dataGridView1.CurrentCell.ColumnIndex;         // номер колонки
            int index = dataGridView1.CurrentCell.RowIndex;             // номер строки
            string id = dataGridView1[column, index].Value.ToString();  // номер студенческого билета
            DB db = new DB("admin", "12345");

            if (db.removeStudent(id))                // метод удаления студента из базы данных
            {
                dataGridView1.Rows.RemoveAt(index);  // удаление студента из таблицы
            }
        }

        private void updateToolStripMenuItem_Click(object sender, EventArgs e)
        {
            int rows_count = dataGridView1.Rows.Count - 2;

            for (int i = rows_count; i >= 0; --i)
            {
                dataGridView1.Rows.RemoveAt(i);
            }

            loadDataStudents();
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
