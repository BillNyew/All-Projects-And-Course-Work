import sys
import subprocess
subprocess.check_call([sys.executable, "-m", "pip", "install", "--upgrade", "dudraw"])
import dudraw
dudraw.set_canvas_size(400,400)
dudraw.filled_circle(0.5, 0.5, 0.25)
dudraw.show(10000)
