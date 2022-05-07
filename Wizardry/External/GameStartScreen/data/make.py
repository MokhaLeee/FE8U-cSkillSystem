import os, sys, glob, codecs, shutil
import numpy as np
import struct


 # 生成了一个正常的顺序排列的图片TSA
def fun1():
	with open("GameIntro_BG1.tsa", 'wb') as fp:
		fp.write(struct.pack('B', 0x1D))
		fp.write(struct.pack('B', 0x13))
		
		for j in range(4):
			for i in range(0x1E):
				fp.write(struct.pack('B', 0x60 - 0x20 * j + i))
				fp.write(struct.pack('B', 0x2))
		
		for j in range(8):
			for i in range(0x1E):
				fp.write(struct.pack('B', 0xE0 - 0x20 * j + i))
				fp.write(struct.pack('B', 0x1))
		
		for j in range(8):
			for i in range(0x1E):
				fp.write(struct.pack('B', 0xE0 - 0x20 * j + i))
				fp.write(struct.pack('B', 0x0))

def main():
	fun1()

if __name__ == '__main__':
    main()	