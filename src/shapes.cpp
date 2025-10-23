#include <UltimateShapes/shapes.hpp>

#include <numbers>
#include <cmath>

constexpr float PI = std::numbers::pi_v<float>;

namespace us {
	Shape::Shape() {
		gradientShader.loadFromFile(SHADERS_DIR + std::string("/gradientShader.frag"), sf::Shader::Type::Fragment);
	}
	void Shape::addGradient(const sf::Vector3f color1, const sf::Vector3f color2, bool horizontal = false) {
		if (!gradientShader.isAvailable()) return;

		if (!gradientAdded) {
			sf::Image img;
			img.resize({ 1, 1 }, sf::Color::White);
			texture.loadFromImage(img);
			setTexture(&texture); 
			gradientAdded = true;
		}

		gradientShader.setUniform("color1", sf::Glsl::Vec3(color1));
		gradientShader.setUniform("color2", sf::Glsl::Vec3(color2));
		gradientShader.setUniform("horizontal", horizontal);
	}
	void Shape::draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) {
		if (gradientAdded) states.shader = &gradientShader;
		target.draw(*this, states);
	}


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

	sf::Vector2f RoundedRectangleShape::getSize() const {
		return m_size;
	}


	TriangleShape::TriangleShape(const sf::Vector2f pointA, const sf::Vector2f pointB, const sf::Vector2f pointC)
		: m_p1(pointA), m_p2(pointB), m_p3(pointC) {
		update();
	}

	void TriangleShape::setPoint(std::size_t index, const sf::Vector2f& position) {
		switch (index) {
		case 0: m_p1 = position; break;
		case 1: m_p2 = position; break;
		case 2: m_p3 = position; break;
		}
		update();
	}

	std::size_t TriangleShape::getPointCount() const {
		return 3;
	}
	sf::Vector2f TriangleShape::getPoint(size_t index) const {
		switch (index) {
			case 0: return m_p1;
			case 1: return m_p2;
			case 2: return m_p3;
		}
	}

	SelectiveRoundedRectangleShape::SelectiveRoundedRectangleShape(const sf::Vector2f& size, float radius, unsigned int cornerPoints)
		: m_size(size), m_radius(radius), m_cornerPoints(cornerPoints) {
		update();
	}
	void SelectiveRoundedRectangleShape::setCorners(Corner c) {
		m_corners = c;
		update();
	}
	void SelectiveRoundedRectangleShape::setSize(const sf::Vector2f& size) {
		m_size = size;
		update();
	}
	void SelectiveRoundedRectangleShape::setCornerRadius(const float& radius) {
		m_radius = radius;
		update();
	}
	void SelectiveRoundedRectangleShape::setCornerPointCount(const unsigned int& count) {
		m_cornerPoints = count;
		update();
	}
	std::size_t SelectiveRoundedRectangleShape::getPointCount() const {
		std::size_t count = 0;
		if (static_cast<uint8_t>(m_corners & Corner::TopLeft))     count += m_cornerPoints; else count += 1;
		if (static_cast<uint8_t>(m_corners & Corner::TopRight))    count += m_cornerPoints; else count += 1;
		if (static_cast<uint8_t>(m_corners & Corner::BottomRight)) count += m_cornerPoints; else count += 1;
		if (static_cast<uint8_t>(m_corners & Corner::BottomLeft))  count += m_cornerPoints; else count += 1;
		return count;
	}
	sf::Vector2f SelectiveRoundedRectangleShape::getPoint(std::size_t index) const {
		struct CornerInfo { Corner flag; sf::Vector2f center; float startAngle; float endAngle; };
		CornerInfo cornersInfo[4] = {
			{ Corner::TopLeft,     { m_radius, m_radius },                 PI, 3.f * PI / 2.f },
			{ Corner::TopRight,    { m_size.x - m_radius, m_radius },      -PI / 2.f, 0.f },
			{ Corner::BottomRight, { m_size.x - m_radius, m_size.y - m_radius }, 0.f, PI / 2.f },
			{ Corner::BottomLeft,  { m_radius, m_size.y - m_radius },       PI / 2.f, PI }
		};

		for (int c = 0; c < 4; ++c) {
			bool rounded = static_cast<uint8_t>(m_corners & cornersInfo[c].flag);
			std::size_t pointsInCorner = rounded ? m_cornerPoints : 1;
			if (index < pointsInCorner) {
				if (!rounded) {
					switch (c) {
					case 0: return { 0.f, 0.f };
					case 1: return { m_size.x, 0.f };
					case 2: return { m_size.x, m_size.y };
					case 3: return { 0.f, m_size.y };
					}
				}
				else {
					float angle = cornersInfo[c].startAngle + (cornersInfo[c].endAngle - cornersInfo[c].startAngle) * index / (m_cornerPoints - 1);
					return {
						cornersInfo[c].center.x + m_radius * std::cos(angle),
						cornersInfo[c].center.y + m_radius * std::sin(angle)
					};
				}
			}
			else {
				index -= pointsInCorner;
			}
		}
		return { 0.f, 0.f };
	}
}