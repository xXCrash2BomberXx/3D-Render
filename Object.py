# from __future__ import print_function
import os
import math
import ctypes
try:
    from tkinter import Canvas, Tk
except ModuleNotFoundError:
    os.system('cmd /c "pip install tk"')
    from tkinter import Canvas, Tk


def hex(r, g, b):
    return ('#%02x%02x%02x' % (r, g, b))


class Obj():
    global screensize, canvas

    @staticmethod
    def prism(edges, *args, x=0, y=0, z=0, width=1, height=1, depth=1):
        newArr = []
        arr = [[x+(math.sin(vertex/edges*2*math.pi)+1)/2*width,
                y+(math.cos(vertex/edges*2*math.pi)+1)/2*height] for vertex in range(edges)]
        newArr.append([])
        newArr.append([])
        for i in range(len(arr)):
            newArr[0].append(arr[i]+[z])
            newArr[1].append(arr[i]+[z+depth])
        if len(args) > 0:
            newArr[0].append('fill')
            newArr[0].append(args[(0) % len(args)])
            newArr[1].append('fill')
            newArr[1].append(args[(1) % len(args)])
        for i in range(len(arr)):
            newArr.append([])
            newArr[i+2].append(arr[i]+[z])
            newArr[i+2].append(arr[i]+[z+depth])
            try:
                newArr[i+2].append(arr[i+1]+[z+depth])
                newArr[i+2].append(arr[i+1]+[z])
            except IndexError:
                newArr[i+2].append(arr[0]+[z+depth])
                newArr[i+2].append(arr[0]+[z])
            if len(args) > 0:
                newArr[i+2].append('fill')
                newArr[i+2].append(args[(i+2) % len(args)])
        return newArr

    @staticmethod
    def pyramid(edges, *args, x=0, y=0, z=0, width=1, height=1, depth=1):
        newArr = []
        arr = [[x+(math.sin(vertex/edges*2*math.pi)+1)/2*width, y +
                (math.cos(vertex/edges*2*math.pi)+1)/2*height] for vertex in range(edges)]
        newArr.append([])
        newArr.append([])
        for i in range(len(arr)):
            newArr[0].append(arr[i]+[z])
            newArr[1].append([(2*x+width)/2, (2*y+height)/2, z+depth])
        if len(args) > 0:
            newArr[0].append('fill')
            newArr[0].append(args[(0) % len(args)])
            newArr[1].append('fill')
            newArr[1].append(args[(1) % len(args)])
        for i in range(len(arr)):
            newArr.append([])
            newArr[i+2].append(arr[i]+[z])
            newArr[i+2].append([(2*x+width)/2, (2*y+height)/2, z+depth])
            try:
                newArr[i+2].append([(2*x+width)/2, (2*y+height)/2, z+depth])
                newArr[i+2].append(arr[i+1]+[z])
            except IndexError:
                newArr[i+2].append([(2*x+width)/2, (2*y+height)/2, z+depth])
                newArr[i+2].append(arr[0]+[z])
            if len(args) > 0:
                newArr[i+2].append('fill')
                newArr[i+2].append(args[(i+2) % len(args)])
        return newArr

    @staticmethod
    def rotatePoint(x, y, z, theta_x, theta_y, theta_z):
        return [x*math.cos(theta_z*math.pi/180)*math.cos(theta_y*math.pi/180) + y*math.cos(theta_z*math.pi/180)*math.sin(theta_y*math.pi/180)*math.sin(theta_x*math.pi/180) - y*math.sin(theta_z*math.pi/180)*math.cos(
                theta_x*math.pi/180) + z*math.cos(theta_z*math.pi/180)*math.sin(theta_y*math.pi/180)*math.cos(theta_x*math.pi/180) + z*math.sin(theta_z*math.pi/180)*math.sin(theta_x*math.pi/180),
                x*math.sin(theta_z*math.pi/180)*math.cos(theta_y*math.pi/180) + y*math.sin(theta_z*math.pi/180)*math.sin(theta_y*math.pi/180)*math.sin(theta_x*math.pi/180) + y*math.cos(theta_z*math.pi/180)*math.cos(
                theta_x*math.pi/180) + z*math.sin(theta_z*math.pi/180)*math.sin(theta_y*math.pi/180)*math.cos(theta_x*math.pi/180) - z*math.cos(theta_z*math.pi/180)*math.sin(theta_x*math.pi/180),
                -x*math.sin(theta_y*math.pi/180) + y*math.cos(theta_y*math.pi/180)*math.sin(
                theta_x*math.pi/180) + z*math.cos(theta_y*math.pi/180)*math.cos(theta_x*math.pi/180)]

    def __init__(self, *args, theta_x=0, theta_y=0, theta_z=0, x_axis=None, y_axis=None, z_axis=None, pyramid=False, wireframe=False, tag=None, augment=False, **kwargs):
        '''
        --Notification: Presets are drawn upside-down to account for (0, 0) being the top left corner.
            All shapes are automatically rotated with render--
        args: prebuilt shape name, side generator or custom shape build
        theta_*: angle offset along *-axis in degrees
        *_axis: rotation around the *-axis instead of the object's center
        tag: tag name for object creation
        pyramid:
            True: Creates a pyramid with a base of "args" sides
            False: Creates a prism with a base of "args" sides
        wireframe:
            True: removes fill and adds outlines
            False: Fills shape
        augment:
            --Warning: Use of values other than False may cause rendering issues--
            True: z-value taken relative to x-values and y-values
            *: z-value drawn at angle *
            False: z-value ignored
        kwargs: prebuilt shape settings (usually size and coordinates)
        '''
        self.isPyramid = pyramid
        args = list(args)
        self.augment = augment
        self.x_axis = x_axis
        self.y_axis = y_axis
        self.z_axis = z_axis
        self.wireframe = wireframe
        if 'cube' in args or 'cuboid' in args:
            if 'cube' in args:
                args.remove('cube')
            elif 'cuboid' in args:
                args.remove('cuboid')
            if tag is None:
                val = 0
                while True:
                    if 'cube_'+str(val) not in [canvas.itemcget(i, 'tags') for i in canvas.find_all()]:
                        self.tag = 'cube_'+str(val)
                        break
                    else:
                        val += 1
            else:
                self.tag = tag
            try:
                x = kwargs['x']
            except KeyError:
                x = 0
            try:
                y = kwargs['y']
            except KeyError:
                y = 0
            try:
                z = kwargs['z']
            except KeyError:
                z = 0
            width = kwargs['width']
            height = kwargs['height']
            depth = kwargs['depth']
            self.coords = [
                [  # Front
                    [x, y, z],
                    [x+width, y, z],
                    [x+width, y+height, z],
                    [x, y+height, z],
                    'fill', (hex(255, 0, 0) if len(args) == 0 else args[(0) % len(args)])  # Red
                ],
                [  # Left @ theta_y=270
                    [x, y, z],
                    [x, y, z+depth],
                    [x, y+height, z+depth],
                    [x, y+height, z],
                    'fill', (hex(0, 255, 0) if len(args) == 0 else args[(1) % len(args)])  # Green
                ],
                [  # Bottom @ theta_z = 270
                    [x, y+height, z],
                    [x, y+height, z+depth],
                    [x+width, y+height, z+depth],
                    [x+width, y+height, z],
                    'fill', (hex(0, 0, 255) if len(args) == 0 else args[(2) % len(args)])  # Blue
                ],
                [  # Right @ theta_y=90
                    [x+width, y+height, z],
                    [x+width, y+height, z+depth],
                    [x+width, y, z+depth],
                    [x+width, y, z],
                    'fill', (hex(255, 255, 0) if len(args) == 0 else args[(3) % len(args)])  # Yellow
                ],
                [  # Top @ theta_x=90
                    [x+width, y, z],
                    [x, y, z],
                    [x, y, z+depth],
                    [x+width, y, z+depth],
                    'fill', (hex(0, 255, 255) if len(args) == 0 else args[(4) % len(args)])  # Cyan
                ],
                [  # Back @ theta_y=180
                    [x+width, y, z+depth],
                    [x+width, y+height, z+depth],
                    [x, y+height, z+depth],
                    [x, y, z+depth],
                    'fill', (hex(255, 0, 255) if len(args) == 0 else args[(5) % len(args)])  # Purple
                ]
            ]
        elif 'tetrahedron' in args:
            args.remove('tetrahedron')
            if tag is None:
                val = 0
                while True:
                    if 'tetrahedron_'+str(val) not in [canvas.itemcget(i, 'tags') for i in canvas.find_all()]:
                        self.tag = 'tetrahedron_'+str(val)
                        break
                    else:
                        val += 1
            else:
                self.tag = tag
            try:
                x = kwargs['x']
            except KeyError:
                x = 0
            try:
                y = kwargs['y']
            except KeyError:
                y = 0
            try:
                z = kwargs['z']
            except KeyError:
                z = 0
            width = kwargs['width']
            height = kwargs['height']
            depth = kwargs['depth']
            self.coords = [
                [
                    [x+width, y+height, z+depth],
                    [x+width, y, z],
                    [x, y+height, z],
                    'fill', (hex(255, 0, 0) if len(args) == 0 else args[(0) % len(args)])  # Red
                ],
                [
                    [x+width, y+height, z+depth],
                    [x+width, y, z],
                    [x, y, z+depth],
                    'fill', (hex(0, 255, 0) if len(args) == 0 else args[(1) % len(args)])  # Green
                ],
                [
                    [x+width, y+height, z+depth],
                    [x, y+height, z],
                    [x, y, z+depth],
                    'fill', (hex(0, 0, 255) if len(args) == 0 else args[(2) % len(args)])  # Blue
                ],
                [
                    [x+width, y, z],
                    [x, y+height, z],
                    [x, y, z+depth],
                    'fill', (hex(255, 255, 0) if len(args) == 0 else args[(3) % len(args)])  # Yellow
                ]
            ]
        elif 'octahedron' in args:
            args.remove('octahedron')
            if tag is None:
                val = 0
                while True:
                    if 'octahedron_'+str(val) not in [canvas.itemcget(i, 'tags') for i in canvas.find_all()]:
                        self.tag = 'octahedron_'+str(val)
                        break
                    else:
                        val += 1
            else:
                self.tag = tag
            try:
                x = kwargs['x']
            except KeyError:
                x = 0
            try:
                y = kwargs['y']
            except KeyError:
                y = 0
            try:
                z = kwargs['z']
            except KeyError:
                z = 0
            width = kwargs['width']
            height = kwargs['height']
            depth = kwargs['depth']
            self.coords = [
                [
                    [x, y+height/2, z+depth/2],
                    [x+width/2, y, z+depth/2],
                    [x+width/2, y+height/2, z],
                    'fill', (hex(255, 0, 0) if len(args) == 0 else args[(0) % len(args)])  # Red
                ],
                [
                    [x, y+height/2, z+depth/2],
                    [x+width/2, y, z+depth/2],
                    [x+width/2, y+height/2, z+depth],
                    'fill', (hex(0, 255, 0) if len(args) == 0 else args[(1) % len(args)])  # Green
                ],
                [
                    [x+width, y+height/2, z+depth/2],
                    [x+width/2, y, z+depth/2],
                    [x+width/2, y+height/2, z],
                    'fill', (hex(0, 0, 255) if len(args) == 0 else args[(2) % len(args)])  # Blue
                ],
                [
                    [x+width, y+height/2, z+depth/2],
                    [x+width/2, y, z+depth/2],
                    [x+width/2, y+height/2, z+depth],
                    'fill', (hex(255, 255, 0) if len(args) == 0 else args[(3) % len(args)])  # Yellow
                ],
                [
                    [x, y+height/2, z+depth/2],
                    [x+width/2, y+height, z+depth/2],
                    [x+width/2, y+height/2, z],
                    'fill', (hex(0, 255, 255) if len(args) == 0 else args[(4) % len(args)])  # Cyan
                ],
                [
                    [x, y+height/2, z+depth/2],
                    [x+width/2, y+height, z+depth/2],
                    [x+width/2, y+height/2, z+depth],
                    'fill', (hex(255, 0, 255) if len(args) == 0 else args[(5) % len(args)])  # Purple
                ],
                [
                    [x+width, y+height/2, z+depth/2],
                    [x+width/2, y+height, z+depth/2],
                    [x+width/2, y+height/2, z],
                    'fill', (hex(0, 0, 0) if len(args) == 0 else args[(6) % len(args)])  # Black
                ],
                [
                    [x+width, y+height/2, z+depth/2],
                    [x+width/2, y+height, z+depth/2],
                    [x+width/2, y+height/2, z+depth],
                    'fill', (hex(127, 127, 127) if len(args) == 0 else args[(7) % len(args)])  # Gray
                ]
            ]
        elif 'dodecahedron' in args:
            args.remove('dodecahedron')
            if tag is None:
                val = 0
                while True:
                    if 'dodecahedron_'+str(val) not in [canvas.itemcget(i, 'tags') for i in canvas.find_all()]:
                        self.tag = 'dodecahedron_'+str(val)
                        break
                    else:
                        val += 1
            else:
                self.tag = tag
            try:
                x = kwargs['x']
            except KeyError:
                x = 0
            try:
                y = kwargs['y']
            except KeyError:
                y = 0
            try:
                z = kwargs['z']
            except KeyError:
                z = 0
            width = kwargs['width']
            height = kwargs['height']
            depth = kwargs['depth']
            self.coords = [
                [
                    [x+width*(3-5**0.5)/4, y+height*(3-5**0.5)/4, z+depth*(3-5**0.5)/4],
                    [x+width/2, y, z+depth*(5**0.5-1)/4],
                    [x+width/2, y, z+depth*(5-5**0.5)/4],
                    [x+width*(3-5**0.5)/4, y+height*(3-5**0.5)/4, z+depth*(1+5**0.5)/4],
                    [x, y+height*(5**0.5-1)/4, z+depth/2],
                    'fill', (hex(255, 0, 0) if len(args) == 0 else args[(0) % len(args)])  # Red
                ],
                [
                    [x+width*(1+5**0.5)/4, y+height*(3-5**0.5)/4, z+depth*(3-5**0.5)/4],
                    [x+width/2, y, z+depth*(5**0.5-1)/4],
                    [x+width/2, y, z+depth*(5-5**0.5)/4],
                    [x+width*(1+5**0.5)/4, y+height*(3-5**0.5)/4, z+depth*(1+5**0.5)/4],
                    [x+width, y+height*(5**0.5-1)/4, z+depth/2],
                    'fill', (hex(0, 255, 0) if len(args) == 0 else args[(1) % len(args)])  # Green
                ],
                [
                    [x+width*(3-5**0.5)/4, y+height*(3-5**0.5)/4, z+depth*(1+5**0.5)/4],
                    [x+width/2, y, z+depth*(5-5**0.5)/4],
                    [x+width*(1+5**0.5)/4, y+height*(3-5**0.5)/4, z+depth*(1+5**0.5)/4],
                    [x+width*(5-5**0.5)/4, y+height/2, z+depth],
                    [x+width*(5**0.5-1)/4, y+height/2, z+depth],
                    'fill', (hex(0, 0, 255) if len(args) == 0 else args[(2) % len(args)])  # Blue
                ],
                [
                    [x+width*(3-5**0.5)/4, y+height*(3-5**0.5)/4, z+depth*(3-5**0.5)/4],
                    [x+width/2, y, z+depth*(5**0.5-1)/4],
                    [x+width*(1+5**0.5)/4, y+height*(3-5**0.5)/4, z+depth*(3-5**0.5)/4],
                    [x+width*(5-5**0.5)/4, y+height/2, z],
                    [x+width*(5**0.5-1)/4, y+height/2, z],
                    'fill', (hex(255, 255, 0) if len(args) == 0 else args[(3) % len(args)])  # Yellow
                ],
                [
                    [x+width*(3-5**0.5)/4, y+height*(1+5**0.5)/4, z+depth*(3-5**0.5)/4],
                    [x+width/2, y+height, z+depth*(5**0.5-1)/4],
                    [x+width/2, y+height, z+depth*(5-5**0.5)/4],
                    [x+width*(3-5**0.5)/4, y+height*(1+5**0.5)/4, z+depth*(1+5**0.5)/4],
                    [x, y+height*(5-5**0.5)/4, z+depth/2],
                    'fill', (hex(0, 255, 255) if len(args) == 0 else args[(4) % len(args)])  # Cyan
                ],
                [
                    [x+width*(1+5**0.5)/4, y+height*(1+5**0.5)/4, z+depth*(3-5**0.5)/4],
                    [x+width/2, y+height, z+depth*(5**0.5-1)/4],
                    [x+width/2, y+height, z+depth*(5-5**0.5)/4],
                    [x+width*(1+5**0.5)/4, y+height*(1+5**0.5)/4, z+depth*(1+5**0.5)/4],
                    [x+width, y+height*(5-5**0.5)/4, z+depth/2],
                    'fill', (hex(255, 0, 255) if len(args) == 0 else args[(5) % len(args)])  # Purple
                ],
                [
                    [x+width*(3-5**0.5)/4, y+height*(1+5**0.5)/4, z+depth*(1+5**0.5)/4],
                    [x+width/2, y+height, z+depth*(5-5**0.5)/4],
                    [x+width*(1+5**0.5)/4, y+height*(1+5**0.5)/4, z+depth*(1+5**0.5)/4],
                    [x+width*(5-5**0.5)/4, y+height/2, z+depth],
                    [x+width*(5**0.5-1)/4, y+height/2, z+depth],
                    'fill', (hex(0, 0, 0) if len(args) == 0 else args[(6) % len(args)])  # Black
                ],
                [
                    [x+width*(3-5**0.5)/4, y+height*(1+5**0.5)/4, z+depth*(3-5**0.5)/4],
                    [x+width/2, y+height, z+depth*(5**0.5-1)/4],
                    [x+width*(1+5**0.5)/4, y+height*(1+5**0.5)/4, z+depth*(3-5**0.5)/4],
                    [x+width*(5-5**0.5)/4, y+height/2, z],
                    [x+width*(5**0.5-1)/4, y+height/2, z],
                    'fill', (hex(127, 127, 127) if len(args) == 0 else args[(7) % len(args)])  # Gray
                ],
                [
                    [x+width*(1+5**0.5)/4, y+height*(3-5**0.5)/4, z+depth*(3-5**0.5)/4],
                    [x+width*(5-5**0.5)/4, y+height/2, z],
                    [x+width*(1+5**0.5)/4, y+height*(1+5**0.5)/4, z+depth*(3-5**0.5)/4],
                    [x+width, y+height*(5-5**0.5)/4, z+depth/2],
                    [x+width, y+height*(5**0.5-1)/4, z+depth/2],
                    'fill', (hex(127, 0, 0) if len(args) == 0 else args[(8) % len(args)])  # Dark-Red
                ],
                [
                    [x+width*(1+5**0.5)/4, y+height*(3-5**0.5)/4, z+depth*(1+5**0.5)/4],
                    [x+width*(5-5**0.5)/4, y+height/2, z+depth],
                    [x+width*(1+5**0.5)/4, y+height*(1+5**0.5)/4, z+depth*(1+5**0.5)/4],
                    [x+width, y+height*(5-5**0.5)/4, z+depth/2],
                    [x+width, y+height*(5**0.5-1)/4, z+depth/2],
                    'fill', (hex(0, 127, 0) if len(args) == 0 else args[(9) % len(args)])  # Dark-Green
                ],
                [
                    [x+width*(3-5**0.5)/4, y+height*(3-5**0.5)/4, z+depth*(3-5**0.5)/4],
                    [x+width*(5**0.5-1)/4, y+height/2, z],
                    [x+width*(3-5**0.5)/4, y+height*(1+5**0.5)/4, z+depth*(3-5**0.5)/4],
                    [x, y+height*(5-5**0.5)/4, z+depth/2],
                    [x, y+height*(5**0.5-1)/4, z+depth/2],
                    'fill', (hex(0, 0, 127) if len(args) == 0 else args[(10) % len(args)])  # Dark-Blue
                ],
                [
                    [x+width*(3-5**0.5)/4, y+height*(3-5**0.5)/4, z+depth*(1+5**0.5)/4],
                    [x+width*(5**0.5-1)/4, y+height/2, z+depth],
                    [x+width*(3-5**0.5)/4, y+height*(1+5**0.5)/4, z+depth*(1+5**0.5)/4],
                    [x, y+height*(5-5**0.5)/4, z+depth/2],
                    [x, y+height*(5**0.5-1)/4, z+depth/2],
                    'fill', (hex(127, 127, 0) if len(args) == 0 else args[(11) % len(args)])  # Dark-Yellow
                ]
            ]
        elif 'icosahedron' in args:
            args.remove('icosahedron')
            if tag is None:
                val = 0
                while True:
                    if 'icosahedron_'+str(val) not in [canvas.itemcget(i, 'tags') for i in canvas.find_all()]:
                        self.tag = 'icosahedron_'+str(val)
                        break
                    else:
                        val += 1
            else:
                self.tag = tag
            try:
                x = kwargs['x']
            except KeyError:
                x = 0
            try:
                y = kwargs['y']
            except KeyError:
                y = 0
            try:
                z = kwargs['z']
            except KeyError:
                z = 0
            width = kwargs['width']
            height = kwargs['height']
            depth = kwargs['depth']
            self.coords = [
                [
                    [x+width/2, y, z+depth*(3-5**0.5)/4],
                    [x+width*(3-5**0.5)/4, y+height/2, z],
                    [x+width*(1+5**0.5)/4, y+height/2, z],
                    'fill', (hex(255, 0, 0) if len(args) == 0 else args[(0) % len(args)])  # Red
                ],
                [
                    [x+width/2, y+height, z+depth*(3-5**0.5)/4],
                    [x+width*(3-5**0.5)/4, y+height/2, z],
                    [x+width*(1+5**0.5)/4, y+height/2, z],
                    'fill', (hex(0, 255, 0) if len(args) == 0 else args[(1) % len(args)])  # Green
                ],
                [
                    [x+width/2, y+height, z+depth*(3-5**0.5)/4],
                    [x+width*(1+5**0.5)/4, y+height/2, z],
                    [x+width, y+height*(1+5**0.5)/4, z+depth/2],
                    'fill', (hex(0, 0, 255) if len(args) == 0 else args[(2) % len(args)])  # Blue
                ],
                [
                    [x+width/2, y, z+depth*(3-5**0.5)/4],
                    [x+width*(1+5**0.5)/4, y+height/2, z],
                    [x+width, y+height*(3-5**0.5)/4, z+depth/2],
                    'fill', (hex(255, 255, 0) if len(args) == 0 else args[(3) % len(args)])  # Yellow
                ],
                [
                    [x+width*(1+5**0.5)/4, y+height/2, z],
                    [x+width, y+height*(1+5**0.5)/4, z+depth/2],
                    [x+width, y+height*(3-5**0.5)/4, z+depth/2],
                    'fill', (hex(0, 255, 255) if len(args) == 0 else args[(4) % len(args)])  # Cyan
                ],
                [
                    [x+width/2, y+height, z+depth*(1+5**0.5)/4],
                    [x+width/2, y+height, z+depth*(3-5**0.5)/4],
                    [x+width, y+height*(1+5**0.5)/4, z+depth/2],
                    'fill', (hex(255, 0, 255) if len(args) == 0 else args[(5) % len(args)])  # Purple
                ],
                [
                    [x+width/2, y+height, z+depth*(1+5**0.5)/4],
                    [x+width/2, y+height, z+depth*(3-5**0.5)/4],
                    [x, y+height*(1+5**0.5)/4, z+depth/2],
                    'fill', (hex(0, 0, 0) if len(args) == 0 else args[(6) % len(args)])  # Black
                ],
                [
                    [x+width*(1+5**0.5)/4, y+height/2, z+depth],
                    [x+width, y+height*(1+5**0.5)/4, z+depth/2],
                    [x+width, y+height*(3-5**0.5)/4, z+depth/2],
                    'fill', (hex(127, 127, 127) if len(args) == 0 else args[(7) % len(args)])  # Gray
                ],
                [
                    [x+width/2, y, z+depth*(1+5**0.5)/4],
                    [x+width*(3-5**0.5)/4, y+height/2, z+depth],
                    [x+width*(1+5**0.5)/4, y+height/2, z+depth],
                    'fill', (hex(127, 0, 0) if len(args) == 0 else args[(8) % len(args)])  # Dark-Red
                ],
                [
                    [x+width/2, y+height, z+depth*(1+5**0.5)/4],
                    [x+width*(3-5**0.5)/4, y+height/2, z+depth],
                    [x+width*(1+5**0.5)/4, y+height/2, z+depth],
                    'fill', (hex(0, 127, 0) if len(args) == 0 else args[(9) % len(args)])  # Dark-Green
                ],
                [
                    [x+width, y+height*(1+5**0.5)/4, z+depth/2],
                    [x+width/2, y+height, z+depth*(1+5**0.5)/4],
                    [x+width*(1+5**0.5)/4, y+height/2, z+depth],
                    'fill', (hex(0, 0, 127) if len(args) == 0 else args[(10) % len(args)])  # Dark-Blue
                ],
                [
                    [x+width/2, y, z+depth*(1+5**0.5)/4],
                    [x+width*(1+5**0.5)/4, y+height/2, z+depth],
                    [x+width, y+height*(3-5**0.5)/4, z+depth/2],
                    'fill', (hex(127, 127, 0) if len(args) == 0 else args[(11) % len(args)])  # Dark-Yellow
                ],
                [
                    [x+width/2, y, z+depth*(1+5**0.5)/4],
                    [x+width/2, y, z+depth*(3-5**0.5)/4],
                    [x+width, y+height*(3-5**0.5)/4, z+depth/2],
                    'fill', (hex(0, 127, 127) if len(args) == 0 else args[(12) % len(args)])  # Dark-Cyan
                ],
                [
                    [x+width/2, y, z+depth*(1+5**0.5)/4],
                    [x+width/2, y, z+depth*(3-5**0.5)/4],
                    [x, y+height*(3-5**0.5)/4, z+depth/2],
                    'fill', (hex(127, 0, 127) if len(args) == 0 else args[(13) % len(args)])  # Dark-Purple
                ],
                [
                    [x+width/2, y+height, z+depth*(3-5**0.5)/4],
                    [x+width*(3-5**0.5)/4, y+height/2, z],
                    [x, y+height*(1+5**0.5)/4, z+depth/2],
                    'fill', (hex(255, 127, 127) if len(args) == 0 else args[(14) % len(args)])  # Light-Red
                ],
                [
                    [x+width/2, y, z+depth*(3-5**0.5)/4],
                    [x+width*(3-5**0.5)/4, y+height/2, z],
                    [x, y+height*(3-5**0.5)/4, z+depth/2],
                    'fill', (hex(127, 255, 127) if len(args) == 0 else args[(15) % len(args)])  # Light-Green
                ],
                [
                    [x+width*(3-5**0.5)/4, y+height/2, z],
                    [x, y+height*(1+5**0.5)/4, z+depth/2],
                    [x, y+height*(3-5**0.5)/4, z+depth/2],
                    'fill', (hex(127, 127, 255) if len(args) == 0 else args[(16) % len(args)])  # Light-Blue
                ],
                [
                    [x, y+height*(1+5**0.5)/4, z+depth/2],
                    [x+width/2, y+height, z+depth*(1+5**0.5)/4],
                    [x+width*(3-5**0.5)/4, y+height/2, z+depth],
                    'fill', (hex(255, 255, 127) if len(args) == 0 else args[(17) % len(args)])  # Light-Yellow
                ],
                [
                    [x+width/2, y, z+depth*(1+5**0.5)/4],
                    [x+width*(3-5**0.5)/4, y+height/2, z+depth],
                    [x, y+height*(3-5**0.5)/4, z+depth/2],
                    'fill', (hex(127, 255, 255) if len(args) == 0 else args[(18) % len(args)])  # Light-Cyan
                ],
                [
                    [x+width*(3-5**0.5)/4, y+height/2, z+depth],
                    [x, y+height*(1+5**0.5)/4, z+depth/2],
                    [x, y+height*(3-5**0.5)/4, z+depth/2],
                    'fill', (hex(255, 127, 255) if len(args) == 0 else args[(19) % len(args)])  # Light-Purple
                ]
            ]
        elif type(args[0]) == int or type(args[0]) == float:
            if tag is None:
                val = 0
                while True:
                    if str(args[0])+'_'+str(val) not in [canvas.itemcget(i, 'tags') for i in canvas.find_all()]:
                        self.tag = str(args[0])+'_'+str(val)
                        break
                    else:
                        val += 1
            else:
                self.tag = tag
            try:
                x = kwargs['x']
            except KeyError:
                x = 0
            try:
                y = kwargs['y']
            except KeyError:
                y = 0
            try:
                z = kwargs['z']
            except KeyError:
                z = 0
            width = kwargs['width']
            height = kwargs['height']
            depth = kwargs['depth']  # prism
            if pyramid:
                self.coords = Obj.pyramid(args[0], *args[1:], x=x, y=y, z=z,
                                          width=width, height=height, depth=depth)
            else:
                self.coords = Obj.prism(args[0], *args[1:], x=x, y=y, z=z,
                                        width=width, height=height, depth=depth)
        else:
            if tag is None:
                val = 0
                while True:
                    if 'custom_'+str(val) not in [canvas.itemcget(i, 'tags') for i in canvas.find_all()]:
                        self.tag = 'custom_'+str(val)
                        break
                    else:
                        val += 1
            else:
                self.tag = tag
            self.coords = args
        self.rotate(theta_x+180, theta_y+180, theta_z+180, around_x="s", around_y="s", around_z="s")

    def draw(self):
        canvas.delete(self.tag)
        self.coords = sorted(self.coords, key=lambda edge: sum(
            vertex[2] for vertex in edge if type(vertex) == list), reverse=True)
        for face in (self.coords if self.wireframe else (self.coords[1:len(self.coords)] if self.isPyramid else self.coords[int(len(self.coords)/2):])):
            points = []
            for edge in face:
                if type(edge) == list:
                    if self.augment is not False:
                        if type(self.augment) == int or type(self.augment) == float:
                            angle = self.augment
                        elif type(self.augment) == list or type(self.augment) == tuple:
                            angle = math.atan2(
                                self.augment[1]-self.y_avg, -self.augment[0]+self.x_avg)/math.pi*180
                        elif self.augment:
                            angle = math.atan2(
                                self.z_avg-self.y_avg, -self.z_avg+self.x_avg)/math.pi*180
                        else:
                            raise ValueError("Invalid Depth Visualization")
                        points.append(
                            edge[0]-edge[2]*math.cos(math.atan2(math.sin(angle*math.pi/180), -math.cos(angle*math.pi/180))))
                        points.append(
                            edge[1]-edge[2]*math.sin(math.atan2(math.sin(angle*math.pi/180), -math.cos(angle*math.pi/180))))
                    else:
                        points.append(edge[0])
                        points.append(edge[1])
            item = canvas.create_polygon(points, tags=self.tag)
            try:  # dash=(5,2)
                canvas.itemconfig(item, dash=face[face.index('dash')+1])
            except ValueError:
                pass
            try:  # dashoffset=0
                canvas.itemconfig(
                    item, dashoffset=face[face.index('dashoffset')+1])
            except ValueError:
                pass
            try:  # fill=hex(0, 0, 0)
                if type(self.wireframe) == str:
                    canvas.itemconfig(item, outline=self.wireframe)
                    canvas.itemconfig(item, fill='')
                elif self.wireframe:
                    canvas.itemconfig(item, outline=hex(0, 0, 0))
                    canvas.itemconfig(item, fill='')
                else:
                    canvas.itemconfig(item, fill=face[face.index('fill')+1])
            except ValueError:
                pass
            try:  # joinstyle='round'
                canvas.itemconfig(
                    item, joinstyle=face[face.index('joinstyle')+1])
            except ValueError:
                pass
            try:  # offset=0
                canvas.itemconfig(item, offset=face[face.index('offset')+1])
            except ValueError:
                pass
            try:  # outline=hex(0, 0, 0)
                canvas.itemconfig(item, outline=face[face.index('outline')+1])
            except ValueError:
                pass
            try:  # outlineoffset=0
                canvas.itemconfig(
                    item, outlineoffset=face[face.index('outlineoffset')+1])
            except ValueError:
                pass
            try:  # outlinestipple='gray25'
                canvas.itemconfig(
                    item, outlinestipple=face[face.index('outlinestipple')+1])
            except ValueError:
                pass
            try:  # smooth=0
                canvas.itemconfig(item, smooth=face[face.index('smooth')+1])
            except ValueError:
                pass
            try:  # splinesteps=12
                canvas.itemconfig(
                    item, splinesteps=face[face.index('splinesteps')+1])
            except ValueError:
                pass
            try:  # stipple='gray25'
                canvas.itemconfig(item, stipple=face[face.index('stipple')+1])
            except ValueError:
                pass
            try:  # tags=('')
                canvas.itemconfig(item, tags=face[face.index('tags')+1])
            except ValueError:
                pass
            try:  # 'width'=1
                canvas.itemconfig(item, width=face[face.index('linewidth')+1])
            except ValueError:
                pass

    def rotate(self, theta_x, theta_y, theta_z, around_x=None, around_y=None, around_z=None):
        x_avg = 0
        y_avg = 0
        z_avg = 0
        vertices = 0
        for face in self.coords:
            for edge in face:
                if type(edge) == list:
                    x_avg += edge[0]
                    y_avg += edge[1]
                    z_avg += edge[2]
                    vertices += 1
        x_avg /= vertices
        y_avg /= vertices
        z_avg /= vertices
        self.x_avg = x_avg
        self.y_avg = y_avg
        self.z_avg = z_avg
        if around_x is not None:
            if type(around_x) == str and around_x[0].lower() == "s":
                pass
            else:
                x_avg = float(around_x)
        elif self.x_axis is not None:
            x_avg = self.x_axis
        if around_y is not None:
            if type(around_y) == str and around_y[0].lower() == "s":
                pass
            else:
                y_avg = float(around_y)
        elif self.y_axis is not None:
            y_avg = self.y_axis
        if around_z is not None:
            if type(around_z) == str and around_z[0].lower() == "s":
                pass
            else:
                z_avg = float(around_z)
        elif self.z_axis is not None:
            z_avg = self.z_axis
        for face in range(len(self.coords)):
            for edge in range(len(self.coords[face])):
                if type(self.coords[face][edge]) == list:
                    x = self.coords[face][edge][0] - x_avg
                    y = self.coords[face][edge][1] - y_avg
                    z = self.coords[face][edge][2] - z_avg
                    x2, y2, z2 = Obj.rotatePoint(x, y, z, theta_x, theta_y, theta_z)
                    self.coords[face][edge] = [x2+x_avg, y2+y_avg, z2+z_avg]
        self.draw()


