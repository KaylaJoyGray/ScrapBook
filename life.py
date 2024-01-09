import pygame
import random

import os
import time

# John Conway's game of life
#
# Rules:
# Any live cell with fewer than two live neighbours dies, as if by underpopulation.
# Any live cell with two or three live neighbours lives on to the next generation.
# Any live cell with more than three live neighbours dies, as if by overpopulation.
# Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.

def clear_console():
	os.system("clear")
	return 0

def create_map(width, height, seed):
	# generates a randomly populated game map,
	# unless seed is zero (creates blank map)
	if seed != 0:
		random.seed(seed)
	
	tile_map = []
	
	row = []
	for h in range(0, height):
		for w in range(0, width):
			if seed != 0:
				chance = random.randint(0,2)
				if chance == 2:	
					row.append(1)
				else:
					row.append(0)
			else:
				row.append(0)
		tile_map.append(row)
		row = []

	return tile_map

def find_neighbors(x, y, tile_map):
	# find number of all 8 neighbors (left, right, up, down, diagonal) for given cell
	neighbors = []

	#upper
	if y != 0:
		neighbors.append(tile_map[y-1][x])
		if x != 0:
			#upper left
			neighbors.append(tile_map[y-1][x-1])
		if x < (len(tile_map)-1):
			#upper right
			neighbors.append(tile_map[y-1][x+1])
	#lower
	if y < (len(tile_map)-1):
		neighbors.append(tile_map[y+1][x])
		if  x != 0:
			#lower left
			neighbors.append(tile_map[y+1][x-1])
		if x < (len(tile_map)-1):
			#lower right
			neighbors.append(tile_map[y+1][x+1])

	#left
	if x != 0:
		neighbors.append(tile_map[y][x-1])
	#right
	if x < (len(tile_map)-1):
		neighbors.append(tile_map[y][x+1])

	count = 0
	for c in neighbors:
		count += c

	return count


def insert_at_map(value, x, y, tile_map):
	# inserts a value at the selected point on the map
	try:
		new_map = tile_map
		new_map[y][x] = value
		return new_map
	except:
		print("Cannot insert_at_map: coordinates out of bounds!")
		return 1

def print_map(tile_map):
	for row in tile_map:
		for cell in row:
			if cell == 1:
				print(chr(0x2588), end = '')
				print(chr(0x2588), end = '')
			else:
				print(chr(0x2591), end = '')
				print(chr(0x2591), end = '')
		print("")


def run_life():
	random.seed()
	seed = random.randint(0,999)

	# interesting seeds:
	# 997
	# 641
	life_map = create_map(40, 40, 641)
	
	running = 400
	while running:
		clear_console()
		print_map(life_map)
		time.sleep(0.2)

		x = 0
		y = 0
		next_frame = create_map(40, 40, 0)

		for row in life_map:
			for cell in row:
				n = find_neighbors(x, y, life_map)

				if cell == 1:
					if n < 2:
						next_frame = insert_at_map(0, x, y, next_frame)
					if n == 2:
						next_frame = insert_at_map(1, x, y, next_frame)
					if n == 3:
						next_frame = insert_at_map(1, x, y, next_frame)
					if n > 3:
						next_frame = insert_at_map(0, x, y, next_frame)

				if cell == 0:
					if n == 3:
						next_frame = insert_at_map(1, x, y, next_frame)

				if x < (len(row)-1):
					x += 1
				else:
					x = 0
			if y < (len(life_map)-1):
				y += 1

		life_map = next_frame
		running -= 1

	print("The seed was "+str(seed))
	
if __name__ == "__main__":
	run_life()
	
