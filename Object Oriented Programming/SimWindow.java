package hw3;

import java.util.ArrayList;
import edu.du.dudraw.Draw;
import edu.du.dudraw.DrawListener;

public class SimWindow implements DrawListener {
    // Constants and fields
    public final static int windowWidth = 1050;
    public final static int windowHeight = 700;

    private TerrainMap tm;
    private Draw duDwin;
    private ArrayList<Avatar> theAvatars;
    
    public SimWindow(TerrainMap tm) throws BadAvatarException{
        this.tm = tm;
        

        // Initialize the DuDraw window
        duDwin = new Draw("Animal Simulation");
        duDwin.setCanvasSize(SimWindow.windowWidth, SimWindow.windowHeight);
        duDwin.enableDoubleBuffering();
        duDwin.setXscale(0, SimWindow.windowWidth);
        duDwin.setYscale(0, SimWindow.windowHeight);

        // Set up the DrawListener to handle mouse clicks
        this.tm = tm;
        duDwin.addListener(this);
        this.theAvatars = new ArrayList<Avatar>();
        theAvatars.add(AvatarFactory.newAvatar("Tiger", tm, new GridPoint(18, 11)));
        theAvatars.add(AvatarFactory.newAvatar("Rabbit", tm, new GridPoint(18, 15)));
        //theAvatars.add(AvatarFactory.newAvatar("Fish", tm, new GridPoint(2, 2)));
        theAvatars.add(AvatarFactory.newAvatar("Bird", tm, new GridPoint(2, 2)));
        theAvatars.add(AvatarFactory.newAvatar("Human", tm, new GridPoint(3, 1)));
        theAvatars.add(AvatarFactory.newAvatar("Cod", tm, new GridPoint(14, 11)));
        theAvatars.add(AvatarFactory.newAvatar("Shark", tm, new GridPoint(12, 12)));
        

    }

    public void update() {
        // Clear the window and draw the TerrainMap
        duDwin.clear(255, 255, 255);
        tm.draw(duDwin);

        // Draw the Human avatar
        for (Avatar avatar: theAvatars) {
        	if(duDwin.isMousePressed() ) {
        		avatar.ProcessEvent(duDwin);
        	}
        	
        	avatar.moveAvatar();
        	avatar.draw(duDwin);
        	System.out.println(avatar);
        	
        }
        duDwin.show(); // Used for double buffering
    }

    public void runSimulation() {
        update(); // Initial positioning

        while (true) {
            try {
                Thread.sleep(100);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }

            update();
        }
    }

 

	@Override
	public void keyPressed(int arg0) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void keyReleased(int arg0) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void keyTyped(char arg0) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void mouseClicked(double arg0, double arg1) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void mouseDragged(double arg0, double arg1) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void mousePressed(double arg0, double arg1) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void mouseReleased(double arg0, double arg1) {
		// TODO Auto-generated method stub
		
	}
}

