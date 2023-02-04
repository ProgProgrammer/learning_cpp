using FurnitureFactory.interfaces;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FurnitureFactory.classes
{
    internal class MacCheckbox : ICheckbox
    {
        public void paint()
        {
            Console.WriteLine("MacCheckbox.");
        }
    }
}
