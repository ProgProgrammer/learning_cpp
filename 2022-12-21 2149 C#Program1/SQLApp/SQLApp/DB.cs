using MySql.Data.MySqlClient;
using MySqlX.XDevAPI.Relational;
using System;
using System.Collections.Generic;
using System.Data;
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
            MySqlCommand command = new MySqlCommand("INSERT INTO students(student_number, name, surname, num_faculty, num_group) VALUES(@student_number, @name, @surname, @num_faculty, @num_group)", connection);
            command.Parameters.Add("@student_number", MySqlDbType.VarChar).Value = infoStudent.number_student;
            command.Parameters.Add("@name", MySqlDbType.VarChar).Value = infoStudent.name_student;
            command.Parameters.Add("@surname", MySqlDbType.VarChar).Value = infoStudent.surname_student;
            command.Parameters.Add("@num_faculty", MySqlDbType.VarChar).Value = infoStudent.faculty_combo;
            command.Parameters.Add("@num_group", MySqlDbType.VarChar).Value = infoStudent.group_combo;

            openConnection();

            if (command.ExecuteNonQuery() == 1)
            {
                MessageBox.Show("User added.");
                closeConnection();

                return true;
            }
            else
            {
                MessageBox.Show("User has not been added.");
                closeConnection();

                return false;
            }
        }

        public bool removeData(String login)
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

        public List<string[]> getDataUsers()
        {
            MySqlCommand command = new MySqlCommand("SELECT * FROM users ORDER BY id", connection);

            openConnection();

            MySqlDataReader reader = command.ExecuteReader();
            List<string[]> data = new List<string[]>();

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

        public List<string[]> getFacultiesGroups()
        {
            MySqlCommand command_groups_num = new MySqlCommand("SELECT COUNT(*) FROM groups", connection);

            openConnection();
            int numRowsGroups = Convert.ToInt32(command_groups_num.ExecuteScalar());
            closeConnection();

            List<string[]> data = new List<string[]>();

            MySqlCommand command = new MySqlCommand("SELECT * FROM faculties_groups JOIN faculties ON faculties_groups.num_faculty = faculties.id JOIN groups ON faculties_groups.num_group = groups.id", connection);

            openConnection();
            MySqlDataReader reader = command.ExecuteReader();

            for (int i = 0; i < numRowsGroups; i++)
            {
                if (reader.Read())
                {
                    data.Add(new string[4]);
                    data[i][0] = reader[3].ToString();
                    data[i][1] = reader[4].ToString();
                    data[i][2] = reader[5].ToString();
                    data[i][3] = reader[6].ToString();
                }
            }

            reader.Close();
            closeConnection();

            return data;
        }
    }
}
