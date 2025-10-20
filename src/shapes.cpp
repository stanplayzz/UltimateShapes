#include <UltimateShapes/shapes.hpp>

#include <numbers>
#include <cmath>

constexpr float PI = std::numbers::pi_v<float>;

namespace us {
	RoundedRectangleShape::RoundedRectangleShape(const sf::Vector2f& size, float radius, unsigned int cornerPoints)
		: m_size(size), m_radius(radius), m_cornerPoints(cornerPoints) {
		update();
	}
	void RoundedRectangleShape::setSize(const sf::Vector2f& size) {
		m_size = size;
		update();
	}
	void RoundedRectangleShape::setCornerRadius(const float& radius) {
		m_radius = radius;
		update();
	}
	void RoundedRectangleShape::setCornerPointCount(const unsigned int& count) {
		m_cornerPoints = count;
		update();
	}

	size_t RoundedRectangleShape::getPointCount() const {
		return m_cornerPoints * 4;
	}

	sf::Vector2f RoundedRectangleShape::getPoint(size_t index) const {
		unsigned int corner = index / m_cornerPoints;
		unsigned int i = index % m_cornerPoints;
		float angle = 0.f;
		sf::Vector2f center;

		switch (corner) {
		case 0:
			center = { m_radius, m_radius };
			angle = PI + (i * PI / 2 / (m_cornerPoints - 1));
			break;
		case 1:
			center = { m_size.x - m_radius, m_radius };
			angle = -PI / 2 + (i * PI / 2 / (m_cornerPoints - 1));
			break;
		case 2:
			center = { m_size.x - m_radius, m_size.y - m_radius };
			angle =  (i * PI / 2 / (m_cornerPoints - 1));
			break;
		case 3:
			center = { m_radius, m_size.y - m_radius };
			angle = PI / 2 + (i * PI / 2 / (m_cornerPoints - 1));
			break;
		}
		return { center.x + m_radius * std::cos(angle), center.y + m_radius * std::sin(angle) };
	}



	Triangle::Triangle(const sf::Vector2f pointA, const sf::Vector2f pointB, const sf::Vector2f pointC) 
		: m_p1(pointA), m_p2(pointB), m_p3(pointC) {
		update();
	}

	void Triangle::setPoint(std::size_t index, const sf::Vector2f& position) {
		switch (index) {
		case 0: m_p1 = position; break;
		case 1: m_p2 = position; break;
		case 2: m_p3 = position; break;
		}
		update();
	}

	std::size_t Triangle::getPointCount() const {
		return 3;
	}
	sf::Vector2f Triangle::getPoint(size_t index) const {
		switch (index) {
			case 0: return m_p1;
			case 1: return m_p2;
			case 2: return m_p3;
		}
	}
}