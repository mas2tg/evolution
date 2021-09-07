//
//  main.cpp
//  evolution
//
//  Created by Marco Antonio de Souza Azevedo on 6/18/21.
//

#include <SFML/Graphics.hpp>
#include "Collision.hpp"

#include <iostream>
#include <vector>
#include <math.h>

const int WIDTH = 640;
const int HEIGHT = 480;

class CircleEntity{
    
public:
    float _xDisp;
    float _yDisp;
    float _mass; //TODO:
    int _speed; //TODO:
    CircleEntity(){};
    CircleEntity(int x, int y, float xDisp, float yDisp, float radius, int speed, sf::CircleShape cs):_xDisp(xDisp), _yDisp(yDisp), _speed(speed), m_circle(cs){
        m_circle.setPosition(x, y);
        m_circle.setRadius(radius);
    }
    
    sf::CircleShape *getCircleShape(){
        return& m_circle;
    }
    
private:
    sf::CircleShape m_circle;
};



int main(int argc, const char * argv[]) {
    std::cout << "Hello, World!\n";
    
    sf::RenderWindow window( sf::VideoMode(WIDTH, HEIGHT), "Evolution Game");
    CircleEntity circle1(130, 130, 0.1f, 0.1f, 75, 1, sf::CircleShape());
    CircleEntity circle2(500, 70, 0.1f, -0.1f, 50, 2, sf::CircleShape());
    CircleEntity circle3(300, 300, -0.1f, -0.1f, 25, 3, sf::CircleShape());

    
    std::vector<CircleEntity *> circles;
    circles.push_back(&circle1);
    circles.push_back(&circle2);
    circles.push_back(&circle3);

    
//    float deltaTime = 0.0f;
//    sf::Clock clock;
    
    
    while (window.isOpen()){
        sf::Event event;
//         deltaTime = clock.restart().asSeconds();
//         sf::Sprite sp;
        
        // HANDLE EVENTS
        while( window.pollEvent(event)){
            switch(event.type){
                case sf::Event::Closed:
                    window.close();
                    break;
            }
        }
        window.clear();
        
        for (auto circle: circles){
            window.draw(*circle->getCircleShape());
        }
        
        window.display();
        

        // HANDLE COLLISION
        for (int i = 0; i < circles.size(); i++){
            
            // HANDLE EDGES OF THE SCREEN
            if (circles[i]->getCircleShape()->getPosition().x > WIDTH-circles[i]->getCircleShape()->getRadius()*2)
                circles[i]->_xDisp = -.1f*circles[i]->_speed;
                //circle->move(-0.1f, 0.1);
            else if (circles[i]->getCircleShape()->getPosition().x < 0)
                circles[i]->_xDisp = .1f*circles[i]->_speed;
            
            if (circles[i]->getCircleShape()->getPosition().y > HEIGHT-circles[i]->getCircleShape()->getRadius()*2)
                circles[i]->_yDisp = -.1f*circles[i]->_speed;
            else if (circles[i]->getCircleShape()->getPosition().y < 0)
                circles[i]->_yDisp = .1f*circles[i]->_speed;
            
            // HANDLE OTHER OBJECTS
            for (int j = i+1; j < circles.size(); j++){
               
    
                //distance between centers
                auto sum_radii = circles[i]->getCircleShape()->getRadius()+circles[j]->getCircleShape()->getRadius();
                
                auto x_squared = (pow(circles[i]->getCircleShape()->getPosition().x + circles[i]->getCircleShape()->getRadius() - circles[j]->getCircleShape()->getPosition().x - circles[j]->getCircleShape()->getRadius(), 2));
                auto y_squared = (pow(circles[i]->getCircleShape()->getPosition().y + circles[i]->getCircleShape()->getRadius() - circles[j]->getCircleShape()->getPosition().y - circles[j]->getCircleShape()->getRadius(), 2));
                
                auto z = sqrt(x_squared+y_squared);
                
            
                if(z < sum_radii){
                    std::cout << z << " collision!\n";
                    circles[i]->_xDisp *= -1;
                    circles[j]->_xDisp *= -1;
                    circles[i]->_yDisp *= -1;
                    circles[j]->_yDisp *= -1;

                }
            }
            circles[i]->getCircleShape()->move(circles[i]->_xDisp, circles[i]->_yDisp);
        }
    }
    
    return 0;
}
