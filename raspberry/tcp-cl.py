import socket
import sys

# СоздаемTCP/IP сокет
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Подключаем сокет к порту, через который прослушивается сервер
server_address = ('localhost', 10000)
print('Подключено к {} порт {}'.format(*server_address))
sock.connect(server_address)
try:
    while 1:
        try:
            # Отправка данных
            mess = input()
            print(f'Отправка: {mess}')
            message = mess.encode()
            sock.sendall(message)
        except:
            print("Error")

finally:
    print('Закрываем сокет')
    sock.close()