import cv2, socket, pickle

s=socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
s.setsockopt(socket.SOL_SOCKET, socket.SO_SNDBUF, 10000000)
receiverip="192.168.1.108"
receiverport=8080

cap = cv2.VideoCapture(0)
while True:
    ret,photo = cap.read()
    ret, buffer = cv2.imencode(".jpg", photo,[int(cv2.IMWRITE_JPEG_QUALITY),30])    
    x_as_bytes = pickle.dumps(buffer)    
    s.sendto(x_as_bytes,(receiverip , receiverport))    
    if cv2.waitKey(10) == 27:        
        break

cv2.destroyAllWindows()
cap.release()