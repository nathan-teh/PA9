import socket
import time

# Game Networking Server Script
# -----------------------------
# This script is designed to act as a simple TCP server to receive
# position updates from the duck player in the SFML-based jump game.
# The client (game) sends the player's position, and the server logs
# and prints updates periodically.

HOST = '127.0.0.1'  # Localhost; game and server run on the same machine
PORT = 54000        # Port to listen on; must match the port used by the game client

# Create a TCP socket using IPv4
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Bind the socket to the host and port so it can listen for incoming connections
server_socket.bind((HOST, PORT))

# Start listening for incoming client connections
server_socket.listen()

print(f"Server listening on {HOST}:{PORT}")

# Accept incoming connections from the game client (player)
while True:
    client_socket, addr = server_socket.accept()
    print(f"Connected by {addr}")
    
    last_position = ""           # Store the most recent position string received
    last_sent_time = time.time() # Track the time the last message was printed
    first_printed = False        # Flag to print the first position received only once

    try:
        while True:
            # Receive data sent from the game client (e.g., "x:100 y:200")
            data = client_socket.recv(1024).decode('utf-8')
            if not data:
                break  # Exit the loop if the client disconnects or sends nothing

            last_position = data  # Update the latest known position

            if not first_printed:
                # Print the first received position immediately
                print(f"Initial position received: {last_position}")
                first_printed = True

            current_time = time.time()
            # Every 10 seconds, print the last received position (throttled logging)
            if current_time - last_sent_time >= 10:
                print(f"Sending position after 10 seconds: {last_position}")
                last_sent_time = current_time

    except Exception as e:
        # Handle any connection or data-related errors gracefully
        print(f"Error: {e}")
    finally:
        # Always close the client socket after done with it
        client_socket.close()
