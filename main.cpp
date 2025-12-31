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

    const float HEX_RADIUS = 60.f;
    sf::CircleShape hexagon(HEX_RADIUS, 6);
    hexagon.setFillColor(sf::Color::Transparent);
    hexagon.setOutlineThickness(3);
    hexagon.setOutlineColor(sf::Color(255, 127, 80));
    hexagon.setOrigin(HEX_RADIUS, HEX_RADIUS);

    sf::Color trailFromSpacedVerticesColor = sf::Color::Yellow;
    sf::Color shortLinesColor = sf::Color::Green;

    // Tạo 6 màu ngẫu nhiên riêng biệt cho 6 trail pixel (cố định suốt chương trình)
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
    float orbitRadius = 150.0f;

    std::vector<std::deque<sf::Vertex>> spacedVertexTrails(3);
    std::vector<std::deque<sf::Vertex>> shortEndPixelTrails(6); // 6 trails pixel

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

        // === 1. Trails đường từ 3 đỉnh chẵn (0, 2, 4) ===
        int trailIdx = 0;
        for (int i = 0; i < 6; i += 2) {
            sf::Vector2f v = vertices[i];
            spacedVertexTrails[trailIdx].push_back(sf::Vertex(v, trailFromSpacedVerticesColor));

            if (spacedVertexTrails[trailIdx].size() > 1) {
                sf::VertexArray trailVA(sf::LineStrip);
                for (const auto& vertex : spacedVertexTrails[trailIdx]) {
                    trailVA.append(vertex);
                }
                window.draw(trailVA);
            }
            trailIdx++;
        }

        // === 2. Vẽ 6 đoạn ngắn và 6 trail pixel từ các đầu đoạn ===
        int pixelTrailIdx = 0;
        for (int i = 0; i < 6; ++i) { // Duyệt hết 6 đỉnh
            sf::Vector2f v = vertices[i];

            // Chỉ xử lý các đỉnh lẻ (1,3,5) làm gốc cho đoạn ngắn, vì đoạn ngắn xuất phát từ đó
            if (i % 2 == 0) continue; // Bỏ qua đỉnh chẵn

            sf::Vector2f dirToVertex = v - hexagon.getPosition();
            float baseAngle = std::atan2(dirToVertex.y, dirToVertex.x);

            for (int k = -1; k <= 1; k += 2) { // hai hướng: +60° và -60°
                float angle = baseAngle + k * (PI / 3.0f);
                sf::Vector2f shortDir(std::cos(angle), std::sin(angle));
                sf::Vector2f shortEnd = v + shortDir * 40.0f;

                // Vẽ đoạn ngắn màu xanh lá
                sf::VertexArray shortLine(sf::Lines, 2);
                shortLine[0] = sf::Vertex(v, shortLinesColor);
                shortLine[1] = sf::Vertex(shortEnd, shortLinesColor);
                window.draw(shortLine);

                // Thêm điểm vào trail pixel tương ứng với màu cố định
                sf::Color pixelColor = pixelTrailColors[pixelTrailIdx];
                shortEndPixelTrails[pixelTrailIdx].push_back(sf::Vertex(shortEnd, pixelColor));

                // Vẽ trail pixel
                if (!shortEndPixelTrails[pixelTrailIdx].empty()) {
                    sf::VertexArray pixelVA(sf::Points);
                    for (const auto& vertex : shortEndPixelTrails[pixelTrailIdx]) {
                        pixelVA.append(vertex);
                    }
                    window.draw(pixelVA);
                }

                pixelTrailIdx++; // Tăng chỉ số trail
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
