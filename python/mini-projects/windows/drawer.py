import canvas_matrix
import tkinter

ROOT_WINDOW_WIDTH = 600
ROOT_WINDOW_HEIGHT = 600

WIDTH_IN_SQUARES = 16
HEIGHT_IN_SQUARES = 16
SQUARE_SIZE = 25

def center(toplevel):
    toplevel.update_idletasks()
    w = toplevel.winfo_screenwidth()
    h = toplevel.winfo_screenheight()
    size = tuple(int(_) for _ in toplevel.geometry().split('+')[0].split('x'))
    x = w/2 - size[0]/2
    y = h/2 - size[1]/2
    toplevel.geometry("%dx%d+%d+%d" % (size + (x, y)))

class Drawer:
    pallete = ['spring green']
    color_index = 0
    background_color = 'RoyalBlue1'
    cur_color = pallete[color_index]
    
    def __init__(self, root, width, height, pixel_size, pallete, background):
        if pallete:
            Drawer.pallete = pallete
        else:
            pallete = Drawer.pallete
        if background:
            Drawer.background_color = background
        else:
            background = Drawer.background_color
        
        self.root = root
        self.width = width
        self.height = height
        self.pixel_size = pixel_size
        self.pallete = pallete
        
        self.canvas_matrix = canvas_matrix.CanvasMatrix(DrawerTyle, root, 
                                                        width, height,
                                                        pixel_size, pixel_size, 
                                                        background)


class DrawerTyle(canvas_matrix.Tyle):    
    def on_left_click(self, event):
        self.canvas.config(background=Drawer.cur_color)
    
    def on_center_click(self, event):
        Drawer.cur_color = Drawer.background_color    
    
    def on_right_click(self, event):
        if Drawer.cur_color == Drawer.background_color:
            Drawer.cur_color = Drawer.pallete[Drawer.color_index % len(Drawer.pallete)]
        else:
            Drawer.color_index = Drawer.color_index + 1
            Drawer.cur_color = Drawer.pallete[Drawer.color_index % len(Drawer.pallete)]

    def on_motion(self, event):
        cur_x = ((self.x * self.matrix.canvas_width + event.x) // 
                 self.matrix.canvas_width)
        cur_y = ((self.y * self.matrix.canvas_height + event.y) // 
                 self.matrix.canvas_height)
        
        self.matrix.tyle_matrix[cur_x][cur_y].on_left_click(event)    

def main():
    background = input('Background_color: ')
    pallete = input('Colors to use (space separated, do not use background): ')
    if pallete:
        pallete = list(pallete.split())
    print('[Help] LMB - draw, RMB - change colors (circused), CMB - background color')
    
    root = tkinter.Tk()
    root.geometry(str(ROOT_WINDOW_WIDTH) + 'x' + str(ROOT_WINDOW_HEIGHT) + '+500+200')
    
    pixel_size = ROOT_WINDOW_WIDTH // WIDTH_IN_SQUARES
    Drawer(root, WIDTH_IN_SQUARES, HEIGHT_IN_SQUARES, pixel_size, 
           pallete, background)
    
    center(root)
    
    root.mainloop()

if __name__ == '__main__':
    main()
