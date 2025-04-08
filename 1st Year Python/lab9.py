import dudraw
# open 500x500 pixel window
dudraw.set_canvas_size(500,500)
brightness = -2
brightness_change = 1
while True:
    # clear the previous frame
    dudraw.clear(dudraw.CYAN)
    # draw the next frame of the animation
    dudraw.set_pen_color_rgb(brightness, brightness, brightness)
    dudraw.filled_circle(0.5, 0.5, 0.5)
    # display the image for 50 milliseceonds, which is 20 frames per second
    dudraw.show(20)
    # prepare for next frame by change the brightness
    if brightness > 255 or brightness < 0:
        brightness_change = -brightness_change
    brightness = brightness + brightness_change

    


