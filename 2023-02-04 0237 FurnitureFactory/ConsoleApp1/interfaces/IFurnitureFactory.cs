using ConsoleApp1.classes;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApp1.interfaces
{
    internal interface IFurnitureFactory
    {
        Chair createChair();
        CoffeeTable createCoffeeTable();
        Sofa createSofa();
    }
}
