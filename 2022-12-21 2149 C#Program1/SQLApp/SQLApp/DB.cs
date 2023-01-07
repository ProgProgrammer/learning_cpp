using MySql.Data.MySqlClient;
using MySqlX.XDevAPI.Relational;
using System;
using System.Collections.Generic;
using System.Data;
using System.Data.Common;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace SQLApp
{
    internal class DB
    {
        private readonly String loginUser;
        private readonly String passUser;
        private String userName;
        private String userSurname;
        MySqlConnection connection = new MySqlConnection("server=localhost;port=3306;username=root;password=root;database=itproger");

        public DB(String lu, String pu)
        {
            loginUser = lu;
            passUser = pu;
        }

        public DB(String lu, String pu, String un, String us)
        {
            loginUser = lu;
            passUser = pu;
            userName = un;
            userSurname = us;
        }

        private void openConnection()
        {
            if (connection.State == System.Data.ConnectionState.Closed)
            {
                connection.Open();
            }
        }

        private void closeConnection()
        {
            if (connection.State == System.Data.ConnectionState.Open)
            {
                connection.Close();
            }
        }

        private bool userExistCheck(DataTable table, MySqlDataAdapter adapter, MySqlCommand command)
        {
            openConnection();                 // открытие соединение с БД
            adapter.SelectCommand = command;  // отправка команды в БД на выполнение
            adapter.Fill(table);              // запись в объект table информации о том, что совпадение найдено / не найдено
            closeConnection();                // закрытие соединения с БД, чтобы не перегружать БД

            if (table.Rows.Count > 0)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        public bool authorization()
        {
            DataTable table = new DataTable();
            MySqlDataAdapter adapter = new MySqlDataAdapter();
            MySqlCommand command = new MySqlCommand($"SELECT * FROM users WHERE login = @login AND password = @password", connection);  // создание команды
            command.Parameters.Add("@login", MySqlDbType.VarChar).Value = loginUser;     // присвоение значения псевдониму
            command.Parameters.Add("@password", MySqlDbType.VarChar).Value = passUser;   // присвоение значения псевдониму

            if (userExistCheck(table, adapter, command))
            {
                return true;
            }
            else
            {
                MessageBox.Show("This user is not in the database.");

                return false;
            }
        }

        public bool registrationUser()
        {
            DataTable table = new DataTable();
            MySqlDataAdapter adapter = new MySqlDataAdapter();
            MySqlCommand command = new MySqlCommand("SELECT * FROM users WHERE login = @login", connection);
            command.Parameters.Add("@login", MySqlDbType.VarChar).Value = loginUser;

            if (userExistCheck(table, adapter, command))
            {
                MessageBox.Show("A user with this login already exists in the database. Add another login.");

                return false;
            }

            command = new MySqlCommand("INSERT INTO users(login, password, name, surname) VALUES(@login, @password, @name, @surname)", connection);
            command.Parameters.Add("@login", MySqlDbType.VarChar).Value = loginUser;
            command.Parameters.Add("@password", MySqlDbType.VarChar).Value = passUser;
            command.Parameters.Add("@name", MySqlDbType.VarChar).Value = userName;
            command.Parameters.Add("@surname", MySqlDbType.VarChar).Value = userSurname;

            openConnection();

            if (command.ExecuteNonQuery() == 1)
            {
                MessageBox.Show("Account created.");
                closeConnection();

                return true;
            }
            else
            {
                MessageBox.Show("Account has not been created.");
                closeConnection();

                return false;
            }
        }

        public bool registrationStudent(AddStudentForm.InfoStudent infoStudent)
        {
            DataTable table = new DataTable();
            MySqlDataAdapter adapter = new MySqlDataAdapter();
            MySqlCommand command = new MySqlCommand("SELECT * FROM students WHERE student_number = @student_number", connection);
            command.Parameters.Add("@student_number", MySqlDbType.VarChar).Value = infoStudent.number_student;

            if (userExistCheck(table, adapter, command))
            {
                MessageBox.Show("A student with this student ID number already exists in the database. Add another student ID number.");

                return false;
            }

            List<string[]> list_faculties_groups = getFacultiesGroups();

            for (int i = 0; i < list_faculties_groups.Count; ++i)
            {
                if (list_faculties_groups[i][0] == infoStudent.faculty_combo
                    && list_faculties_groups[i][2] == infoStudent.group_combo)  // проверка на то, есть ли переданная группа в переданном факультете или нет
                {
                    command = new MySqlCommand("INSERT INTO students(student_number, name, surname, num_faculty, num_group) VALUES(@student_number, @name, @surname, @num_faculty, @num_group)", connection);
                    command.Parameters.Add("@student_number", MySqlDbType.VarChar).Value = infoStudent.number_student;
                    command.Parameters.Add("@name", MySqlDbType.VarChar).Value = infoStudent.name_student;
                    command.Parameters.Add("@surname", MySqlDbType.VarChar).Value = infoStudent.surname_student;
                    command.Parameters.Add("@num_faculty", MySqlDbType.VarChar).Value = infoStudent.faculty_combo;
                    command.Parameters.Add("@num_group", MySqlDbType.VarChar).Value = infoStudent.group_combo;

                    openConnection();

                    if (command.ExecuteNonQuery() == 1)
                    {
                        MessageBox.Show("Student added.");
                        closeConnection();

                        return true;
                    }
                    else
                    {
                        MessageBox.Show("Student has not been added.");
                        closeConnection();

                        return false;
                    }
                }
            }

            MessageBox.Show("This faculty does not have such a group.");

            return false;
        }

        public bool removeUser(String login)
        {
            DataTable table = new DataTable();
            MySqlCommand command = new MySqlCommand("DELETE FROM users WHERE login = @login", connection);
            command.Parameters.Add("@login", MySqlDbType.VarChar).Value = login;

            openConnection();

            if (command.ExecuteNonQuery() == 1)
            {
                closeConnection();

                return true;
            }
            else
            {
                MessageBox.Show("Account has not been deleted.");
                closeConnection();

                return false;
            }
        }

        public bool removeStudent(String student_id)
        {
            DataTable table = new DataTable();
            MySqlCommand command = new MySqlCommand("DELETE FROM students WHERE student_number = @student_id", connection);
            command.Parameters.Add("@student_id", MySqlDbType.VarChar).Value = student_id;

            openConnection();

            if (command.ExecuteNonQuery() == 1)
            {
                closeConnection();

                return true;
            }
            else
            {
                MessageBox.Show("Student has not been deleted.");
                closeConnection();

                return false;
            }
        }

        public List<string[]> getUsers()
        {
            MySqlCommand command = new MySqlCommand("SELECT * FROM users ORDER BY id", connection);
            List<string[]> data = new List<string[]>();

            openConnection();

            MySqlDataReader reader = command.ExecuteReader();

            while (reader.Read())
            {
                data.Add(new string[3]);

                data[data.Count - 1][0] = reader[1].ToString();
                data[data.Count - 1][1] = reader[3].ToString();
                data[data.Count - 1][2] = reader[4].ToString();
            }

            reader.Close();
            closeConnection();

            return data;
        }

        public List<string[]> getStudents()
        {
            MySqlCommand command = new MySqlCommand("SELECT * FROM students ORDER BY id", connection);
            List<string[]> data = new List<string[]>();

            openConnection();

            MySqlDataReader reader = command.ExecuteReader();
            int num_cell_data = reader.FieldCount - 1;

            while (reader.Read())
            {
                data.Add(new string[num_cell_data]);

                for (int i = 0; i < num_cell_data; ++i)
                {
                    data[data.Count - 1][i] = reader[i + 1].ToString();
                }
            }

            reader.Close();
            closeConnection();

            return data;
        }

        public List<string[]> getFacultiesGroups()
        {
            MySqlCommand command_groups_num = new MySqlCommand("SELECT COUNT(*) FROM groups", connection);

            openConnection();
            int numRowsGroups = Convert.ToInt32(command_groups_num.ExecuteScalar());
            closeConnection();

            List<string[]> data = new List<string[]>();
            MySqlCommand command = new MySqlCommand("SELECT faculties.id, faculties.name, groups.id, groups.name FROM faculties_groups JOIN faculties ON faculties_groups.num_faculty = faculties.id JOIN groups ON faculties_groups.num_group = groups.id", connection);

            openConnection();
            MySqlDataReader reader = command.ExecuteReader();
            int num_cell_data = reader.FieldCount;

            for (int i = 0; i < numRowsGroups; ++i)
            {
                if (reader.Read())
                {
                    data.Add(new string[num_cell_data]);

                    for (int a = 0; a < num_cell_data; ++a)
                    {
                        data[data.Count - 1][a] = reader[a].ToString();
                    }
                }
            }

            reader.Close();
            closeConnection();

            return data;
        }
    }
}
