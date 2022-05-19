# INT2215 Project: CHASE #
# Thông tin chung #
  - Sản phẩm: Bài tập lớn cuối kì môn Lập trình nâng cao.
  - Sinh viên: Nguyễn Trần Gia Bảo - 21020751.
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

  
