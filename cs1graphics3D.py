import math
from cs1graphics import Canvas, Polygon, Point, Layer


class Obj(Layer):
    @staticmethod
    def prism(edges, *args, x=0, y=0, z=0, width=1, height=1, depth=1):
        '''Create an edges-sided prism cs1graphics shape'''
        newArr = []
        arr = [[x+(math.sin(vertex/edges*2*math.pi)+1)/2*width, y +
                (math.cos(vertex/edges*2*math.pi)+1)/2*height] for vertex in range(edges)]
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
        '''Create an edges-sided pyramid cs1graphics shape'''
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
    def rotatePoint(x, y, z, theta_x=0, theta_y=0, theta_z=0):
        '''Rotate a point in 3-dimensions by theta degrees in the x-y-z planes'''
        return [x*math.cos(theta_z*math.pi/180)*math.cos(theta_y*math.pi/180) + y*math.cos(theta_z*math.pi/180)*math.sin(theta_y*math.pi/180)*math.sin(theta_x*math.pi/180) - y*math.sin(theta_z*math.pi/180)*math.cos(
                theta_x*math.pi/180) + z*math.cos(theta_z*math.pi/180)*math.sin(theta_y*math.pi/180)*math.cos(theta_x*math.pi/180) + z*math.sin(theta_z*math.pi/180)*math.sin(theta_x*math.pi/180),
                x*math.sin(theta_z*math.pi/180)*math.cos(theta_y*math.pi/180) + y*math.sin(theta_z*math.pi/180)*math.sin(theta_y*math.pi/180)*math.sin(theta_x*math.pi/180) + y*math.cos(theta_z*math.pi/180)*math.cos(
                theta_x*math.pi/180) + z*math.sin(theta_z*math.pi/180)*math.sin(theta_y*math.pi/180)*math.cos(theta_x*math.pi/180) - z*math.cos(theta_z*math.pi/180)*math.sin(theta_x*math.pi/180),
                -x*math.sin(theta_y*math.pi/180) + y*math.cos(theta_y*math.pi/180)*math.sin(
                theta_x*math.pi/180) + z*math.cos(theta_y*math.pi/180)*math.cos(theta_x*math.pi/180)]

    def __init__(self, *args, theta_x=0, theta_y=0, theta_z=0, x_axis=None, y_axis=None, z_axis=None, pyramid=False, wireframe=False, **kwargs):
        super().__init__()
        args = list(args)
        if 'cube' in args or 'cuboid' in args:
            if 'cube' in args:
                args.remove('cube')
            elif 'cuboid' in args:
                args.remove('cuboid')
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
                    'fill', ((255, 0, 0) if len(args) == 0 else args[(0) % len(args)])  # Red
                ],
                [  # Left @ theta_y=270
                    [x, y, z],
                    [x, y, z+depth],
                    [x, y+height, z+depth],
                    [x, y+height, z],
                    'fill', ((0, 255, 0) if len(args) == 0 else args[(1) % len(args)])  # Green
                ],
                [  # Bottom @ theta_z=270
                    [x, y+height, z],
                    [x, y+height, z+depth],
                    [x+width, y+height, z+depth],
                    [x+width, y+height, z],
                    'fill', ((0, 0, 255) if len(args) == 0 else args[(2) % len(args)])  # Blue
                ],
                [  # Right @ theta_y=90
                    [x+width, y+height, z],
                    [x+width, y+height, z+depth],
                    [x+width, y, z+depth],
                    [x+width, y, z],
                    'fill', ((255, 255, 0) if len(args) == 0 else args[(3) % len(args)])  # Yellow
                ],
                [  # Top @ theta_x=90
                    [x+width, y, z],
                    [x, y, z],
                    [x, y, z+depth],
                    [x+width, y, z+depth],
                    'fill', ((0, 255, 255) if len(args) == 0 else args[(4) % len(args)])  # Cyan
                ],
                [  # Back @ theta_y=180
                    [x+width, y, z+depth],
                    [x+width, y+height, z+depth],
                    [x, y+height, z+depth],
                    [x, y, z+depth],
                    'fill', ((255, 0, 255) if len(args) == 0 else args[(5) % len(args)])  # Purple
                ]
            ]
        elif 'tetrahedron' in args:
            args.remove('tetrahedron')
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
                    'fill', ((255, 0, 0) if len(args) == 0 else args[(0) % len(args)])  # Red
                ],
                [
                    [x+width, y+height, z+depth],
                    [x+width, y, z],
                    [x, y, z+depth],
                    'fill', ((0, 255, 0) if len(args) == 0 else args[(1) % len(args)])  # Green
                ],
                [
                    [x+width, y+height, z+depth],
                    [x, y+height, z],
                    [x, y, z+depth],
                    'fill', ((0, 0, 255) if len(args) == 0 else args[(2) % len(args)])  # Blue
                ],
                [
                    [x+width, y, z],
                    [x, y+height, z],
                    [x, y, z+depth],
                    'fill', ((255, 255, 0) if len(args) == 0 else args[(3) % len(args)])  # Yellow
                ]
            ]
        elif 'octahedron' in args:
            args.remove('octahedron')
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
                    'fill', ((255, 0, 0) if len(args) == 0 else args[(0) % len(args)])  # Red
                ],
                [
                    [x, y+height/2, z+depth/2],
                    [x+width/2, y, z+depth/2],
                    [x+width/2, y+height/2, z+depth],
                    'fill', ((0, 255, 0) if len(args) == 0 else args[(1) % len(args)])  # Green
                ],
                [
                    [x+width, y+height/2, z+depth/2],
                    [x+width/2, y, z+depth/2],
                    [x+width/2, y+height/2, z],
                    'fill', ((0, 0, 255) if len(args) == 0 else args[(2) % len(args)])  # Blue
                ],
                [
                    [x+width, y+height/2, z+depth/2],
                    [x+width/2, y, z+depth/2],
                    [x+width/2, y+height/2, z+depth],
                    'fill', ((255, 255, 0) if len(args) == 0 else args[(3) % len(args)])  # Yellow
                ],
                [
                    [x, y+height/2, z+depth/2],
                    [x+width/2, y+height, z+depth/2],
                    [x+width/2, y+height/2, z],
                    'fill', ((0, 255, 255) if len(args) == 0 else args[(4) % len(args)])  # Cyan
                ],
                [
                    [x, y+height/2, z+depth/2],
                    [x+width/2, y+height, z+depth/2],
                    [x+width/2, y+height/2, z+depth],
                    'fill', ((255, 0, 255) if len(args) == 0 else args[(5) % len(args)])  # Purple
                ],
                [
                    [x+width, y+height/2, z+depth/2],
                    [x+width/2, y+height, z+depth/2],
                    [x+width/2, y+height/2, z],
                    'fill', ((0, 0, 0) if len(args) == 0 else args[(6) % len(args)])  # Black
                ],
                [
                    [x+width, y+height/2, z+depth/2],
                    [x+width/2, y+height, z+depth/2],
                    [x+width/2, y+height/2, z+depth],
                    'fill', ((127, 127, 127) if len(args) == 0 else args[(7) % len(args)])  # Gray
                ]
            ]
        elif 'dodecahedron' in args:
            args.remove('dodecahedron')
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
                    'fill', ((255, 0, 0) if len(args) == 0 else args[(0) % len(args)])  # Red
                ],
                [
                    [x+width*(1+5**0.5)/4, y+height*(3-5**0.5)/4, z+depth*(3-5**0.5)/4],
                    [x+width/2, y, z+depth*(5**0.5-1)/4],
                    [x+width/2, y, z+depth*(5-5**0.5)/4],
                    [x+width*(1+5**0.5)/4, y+height*(3-5**0.5)/4, z+depth*(1+5**0.5)/4],
                    [x+width, y+height*(5**0.5-1)/4, z+depth/2],
                    'fill', ((0, 255, 0) if len(args) == 0 else args[(1) % len(args)])  # Green
                ],
                [
                    [x+width*(3-5**0.5)/4, y+height*(3-5**0.5)/4, z+depth*(1+5**0.5)/4],
                    [x+width/2, y, z+depth*(5-5**0.5)/4],
                    [x+width*(1+5**0.5)/4, y+height*(3-5**0.5)/4, z+depth*(1+5**0.5)/4],
                    [x+width*(5-5**0.5)/4, y+height/2, z+depth],
                    [x+width*(5**0.5-1)/4, y+height/2, z+depth],
                    'fill', ((0, 0, 255) if len(args) == 0 else args[(2) % len(args)])  # Blue
                ],
                [
                    [x+width*(3-5**0.5)/4, y+height*(3-5**0.5)/4, z+depth*(3-5**0.5)/4],
                    [x+width/2, y, z+depth*(5**0.5-1)/4],
                    [x+width*(1+5**0.5)/4, y+height*(3-5**0.5)/4, z+depth*(3-5**0.5)/4],
                    [x+width*(5-5**0.5)/4, y+height/2, z],
                    [x+width*(5**0.5-1)/4, y+height/2, z],
                    'fill', ((255, 255, 0) if len(args) == 0 else args[(3) % len(args)])  # Yellow
                ],
                [
                    [x+width*(3-5**0.5)/4, y+height*(1+5**0.5)/4, z+depth*(3-5**0.5)/4],
                    [x+width/2, y+height, z+depth*(5**0.5-1)/4],
                    [x+width/2, y+height, z+depth*(5-5**0.5)/4],
                    [x+width*(3-5**0.5)/4, y+height*(1+5**0.5)/4, z+depth*(1+5**0.5)/4],
                    [x, y+height*(5-5**0.5)/4, z+depth/2],
                    'fill', ((0, 255, 255) if len(args) == 0 else args[(4) % len(args)])  # Cyan
                ],
                [
                    [x+width*(1+5**0.5)/4, y+height*(1+5**0.5)/4, z+depth*(3-5**0.5)/4],
                    [x+width/2, y+height, z+depth*(5**0.5-1)/4],
                    [x+width/2, y+height, z+depth*(5-5**0.5)/4],
                    [x+width*(1+5**0.5)/4, y+height*(1+5**0.5)/4, z+depth*(1+5**0.5)/4],
                    [x+width, y+height*(5-5**0.5)/4, z+depth/2],
                    'fill', ((255, 0, 255) if len(args) == 0 else args[(5) % len(args)])  # Purple
                ],
                [
                    [x+width*(3-5**0.5)/4, y+height*(1+5**0.5)/4, z+depth*(1+5**0.5)/4],
                    [x+width/2, y+height, z+depth*(5-5**0.5)/4],
                    [x+width*(1+5**0.5)/4, y+height*(1+5**0.5)/4, z+depth*(1+5**0.5)/4],
                    [x+width*(5-5**0.5)/4, y+height/2, z+depth],
                    [x+width*(5**0.5-1)/4, y+height/2, z+depth],
                    'fill', ((0, 0, 0) if len(args) == 0 else args[(6) % len(args)])  # Black
                ],
                [
                    [x+width*(3-5**0.5)/4, y+height*(1+5**0.5)/4, z+depth*(3-5**0.5)/4],
                    [x+width/2, y+height, z+depth*(5**0.5-1)/4],
                    [x+width*(1+5**0.5)/4, y+height*(1+5**0.5)/4, z+depth*(3-5**0.5)/4],
                    [x+width*(5-5**0.5)/4, y+height/2, z],
                    [x+width*(5**0.5-1)/4, y+height/2, z],
                    'fill', ((127, 127, 127) if len(args) == 0 else args[(7) % len(args)])  # Gray
                ],
                [
                    [x+width*(1+5**0.5)/4, y+height*(3-5**0.5)/4, z+depth*(3-5**0.5)/4],
                    [x+width*(5-5**0.5)/4, y+height/2, z],
                    [x+width*(1+5**0.5)/4, y+height*(1+5**0.5)/4, z+depth*(3-5**0.5)/4],
                    [x+width, y+height*(5-5**0.5)/4, z+depth/2],
                    [x+width, y+height*(5**0.5-1)/4, z+depth/2],
                    'fill', ((127, 0, 0) if len(args) == 0 else args[(8) % len(args)])  # Dark-Red
                ],
                [
                    [x+width*(1+5**0.5)/4, y+height*(3-5**0.5)/4, z+depth*(1+5**0.5)/4],
                    [x+width*(5-5**0.5)/4, y+height/2, z+depth],
                    [x+width*(1+5**0.5)/4, y+height*(1+5**0.5)/4, z+depth*(1+5**0.5)/4],
                    [x+width, y+height*(5-5**0.5)/4, z+depth/2],
                    [x+width, y+height*(5**0.5-1)/4, z+depth/2],
                    'fill', ((0, 127, 0) if len(args) == 0 else args[(9) % len(args)])  # Dark-Green
                ],
                [
                    [x+width*(3-5**0.5)/4, y+height*(3-5**0.5)/4, z+depth*(3-5**0.5)/4],
                    [x+width*(5**0.5-1)/4, y+height/2, z],
                    [x+width*(3-5**0.5)/4, y+height*(1+5**0.5)/4, z+depth*(3-5**0.5)/4],
                    [x, y+height*(5-5**0.5)/4, z+depth/2],
                    [x, y+height*(5**0.5-1)/4, z+depth/2],
                    'fill', ((0, 0, 127) if len(args) == 0 else args[(10) % len(args)])  # Dark-Blue
                ],
                [
                    [x+width*(3-5**0.5)/4, y+height*(3-5**0.5)/4, z+depth*(1+5**0.5)/4],
                    [x+width*(5**0.5-1)/4, y+height/2, z+depth],
                    [x+width*(3-5**0.5)/4, y+height*(1+5**0.5)/4, z+depth*(1+5**0.5)/4],
                    [x, y+height*(5-5**0.5)/4, z+depth/2],
                    [x, y+height*(5**0.5-1)/4, z+depth/2],
                    'fill', ((127, 127, 0) if len(args) == 0 else args[(11) % len(args)])  # Dark-Yellow
                ]
            ]
        elif 'icosahedron' in args:
            args.remove('icosahedron')
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
                    'fill', ((255, 0, 0) if len(args) == 0 else args[(0) % len(args)])  # Red
                ],
                [
                    [x+width/2, y+height, z+depth*(3-5**0.5)/4],
                    [x+width*(3-5**0.5)/4, y+height/2, z],
                    [x+width*(1+5**0.5)/4, y+height/2, z],
                    'fill', ((0, 255, 0) if len(args) == 0 else args[(1) % len(args)])  # Green
                ],
                [
                    [x+width/2, y+height, z+depth*(3-5**0.5)/4],
                    [x+width*(1+5**0.5)/4, y+height/2, z],
                    [x+width, y+height*(1+5**0.5)/4, z+depth/2],
                    'fill', ((0, 0, 255) if len(args) == 0 else args[(2) % len(args)])  # Blue
                ],
                [
                    [x+width/2, y, z+depth*(3-5**0.5)/4],
                    [x+width*(1+5**0.5)/4, y+height/2, z],
                    [x+width, y+height*(3-5**0.5)/4, z+depth/2],
                    'fill', ((255, 255, 0) if len(args) == 0 else args[(3) % len(args)])  # Yellow
                ],
                [
                    [x+width*(1+5**0.5)/4, y+height/2, z],
                    [x+width, y+height*(1+5**0.5)/4, z+depth/2],
                    [x+width, y+height*(3-5**0.5)/4, z+depth/2],
                    'fill', ((0, 255, 255) if len(args) == 0 else args[(4) % len(args)])  # Cyan
                ],
                [
                    [x+width/2, y+height, z+depth*(1+5**0.5)/4],
                    [x+width/2, y+height, z+depth*(3-5**0.5)/4],
                    [x+width, y+height*(1+5**0.5)/4, z+depth/2],
                    'fill', ((255, 0, 255) if len(args) == 0 else args[(5) % len(args)])  # Purple
                ],
                [
                    [x+width/2, y+height, z+depth*(1+5**0.5)/4],
                    [x+width/2, y+height, z+depth*(3-5**0.5)/4],
                    [x, y+height*(1+5**0.5)/4, z+depth/2],
                    'fill', ((0, 0, 0) if len(args) == 0 else args[(6) % len(args)])  # Black
                ],
                [
                    [x+width*(1+5**0.5)/4, y+height/2, z+depth],
                    [x+width, y+height*(1+5**0.5)/4, z+depth/2],
                    [x+width, y+height*(3-5**0.5)/4, z+depth/2],
                    'fill', ((127, 127, 127) if len(args) == 0 else args[(7) % len(args)])  # Gray
                ],
                [
                    [x+width/2, y, z+depth*(1+5**0.5)/4],
                    [x+width*(3-5**0.5)/4, y+height/2, z+depth],
                    [x+width*(1+5**0.5)/4, y+height/2, z+depth],
                    'fill', ((127, 0, 0) if len(args) == 0 else args[(8) % len(args)])  # Dark-Red
                ],
                [
                    [x+width/2, y+height, z+depth*(1+5**0.5)/4],
                    [x+width*(3-5**0.5)/4, y+height/2, z+depth],
                    [x+width*(1+5**0.5)/4, y+height/2, z+depth],
                    'fill', ((0, 127, 0) if len(args) == 0 else args[(9) % len(args)])  # Dark-Green
                ],
                [
                    [x+width, y+height*(1+5**0.5)/4, z+depth/2],
                    [x+width/2, y+height, z+depth*(1+5**0.5)/4],
                    [x+width*(1+5**0.5)/4, y+height/2, z+depth],
                    'fill', ((0, 0, 127) if len(args) == 0 else args[(10) % len(args)])  # Dark-Blue
                ],
                [
                    [x+width/2, y, z+depth*(1+5**0.5)/4],
                    [x+width*(1+5**0.5)/4, y+height/2, z+depth],
                    [x+width, y+height*(3-5**0.5)/4, z+depth/2],
                    'fill', ((127, 127, 0) if len(args) == 0 else args[(11) % len(args)])  # Dark-Yellow
                ],
                [
                    [x+width/2, y, z+depth*(1+5**0.5)/4],
                    [x+width/2, y, z+depth*(3-5**0.5)/4],
                    [x+width, y+height*(3-5**0.5)/4, z+depth/2],
                    'fill', ((0, 127, 127) if len(args) == 0 else args[(12) % len(args)])  # Dark-Cyan
                ],
                [
                    [x+width/2, y, z+depth*(1+5**0.5)/4],
                    [x+width/2, y, z+depth*(3-5**0.5)/4],
                    [x, y+height*(3-5**0.5)/4, z+depth/2],
                    'fill', ((127, 0, 127) if len(args) == 0 else args[(13) % len(args)])  # Dark-Purple
                ],
                [
                    [x+width/2, y+height, z+depth*(3-5**0.5)/4],
                    [x+width*(3-5**0.5)/4, y+height/2, z],
                    [x, y+height*(1+5**0.5)/4, z+depth/2],
                    'fill', ((255, 127, 127) if len(args) == 0 else args[(14) % len(args)])  # Light-Red
                ],
                [
                    [x+width/2, y, z+depth*(3-5**0.5)/4],
                    [x+width*(3-5**0.5)/4, y+height/2, z],
                    [x, y+height*(3-5**0.5)/4, z+depth/2],
                    'fill', ((127, 255, 127) if len(args) == 0 else args[(15) % len(args)])  # Light-Green
                ],
                [
                    [x+width*(3-5**0.5)/4, y+height/2, z],
                    [x, y+height*(1+5**0.5)/4, z+depth/2],
                    [x, y+height*(3-5**0.5)/4, z+depth/2],
                    'fill', ((127, 127, 255) if len(args) == 0 else args[(16) % len(args)])  # Light-Blue
                ],
                [
                    [x, y+height*(1+5**0.5)/4, z+depth/2],
                    [x+width/2, y+height, z+depth*(1+5**0.5)/4],
                    [x+width*(3-5**0.5)/4, y+height/2, z+depth],
                    'fill', ((255, 255, 127) if len(args) == 0 else args[(17) % len(args)])  # Light-Yellow
                ],
                [
                    [x+width/2, y, z+depth*(1+5**0.5)/4],
                    [x+width*(3-5**0.5)/4, y+height/2, z+depth],
                    [x, y+height*(3-5**0.5)/4, z+depth/2],
                    'fill', ((127, 255, 255) if len(args) == 0 else args[(18) % len(args)])  # Light-Cyan
                ],
                [
                    [x+width*(3-5**0.5)/4, y+height/2, z+depth],
                    [x, y+height*(1+5**0.5)/4, z+depth/2],
                    [x, y+height*(3-5**0.5)/4, z+depth/2],
                    'fill', ((255, 127, 255) if len(args) == 0 else args[(19) % len(args)])  # Light-Purple
                ]
            ]
        elif type(args[0]) == int or type(args[0]) == float:
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
            if(pyramid):
                self.coords = Obj.pyramid(args[0], *args[1:], x=x, y=y, z=z, width=width, height=height, depth=depth)
            else:
                self.coords = Obj.prism(args[0], *args[1:], x=x, y=y, z=z, width=width, height=height, depth=depth)
        else:
            self.coords = args
        self.copy = [([(edge[:] if type(edge) == list else edge) for edge in face] if type(face) == list else face) for face in self.coords]
        self.wireframe = wireframe
        self.x_axis = x_axis
        self.y_axis = y_axis
        self.z_axis = z_axis
        self.pointers = []
        try:
            theta_x = kwargs['theta_x']
        except KeyError:
            theta_x = 0
        try:
            theta_y = kwargs['theta_y']
        except KeyError:
            theta_y = 0
        try:
            theta_z = kwargs['theta_z']
        except KeyError:
            theta_z = 0
        self.rotate(theta_x+180, theta_y+180, theta_z+180, around_x="s", around_y="s", around_z="s")

    def rotate(self, theta_x, theta_y, theta_z, around_x=None, around_y=None, around_z=None):
        for face in self.pointers:
            self.remove(face)
        x_avg = 0
        y_avg = 0
        z_avg = 0
        vertices = 0
        for i in self.coords:
            for t in filter(lambda val: type(val) == list, i):
                x_avg += t[0]
                y_avg += t[1]
                z_avg += t[2]
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
        self.pointers = []
        for side in range(len(self.coords)):
            points = []
            for point in range(len(self.coords[side])):
                if type(self.coords[side][point]) == list:
                    self.coords[side][point] = Obj.rotatePoint(self.coords[side][point][0]-x_avg, self.coords[side][point][1]-y_avg, self.coords[side][point][2]-z_avg, theta_x, theta_y, theta_z)
                    self.coords[side][point][0] += x_avg
                    self.coords[side][point][1] += y_avg
                    self.coords[side][point][2] += z_avg
                    points.append(self.coords[side][point])
            new = Polygon(*[Point(i[0], i[1]) for i in points])
            new.setDepth(sum([i[2] for i in points])/len(points))
            if self.wireframe:
                new.setFillColor('Transparent')
            else:
                try:
                    new.setBorderWidth(0)
                    color = self.coords[side][self.coords[side].index('fill')+1]
                    if type(color) == str:
                        color = tuple(int(color.replace('#', '')[i:i+2], 16) for i in (0, 2, 4))
                    new.setFillColor(color)
                except ValueError:
                    new.setFillColor((0, 0, 0))
            self.pointers.append(new)
        for face in self.pointers:
            self.add(face)
        self.setDepth(self.z_avg)

    def reset(self):
        self.coords = [([(edge[:] if type(edge) == list else edge) for edge in face] if type(face) == list else face) for face in self.copy]
        self.rotate(0, 0, 0)

    def delete(self):
        for face in self.pointers:
            self.remove(face)
        del(self)


