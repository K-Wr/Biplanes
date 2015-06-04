#include "TextureManager.h"
#include "GameException.h"

std::map<const TextureManager::TextureName, std::unique_ptr<sf::Texture>> TextureManager::textures;

void TextureManager::loadAllTextures(){
	textures.insert({ TextureName::Sky, fromFile("textures\\Sky.png") });
	textures.insert({ TextureName::GreenBiplane, fromFile("textures\\GreenBiplane.png") });
	textures.insert({ TextureName::RedBiplane, fromFile("textures\\RedBiplane.png") });
	textures.insert({ TextureName::GrassGround1, fromFile("textures\\ground\\GrassGround1.jpg") });
	textures.insert({ TextureName::GrassGround2, fromFile("textures\\ground\\GrassGround2.jpg") });
	textures.insert({ TextureName::GrassGround3, fromFile("textures\\ground\\GrassGround3.jpg") });
	textures.insert({ TextureName::SandGround1, fromFile("textures\\ground\\SandGround1.jpg") });
	textures.insert({ TextureName::SandGround2, fromFile("textures\\ground\\SandGround2.jpg") });
	textures.insert({ TextureName::DirtGround, fromFile("textures\\ground\\DirtGround.jpg") });
	textures.insert({ TextureName::DefaultBullet, fromFile("textures\\DefaultBullet.png") });

}
const sf::Texture* TextureManager::getTexture(const TextureName name){
	return textures.at(name).get();
}
std::unique_ptr<sf::Texture> TextureManager::fromFile(const std::string& filename){
	sf::Texture* retval = new sf::Texture;
	if (!retval->loadFromFile(filename)){
		throw GameException("Error loading texture from file " + filename + " : file is missing or access is forbidden"
			, "TextureManager::fromFile() called from TextureManager::loadAllTextures()");
	}
	return std::unique_ptr<sf::Texture>(retval);
}