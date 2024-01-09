from life import *
import math

tile_map = create_map(100, 100, 0)

# euler's number
euler = 2.71828

def find_point_from (origin, angle, distance):
	# angle is given in degrees
	angle_rads = math.radians(angle)

	x = origin[0] + (distance * math.cos(angle_rads))
	y = origin[1] + (distance * math.sin(angle_rads))

	return (x,y)
	
def find_max (tile_map):
	# find max x y
	#x_min = 0
	#y_min = 0
	
	x_max = len(tile_map[0])+1
	y_max = len(tile_map)+1
	
	maxes = (x_max, y_max)
	
	return (maxes)
	
def out_of_bounds(point, tile_map):
	# returns TRUE if point out of bounds
	bflag = False
	x = point[0]
	y = point[1]
	x_max = find_max(tile_map)[0]
	y_max = find_max(tile_map)[1]
	
	if x > x_max or x < 0:
		bflag = True
		
	if y > y_max or y < 0:
		bflag = True
	
	return bflag
	

def draw_log_spiral (a, b, origin, step_size, turns, tile_map):
	# origin is a tile grid coordinate
	# step_size tells how much to advance angle between line segments (resolution)
	# turns is the angle to draw to (in degrees)
	new_map = tile_map

	if turns == 0:
		turns = 360

	points = []

	angle = 0
	while angle <= (turns+step_size):
		# find distance from the origin for that angle
		r = (a * euler) ** (b * math.radians(angle))

		next_point = find_point_from(origin, angle, r)

		if not out_of_bounds(next_point, new_map):
			points.append(next_point)

		angle += step_size

	step = 0
	while (step < (len(points) - 2) and len(points) != 0):
		new_map = draw_tile_line(points[step], points[step+1], new_map)
		step += 1
	
	return new_map

def draw_tile_line(origin, dest, tile_map):
	# returns a tile map with a line drawn from origin to dest
	new_map = tile_map
	x1 = origin[0]
	x2 = dest[0]
	y1 = origin[1]
	y2 = dest[1]
	
	# trip if line is vertical
	vflag = False
	
	x_max = find_max(new_map)[0]
	y_max = find_max(new_map)[1]
	
	x_min = 0
	y_min = 0
	
	if x1 > x_max: x1 = x_max
	if x2 > x_max: x2 = x_max
	if y1 > y_max: y1 = y_max
	if y2 > y_max: y2 = y_max
	
	if x1 < x_min: x1 = x_min
	if x2 < x_min: x2 = x_min
	if y1 < y_min: y1 = y_min
	if y1 < y_min: y2 = y_min
	
	difx = abs(x2-x1)
	dify = abs(y2-y1)
	
	if difx == 0:
		vflag = True
	
	if not vflag: m = (y2-y1)/(x2-x1)
	if not vflag: b = y1 - (m*x1)
	
	if (difx >= dify) and not vflag:
		if x2 >= x1:
			scan = x2
			while scan >= x1:
				x = round(scan)
				y = round(m*x+b)
				try:
					new_map[y][x] = 1
				except:
					print(x,y)
					break
				scan -= 1
		elif x1 > x2:
			scan = x1
			while scan >= x2:
				x = round(scan)
				y = round(m*x+b)
				new_map[y][x] = 1
				scan -= 1
	elif (dify > difx) and not vflag:
		if y2 >= y1:
			scan = y2
			while scan >= y1:
				y = round(scan)
				x = round((y-b)/m)
				new_map[y][x] = 1
				scan -= 1
		elif y1 > y2:
			scan = y1
			while scan >= y2:
				y = round(scan)
				x = round((y-b)/m)
				new_map[y][x] = 1
				scan -= 1
	else:
		# this is a vertical line
		if y2 >= y1:
			scan = y2
			while (scan > y1):
				y = round(scan)
				x = x2
				new_map[y][x] = 1
				scan -= 1
		elif y1 > y2:
			scan = y1
			while (scan > y2):	
				y = round (scan)
				x = x2
				new_map[y][x] = 1
				scan -= 1
		
	return new_map

point1 = (4,4)
point2 = (4,50)

#new_map = draw_tile_line(point2, point1, tile_map)
new_map = draw_log_spiral(1, 1, (50,50), 1, 800, tile_map)

print_map(new_map)
