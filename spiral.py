import pygame
import math

# This program draws a logarithmic spiral as a set of line segements
#
# The polar coordinates of a logarithmic spiral can be written as:
# r = ae pow (bO)
# 
# r = distance from origin, O is the angle from the x-axis (in radians)
# a and b are arbitrary constants

def angle_to_slope (angle):
	# converts angle to slope for linear formula
	# angle must be in radians

	return math.tan(angle)

# white color
white = (255, 255, 255)

# euler's number
euler = 2.71828

def find_point_from (origin, angle, distance):
	# angle is given in degrees
	angle_rads = math.radians(angle)

	x = origin[0] + (distance * math.cos(angle_rads))
	y = origin[1] + (distance * math.sin(angle_rads))

	return (x,y)

def draw_log_spiral (surface, a, b, origin, step_size, turns):
	# here is where the magic is

	# origin is a screen coordinate
	# step_size tells how much to advance angle between line segments (resolution)
	# turns is the angle to draw to (in degrees)

	if turns == 0:
		turns = 360

	points = []

	angle = 0
	while angle <= (turns+step_size):
		# find distance from the origin for that angle
		r = (a * euler) ** (b * math.radians(angle))

		next_point = find_point_from(origin, angle, r)

		points.append(next_point)

		angle += step_size

	step = 0
	while (step < (len(points) - 2)):
		pygame.draw.line(surface, white, points[step], points[step+1])
		step += 1

	return 0


def main():
	pygame.init()

	is_running = True

	while (is_running):
		print("Do you want to quit?")
		if input() == "yes":
			break

		print("What is A? ")
		A = float(input())
		print("What is B? ")
		B = float(input())
		print("what is the resolution? ")
		steps = float(input())
		print("what is the number of degrees to draw? ")
		degrees = float(input())

		pygame.display.set_caption("Logarithmic Spiral Program")
		screen = pygame.display.set_mode((500, 500))
		done = False
		while not done:
			for event in pygame.event.get():
				if event.type == pygame.QUIT:
					done = True
			
			draw_log_spiral(screen, A, B, (250,250), steps, degrees)

			pygame.display.flip()

		pygame.display.quit()

	pygame.quit()
	return 0

main()	
