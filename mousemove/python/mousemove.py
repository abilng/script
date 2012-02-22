#!/usr/bin/env python2
#-*-python-2.7-
####################################################################################
#		Mouse---Move	
#-----------------------------------------------------------------------------------
# 
# 
#
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANT-ABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License along
# with this program; if not, write to the Free Software Foundation, Inc.,
# 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
#Or see <http://www.gnu.org/licenses/>.
#
#Authors: Abil N George
####################################################################################
import argparse
parser = argparse.ArgumentParser(description='',prog='')
parser.add_argument('x', type=int,help='xpostion')
parser.add_argument('y', type=int,help='ypostion')
parser.add_argument('-l','--click',help='for left click',dest='action',action='store_true',default=False)
parser.add_argument('-r','--rclick',help='for right click',dest='raction',action='store_true',default=False)

try:
	from Xlib import X
	from Xlib.display import Display
	from Xlib import X
	from Xlib.ext.xtest import fake_input
except ImportError:
		print ('Xlib is not found.Install Xlib\n')


class Mouse:
	def __init__(self):
		self.display = Display()

	def press(self, x, y, button = 1):
		"""simulate a mouse press"""
		self.move(x, y)
		fake_input(self.display, X.ButtonPress, button)
		self.display.sync()

	def release(self, x, y, button = 1):
		"""simulate release of pressed-mouse"""
		self.move(x, y)
		fake_input(self.display, X.ButtonRelease,button)
		self.display.sync()

	def move(self, x, y):
		"""move  mouse"""
		fake_input(self.display, X.MotionNotify, x=x, y=y)
		self.display.sync()

	def position(self):
		"""return curent postion"""
		coord = self.display.screen().root.query_pointer()._data
		return coord["root_x"], coord["root_y"]

	def screen_size(self):
		"""return screen size"""
		width = self.display.screen().width_in_pixels
		height = self.display.screen().height_in_pixels
		return width, height

	def click(self,x,y,clicktype="LEFT"):
		"""simulate a mouse left or right click"""
		if clicktype=="LEFT":
			self.press(x,y)
			self.release(x,y)
		elif clicktype=="RIGHT":
			self.press(x,y,3)
			self.release(x,y,3)
		else:
			print("Error:Unknown click type\n")
def main():
#parse processing
	args = parser.parse_args()
	x=args.x
	y=args.y
#prg
	m=Mouse()
	if(args.action):
		m.click(x,y)
	elif(args.raction):
		m.click(x,y,"RIGHT")
	else:
		m.move(x,y)
			

if __name__ == "__main__":
	main()