if __name__ == "__main__":
    canvas = Canvas(500, 500)
    canvas.setTitle('3D Objects')

    objs = [Obj('cube', x=200, y=200, z=0, width=50, height=50, depth=50)]  # Front Center Cube
    objs += [Obj('cube', x=200, y=200, z=50, width=50, height=50, depth=50, x_axis=objs[0].x_avg, y_axis=objs[0].y_avg, z_axis=objs[0].z_avg)]  # Back Center Cube
    objs += [Obj('cube', x=150, y=200, z=0, width=50, height=50, depth=50, x_axis=objs[0].x_avg, y_axis=objs[0].y_avg, z_axis=objs[0].z_avg)]  # Left Front Cube
    objs += [Obj(6, x=50, y=50, z=0, width=50, height=50, depth=50, pyramid=True, wireframe=True)]  # Top Left Pyramid
    objs += [Obj(8, (255, 0, 0), (0, 255, 0), (0, 0, 255), x=400, y=50, z=0, width=50, height=50, depth=50, wireframe=False)]  # Top Right Prism
    objs += [Obj(6, (255, 0, 0), (0, 0, 255), x=400, y=400, z=0, pyramid=True, width=50, height=50, depth=50)]  # Bottom Right Pyramid
    objs += [Obj('icosahedron', x=50, y=400, z=0, width=50, height=50, depth=50, wireframe=True)]  # Bottom Left Icosahedron
    objs += [Obj(4, "#FF0000", "#00FF00", x=200, y=400, z=0, width=50, height=50, depth=50)]  # Bottom Middle Cube

    for i in objs:
        canvas.add(i)

    '''Controls'''
    rot = 20
    while True:
        try:
            event = canvas.wait()
            eventType = event.getDescription()
            if eventType == 'keyboard':
                key = event.getKey()
                if key == '\x1b':  # (Esc) Key Close
                    print('Quit')
                    canvas.close()
                    break
                elif key == 's' or key == 'S':
                    for obj in objs:
                        obj.rotate(rot, 0, 0)
                elif key == 'w' or key == 'W':
                    for obj in objs:
                        obj.rotate(-rot, 0, 0)
                elif key == 'a' or key == 'A':
                    for obj in objs:
                        obj.rotate(0, rot, 0)
                elif key == 'd' or key == 'D':
                    for obj in objs:
                        obj.rotate(0, -rot, 0)
                elif key == 'q' or key == 'Q':
                    for obj in objs:
                        obj.rotate(0, 0, -rot)
                elif key == 'e' or key == 'E':
                    for obj in objs:
                        obj.rotate(0, 0, rot)
                elif key == 'x' or key == 'X':
                    for obj in objs:
                        obj.reset()
                else:
                    print('Key:', key)
            elif eventType == 'mouse click':
                start = event.getMouseLocation()
                print('Mouse Down:', (int(start.getX()), int(start.getY())))
            elif eventType == 'mouse release':
                start = event.getMouseLocation()
                print('Mouse Up:', (int(start.getX()), int(start.getY())))
            elif eventType == 'mouse drag':
                start = event.getOldMouseLocation()
                end = event.getMouseLocation()
                print('Mouse Drag:', ((int(start.getX()), int(start.getY())), (int(end.getX()), int(end.getX()))))
        except AttributeError:  # Manual Close
            print('Quit')
            canvas.close()
            raise SystemExit
