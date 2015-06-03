import threading
import time
import os
def update():
	while(1):
		print "I'm thread"
		time.sleep(1)
thread1 = threading.Thread(target = update)
#thread1.setDaemon(True)
thread1.start()
while(1):
	print "I'm Father"
	time.sleep(1)
	exit(thread1)
	