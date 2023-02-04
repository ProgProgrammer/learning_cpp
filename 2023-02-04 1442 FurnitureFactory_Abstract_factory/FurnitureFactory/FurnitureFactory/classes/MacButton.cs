using FurnitureFactory.interfaces;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FurnitureFactory.classes
{
    internal class MacButton : IButton
    {
        public void paint()
        {
            Console.WriteLine("MacButton.");
        }
    }
}
