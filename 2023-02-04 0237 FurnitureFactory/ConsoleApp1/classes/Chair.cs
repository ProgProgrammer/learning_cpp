using ConsoleApp1.interfaces;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApp1.classes
{
    internal class Chair : IChair
    {
        public void hasLegs()
        {
            Console.WriteLine("Chair hasLegs().");
        }
        public void sitOn()
        {
            Console.WriteLine("Chair sitOn().");
        }
    }
}
