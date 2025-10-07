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



	SuperEllipseShape::SuperEllipseShape(float a, float b, float n, unsigned int points) : m_a(a), m_b(b), m_n(n), m_points(points) {
		update();
	}

	std::size_t SuperEllipseShape::getPointCount() const { 
		return m_points; 
	}

	sf::Vector2f SuperEllipseShape::getPoint(size_t index) const {
		float t = 2.f * PI * index / m_points;
		float cos_t = std::cos(t);
		float sin_t = std::sin(t);

		float x = m_a * sgn(cos_t) * std::pow(std::abs(cos_t), 2.f / m_n);
		float y = m_b * sgn(sin_t) * std::pow(std::abs(sin_t), 2.f / m_n);

		return { x + m_a, y + m_b };
	}
}