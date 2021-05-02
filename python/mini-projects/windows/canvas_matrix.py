import tkinter as __tkinter__

STANDARD_ROOT_WINDOW_WIDTH = 800
STANDARD_ROOT_WINDOW_HEIGHT = 600
STANDARD_CANVAS_SIZE = 50


class Tyle:
    def __init__(self, canvas_matrix, x, y, canvas):
        self.matrix = canvas_matrix
        
        self.canvas = canvas
        canvas.bind('<Button-1>', self.on_left_click)
        canvas.bind('<Button-2>', self.on_center_click)
        canvas.bind('<Button-3>', self.on_right_click)
        canvas.bind('<B1-Motion>', self.on_motion)
        
        self.x = x
        self.y = y
    
    def on_left_click(self, event):
        pass
    
    def on_center_click(self, event):
        pass
 
    def on_right_click(self, event):
        pass

    def on_motion(self, event):
        pass

class CanvasMatrix:
    def __init__(self, Tyle, root_window, width, height, canvas_width, canvas_height,
                 bgcolor='white'):
        self.root = root_window
        self.width = width
        self.height = height
        self.canvas_width = canvas_width
        self.canvas_height = canvas_height
        
        self.tyle_matrix = [[0 for i in range(width)] for j in range(height)]
        for i in range(height):
            for j in range(width):
                new_canvas = __tkinter__.Canvas(root_window, width=canvas_width,
                                            height=canvas_height, background=bgcolor)
                
                new_canvas.place(x = i * canvas_height, y = j * canvas_width)
                self.tyle_matrix[i][j] = Tyle(self, i, j, new_canvas)

        

def main():
    root = __tkinter__.Tk()
    root.geometry(''
                  + str(STANDARD_ROOT_WINDOW_WIDTH)
                  + 'x'
                  + str(STANDARD_ROOT_WINDOW_HEIGHT) 
                  + '+500+200')
    
    
    width = int(STANDARD_ROOT_WINDOW_HEIGHT/STANDARD_CANVAS_SIZE)
    height = int(STANDARD_ROOT_WINDOW_WIDTH/STANDARD_CANVAS_SIZE)
    cm = CanvasMatrix(Tyle, root, width, height, 
                      STANDARD_CANVAS_SIZE, STANDARD_CANVAS_SIZE)
    
    root.mainloop()

if __name__ == '__main__':
    main()