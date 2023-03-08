using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Xml.Linq;
using static System.Windows.Forms.LinkLabel;

namespace lists
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            FileInfo fileInf = new FileInfo(@"lists.txt");

            if (fileInf.Exists)
            {
                LinkedList<string> arr_text = new LinkedList<string>();

                using (StreamReader sr = fileInf.OpenText())
                {
                    string str = "";
                    while ((str = sr.ReadLine()) != null)
                    {
                        string[] subs = str.Split(' ');

                        for (int i = 0; i < subs.Length; ++i)
                        {
                            arr_text.AddLast(subs[i]);
                        }
                    }

                    LinkedListNode<string> node;
                    string word = "";

                    for (node = arr_text.First; node != null; node = node.Next)
                    {
                        if (word.Length == 0)
                        {
                            string str2 = node.Value;
                            char ch;
                            int a = 0;

                            while (a < str2.Length)
                            {
                                ch = str2[a];
                                int b = a;

                                while (b < str2.Length - 1)
                                {
                                    if (ch == str2[b + 1])
                                    {
                                        word = str2;
                                        break;
                                    }

                                    ++b;
                                }

                                ++a;
                            }
                        }
                        else
                        {
                            break;
                        }
                    }

                    for (node = arr_text.First; node != null;)
                    {
                        if (node.Value == word)
                        {
                            LinkedListNode<string> node2 = node;
                            node = node.Next;
                            arr_text.Remove(node2);
                            continue;
                        }

                        node = node.Next;
                    }

                    int num = 1;

                    for (node = arr_text.First; node != null; node = node.Next)
                    {
                        int result = num % 10;

                        if (result == 0)
                        {
                            textBox1.Text += Environment.NewLine;
                        }
                        else
                        {
                            textBox1.Text += node.Value += " ";
                        }

                        ++num;
                    }
                }
            }
        }
    }
}