def help():
    print('Call "model.setup()" to initialize the window and link the required files to the (optional) given list. Store the returned value to a variable.\n\nCall "model.prebuilt(list)" to add a prebuilt example to the variable made in the setup.\n\nCall "model.start() when ready to run')


def setup(render=[], x=500, y=500, fullscreen=False):
    '''Create Canvas Element as List'''
    global canvas, history, lastMouse, root, inverse
    user32 = ctypes.windll.user32
    if fullscreen:
        screensize = user32.GetSystemMetrics(0), user32.GetSystemMetrics(1)
    else:
        screensize = x, y

    root = Tk()

    canvas = Canvas(root, height=screensize[1],
                    width=screensize[0], bg=hex(255, 255, 255))
    canvas.grid()
    canvas.focus_set()
    if fullscreen is None:
        root.wm_attributes('-alpha', 1, '-fullscreen', 1)

    history = []

    def keyDown(event):
        global history, canvas
        if event.keycode not in history:
            history.append(event.keycode)

    def keyUp(event):
        global history
        try:
            history.remove(event.keycode)
        except ValueError:
            pass

    def move(render):
        global canvas, history
        render = sorted(render, key=lambda obj: obj.z_avg, reverse=True)
        inc = 5
        for i in history:
            if i == 32:  # Space Bar
                for t in render:
                    t.rotate(0, 0, inc)
            elif i == 16:  # Shift
                for t in render:
                    t.rotate(0, 0, -inc)
            elif i == 37:  # Left Arrow
                for t in render:
                    t.rotate(0, inc, 0)
            elif i == 38:  # Up Arrow
                for t in render:
                    t.rotate(-inc, 0, 0)
            elif i == 39:  # Right Arrow
                for t in render:
                    t.rotate(0, -inc, 0)
            elif i == 40:  # Down Arrow
                for t in render:
                    t.rotate(inc, 0, 0)
            elif i == 27 or i == 81:  # Esc or Q
                root.destroy()
                num = 1
                while True:
                    try:
                        open("export3D."+str(num)+".txt", "r")
                        num += 1
                    except FileNotFoundError:
                        with open("export3D."+str(num)+".txt", "w") as file:
                            for obj in [v.coords for v in render]:
                                for side in obj:
                                    file.write(str(side)+"\n")
                                file.write("\n")
                        break
            else:
                pass
        canvas.after(5, lambda: move(render))

    lastMouse = [0, 0]
    inverse = 1

    def motion(event, render):
        global canvas, lastMouse, inverse
        render = sorted(render, key=lambda obj: obj.z_avg, reverse=True)
        mouseMult = 0.5
        for t in render:
            t.rotate(round((event.y-lastMouse[1])*mouseMult)*inverse,
                     round((-event.x+lastMouse[0])*mouseMult)*inverse, 0)
        lastMouse = [event.x, event.y]

    def click(event):
        global inverse
        inverse *= -1

    canvas.after(5, lambda: move(render))

    canvas.bind('<KeyPress>', keyDown)  # Keyboard Down
    canvas.bind('<KeyRelease>', keyUp)  # Keyboard Up
    canvas.bind('<ButtonPress-1>', click)  # Left Mouse Down
    canvas.bind('<ButtonRelease-1>', click)  # Left Mouse Up
    canvas.bind('<Motion>', lambda event: motion(event, render))  # Move Mouse
    canvas.pack()
    return render


