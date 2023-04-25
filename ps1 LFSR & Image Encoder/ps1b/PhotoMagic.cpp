#include "FibLFSR.hpp"

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

// Transforms image using FibLFSR
void transform(sf::Image&, FibLFSR*);
// Display an encrypted copy of the picture, using the LFSR to do the encryption


int main(int argc, char* argv[]) {

	// Command line arguments
	const string inputFileName = argv[1];
  	const string outputFileName = argv[2];
  	const string binaryString = argv[3];

	// Create a base image and a to-be-encrypted image
	sf::Image imageBase, imageEncrypt;
	if (!imageBase.loadFromFile(inputFileName)) return -1;
	if (!imageEncrypt.loadFromFile(inputFileName)) return -1;

	// Create sprite for base image
	sf::Vector2u size = imageBase.getSize();
	sf::RenderWindow windowBase(sf::VideoMode(size.x, size.y), "Base Image");
	sf::Texture textureBase;
	textureBase.loadFromImage(imageBase);
	sf::Sprite spriteBase;
	spriteBase.setTexture(textureBase);

	// Perform the transformation using the given binary string
	FibLFSR L1(binaryString);
	transform(imageEncrypt, &L1);

	// Create sprite for encrypted image 
	sf::RenderWindow windowEncrypt(sf::VideoMode(size.x, size.y), "Encrypted Image");
	sf::Texture textureEncrypt;
	textureEncrypt.loadFromImage(imageEncrypt);
	sf::Sprite spriteEncrypt;
	spriteEncrypt.setTexture(textureEncrypt);

	// While both windows are open
	while (windowBase.isOpen() && windowEncrypt.isOpen()){

		sf::Event event;
		// If either recieve a call to close, close both
		while (windowBase.pollEvent(event) || windowEncrypt.pollEvent(event)){
			if (event.type == sf::Event::Closed){
				windowBase.close(); windowEncrypt.close();
			} 
		}
		// Display base image
		windowBase.clear(sf::Color::White);
		windowBase.draw(spriteBase);
		windowBase.display();
		// Display encrypted image
		windowEncrypt.clear(sf::Color::White);
		windowEncrypt.draw(spriteEncrypt);
		windowEncrypt.display();
	}
	// Save to file, else return failure/error
	if (!imageEncrypt.saveToFile(outputFileName)) return -1;
	return 0;
}

void transform(sf::Image& img, FibLFSR* lfsr){

	sf::Color p;
	sf::Vector2u size = img.getSize();
	// For every x and y in img, xor each rgb val with a newly generated 8 bit num
	for (int x = 0; x < (int)size.x; x++) {
		for (int y = 0; y < (int)size.y; y++) {
			p = img.getPixel(x, y);
			p.r ^= lfsr->generate(8);
			p.g ^= lfsr->generate(8);
			p.b ^= lfsr->generate(8);
			img.setPixel(x, y, p);
		}
	}
}