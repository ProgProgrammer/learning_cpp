#pragma once
#include "config.h"
#include "i_drawable.h"
#include <fstream>
#include <string>
#include <random>
#include <sstream>
#include <chrono>
#include <thread>

using Level = std::vector<std::string>;
using Levels = std::vector<Level>;

class World : public iDrawable
{
    private:
        Levels m_levels;
        Level m_level;
        std::string m_symbols;
        std::shared_ptr<sf::RenderWindow> m_window;
        std::shared_ptr<Config> m_config;
        sf::Color m_emptyPlace = sf::Color(0, 0, 0);
        std::vector<sf::Color> m_colors = { sf::Color(192, 192, 192), sf::Color(128, 0, 0),    sf::Color(165, 42, 42),
                                       sf::Color(160, 82, 45),   sf::Color(139, 69, 19),  sf::Color(210, 105, 30),
                                       sf::Color(205, 133, 63),  sf::Color(184, 134, 11), sf::Color(218, 165, 32),
                                       sf::Color(244, 164, 96) };
        std::vector<int> m_xPosition;
        std::vector<int> m_yPosition;
        void setPositions();
        int numLevels() const;
        Level getLevel(int num_level) const;
        void readLevelsFromFile(const std::string filename);
        void draw() const override;

    public:
        World();
        void startLoop();
};