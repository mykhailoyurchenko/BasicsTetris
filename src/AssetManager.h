#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include <memory>
#include <stdexcept>

class AssetManager {
public:
    AssetManager() = default;

    sf::Texture& getTexture(const std::string& filename) {
        auto it = textures.find(filename);
        if (it != textures.end()) {
            return it->second;
        }

        sf::Texture texture;
        if (!texture.loadFromFile(filename)) {
            throw std::runtime_error("Failed to load texture: " + filename);
        }
        
        return textures.emplace(filename, std::move(texture)).first->second;
    }

    sf::Font& getFont(const std::string& filename) {
        auto it = fonts.find(filename);
        if (it != fonts.end()) {
            return it->second;
        }

        sf::Font font{};
        if (!font.openFromFile(filename)) {
            throw std::runtime_error("Failed to load font: " + filename);
        }

        return fonts.emplace(filename, std::move(font)).first->second;
    }

private:
    std::map<std::string, sf::Texture> textures;
    std::map<std::string, sf::Font> fonts;
};