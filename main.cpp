#define for_all_particles for(int i = 0; i < num_particles; i++)
#define curr_particle particles[i]
#define elasticity 0.4f


#include <SFML/Graphics.hpp>
// #include "/imgui.h"
// #include "backends/imgui_impl_win32.h"
// #include "imgui/backends/imgui_impl_dx11.h"

const int num_particles = 2000000;
const float radius = 1.f;
const float gravity = 300.f;
const float err = 0.0001;
struct particle {
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Vector2f acceleration;
};

particle particles[num_particles]= {};


particle generate_particle(auto windowSize){
   
    particle particle;

    particle.position = {((rand() % (windowSize.x - 19)) + 20),((rand() % (windowSize.y - 19)) + 20)};
    particle.velocity = {((rand() % 1001) - 500),((rand() % 1001) - 500)};
    particle.acceleration = {0, gravity};
    
return particle;
}

void update_particles(float time, auto windowSize){
    for_all_particles{
        particles[i].velocity += particles[i].acceleration * time;
        particles[i].position += particles[i].velocity * time;


        if(curr_particle.position.x <= 0 ){
            curr_particle.position.x = err;
            curr_particle.velocity.x *= -elasticity;
        }
        if(curr_particle.position.x >= windowSize.x - (2*radius) ){
            curr_particle.position.x = windowSize.x - err - (2*radius);
            curr_particle.velocity.x *= -elasticity;
        }
        if(curr_particle.position.y <= 0 ){
            curr_particle.position.y = err;
            curr_particle.velocity.y *= -elasticity;
        }
        if(curr_particle.position.y >= windowSize.y - (2*radius) ){
            curr_particle.position.y = windowSize.y - err - (2*radius);
            curr_particle.velocity.y *= -elasticity;
        }
       
    }

    
}
int main()
{

    sf::RenderWindow window(sf::VideoMode({1500, 1000}), "SFML works!");
    window.setFramerateLimit(60);

    auto windowSize = window.getSize();

   for_all_particles{
        curr_particle = generate_particle(windowSize);
    }
    // sf::CircleShape shape(100.f);
    // shape.setFillColor(sf::Color::Green);

    // sf::VertexArray triangle(sf::PrimitiveType::Triangles, 3);
    
    // triangle[0].position = sf::Vector2f(310.f, 10.f);
    // triangle[2].position = sf::Vector2f(400.f, 100.f);
    // triangle[1].position = sf::Vector2f(400.f, 10.f);

    // triangle[0].color = sf::Color::Red;
    // triangle[1].color = sf::Color::Blue;
    // triangle[2].color = sf::Color::Green;
    
    sf::Clock clock;
    // sf :: CircleShape circle(radius);
    sf::VertexArray vertices(sf::PrimitiveType::Triangles, num_particles * 6);
    // circle.setFillColor(sf::Color::Cyan);
    
    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();
       for_all_particles{
        //    circle.setPosition(curr_particle.position);
        //    window.draw(circle);
        vertices[i*6].position = curr_particle.position;
        vertices[(i*6)+1].position = curr_particle.position + sf::Vector2f(0, 2*radius);
        vertices[(i*6)+2].position = curr_particle.position + sf::Vector2f(2*radius, 0);
        vertices[(i*6)+3].position = curr_particle.position + sf::Vector2f(0, 2*radius);
        vertices[(i*6)+4].position = curr_particle.position + sf::Vector2f(2* radius, 2*radius);
        vertices[(i*6)+5].position = curr_particle.position + sf::Vector2f(2*radius,0);

        for(int j = 0; j < 6; j++){
            vertices[(i*6)+j].color = sf::Color::Cyan;
        }
        }
        update_particles(deltaTime, windowSize);
        window.draw(vertices);
        // window.draw(shape);
        // window.draw(triangle);
        window.display();
    }
}
