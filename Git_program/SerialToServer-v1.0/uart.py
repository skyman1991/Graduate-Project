import serial
import os
import sys,	getopt
import urllib2 

def read_until(until):
	buf = ""
	done = False
	while not done:
		n = uart.read(1)
		if n == '':
        # FIXME: Maybe worth blocking instead of busy-looping?
			time.sleep(0.01)
			continue
		buf = buf + n
		if n == until:
			done = True
	return buf
def Get_data(data):
	#params = urllib2.urlencode({'data': data})
	response  = urllib2.urlopen("http://123.57.11.98:8080/mm/set_new?data" + data)
if __name__	== "__main__":
	serialPort = "COM1"
	bufdata=[]
	a=0;
	getdata=""
	b=0;
	try:
		opts, args = getopt.getopt(sys.argv[1:], "p:")
	except getopt.GetoptError, err:
		# print	help information and exit:
		print str(err) # will print	something like "option -a not recognized"
		sys.exit(2)
	for	option,value in	opts:
		if option == '-p':
			serialPort = str(value)
			uart = serial.Serial(serialPort,115200)  
			print "SerialPort: "+serialPort+" is open,boardrate=115200"
			while True:
				data = uart.read(8);
				for i in data:
					hexdata = ord(i)
					bufdata.append(str(hexdata))
					a+=1
					if(a%2==1):
						bufdata.append("|")
					else:
						bufdata.append(",")
					# file.write(str(hexdata))
					# print hexdata
				for i in range(len(bufdata)-1):
					getdata += str(bufdata[i])
				print getdata+"\n"
				b=b+1
				print b
				Get_data(getdata)
				bufdata=[]
				getdata=""
				

	

 

