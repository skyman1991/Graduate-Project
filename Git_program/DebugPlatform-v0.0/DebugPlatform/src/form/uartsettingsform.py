# coding=utf-8
import Tkinter as tk
import ttk
from Tix import COLUMN
from distutils.cmd import Command
from mainform import *
class UartRoot(tk.Tk):
    """Container for all frames within the application"""
    
    def __init__(self, *args, **kwargs):
        tk.Tk.__init__(self, *args, **kwargs)

        self.title("串口配置")
        self.geometry('200x400')
        ttk.Label(self, text="串口号:", padding=5).grid(row=0)
        comnum = []
        self.comnumbox = ttk.Combobox(self, width=10)
#         comnum.append('com2')
        self.comnumbox['value'] = comnum
        self.comnumbox.grid(row=0, column=1)
        
        ttk.Label(self, text="波特率:", padding=5).grid(row=1)
        bordrate = ['9600','14400','19200','28800','38400','56000','57600','115200']
        self.bordratebox = ttk.Combobox(self, width=10)
        self.bordratebox['value']=bordrate
        self.bordratebox.set('115200')
        self.bordratebox.grid(row=1,column=1)
        
        ttk.Label(self, text="数据位:", padding=5).grid(row=2)
        ttk.Label(self, text="停止位:", padding=5).grid(row=3)
        
        ttk.Button(self,text='打开串口',command=self.OpenUart).grid(row=4,column=1)
        
    def OpenUart(self):
#         mainform.root.status.set("%s",'sdf')
        mainvalue = 7
 
        

if __name__ == '__main__':
    uartroot = UartRoot()
    uartroot.mainloop()
