using FurnitureFactory.interfaces;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection.Emit;
using System.Text;
using System.Threading.Tasks;

namespace FurnitureFactory.classes
{
    internal class Application
    {
        private IGUIFactory factory;
        private ICheckbox checkbox;
        private IButton button;
        public Application(IGUIFactory factory)
        {
            this.factory = factory;
        }

        public void createUI()
        {
            this.checkbox = factory.createCheckbox();
            this.button = factory.createButton();
        }

        public void paint()
        {
            this.checkbox.paint();
            this.button.paint();
        }
    }
}
