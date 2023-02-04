using FurnitureFactory.interfaces;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FurnitureFactory.classes
{
    internal class MacFactory : IGUIFactory
    {
        public IButton createButton()
        {
            return new MacButton();
        }

        public ICheckbox createCheckbox()
        {
            return new MacCheckbox();
        }
    }
}
