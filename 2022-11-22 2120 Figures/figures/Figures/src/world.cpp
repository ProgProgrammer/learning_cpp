#include "world.h"

int castToInt(const char ch)
{
    std::stringstream ss;
    ss << ch;
    int num = std::stoi(ss.str());

    return num;
}

int getRandomInt(const int min, const int max)
{
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> uni(min, max);
    auto random_integer = uni(rng);

    return random_integer;
}

void World::setPositions()
{
    for (int pos_y = 0; pos_y < m_level.size(); pos_y++)
    {
        const auto& line = m_level[pos_y];

        for (int pos_x = 0; pos_x < line.size(); pos_x++)
        {
            m_symbols.push_back(line[pos_x]);
            m_xPosition.push_back(m_config->m_dx * (pos_x + 1));
            m_yPosition.push_back(m_config->m_dy * (pos_y + 1));
        }
    }
}
int World::numLevels() const
{
    return m_levels.size();
}

Level World::getLevel(int num_level) const
{
    if (num_level < m_levels.size() && m_levels[0].size() != 0)
    {
        return m_levels[num_level];
    }
    else
    {
        throw std::runtime_error("There is no such element on the level.");
    }
}

void World::readLevelsFromFile(const std::string filename)
{
    std::string input_file = filename;
    std::ifstream inFile;
    inFile.open(filename);

    if (inFile.is_open())
    {
        Level current_figure;

        do
        {
            std::string str_figure = "";
            std::getline(inFile, str_figure);

            if (str_figure != "")
            {
                current_figure.push_back(str_figure);
            }
            else
            {
               m_levels.push_back(current_figure);
                current_figure.clear();
            }
        } while (!inFile.eof());

       m_levels.push_back(current_figure);
    }
    else
    {
        throw std::runtime_error("Levels file missing.");
    }

    inFile.close();
}

void World::draw() const
{
    m_window->clear();

    sf::Color color;
    int num_position = 0;

    for (int i = 0; i < m_symbols.size(); i++)
    {
        if (m_symbols[i] == '.')
        {
            color = m_emptyPlace;
        }
        else
        {
            int elem = castToInt(m_symbols[i]);
            color = m_colors[elem];
        }

        sf::RectangleShape rec_shape = sf::RectangleShape(sf::Vector2f(m_config->m_dx, m_config->m_dy));
        rec_shape.setFillColor(color);
        rec_shape.setPosition(m_xPosition[num_position], m_yPosition[num_position]);
        rec_shape.setOrigin(rec_shape.getSize().x, rec_shape.getSize().y);
        num_position++;

        m_window->draw(rec_shape);
    }

    m_window->display();
}

World::World()
{
    int x = 30;
    int y = 30;
    int width_window = 1200;
    int height_window = 600;
    m_window = std::shared_ptr<sf::RenderWindow>(new sf::RenderWindow(sf::VideoMode(width_window, height_window), "Figures"));
    m_config = std::shared_ptr<Config>(new Config(x, y, width_window, height_window));

    try
    {
        readLevelsFromFile("levels.txt");
        int num_levels = numLevels();
        int num_level = getRandomInt(0, num_levels - 1);
        m_level = getLevel(num_level);
    }
    catch (std::runtime_error& error)
    {
        std::cout << error.what() << "\n";
        exit(0);
    }

    setPositions();
}

void World::startLoop()
{
    while (m_window->isOpen())
    {
        using namespace std::chrono_literals;
        auto start = std::chrono::high_resolution_clock::now();

        sf::Event event;
        m_window->pollEvent(event);

        draw();

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsed = end - start;
        std::this_thread::sleep_for(40ms - elapsed); // TODO 40ms to config

        if (event.type == sf::Event::Closed)
            m_window->close();
    }
}