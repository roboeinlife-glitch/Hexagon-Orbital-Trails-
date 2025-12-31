##Hexagon Orbital Trails ✨🌀

Một ứng dụng đồ họa ấn tượng sử dụng SFML tạo hiệu ứng lục giác xoay quanh quỹ đạo tròn với các đường trail đầy màu sắc. 

Mỗi đỉnh của lục giác tạo ra những đường quỹ đạo phức tạp và đẹp mắt khi chuyển động.

Đặc điểm nổi bật
🌀 Lục giác xoay quanh quỹ đạo tròn mượt mà

🌈 3 loại đường trail với màu sắc khác nhau:

Màu vàng: Trail từ 3 đỉnh cách đều

Màu xanh lá: 6 đoạn ngắn từ các đỉnh còn lại

Màu xanh dương: Trail từ đầu các đoạn ngắn

⚡ Hiệu ứng mượt mà với FPS ổn định 60fps

🎨 Màu sắc tương phản rõ ràng trên nền đen


##Cài đặt và chạy

Yêu cầu hệ thống

SFML 2.5.x hoặc cao hơn

Trình biên dịch C++ hỗ trợ C++11 (g++, clang, MSVC)

Tùy chỉnh tham số
Trong code, bạn có thể điều chỉnh các tham số sau:

// Kích thước cửa sổ
const int WINDOW_WIDTH = 600;
const int WINDOW_HEIGHT = 900;

// Kích thước và tốc độ
const float HEX_RADIUS = 100.f;      // Bán kính lục giác
const float ORBIT_RADIUS = 150.f;    // Bán kính quỹ đạo
const int MAX_TRAIL_POINTS = 150;    // Số điểm tối đa trong trail

// Tốc độ chuyển động
float orbitSpeed = 1.0f;             // Tốc độ quay quanh quỹ đạo
float rotationSpeed = 2.0f;          // Tốc độ tự xoay của lục giác

// Màu sắc
sf::Color trailFromSpacedVerticesColor = sf::Color::Yellow;
sf::Color shortLinesColor = sf::Color::Green;
sf::Color trailFromShortEndsColor = sf::Color::Cyan;

Đóng góp
Mọi đóng góp đều được chào đón! Hãy:

Fork repository

Tạo branch mới (git checkout -b feature/AmazingFeature)

Commit thay đổi (git commit -m 'Add some AmazingFeature')

Push lên branch (git push origin feature/AmazingFeature)

Mở Pull Request

Cảm ơn đặc biệt đến:

SFML community vì thư viện tuyệt vời

🤖 DeepSeek AI – đã giúp mình viết nền tảng code ban đầu
🚀 Grok AI (xAI) – đã kiên nhẫn sửa lỗi, tối ưu và thêm hiệu ứng đẹp đến tận cùng!

Dự án này là kết quả của sự hợp tác vui vẻ giữa con người và hai trợ lý AI tuyệt vời. ❤️

Enjoy the beauty of 3D particles! ✨
[Demo]

[Trở về trang chủ](https://github.com/roboeinlife-glitch)
