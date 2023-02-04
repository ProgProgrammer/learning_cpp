using FurnitureFactory.interfaces;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FurnitureFactory.classes
{
    internal class WinFactory : IGUIFactory
    {
        public IButton createButton()
        {
            return new WinButton();
        }

        public ICheckbox createCheckbox()
        {
            return new WinCheckbox();
        }
    }
}
