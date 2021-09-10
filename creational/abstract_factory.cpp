/*
 * Example of `Abstract Factory' design pattern (Creational Pattern).
 * The Abstract Factory is defining an interface to create families of 
 * related or dependent objects without specifying their concrete classes.
 * 
 * The class consists of the following entities
 * 1. Abstract Factory
 * 2. Concrete Factory
 * 3. Abstract Product
 * 4. Concrete Product
 * 5. Client
 */

#include <iostream>
#include <string>

class Window
{
    protected:
        int width;
        int height;
        std::string toolkit;
        std::string type;

        Window(std::string usedToolkit, std::string windowType)
            : toolkit(usedToolkit), type(windowType)
        {}

    public:
        std::string getToolkit()
        {
            return toolkit;
        }

        std::string getType()
        {
            return type;
        }
};

class GtkToolboxWindow : public Window
{
    public:
        GtkToolboxWindow()
            : Window("Gtk", "ToolboxWindow")
        {}
};

class GtkLayersWindow : public Window
{
    public:
        GtkLayersWindow()
            : Window("Gtk", "LayersWindow")
        {}
};

class GtkMainWindow : public Window
{ 
    public:
        GtkMainWindow()
            : Window("Gtk", "MainWindow")
        {}
};


class QtToolboxWindow : public Window
{
    public:
        QtToolboxWindow()
            : Window("Qt", "ToolboxWindow")
        {}
};

class QtLayersWindow : public Window
{
    public:
        QtLayersWindow()
            : Window("Qt", "LayersWindow")
        {}
};

class QtMainWindow : public Window
{
    public:
        QtMainWindow()
            : Window("Qt", "MainWindow")
        {}
};


/* This is the abstract factory. */
class UIFactory
{
    public:
        virtual Window* getToolboxWindow() = 0;
        virtual Window* getLayersWindow() = 0;
        virtual Window* getMainWindow() = 0;

};

/* Factory for Gtk toolkit */
class GtkUIFactory : public UIFactory
{
    public:
        Window* getToolboxWindow()
        {
            return new GtkToolboxWindow();
        }

        Window* getLayersWindow()
        {
            return new GtkLayersWindow();
        }

        Window* getMainWindow()
        {
            return new GtkMainWindow();
        }
};

/* Factory for Qt toolkit */
class QtUIFactory : public UIFactory
{
    public:
        Window* getToolboxWindow()
        {
            return new QtToolboxWindow();
        }

        Window* getLayersWindow()
        {
            return new QtLayersWindow();
        }

        Window* getMainWindow()
        {
            return new QtMainWindow();
        }
};

int main()
{
    UIFactory* ui = 0;

    /* Check what environment is running
       and create appropriate factory. */
    if (/* Gtk == */ true)
    {
        ui = new GtkUIFactory();
    }
    else
    {
        ui = new QtUIFactory();
    }

    /* Use the factory to build interface. */
    Window* toolbox = ui->getToolboxWindow();
    Window* layers  = ui->getLayersWindow();
    Window* main    = ui->getMainWindow();

    /* See what have we recieved. */
    std::cout << toolbox->getToolkit() << ":"
              << toolbox->getType() << std::endl;

    std::cout << layers->getToolkit() << ":"
              << layers->getType() << std::endl;

    std::cout << main->getToolkit() << ":"
              << main->getType() << std::endl;
}
