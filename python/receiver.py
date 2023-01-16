import cv2, socket, pickle

s=socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
ip="192.168.1.108"
port=8080
s.bind((ip,port))

while True:
    x=s.recvfrom(1000000)
    clientip = x[1][0]
    data=x[0]
    data=pickle.loads(data)
    data = cv2.imdecode(data, cv2.IMREAD_COLOR)
    cv2.imshow('received image', data)
    if cv2.waitKey(10) == 27:
        break
    
cv2.destroyAllWindows()