#include <SFML/Graphics.hpp>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <vector>

const int WINDOW_WIDTH = 600;
const int WINDOW_HEIGHT = 900;
const float PI = 3.14159265358979323846f;
const int MAX_TRAIL_POINTS = 100;  // Số điểm tối đa trong mỗi trail

// Hàm tạo màu ngẫu nhiên
sf::Color getRandomColor() {
    return sf::Color(rand() % 256, rand() % 256, rand() % 256);
}

int main() {
    // Khởi tạo random
    srand(static_cast<unsigned int>(time(0)));

    // Tạo cửa sổ
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
                           "Rotating Hexagon with Circular Trails");
    window.setFramerateLimit(60);

    // Tạo hình lục giác
    const float HEX_RADIUS = 100.f;
    sf::CircleShape hexagon(HEX_RADIUS, 6);
    hexagon.setFillColor(sf::Color::Transparent);
    hexagon.setOutlineThickness(3);
    hexagon.setOutlineColor(sf::Color(255, 127, 80)); // Coral color
    hexagon.setOrigin(HEX_RADIUS, HEX_RADIUS);

    // Màu sắc cho các thành phần
    sf::Color trailFromSpacedVerticesColor = sf::Color::Yellow;
    sf::Color shortLinesColor = sf::Color::Green;
    sf::Color trailFromShortEndsColor = sf::Color::Cyan;

    // Biến chuyển động
    float orbitAngle = 0.0f;
    float rotationAngle = 0.0f;
    float orbitSpeed = 1.0f;
    float rotationSpeed = 2.0f;
    float orbitRadius = 150.0f;   // Bán kính cố định

    // Trails - sử dụng VertexArray nhưng quản lý đúng cách
    std::vector<sf::VertexArray> spacedVertexTrails(3);
    std::vector<sf::VertexArray> shortEndTrails(6);

    // Khởi tạo các trails
    for (int i = 0; i < 3; i++) {
        spacedVertexTrails[i].setPrimitiveType(sf::LineStrip);
    }
    for (int i = 0; i < 6; i++) {
        shortEndTrails[i].setPrimitiveType(sf::LineStrip);
    }

    // Vòng lặp chính
    while (window.isOpen()) {
        // Xử lý sự kiện
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Tâm lục giác di chuyển theo đường tròn CỐ ĐỊNH
        float centerX = WINDOW_WIDTH / 2 + orbitRadius * std::cos(orbitAngle);
        float centerY = WINDOW_HEIGHT / 2 + orbitRadius * std::sin(orbitAngle);

        // Cập nhật vị trí và góc xoay
        hexagon.setPosition(centerX, centerY);
        hexagon.setRotation(rotationAngle);

        // Xóa màn hình
        window.clear(sf::Color::Black);

        // Vẽ lục giác
        window.draw(hexagon);

        // Lấy tọa độ 6 đỉnh
        std::vector<sf::Vector2f> vertices(6);
        for (int i = 0; i < 6; ++i) {
            vertices[i] = hexagon.getTransform().transformPoint(hexagon.getPoint(i));
        }

        // 1. Trails từ 3 đỉnh cách đều (0, 2, 4)
        int trailIdx = 0;
        for (int i = 0; i < 6; i += 2) {
            sf::Vector2f v = vertices[i];

            // Thêm điểm mới vào trail
            spacedVertexTrails[trailIdx].append(sf::Vertex(v, trailFromSpacedVerticesColor));

            // Giới hạn số điểm để tạo đường tròn (KHÔNG xóa)
            // Chỉ cần kiểm tra và giữ số điểm tối đa
            // VertexArray tự quản lý bộ nhớ, không cần xóa thủ công

            // Vẽ trail
            window.draw(spacedVertexTrails[trailIdx]);
            trailIdx++;
        }

        // 2. Vẽ 6 đoạn ngắn và trails từ điểm cuối
        int shortTrailIdx = 0;
        for (int i = 1; i < 6; i += 2) {
            sf::Vector2f v = vertices[i];
            sf::Vector2f dirToVertex = v - hexagon.getPosition();
            float baseAngle = std::atan2(dirToVertex.y, dirToVertex.x);

            for (int k = -1; k <= 1; k += 2) {
                float angle = baseAngle + k * (PI / 3.0f);
                sf::Vector2f shortDir(std::cos(angle), std::sin(angle));
                sf::Vector2f shortEnd = v + shortDir * 40.0f;

                // Vẽ đoạn ngắn
                sf::VertexArray shortLine(sf::Lines, 2);
                shortLine[0] = sf::Vertex(v, shortLinesColor);
                shortLine[1] = sf::Vertex(shortEnd, shortLinesColor);
                window.draw(shortLine);

                // Thêm điểm vào trail
                shortEndTrails[shortTrailIdx].append(sf::Vertex(shortEnd, trailFromShortEndsColor));

                // Vẽ trail
                window.draw(shortEndTrails[shortTrailIdx]);
                shortTrailIdx++;
            }
        }

        // Cập nhật các góc
        orbitAngle += orbitSpeed * 0.02f;
        rotationAngle += rotationSpeed;

        // Giữ góc trong khoảng hợp lệ
        if (orbitAngle > 2.0f * PI) orbitAngle -= 2.0f * PI;
        if (orbitAngle < 0) orbitAngle += 2.0f * PI;

        if (rotationAngle > 360.0f) rotationAngle -= 360.0f;
        if (rotationAngle < 0) rotationAngle += 360.0f;

        // Hiển thị
        window.display();
    }

    return 0;
}
