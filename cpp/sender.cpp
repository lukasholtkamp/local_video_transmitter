#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include <vector>
#include <iostream>
#include <opencv2/opencv.hpp>

int main() {
  int s;
  struct sockaddr_in serv_addr;
  cv::Mat img;
  std::vector<uchar> buf;
  cv::VideoCapture cap(0);

  s = socket(AF_INET, SOCK_DGRAM, 0);

  memset(&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = inet_addr("192.168.1.108");
  serv_addr.sin_port = htons(8080);

  while (true) {
    cap >> img;
    cv::imencode(".jpg", img, buf, {cv::IMWRITE_JPEG_QUALITY, 30});
    sendto(s, &buf[0], buf.size(), 0, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
  }

  close(s);
  cap.release();
  return 0;
}