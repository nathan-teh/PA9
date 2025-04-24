import socket
import time

HOST = '127.0.0.1'
PORT = 54000

server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.bind((HOST, PORT))
server_socket.listen()

print(f"Server listening on {HOST}:{PORT}")

while True:
    client_socket, addr = server_socket.accept()
    print(f"Connected by {addr}")
    
    last_position = ""
    last_sent_time = time.time()
    first_printed = False

    try:
        while True:
            data = client_socket.recv(1024).decode('utf-8')
            if not data:
                break

            last_position = data

            if not first_printed:
                print(f"Initial position received: {last_position}")
                first_printed = True

            current_time = time.time()
            if current_time - last_sent_time >= 10:
                print(f"Sending position after 10 seconds: {last_position}")
                last_sent_time = current_time

    except Exception as e:
        print(f"Error: {e}")
    finally:
        client_socket.close()