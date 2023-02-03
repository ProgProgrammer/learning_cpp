using ConsoleApp1.interfaces;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApp1.classes
{
    internal class FurnitureFactory : IFurnitureFactory
    {
        public Chair createChair()
        {
            return new Chair();
        }

        public CoffeeTable createCoffeeTable()
        {
            return new CoffeeTable();
        }

        public Sofa createSofa()
        {
            return new Sofa();
        }
    }
}
