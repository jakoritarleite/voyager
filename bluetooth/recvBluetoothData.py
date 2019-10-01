from bluetooth import *
import sys

try: 
	if sys.argv[1]: 
		address = str(sys.argv[1])

except IndexError:
	try: discover_devices()
	except OSError: 
		print("Connected an bluetooth dongo weido.")
		sys.exit()
	print("[+] Performing inquiry...")
	nearby = discover_devices(lookup_names = True)
	print("[!] Found {} devices: ".format(len(nearby))) 

	for name, addr in nearby:
		print("{} . {}". format(addr, name))

	address = input(str(f"[>] Address to connect: "))

sock = BluetoothSocket( RFCOMM )
sock.connect((address, 1))
print("[!] Connected to: {}".format(address))

while True:
	try:
		data = sock.recv(2**10)
		print(data)

	except KeyboardInterrupt:
		sock.close()
		sys.exit()