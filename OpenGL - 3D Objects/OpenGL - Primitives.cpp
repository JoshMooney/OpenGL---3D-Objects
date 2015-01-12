// OpenGL - Primitives.cpp : Defines the entry point for the console application.
//

//////////////////////////////////////////////////////////// 
// Headers 
//////////////////////////////////////////////////////////// 
#include "stdafx.h" 
#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 
#pragma comment(lib,"opengl32.lib") 
#pragma comment(lib,"glu32.lib") 

#include <iostream> 
#define _USE_MATH_DEFINES
#include <math.h>

int main()
{
	bool cylinderActive = true;
	bool cubeActive = false;

	// Create the main window 
	sf::RenderWindow window(sf::VideoMode(800, 800, 32), "OpenGL - 3D Objects");
	window.setFramerateLimit(60);

	//load a font
	sf::Font font;
	font.loadFromFile("C:\\Windows\\Fonts\\GARA.TTF");

	//create a formatted text string
	sf::Text text;
	text.setFont(font);
	text.setString("Hello World");

	sf::Texture tex;
	//std::string image = "dog.jpg";
	std::string image = "die.png";
	if (!tex.loadFromFile(image))
	{
		std::cout << "Could not load" << image;
		char c;
		std::cin >> c;
		return false;
	}

	sf::Texture::bind(&tex);
	glEnable(GL_TEXTURE_2D);

	GLdouble aaa[] = { 1, 1, 1 };
	GLdouble aab[] = { 1, 1, -1 };
	GLdouble abb[] = { 1, -1, -1 };
	GLdouble aba[] = { 1, -1, 1 };

	GLdouble baa[] = { -1, 1, 1 };
	GLdouble bab[] = { -1, 1, -1 };
	GLdouble bba[] = { -1, -1, 1 };
	GLdouble bbb[] = { -1, -1, -1 };

	GLUquadricObj *quadratic;		//For cylinder

	//Enable Back Face Culling
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glClearDepth(1.0f);

	double r = 0;
	// Start game loop 
	while (window.isOpen())
	{
		// Process events 
		sf::Event Event;
		while (window.pollEvent(Event))
		{
			// Close window : exit 
			if (Event.type == sf::Event::Closed)
				window.close();

			// Escape key : exit 
			if ((Event.type == sf::Event::KeyPressed) &&
				(Event.key.code == sf::Keyboard::Escape))
				window.close();

			if (Event.type == sf::Event::KeyPressed)
			{
				if (Event.key.code == sf::Keyboard::Num1)
				{
					switch (cubeActive)
					{
					case true:
						cubeActive = false;
						break;
					case false:
						cubeActive = true;
						cylinderActive = false;
						break;

					}
				}
				if (Event.key.code == sf::Keyboard::Num2)
				{
					switch (cylinderActive)
					{
					case true:
						cylinderActive = false;
						break;
					case false:
						cylinderActive = true;
						cubeActive = false;
						break;

					}
				}
			}
		}

		r += 0.5;

		//prepare frame
		window.clear();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		glMatrixMode(GL_MODELVIEW);
		//glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		glRotated(r, 1, 0, 0);
		glRotated(r, 0, 1, 0);
		glScaled(0.5, 0.5, 0.5);

		if (cubeActive)
		{
			int dieSide = 1;
			float dieSideSize = 0.166666f;
			
			#pragma region Top
			glBegin(GL_QUADS);
			//glColor3f(0, 1, 0);

			glTexCoord2d(0, 0);
			glVertex3dv(aaa);

			glTexCoord2d(dieSide * dieSideSize, 0);
			glVertex3dv(aab);

			glTexCoord2d(dieSide * dieSideSize, 1);
			glVertex3dv(abb);

			glTexCoord2d(0, 1);
			glVertex3dv(aba);

			dieSide++;
			glEnd();
#pragma endregion
			#pragma region Bottom
			glBegin(GL_QUADS);
			//glColor3f(1, 0, 0);

			glTexCoord2d((dieSide - 1) * dieSideSize, 0);
			glVertex3dv(baa);

			glTexCoord2d(dieSide * dieSideSize, 0);
			glVertex3dv(bab);

			glTexCoord2d(dieSide * dieSideSize, 1);
			glVertex3dv(bbb);

			glTexCoord2d((dieSide - 1) * dieSideSize, 1);
			glVertex3dv(bba);

			dieSide++;
			glEnd();
#pragma endregion 
			#pragma region Left
			glBegin(GL_QUADS);
			//glColor3f(0, 0, 1);

			glTexCoord2d((dieSide - 1) * dieSideSize, 0);
			glVertex3dv(aaa);

			glTexCoord2d(dieSide * dieSideSize, 0);
			glVertex3dv(aab);

			glTexCoord2d(dieSide * dieSideSize, 1);
			glVertex3dv(bab);

			glTexCoord2d((dieSide - 1) * dieSideSize, 1);
			glVertex3dv(baa);

			dieSide++;
			glEnd();
#pragma endregion
			#pragma region Right
			glBegin(GL_QUADS);
			//glColor3f(1, 0, 1);

			glTexCoord2d((dieSide - 1) * dieSideSize, 0);
			glVertex3dv(aba);

			glTexCoord2d(dieSide * dieSideSize, 0);
			glVertex3dv(abb);

			glTexCoord2d(dieSide * dieSideSize, 1);
			glVertex3dv(bbb);

			glTexCoord2d((dieSide - 1) * dieSideSize, 1);
			glVertex3dv(bba);

			dieSide++;
			glEnd();
#pragma endregion
			#pragma region Back
			glBegin(GL_QUADS);
			//glColor3f(1, 1, 0);

			glTexCoord2d((dieSide - 1) * dieSideSize, 0);
			glVertex3dv(aaa);

			glTexCoord2d(dieSide * dieSideSize, 0);
			glVertex3dv(aba);

			glTexCoord2d(dieSide * dieSideSize, 1);
			glVertex3dv(bba);

			glTexCoord2d((dieSide - 1) * dieSideSize, 1);
			glVertex3dv(baa);

			dieSide++;
			glEnd();
#pragma endregion
			#pragma region Front
			glBegin(GL_QUADS);
			//glColor3f(0, 1, 1);

			glTexCoord2d((dieSide - 1) * dieSideSize, 0);
			glVertex3dv(aab);

			glTexCoord2d(dieSide * dieSideSize, 0);
			glVertex3dv(abb);

			glTexCoord2d(dieSide * dieSideSize, 1);
			glVertex3dv(bbb);

			glTexCoord2d((dieSide - 1) * dieSideSize, 1);
			glVertex3dv(bab);

			glEnd();
#pragma endregion
					
		}
		if (cylinderActive)
		{
			//glColor3f(0, 1, 0);
			//glBegin(GL_POLYGON);

			//quadratic = gluNewQuadric();
			//gluCylinder(quadratic, 5, 5, 3, 32, 32);

			//glEnd();
			glBegin(GL_POLYGON);

			quadratic = gluNewQuadric();
			gluQuadricDrawStyle(quadratic, GLU_FILL); /* flat shaded */
			gluQuadricNormals(quadratic, GLU_FLAT);
			gluCylinder(quadratic, 0.5, 0.3, 1.0, 15, 5);

			glEnd();
		}


		// Finally, display rendered frame on screen 
		window.display();
	} //loop back for next frame

	return EXIT_SUCCESS;
}
