using _1_course_number_1.classes;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace _1_course_number_1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void clickButton_Click(object sender, EventArgs e)
        {
            const int count = 4;
            List<double[]> arr_a = new List<double[]>();
            List<double> arr_b = new List<double>();
            string sen = sender.ToString();

            for (int i = 0; i < count; ++i)
            {
                arr_a.Add(new double[count]);

                for (int a = 0; a < count; ++a)
                {
                    if (i == 0)
                    {
                        if (a == 0)
                        {
                            arr_a[i][a] = double.Parse(this.textBox1.Text);
                        }
                        else if (a == 1)
                        {
                            arr_a[i][a] = double.Parse(this.textBox2.Text);
                        }
                        else if (a == 2)
                        {
                            arr_a[i][a] = double.Parse(this.textBox3.Text);
                        }
                        else if (a == 3)
                        {
                            arr_a[i][a] = double.Parse(this.textBox4.Text);
                        }
                    }
                    else if (i == 1)
                    {
                        if (a == 0)
                        {
                            arr_a[i][a] = double.Parse(this.textBox5.Text);
                        }
                        else if (a == 1)
                        {
                            arr_a[i][a] = double.Parse(this.textBox6.Text);
                        }
                        else if (a == 2)
                        {
                            arr_a[i][a] = double.Parse(this.textBox7.Text);
                        }
                        else if (a == 3)
                        {
                            arr_a[i][a] = double.Parse(this.textBox8.Text);
                        }
                    }
                    else if (i == 2)
                    {
                        if (a == 0)
                        {
                            arr_a[i][a] = double.Parse(this.textBox9.Text);
                        }
                        else if (a == 1)
                        {
                            arr_a[i][a] = double.Parse(this.textBox10.Text);
                        }
                        else if (a == 2)
                        {
                            arr_a[i][a] = double.Parse(this.textBox11.Text);
                        }
                        else if (a == 3)
                        {
                            arr_a[i][a] = double.Parse(this.textBox12.Text);
                        }
                    }
                    else if (i == 3)
                    {
                        if (a == 0)
                        {
                            arr_a[i][a] = double.Parse(this.textBox13.Text);
                        }
                        else if (a == 1)
                        {
                            arr_a[i][a] = double.Parse(this.textBox14.Text);
                        }
                        else if (a == 2)
                        {
                            arr_a[i][a] = double.Parse(this.textBox15.Text);
                        }
                        else if (a == 3)
                        {
                            arr_a[i][a] = double.Parse(this.textBox16.Text);
                        }
                    }
                }

                if (i == 0)
                {
                    arr_b.Add(double.Parse(textBox17.Text));
                }
                else if (i == 1)
                {
                    arr_b.Add(double.Parse(textBox18.Text));
                }
                else if (i == 2)
                {
                    arr_b.Add(double.Parse(textBox19.Text));
                }
                else if (i == 3)
                {
                    arr_b.Add(double.Parse(textBox20.Text));
                }
            }

            GaussMethod gm = new GaussMethod();
            List<double> result = gm.getData(arr_a, arr_b, count);

            this.textBox21.Text = result[0] + string.Empty;
            this.textBox22.Text = result[1] + string.Empty;
            this.textBox23.Text = result[2] + string.Empty;
            this.textBox24.Text = result[3] + string.Empty;
        }
    }
}
