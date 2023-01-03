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
        private String loginUser;
        private String passUser;
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

        private MySqlConnection getConnection()
        {
            return connection;
        }

        private bool userExistCheck(DataTable table, MySqlDataAdapter adapter, MySqlCommand command)
        {
            openConnection();                 // открытие соединение с БД
            adapter.SelectCommand = command;  // отправка команды в БД на выполнение
            adapter.Fill(table);              // запись в объект table информации о том, что совпадение найдено
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
            MySqlCommand command = new MySqlCommand("SELECT * FROM users WHERE login = @login AND password = @password", connection);  // создание команды
            command.Parameters.Add("@login", MySqlDbType.VarChar).Value = loginUser;    // присвоение значения псевдониму
            command.Parameters.Add("@password", MySqlDbType.VarChar).Value = passUser;  // присвоение значения псевдониму

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

        public bool registration()
        {
            DataTable table = new DataTable();
            MySqlDataAdapter adapter = new MySqlDataAdapter();
            MySqlCommand command = new MySqlCommand("SELECT * FROM users WHERE login = @login", connection);
            command.Parameters.Add("@login", MySqlDbType.VarChar).Value = loginUser;

            openConnection();                 // открытие соединение с БД
            adapter.SelectCommand = command;  // отправка команды в БД на выполнение
            adapter.Fill(table);              // запись в объект table информации о том, что совпадение найдено
            closeConnection();

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
            }
            else
            {
                MessageBox.Show("Account has not been created.");

                return false;
            }

            closeConnection();

            return true;
        }
    }
}
