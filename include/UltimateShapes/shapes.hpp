#pragma once
#include <SFML/Graphics.hpp>
namespace us {
	class RoundedRectangleShape : public sf::Shape {
	public:
		RoundedRectangleShape(const sf::Vector2f& size = sf::Vector2f(0, 0), float radius = 0, unsigned int cornerPointCount = 8);

		void setSize(const sf::Vector2f& size);
		void setCornerRadius(const float& radius);
		void setCornerPointCount(const unsigned int& count);

		virtual size_t getPointCount() const override;
		virtual sf::Vector2f getPoint(size_t index) const override;
	private:
		sf::Vector2f m_size;
		float m_radius;
		unsigned int m_cornerPoints;
	};

	class Triangle : public sf::Shape {
	public:
		Triangle(const sf::Vector2f pointA, const sf::Vector2f pointB, const sf::Vector2f pointC);

		void setPoint(std::size_t index, const sf::Vector2f& position);
		virtual std::size_t getPointCount() const override;
		virtual sf::Vector2f getPoint(size_t index) const override;
	private:
		sf::Vector2f m_p1, m_p2, m_p3;
	};
}