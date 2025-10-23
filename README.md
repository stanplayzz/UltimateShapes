# Ultimate Shapes #
A lightweight small shape library made for SFML build on C++23. It extends `sf::Shape` with custom shapes that behave just like normal shapes. 
Altough early in development, there are a few releases out.
Missing a feature? Send me a message!

## Current features ##
### <ins>`us::RoundedRectangleShape`</ins> ###
```cpp
class SelectiveRoundedRectangleShape : public sf::Shape {
public:
	SelectiveRoundedRectangleShape(const sf::Vector2f& size = sf::Vector2f(0.f, 0.f), float radius = 0, unsigned int cornerPointCount = 8);

	void setCorners(Corner c);
	void setSize(const sf::Vector2f& size);
	void setCornerRadius(const float& radius);
	void setCornerPointCount(const unsigned int& count);
	sf::Vector2f getSize() const;
```
A simple way to make a rectangle of size `size` with all 4 corners rounded with a radius of `radius` and an amount of corner points `cornerPointCount`.



### <ins>`us::SelectiveRoundedRectangleShape`</ins> ###
```cpp
class SelectiveRoundedRectangleShape : public sf::Shape {
public:
	SelectiveRoundedRectangleShape(const sf::Vector2f& size = sf::Vector2f(0.f, 0.f), float radius = 0, unsigned int cornerPointCount = 8);

	void setCorners(Corner c);
	void setSize(const sf::Vector2f& size);
	void setCornerRadius(const float& radius);
	void setCornerPointCount(const unsigned int& count);
	sf::Vector2f getSize() const;
};
```
Makes a rectangle in which you can choose what corners to be rounded. It has a size of `size`, radius of `radius` and an amount of corner points `cornerPointCount`.

```cpp
enum class Corner{
	TopLeft,
	TopRight,
	BottomRight,
	BottomLeft,
	None
};
```
This is the enum class for setting corners. Usage as follows:
```cpp
us::SelectiveRoundedRectangleShape shape(sf::Vector2f(100.f, 100.f), 10.f, 5);
shape.setCorners(us::Corner::TopLeft | us::Corner::BottomRight);
```


### <ins>`us::Triangle`</ins> ###
```cpp
class TriangleShape : public sf::Shape {
public:
	TriangleShape(const sf::Vector2f pointA, const sf::Vector2f pointB, const sf::Vector2f pointC);

	void setPoint(std::size_t index, const sf::Vector2f& position);
};
```
A super simple function to make a triangle that SFML just didn't implement!
Make a triangle with points `pointA`, `pointB`, `pointC`

## Additional features ##
All these shapes are build on `us::Shape` which is build on `sf::Shape`.
This special shape allows for more additional features to be added to any shapes.
Currently there is one feature using this:
### <ins>`void addGradient(sf::Vector3f color1, sf::Vector3d color2, bool horizontal)`</ins> ###
This inputs 2 `sf::Vector3f`'s for the color. Important is that these colors are values between 0-1 and not 0-255.
The third parameter sets the direction of the gradient. For now only horizontal and vertical are supported, set it to `false` to get a vertical gradient, set it to `true` for a horizontal gradient (defaults to false).

> [!IMPORTANT]
> To use these additional features you have to draw the shapes using `shape.draw(sf::RenderTarget&)`.


## Including this library ##
Use `Fetch_Content`
```
include(FetchContent)

FetchContent_Declare(
    ultimateshapes
    GIT_REPOSITORY https://github.com/stanplayzz/UltimateShapes
    GIT_TAG v1.2
)
FetchContent_MakeAvailable(ultimateshapes)

target_link_libraries(main PRIVATE ultimateshapes)
```
