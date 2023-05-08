import socket

# создаемTCP/IP сокет
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Привязываем сокет к порту
server_address = ('localhost', 10000)
print('Старт сервера на {} порт {}'.format(*server_address))
sock.bind(server_address)

# Слушаем входящие подключения
sock.listen(1)
try:
    print('Ожидание соединения...')
    connection, client_address = sock.accept()

    try:
        print('Подключено к:', client_address)
        # Принимаем данные порциями и ретранслируем их
        while True:
            data = connection.recv(16)
            if data:
                print('Обработка данных...')
                print(f'Получено: {data.decode()}')
            else:
                print('Нет данных от:', client_address)
                break
    except:
        connection.close()

finally:
    # Очищаем соединение
    connection.close()