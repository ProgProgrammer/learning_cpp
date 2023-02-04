using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FurnitureFactory.interfaces
{
    internal interface IGUIFactory
    {
        IButton createButton();
        ICheckbox createCheckbox();
    }
}
