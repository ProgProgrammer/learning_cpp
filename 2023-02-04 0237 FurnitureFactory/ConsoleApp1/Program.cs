// Online C# Editor for free
// Write, Edit and Run your C# code using C# Online Compiler

using ConsoleApp1.classes;
using System;

namespace ConsoleApp1
{
    public class HelloWorld
    {
        public static void Main(string[] args)
        {
            Console.WriteLine("Hello World!");
            FurnitureFactory factory = new FurnitureFactory();
            Chair chair = factory.createChair();
            CoffeeTable coffeTable = factory.createCoffeeTable();
            Sofa sofa = factory.createSofa();
        }
    }
}