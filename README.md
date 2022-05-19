# INT2215 Project: CHASE #
# Thông tin chung #
  - Sản phẩm: Bài tập lớn cuối kì môn Lập trình nâng cao.
  - Sinh viên: Nguyễn Trần Gia Bảo - 21020751.
# Cài đặt #
  - Tải và giải nén [Chase](https://drive.google.com/file/d/1ZHJw16yve_QTpMsUJAVi1zcBFzRKaKcU/view?usp=sharing).
  - Chạy file Chase.exe để bắt đầu.
  - Mời thêm một vài người bạn đề cùng chơi.
  - Enjoy!
# Mô tả sản phẩm #
## Luật chơi ##
  - Những người chơi (Tối đa 4 người) sẽ điều khiển phi thuyền của mình tránh khỏi sự truy đuổi của tên lửa.
  - Tên lửa sẽ đuổi theo phi thuyền của người chơi đang cầm máy theo dõi.
  - Người chơi có thể thể tạm thời tránh khỏi sự truy đuổi của tên lửa bằng cách gắn máy theo dõi sang phi thuyền của người chơi khác.
  - Phi thuyền sẽ phát nổ nếu đâm phải tên lửa, khi đó người chơi mất đi 1 mạng (Tối đa 3 mạng).
  - Người cuối cùng sống sót sẽ là người chiến thắng.
## Phi thuyền ![Spaceship](https://github.com/onlyzabao/Project-Chase/blob/main/asset/png/playground/spaceship_1.png "Phi thuyền 1") ![Spaceship](https://github.com/onlyzabao/Project-Chase/blob/main/asset/png/playground/spaceship_2.png "Phi thuyền 2") ![Spaceship](https://github.com/onlyzabao/Project-Chase/blob/main/asset/png/playground/spaceship_3.png "Phi thuyền 3") ![Spaceship](https://github.com/onlyzabao/Project-Chase/blob/main/asset/png/playground/spaceship_4.png "Phi thuyền 4")
  - Số phi phi thuyền tương ứng với số lượng người chơi.
  - Điều khiển:
  
  Key         | Player 1 | Player 2 | Player 3 | Player 4
------------- | -------- | -------- | -------- | --------
  UP          | W        | &#8593;  | Y        | P
  DOWN        | S        | &#8595;  | H        | ;
  LEFT        | A        | &#8592;  | G        | L
  RIGHT       | D        | &#8594;  | J        | '
  
  - Truyền máy theo dõi: (Kết hợp với phím điều khiển để định hướng)
  
  Key         | Player 1 | Player 2 | Player 3 | Player 4
------------- | -------- | -------- | -------- | --------
  SHOOT       | R        | /        | I        | ]
  
## Tên lửa ![Rocket](https://github.com/onlyzabao/Project-Chase/blob/main/asset/rocket.png "Trạng thái truy đuổi") ![Sign](https://github.com/onlyzabao/Project-Chase/blob/main/asset/sign.png "Trạng thái cảnh bảo")
  - Nếu sau một khoảng thời gian truy đuổi và vẫn không bắn hạ được mục tiêu, tên lửa được được tăng thêm gia tốc.
  - Nếu tên lửa nằm ngoài vùng nhìn thấy, người chơi sẽ được phát tín hiệu cảnh báo.
## Máy theo dõi ![Tracker](https://github.com/onlyzabao/Project-Chase/blob/main/asset/png/playground/tracker.png "Máy theo dõi")
  - Máy treo dõi cần được gắn trúng phi thuyền để phát huy tác dụng.
  - Màu sắc của không gian sẽ thay đổi tương ứng với màu sắc của phi thuyền đang bị theo dõi.
# Video gameplay #
  - [CHASE - Gameplay]()
# Kỹ thuật lập trình #
## C++ ##
  - Lập trình cơ bản:
    - Cấu trúc dữ liệu: Mảng, Vector.
    - Làm việc với con trỏ: Con trỏ hằng, hằng con trỏ, cấp phát và giải phóng bộ nhớ động.
    - Sử dụng `enum` để chương trình tường minh hơn.
    - Sử dụng hằng `constexpr` để cải thiện hiệu suất.
    - Sử dụng biến `static` cho một số mục đích đặc biệt.
    - Đóng gói dữ liệu với `struct`.
    - Làm việc với thời gian hệ thống.
    - Sinh ngẫu nhiêu.
  - Lập trình hướng đối tượng:
    - Đống gói và kế thừa đối tượng với `class`.
## SDL2 ##
  - Khởi tạo SDL subsystem.
  - Load, manipulate và render texture.
  - Xử lý keyboard và mouse event.
  - Dựng hiệu ứng animation đơn giản.
  - Trình phát âm thanh, nhạc nền.
## Khác ##
  - Vận dụng kiến thức vật lý, toán hoặc để xử lý quá trình di chuyển và va chạm của các đối tượng.
# Kết luận #
  - Sau khi hoàn thành sản phẩm đầu tay của bản thân, em hiểu rõ hơn về những vấn đề sau khi lập trình:
    - __OOP:__ Khi bắt tay vào làm game, cá nhân em cảm thấy phong cách lập trình OOP giúp mình dễ dàng hình dung và cài đặt chương trình hơn so với phong cách lập trình POP mà em thường sử dụng khi giải quyết một số bài toán nhỏ.
    - __Concept & Design (in CDIO):__ Sau rất nhiều lần code rồi lại xóa đi viết lại, việc vẽ một sơ đồ mô tả hệ thống chương trình và cách các đối tượng tương tác với nhau khiến hiệu suất làm việc của em được cải thiện rất nhiều.
    - __Clean code:__ Tìm hiểu thêm về một số "luật bất thành văn" khi viết code giúp em bảo dưỡng mã nguồn tốt hơn.
 - Đối với định hướng phát triển sản phẩm CHASE của bản thân:
    - Xuất phát điểm là một tựa game Local multiplayer, em muốn bổ sung thêm cho CHASE tính năng LAN multiplayer và Online multiplayer.
    - Bổ sung một số item: Hồi máu, tạo khiên, tạo hố đen giữ chân người chơi khác, ...
    - Cải thiện đồ họa, thêm tính năng tùy chỉnh phi thuyền của người chơi.
    
  
