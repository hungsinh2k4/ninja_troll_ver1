# **_Game_Troll_**

## **Giới thiệu**

- Họ và tên: Nguyễn Sinh Hùng - K67-CB-UET-VNU

- Mã sinh viên: 22021184

- Bài tập lớn: **Ninja_troll**

## **Mô tả dự án**

### _Mô tả game_

- Ý Tưởng Có thể xây dựng được Game : Trong quá trình nghĩ và lên ý tưởng thì nó là 1 con game chiến binh ninja đi tiêu diệt các con quái . e đã nảy ra 1 ý tưởng là sẽ xây dựng con map sẽ rất nhiều những
  ngoại vật mà người sẽ dính bẫy, sẽ cho con game ban đầu chỉ có đi đánh quái thì giờ nó đã trờ thành 1 con game phải tìm ra những con đường hợp lí mà người chơi sẽ không bị chết .
- Game sử dụng kĩ thuật đọc map từ file txt gồm những con số 1 - ... để xây dựng lên map;

### _Hướng dẫn chơi game_

- chúng ta sẽ di chuyển bằng nút sang trái ,phải , space để nhảy, "S" để ném phi tiêu nếu có đạn
- chúng ta có những block " ? " sẽ có nhưng cái bị troll và những cái được đạn
- số đạn thì sẽ không hiện thị trên màn hình để người chơi phải đếm và tính toán sao cho đủ để tiêu diệt quái , nếu không đủ sẽ mãi không qua được vị tris tiếp theo
- game sau khi người chơi bị chết sẽ lập tức trở lại vị trí ban đầu và không có checkponit (do khi chết map vẫn giữ nguyên và không render lại)
- làm như vậy game sẽ dễ chơi hơn và có thể chiến thắng được game
- Game có rất nhiều các block hay

* Block ẩn người chơi không thể nhìn thấy nhưng vẫn thể va chạm để ở trên đó kĩ năng nhớ vị trí và tưởng tượng
  ....

### _Preview_

## **Hướng dẫn cài đặt game**

### **_Đối tượng_** : **Có nhu cầu tham khảo, sử dụng source code để phát triển thêm**

\*\*\* VSCODE
-Yêu cầu:

    1.Cài đặt VSCODE

    2.Cài các tiện ích trên VSCODE để có cảm hứng cũng như gợi ý để code

-Cài đặt:

    1. Tải project về máy tính dưới dạng file zip hoặc dùng câu lệch sau :
    ...
        git clone  https://github.com/hungsinh2k4/ninja_troll_ver1.git
    ...

    2. mở folder trong VSCODE

    3. Chạy game trên terminal hoặc cmd, gõ mingw32-make nếu bản MINGW 2013, còn không được thì sẽ sao chép :
    g++ -Isrc/Include -Lsrc/lib -o main Commonfunc.cpp BaseObject.cpp Map.cpp  PlayerObject.cpp FPSTimer.cpp Bullet.cpp ThreatsObject.cpp Audio.cpp Game.cpp main.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
    dán vào là chạy được

\*\*\* CodeBlocks

- Yêu cầu:

  1. Cài đặt CodeBlocks.

  2. Tải các thư viện hỗ trợ SDL: SDL2, SDL2_mixer, SDL2_image, SDL2_ttf.

  3. Hướng dẫn cài đặt thư viện SDL2 vào CodeBlocks: https://youtu.be/dC77R3MYjcU?list=PL-IbDGFpCvtluDVQSSslFYzFueSbjDvZO , làm tương tự đối với các thư viện còn lại.

- Cài đặt:

  1. Tải project về máy dưới dạng file ZIP hoặc dùng câu lệnh sau:

  ```
      git clone https://github.com/hungsinh2k4/ninja_troll_ver1.git
  ```

  2. Add headers: Mở project bằng CodeBlocks, vào _Settings_ -> _Complier_ -> _Search directories_ -> _Complier_ -> _Add_ -> lấy đường dẫn file _headers_ trong folder project -> _OK_ -> _OK_.

- Chạy chương trình: Click vào icon _Build and run_ để chạy game.

### _Các kỹ thuật sử dụng trong game_

- Thư viện SDL2.0

- Kĩ thuật tách file.

- Sử dụng và quản lí mảng, xử lí đồ họa.

- Tạo, sử dụng và quản lí class nhiều đối tượng: hình ảnh, âm thanh,...

- Xử lí hình ảnh , sự kiện SDL, di chuyển đối tượng, xử lí va chạm, tính toán tọa độ,....

### _Các nguồn tham khảo_

- Cách sử dụng, cài đặt SDL2, quản lí chương trình, tách file: https://www.youtube.com/channel/UC5BjUr9a3lHAe4a8Y8uuqLw

- Hình ảnh: itch.io - tất cả animations đều tự design.

- Âm thanh: Google

## **Tổng kết**

### _Điều tâm đắc_

- Để làm ra Project em đã đi tham khảo rất nhiều tài liệu và chắt lọc những điều hay

- Cải thiện nhiều kĩ năng lập trình, sử dụng và quản lí file, chương trình.

- Học được cách design hình ảnh, sử dụng photoshop, edit âm thanh,..

### _Điểm hạn chế_

- Quản lí đối tượng chưa thật sự tối ưu.
- Chưa được mượt mà
- cần bổ sung thì sẽ có thể đăng game chơi online

### _Hướng phát triển tiếp theo_

- Phát triển thêm simple AI cho mấy con quái khác ví dụ như dí người chơi, đạn đuổi theo người

- Phát triển nhiều chế độ chơi từ dễ đến khó, tăng dần tốc độ, thêm threats,...

- Cải thiện chất lượng hình ảnh trong game.

### _Mức điểm tự đánh giá_ : 8.5 \*\* 9 / 9.5