def start(*args):
    ''''Start Rendering'''
    global root
    root.mainloop()


def prebuilt(render):
    '''Add prebuilt models'''
    render.append(Obj('cube', x=200, y=200, z=0,
                  width=50, height=50, depth=50))
    render.append(Obj('cube', x=200, y=200, z=50,
                  width=50, height=50, depth=50,
                  x_axis=225, y_axis=225, z_axis=25))
    render.append(Obj('cube', x=150, y=200, z=0,
                  width=50, height=50, depth=50,
                  x_axis=225, y_axis=225, z_axis=25))
    render.append(Obj(6, x=50, y=50, z=0,
                      width=50, height=50, depth=50,
                      pyramid=True, wireframe=True))
    render.append(Obj('dodecahedron', x=400, y=50, z=0,
                      width=50, height=50, depth=50,
                      wireframe=False))
    render.append(Obj(6, hex(255, 0, 0), hex(0, 0, 255), x=400, y=400, z=0,
                      pyramid=True, width=50, height=50, depth=50))
    render.append(Obj('icosahedron', x=50, y=400, z=0,
                      width=50, height=50, depth=50,
                      wireframe=True))
    return render


if __name__ == "__main__":
    arr = setup()  # Create Canvas
    arr = prebuilt(arr)  # Create Objects on Canvas
    arr.append(Obj(4, "#FF0000", "#00FF00", x=200, y=400, z=0, width=50, height=50, depth=50))
    start()
