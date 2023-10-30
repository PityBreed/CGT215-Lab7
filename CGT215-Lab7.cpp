// CGT215-Lab7.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFPhysics.h>
using namespace std;
using namespace sf;
using namespace sfp;
int main()
{
	// Create our window and world with gravity 0,1
	RenderWindow window(VideoMode(800, 600), "Bounce");
	World world(Vector2f(0, 1));

	// Create the ball
	PhysicsCircle ball;
	ball.setCenter(Vector2f(400, 200));
	ball.setRadius(20);
	world.AddPhysicsBody(ball); 

	// Create the floor
	PhysicsRectangle floor;
	floor.setSize(Vector2f(800, 20));
	floor.setCenter(Vector2f(400, 590));
	floor.setStatic(true);
	world.AddPhysicsBody(floor);

	// Create the left wall 
	PhysicsRectangle Lwall;
	Lwall.setSize(Vector2f(20, 600));
	Lwall.setCenter(Vector2f(790, 300));
	Lwall.setStatic(true);
	world.AddPhysicsBody(Lwall);

	// Create the right wall 
	PhysicsRectangle Rwall;
	Rwall.setSize(Vector2f(20, 600));
	Rwall.setCenter(Vector2f(10, 300));
	Rwall.setStatic(true);
	world.AddPhysicsBody(Rwall);

	// Create the ceiling 
	PhysicsRectangle ceil;
	ceil.setSize(Vector2f(800, 20));
	ceil.setCenter(Vector2f(400, 10));
	ceil.setStatic(true);
	world.AddPhysicsBody(ceil);

	// Create the center 
	PhysicsRectangle cent;
	cent.setSize(Vector2f(50, 50));
	cent.setCenter(Vector2f(400, 300));
	cent.setStatic(true);
	world.AddPhysicsBody(cent);

	int thudCount(1);
	floor.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
		cout << "thud " << thudCount << endl;
		thudCount++;
		};

	int bangCount(1);
	cent.onCollision = [&bangCount, &ball](PhysicsBodyCollisionResult result) {
		cout << "bang " << bangCount << endl;
		bangCount++;
		};

	Clock clock;
	Time lastTime(clock.getElapsedTime());
	while (bangCount < 4) {
		// calculate MS since last frame
		Time currentTime(clock.getElapsedTime());
		Time deltaTime(currentTime - lastTime);
		int deltaTimeMS(deltaTime.asMilliseconds());
		if (deltaTimeMS > 0) {
			world.UpdatePhysics(deltaTimeMS);
			lastTime = currentTime;
		}

		// Little bit of silliness
		Color New(255 - (85 * (bangCount - 1)), 255 - (85 * (bangCount - 1)), 255 - (85 * (bangCount - 1)));
		ball.setFillColor(New);
		floor.setFillColor(New);
		Lwall.setFillColor(New);
		Rwall.setFillColor(New);
		ceil.setFillColor(New);
		cent.setFillColor(New);

		window.clear(Color(0, 0, 0));
		window.draw(ball);
		window.draw(floor);
		window.draw(Lwall);
		window.draw(Rwall);
		window.draw(ceil);
		window.draw(cent);
		window.display();
	}
}