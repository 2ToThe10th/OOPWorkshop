#include "src/PlotBuilder.hpp"

int main() {

  PlotBuilder<100> plot_builder(1);

  ChunkedVector<sf::Vector2u, 100> vec;

  vec.EmplaceBack(0, 0);
  vec.EmplaceBack(100, 200);
  vec.EmplaceBack(200, 300);
  vec.EmplaceBack(300, 400);

  plot_builder[0].AddGraph(vec, sf::Color::Red);

  for (size_t i = 0; i < 4; ++i) {
    vec[i].y += 50;
  }

  plot_builder[0].AddGraph(vec, sf::Color::Green);

  plot_builder.Draw();
  /*
  sf::RenderTexture render_texture;

  render_texture.create(500, 500);

  render_texture.clear();

  sf::CircleShape shape(100, 100);
  shape.setFillColor(sf::Color(255, 255, 0));

  render_texture.draw(shape);

  render_texture.display();

  while (true) {

  }

  sf::RenderWindow window(sf::VideoMode(1000, 800), "SFML works!", sf::Style::Close);

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    sf::Texture texture;
    if (!texture.loadFromFile("image.jpeg")) {
      window.close();
    }
    texture.setRepeated(true);
    sf::Sprite sprite(texture);
    sprite.setPosition(sf::Vector2f(100, 100));

    sf::Font font;
    if (!font.loadFromFile("ArialMT.ttf"))
    {
      window.close();
    }

    sf::Text text;
    text.setFont(font);
    text.setString("Darova World");
    text.setFillColor(sf::Color::Yellow);
    text.setOrigin(-300, -300);
    text.setStyle(sf::Text::Bold);

    sf::CircleShape shape(50.f);
    shape.setTexture(&texture);
    shape.setTextureRect(sf::IntRect(10, 10, 100, 100));
    shape.setOutlineThickness(-10);
    shape.setOutlineColor(sf::Color::Green);

    sf::ConvexShape convex;
    convex.setPointCount(5);
    convex.setPoint(0, sf::Vector2f(500.f, 500.f));
    convex.setPoint(1, sf::Vector2f(600.f, 600.f));
    convex.setPoint(2, sf::Vector2f(700.f, 600.f));
    convex.setPoint(3, sf::Vector2f(700.f, 500.f));
    convex.setPoint(4, sf::Vector2f(600.f, 300.f));
    convex.setOutlineThickness(1);
    convex.setOutlineColor(sf::Color::Red);
    convex.setFillColor(sf::Color::Transparent);

    window.clear();

    sf::VertexArray line(sf::TriangleStrip, 6);

// define the position of the line's points
    line[0].position = sf::Vector2f(400.f, 790.f);
    line[1].position = sf::Vector2f(400.f, 800.f);
    line[2].position = sf::Vector2f(500.f, 500.f);
    line[3].position = sf::Vector2f(500.f, 510.f);
    line[4].position = sf::Vector2f(600.f, 300.f);
    line[5].position = sf::Vector2f(600.f, 310.f);

// define the color of the line's points
    line[0].color = sf::Color::Green;
    line[1].color = sf::Color::Green;
    line[2].color = sf::Color::Green;
    line[3].color = sf::Color::Green;
    line[4].color = sf::Color::Green;
    line[5].color = sf::Color::Green;

    window.draw(sprite);
    window.draw(text);
    window.draw(shape);
    window.draw(convex);
    window.draw(line);

    window.display();
  }
*/
  return 0;
}