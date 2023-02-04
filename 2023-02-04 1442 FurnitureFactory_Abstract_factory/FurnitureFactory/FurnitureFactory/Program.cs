using FurnitureFactory.classes;
using FurnitureFactory.interfaces;

namespace UniversityApp
{
    internal static class Program
    {
        static void Main()
        {
            try
            {
                IGUIFactory factory;
                Console.Write("Введите тип ОС (Windows/MacOS): ");
                string? OS = Console.ReadLine();

                if (OS == "Windows")
                {
                    factory = new WinFactory();
                }
                else if (OS == "MacOS")
                {
                    factory = new MacFactory();
                }
                else
                {
                    throw new Exception("Error! Unknown operating system.");
                }

                Application app = new Application(factory);
                app.createUI();
                app.paint();
            }
            catch (Exception e)
            {
                Console.WriteLine($"Ошибка: {e.Message}");
            }
        }
    }
}
