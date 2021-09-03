from websocket import create_connection
ws = create_connection("ws://192.168.0.100:4242")
print("Sending 'Hello, World'...")
ws.send("Hello, World")
print("Sent")
ws.close()
