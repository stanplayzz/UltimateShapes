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

	class SuperEllipseShape : public sf::Shape {
	public:
		SuperEllipseShape(float a = 100, float b = 100, float n = 2.f, unsigned int points = 50);

		virtual std::size_t getPointCount() const override;
		virtual sf::Vector2f getPoint(size_t index) const override;
	private:
		float m_a, m_b, m_n, m_points;
		float sgn(float v) const { return (v >= 0) ? 1.f : -1.f; }
	};
}