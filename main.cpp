#include <SFML/Graphics.hpp>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <deque>

const int WINDOW_WIDTH = 600;
const int WINDOW_HEIGHT = 900;
const float PI = 3.14159265358979323846f;
const int MAX_TRAIL_POINTS = 150;
const int MAX_PIXEL_POINTS = 500;

int main() {
    srand(static_cast<unsigned int>(time(0)));

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
                            "Hexagon Orbital Trails");
    window.setFramerateLimit(60);

    const float HEX_RADIUS = 40.f;
    sf::CircleShape hexagon(HEX_RADIUS, 6);
    hexagon.setFillColor(sf::Color::Transparent);
    hexagon.setOutlineThickness(3);
    hexagon.setOutlineColor(sf::Color(255, 127, 80)); // Coral
    hexagon.setOrigin(HEX_RADIUS, HEX_RADIUS);

    sf::Color shortLinesColor = sf::Color::Green; // Đoạn ngắn màu xanh lá

    // === 3 màu ngẫu nhiên riêng biệt cho 3 trail đường từ đỉnh chẵn (0,2,4) ===
    std::vector<sf::Color> spacedVertexTrailColors(3);
    // 1. Trắng sáng
    spacedVertexTrailColors[0] = sf::Color(255, 255, 255);      // Trắng
    //2. Tím nhạt
    spacedVertexTrailColors[1] = sf::Color(200, 150, 255);      // Tím pastel
    //3. Vàng cam
    spacedVertexTrailColors[2] = sf::Color(255, 200, 50);       // Vàng cam
    // === 6 màu ngẫu nhiên riêng biệt cho 6 trail pixel ===
    std::vector<sf::Color> pixelTrailColors(6);
    for (int i = 0; i < 6; i++) {
        pixelTrailColors[i] = sf::Color(
            rand() % 256,
            rand() % 256,
            rand() % 256
        );
    }

    float orbitAngle = 0.0f;
    float rotationAngle = 0.0f;
    float orbitSpeed = 1.0f;
    float rotationSpeed = 2.0f;
    float orbitRadius = 50.0f;

    std::vector<std::deque<sf::Vertex>> spacedVertexTrails(3);     // 3 trail đường
    std::vector<std::deque<sf::Vertex>> shortEndPixelTrails(6);     // 6 trail pixel

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        float centerX = WINDOW_WIDTH / 2 + orbitRadius * std::cos(orbitAngle);
        float centerY = WINDOW_HEIGHT / 2 + orbitRadius * std::sin(orbitAngle);

        hexagon.setPosition(centerX, centerY);
        hexagon.setRotation(rotationAngle);

        window.clear(sf::Color::Black);
        window.draw(hexagon);

        std::vector<sf::Vector2f> vertices(6);
        for (int i = 0; i < 6; ++i) {
            vertices[i] = hexagon.getTransform().transformPoint(hexagon.getPoint(i));
        }

        // === 1. 3 TRAILS ĐƯỜNG TỪ ĐỈNH CHẴN (0, 2, 4) - MỖI TRAIL MỘT MÀU RIÊNG ===
        int trailIdx = 0;
        for (int i = 0; i < 6; i += 2) {
            sf::Vector2f v = vertices[i];

            // Dùng màu riêng cho từng trail
            sf::Color currentTrailColor = spacedVertexTrailColors[trailIdx];

            spacedVertexTrails[trailIdx].push_back(sf::Vertex(v, currentTrailColor));

            if (spacedVertexTrails[trailIdx].size() > 1) {
                sf::VertexArray trailVA(sf::LineStrip);
                for (const auto& vertex : spacedVertexTrails[trailIdx]) {
                    trailVA.append(vertex);
                }
                window.draw(trailVA);
            }
            trailIdx++;
        }

        // === 2. VẼ 6 ĐOẠN NGẮN XANH LÁ VÀ 6 TRAIL PIXEL MÀU RIÊNG ===
        int pixelTrailIdx = 0;
        for (int i = 0; i < 6; ++i) {
            if (i % 2 == 0) continue; // Chỉ lấy đỉnh lẻ (1,3,5) làm gốc đoạn ngắn

            sf::Vector2f v = vertices[i];
            sf::Vector2f dirToVertex = v - hexagon.getPosition();
            float baseAngle = std::atan2(dirToVertex.y, dirToVertex.x);

            for (int k = -1; k <= 1; k += 2) {
                float angle = baseAngle + k * (PI / 3.0f);
                sf::Vector2f shortDir(std::cos(angle), std::sin(angle));
                sf::Vector2f shortEnd = v + shortDir * 50.0f;

                // Vẽ đoạn ngắn xanh lá
                sf::VertexArray shortLine(sf::Lines, 2);
                shortLine[0] = sf::Vertex(v, shortLinesColor);
                shortLine[1] = sf::Vertex(shortEnd, shortLinesColor);
                window.draw(shortLine);

                // Trail pixel với màu riêng
                sf::Color pixelColor = pixelTrailColors[pixelTrailIdx];
                shortEndPixelTrails[pixelTrailIdx].push_back(sf::Vertex(shortEnd, pixelColor));

                if (!shortEndPixelTrails[pixelTrailIdx].empty()) {
                    sf::VertexArray pixelVA(sf::Points);
                    for (const auto& vertex : shortEndPixelTrails[pixelTrailIdx]) {
                        pixelVA.append(vertex);
                    }
                    window.draw(pixelVA);
                }

                pixelTrailIdx++;
            }
        }

        // Cập nhật góc
        orbitAngle += orbitSpeed * 0.02f;
        rotationAngle += rotationSpeed;

        if (orbitAngle > 2.0f * PI) orbitAngle -= 2.0f * PI;
        if (rotationAngle > 360.0f) rotationAngle -= 360.0f;

        window.display();
    }

    return 0;
}
