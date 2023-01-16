#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include <vector>
#include <iostream>
#include <opencv2/opencv.hpp>

int main() {
  int s;
  char buf[100000];
  struct sockaddr_in serv_addr, cli_addr;
  socklen_t clilen;
  cv::Mat img;

  s = socket(AF_INET, SOCK_DGRAM, 0);

  memset(&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(8080);

  bind(s, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

  while (true) {
    recvfrom(s, buf, sizeof(buf), 0, (struct sockaddr *)&cli_addr, &clilen);
    std::vector<uchar> data(buf, buf + sizeof(buf));
    img = cv::imdecode(data, cv::IMREAD_COLOR);
    cv::imshow("received image", img);
    if (cv::waitKey(10) == 27) {
      break;
    }
  }

  close(s);
  cv::destroyAllWindows();
  return 0;
}