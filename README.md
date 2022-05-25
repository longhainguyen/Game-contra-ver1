# Game-contra-ver1
1.Hướng dẫn cài đặt:          Link cài SDL2: https://drive.google.com/drive/folders/1WiRBNDPVlJo5_i2HkKZbYTty2MMeEC7B?usp=sharing    vào Code::blocks

  - Các bạn fork vào tài khoản của mình.
  - Ấn vào chỗ code rồi copy link .
  - clone the forked với command : git clone 
  - Rồi paste đường link vừa copy vào rồi Enter.
  - Sau đó các bạn mở code block lên, ấn ctrl + o ,rồi chọn file vừa tải về để mở lên.
  - Link Video hướng dẫn chi tiết : https://www.youtube.com/watch?v=de1HS21AoQk

2.Mô tả chung về trò chơi, các ý tưởng chính
  - Mô tả chung:
    + Dựa trên các game contra đã trở nên rất quen thuộc, chúng ta xây dựng nên một nhân vật đi săn quái vật và thu thập lượng tiền trên đường đi.
    + Các đối tượng chính: nhân vật Hero, các creep, hiểm họa mây, Boss.
  - Các ý tưởng chính:
    + Người chơi hóa thân vào nhân vật game để tiêu diệt quái vật.
    + Đặc biệt các đối tượng địch, hero, các đường đạn bắn được sử lý đúng như các hiện tượng vật lý thực tế, nếu chỉnh tốc của đan nhỏ đi bạn hoàn toàn có thể chạy     vượt qua đạn.  


3.Mô tả các chức năng đã cài đặt: link youtube: https://www.youtube.com/watch?v=j2QxxhPIy64
  - Sử dụng thư viện SDL2, SDL_image, SDL_mixer, sdl_ttf.
  - Người chơi sử dụng các phím up, right, left để điều khiển người chơi và sử dụng chuột trái để bắn đạn, ngoài ra còn có thể ấn phím 9 đến bật tắt nhạc,phím 0 tắt      hẳn nhạc.
  - Các kẻ địch bắn đạn gây sát thương cho nhân vật. Đặc biệt là những đám mây có thể di chuyển tìm và bắn chính xác vị trí ta đang đứng.
  - Người chơi ăn các item (như máu, tiền) để có thể tăng thêm mạng.
  - Sau khi tiêu diệt xong boss và ăn hết tiền chúng ta sẽ win. Ngược lại ta bị hết thời gian hoăc chết hết mạng chúng ta sẽ thua.


4.Các kỹ thuật lập trình được sử dụng trong chương trình
  - Sử dụng kĩ thuật Tile Map, Vector, đọc file, class, struct.
  - Các lớp sử dụng chung: 
      + unit : dùng để lữu trư các hằng số, các hàm cơ bản check va chạm, ramdom, menu.
      + LoadTexture : dùng để load image.
  - Các lớp kế thừa lớp chung:
      + chacracter : tạo ra nhân vật chính.
      + Enemy : tạo ra kẻ định.
      + VuNoObject : tạo ra hiệu ứng nổ.
      + Danban : tạo ra đan hỗ trợ cho Enemy và character.
  - Các lớp riêng:
      + Ltime : quản lý thời gian load ảnh.
      + TextObject : load phông chữ.
      + map : load map.


5. Kết luận, hướng phát triển 
  - Kết luận: Đây là một game khá phức tạp khi phải kiểm soát các đối tượng khi map di chuyển.
  - Phương án phát triển: 
       + Tạo ra các loại súng hỗ trợ nhờ nhặt được các item trên map. Súng đó giới hạn số đạn bắn, và có thể bắn nổ các hộp gỗ.
       + Mở rộng bản đồ lên phía trên.
       + Tạo ra vị trí khi nhân vật sống lại.
  - Điều rút ra khi thực hiện chương trình:
       + Cần học hỏi rất nhiều từ các game khác như Flappy Bird, Mario để có thể tổ chức code hợp lý, các kĩ thuật sử lý của game.
       + Nâng cao khả năng debug.
       + Cần học thêm các thuật toán.
  - Điều tâm đắc nhất:
       Sử lý đạn bắn tuân theo đúng thực tế.
