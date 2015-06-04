#pragma once
#include "Header.h"
#include <map>
class TextureManager
{
public:
	enum class TextureName { Sky, RedBiplane, GreenBiplane, GrassGround1, GrassGround2
		, GrassGround3, SandGround1, SandGround2, DirtGround, DefaultBullet };
	static void loadAllTextures();
	static const sf::Texture* getTexture(const TextureName name);
private:
	static std::unique_ptr<sf::Texture> fromFile(const std::string& filename);
	static std::map<const TextureName, std::unique_ptr<sf::Texture>> textures;
};

