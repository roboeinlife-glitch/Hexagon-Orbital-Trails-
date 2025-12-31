## Hexagon Orbital Trails ✨🌀

![C++](https://img.shields.io/badge/C++-17-blue.svg)
![SFML](https://img.shields.io/badge/SFML-2.5-green.svg)
![License](https://img.shields.io/badge/License-MIT-yellow.svg)
![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux%20%7C%20macOS-lightgrey.svg)

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


## 🛠️ Công nghệ sử dụng

- **Ngôn ngữ**: C++17
- **Thư viện đồ họa**: SFML 2.5 (Simple and Fast Multimedia Library)
- **Compiler**: MinGW/GCC (Windows) hoặc GCC/Clang (Linux/macOS)
- **IDE**: Code::Blocks (có thể dùng Visual Studio, CLion, etc.)


## 🚀 Cách cài đặt và chạy

### **Yêu cầu hệ thống**
- SFML 2.5 hoặc cao hơn
- Compiler C++ hỗ trợ C++17
- Hệ điều hành: Windows, Linux, hoặc macOS

### **Cài đặt trên Windows (Code::Blocks)**
1. Tải và cài đặt [Code::Blocks](http://www.codeblocks.org/)
2. Tải [SFML](https://www.sfml-dev.org/download.php) cho MinGW
3. Tạo project mới trong Code::Blocks
4. Thêm file `main.cpp` vào project
5. Cấu hình linker với các thư viện SFML:
   - `sfml-graphics`
   - `sfml-window`
   - `sfml-system`
6. Build và chạy chương trình

## *Tùy chỉnh tham số*
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

🤖 Grok AI (xAI) – đã giúp mình viết nền tảng code ban đầu
🚀 DeepSeek AI – đã kiên nhẫn sửa lỗi và tối ưu!

Dự án này là kết quả của sự hợp tác vui vẻ giữa con người và hai trợ lý AI tuyệt vời. ❤️

Enjoy the beauty of 3D particles! ✨
[Demo]

[Trở về trang chủ](https://github.com/roboeinlife-glitch)
