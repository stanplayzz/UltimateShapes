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
		sf::Vector2f getSize() const;
	private:
		sf::Vector2f m_size;
		float m_radius;
		unsigned int m_cornerPoints;
	};

	class TriangleShape : public sf::Shape {
	public:
		TriangleShape(const sf::Vector2f pointA, const sf::Vector2f pointB, const sf::Vector2f pointC);

		void setPoint(std::size_t index, const sf::Vector2f& position);
		virtual std::size_t getPointCount() const override;
		virtual sf::Vector2f getPoint(size_t index) const override;
	private:
		sf::Vector2f m_p1, m_p2, m_p3;
	};

	enum class Corner : uint8_t {
		TopLeft = 1 << 0,
		TopRight = 1 << 1,
		BottomRight = 1 << 2,
		BottomLeft = 1 << 3,
		None = 0
	};
	inline Corner operator|(Corner a, Corner b) { return static_cast<Corner>(static_cast<uint8_t>(a) | static_cast<uint8_t>(b)); }
	inline Corner operator&(Corner a, Corner b) { return static_cast<Corner>(static_cast<uint8_t>(a) & static_cast<uint8_t>(b)); }

	class SelectiveRoundedRectangleShape : public sf::Shape {
	public:
		SelectiveRoundedRectangleShape(const sf::Vector2f& size = sf::Vector2f(0.f, 0.f), float radius = 0, unsigned int cornerPointCount = 8);

		void setCorners(Corner c);
		void setSize(const sf::Vector2f& size);
		void setCornerRadius(const float& radius);
		void setCornerPointCount(const unsigned int& count);

		virtual size_t getPointCount() const override;
		virtual sf::Vector2f getPoint(size_t index) const override;
		sf::Vector2f getSize() const;
	private:
		sf::Vector2f m_size;
		float m_radius;
		unsigned int m_cornerPoints;
		Corner m_corners = Corner::None;
	};
}