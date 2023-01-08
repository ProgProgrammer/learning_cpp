using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace SQLApp
{
    interface Ivb
    {
        void show();
    }

    abstract class Avb : Ivb
    {
        public abstract void show();
        public void show2()
        {

        }
    }

    class Sdf : Avb
    {
        public override void show()
        {
            
        }
    }

    internal static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new LoginForm());
        }
    }
}
