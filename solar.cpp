#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <vector>
#include <cmath>

// إعدادات Box2D
b2World* world;

class Planet {
public:
    sf::CircleShape shape;
    b2Body* body;

    Planet(float radius, float x, float y, b2World* world) {
        shape.setRadius(radius);
        shape.setFillColor(sf::Color::Green);
        shape.setPosition(x, y);

        // إعداد الجسم الفيزيائي للكوكب
        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(x, y);

        body = world->CreateBody(&bodyDef);

        b2CircleShape circleShape;
        circleShape.m_radius = radius;

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &circleShape;
        fixtureDef.density = 1.0f;
        fixtureDef.friction = 0.3f;

        body->CreateFixture(&fixtureDef);
    }

    void update() {
        shape.setPosition(body->GetPosition().x, body->GetPosition().y);
    }

    bool isCloseToSun(sf::Vector2f sunPosition, float threshold) {
        // نحسب المسافة بين الكوكب والشمس
        float distance = std::sqrt(std::pow(shape.getPosition().x - sunPosition.x, 2) +
            std::pow(shape.getPosition().y - sunPosition.y, 2));
        return distance < threshold;
    }
};

// دالة لحساب السرعة الأولية
b2Vec2 calculateInitialVelocity(b2Vec2 position, b2Vec2 sunPosition, float orbitalSpeed) {
    // نحسب الاتجاه من الشمس إلى الكوكب
    b2Vec2 direction = position - sunPosition;
    direction.Normalize();  // توحيد الاتجاه ليصبح له طول = 1

    // السرعة يجب أن تكون عمودية على الاتجاه
    b2Vec2 perpendicular(-direction.y, direction.x);  // تدوير الاتجاه بمقدار 90 درجة (90 degrees) لعمل السرعة في المدار

    // ضرب perpendicular في orbitalSpeed بشكل يدوي
    return b2Vec2(perpendicular.x * orbitalSpeed, perpendicular.y * orbitalSpeed);
}

// دالة لإنشاء الجاذبية بين الشمس والكواكب
void applyGravity(Planet& planet, sf::Vector2f sunPosition) {
    // تحويل sf::Vector2f إلى b2Vec2
    b2Vec2 sunPos(sunPosition.x, sunPosition.y);

    b2Vec2 direction = sunPos - planet.body->GetPosition();
    float distance = direction.Length();
    if (distance > 0) {
        direction.Normalize();
        float forceMagnitude = (planet.body->GetMass() * 10) / (distance * distance);
        b2Vec2 force = direction;
        force *= forceMagnitude;

        planet.body->ApplyForceToCenter(force, true);
    }
}

int main() {
    // إعداد نافذة SFML
    sf::RenderWindow window(sf::VideoMode(800, 600), "Solar System Simulation");

    // إعداد العالم الفيزيائي باستخدام Box2D
    b2Vec2 gravity(0.0f, 0.0f);
    world = new b2World(gravity);

    // إنشاء الشمس كدائرة صفراء كبيرة
    sf::CircleShape sun(50.0f);  // دائرة نصف قطرها 50 تمثل الشمس
    sun.setFillColor(sf::Color::Yellow);  // تلوينها باللون الأصفر
    sun.setPosition(400 - 50, 300 - 50);  // جعلها في وسط الشاشة (400, 300)

    // قائمة لتخزين الكواكب
    std::vector<Planet> planets;

    // السرعة المدارية الابتدائية
    float orbitalSpeed = 0.3f;

    // محاكاة النظام الشمسي
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                // الحصول على موقع الماوس عند الضغط عليه
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                sf::Vector2f mousePosF(mousePos.x, mousePos.y);  // تحويل إلى sf::Vector2f

                // حساب موقع الكوكب
                float planetRadius = 10.0f;  // نصف قطر الكوكب
                Planet newPlanet(planetRadius, mousePosF.x, mousePosF.y, world);

                // حساب السرعة الأولية
                b2Vec2 planetPosition(mousePosF.x, mousePosF.y);
                b2Vec2 sunPosition(400, 300);  // مكان الشمس

                // حساب السرعة الأولية للمدار
                b2Vec2 velocity = calculateInitialVelocity(planetPosition, sunPosition, orbitalSpeed);

                // تعيين السرعة الأولية للكوكب
                newPlanet.body->SetLinearVelocity(velocity);

                planets.push_back(newPlanet);
            }
        }

        // تحديث المحاكاة الفيزيائية
        world->Step(1.0f / 60.0f, 8, 3);

        // رسم الشمس
        window.clear();
        window.draw(sun);  // رسم الشمس
        for (auto it = planets.begin(); it != planets.end();) {
            it->update();
            window.draw(it->shape);

            // التحقق إذا كان الكوكب قريبًا من الشمس
            if (it->isCloseToSun(sun.getPosition(), 50.0f)) {
                // إزالة الكوكب من العالم والشاشة إذا كان قريبًا من الشمس
                world->DestroyBody(it->body);
                it = planets.erase(it);  // إزالة الكوكب من القائمة
            }
            else {
                ++it;  // الانتقال إلى الكوكب التالي في القائمة
            }
        }

        // تطبيق الجاذبية
        for (auto& planet : planets) {
            applyGravity(planet, sun.getPosition());  // إرسال موقع الشمس
        }

        window.display();
    }

    delete world;
    return 0;
}
