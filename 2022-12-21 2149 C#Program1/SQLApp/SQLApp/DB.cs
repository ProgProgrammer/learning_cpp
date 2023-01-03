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

        public void authorization()
        {
            DataTable table = new DataTable();
            MySqlDataAdapter adapter = new MySqlDataAdapter();
            MySqlCommand command = new MySqlCommand("SELECT * FROM users WHERE login = @lu AND password = @pu", connection);
            command.Parameters.Add("@lu", MySqlDbType.VarChar).Value = loginUser;
            command.Parameters.Add("@pu", MySqlDbType.VarChar).Value = passUser;

            adapter.SelectCommand = command;
            adapter.Fill(table);

            if (table.Rows.Count > 0)
            {
                MessageBox.Show("Yes");
            }
            else
            {
                MessageBox.Show("No");
            }
        }

        public void registration()
        {
            DataTable table = new DataTable();
            MySqlDataAdapter adapter = new MySqlDataAdapter();
            MySqlCommand command = new MySqlCommand("INSERT INTO users(login, password, name, surname) VALUES(@lu, @pu, @un, @us)", connection);
            command.Parameters.Add("@lu", MySqlDbType.VarChar).Value = loginUser;
            command.Parameters.Add("@pu", MySqlDbType.VarChar).Value = passUser;
            command.Parameters.Add("@un", MySqlDbType.VarChar).Value = userName;
            command.Parameters.Add("@us", MySqlDbType.VarChar).Value = userSurname;

            adapter.SelectCommand = command;
            adapter.Fill(table);

            if (table.Rows.Count > 0)
            {
                MessageBox.Show("Yes");
            }
            else
            {
                MessageBox.Show("No");
            }
        }
    }
}
