import socket
import time

# file     Game Networking Server Script
# author   Tifanie Ngo
# date     4/23/2025
# brief This script behaves as a TCP server to receive the latest position 
#       updates from the duck (player) in Yo-Ho Jump. The client (game) sends 
#       the player's position, and the server logs and prints updates periodically 
#       (every 10 seconds).

HOST = '127.0.0.1'  # Localhost; game and server run on the same machine
PORT = 54000        # Port to listen on

# A TCP socket using IPv4
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Bind socket to host and port to listen for incoming connections
server_socket.bind((HOST, PORT))

# Start listening for incoming client connections
server_socket.listen()

print(f"Server listening on {HOST}:{PORT}")

# Accept incoming connections from the game client (player)
while True:
    client_socket, addr = server_socket.accept()
    print(f"Connected by {addr}")
    
    last_position = ""           # Store the most recent position received
    last_sent_time = time.time() # Track the time the last message was printed
    first_printed = False        # Flag to print the initial position received only once

    try:
        while True:
            # Receive coordinate data sent from the game client
            data = client_socket.recv(1024).decode('utf-8')
            if not data:
                break  # Exit the loop if the client disconnects or sends nothing

            last_position = data  # Update the most recent position

            if not first_printed:
                # Immediately prints first received position
                print(f"Initial position received: {last_position}")
                first_printed = True

            current_time = time.time()
            # Print the most recent position every 10 seconds (throttled logging)
            if current_time - last_sent_time >= 10:
                print(f"Sending position after 10 seconds: {last_position}")
                last_sent_time = current_time

    except Exception as e:
        # Handle any connection or data-related errors
        print(f"Error: {e}")
    finally:
        # Close the client socket after usage
        client_socket.close()
