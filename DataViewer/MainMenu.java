package dataviewer3;

import java.awt.Color;
import java.util.SortedMap;
import java.util.TreeMap;

import javax.swing.JOptionPane;

import edu.du.dudraw.Draw;
import edu.du.dudraw.DrawListener;

public class MainMenu extends DataObserver implements DrawListener{
	private Draw m_window;

    private State m_selectedState;
    private Country m_selectedCountry;
    private Integer m_selectedStartYear;
    private Integer m_selectedEndYear;
    private VisState m_visState;
    private TreeMap<Integer, SortedMap<Integer, Double>> m_plotData;
    protected Data m_data;
    protected String m_dataFile;
    

    private UIState m_guiState;

    public MainMenu(Data data, Draw window, DataPlot dataPlot, String dataFile, State selectedState, Country selectedCountry,
        Integer selectedStartYear, Integer selectedEndYear, VisState visState) {
    	super(dataPlot);
		m_window = window;
		m_selectedState = selectedState;
		m_selectedCountry = selectedCountry;
		m_selectedStartYear = selectedStartYear;
		m_selectedEndYear = selectedEndYear;
		m_visState = visState;
		m_guiState = new MenuState();
		m_data = data;
		m_dataFile = dataFile;
		m_dataPlot = dataPlot;
		window.addListener(this);
    }
	
    
    private void setDefaultState() {
    	m_selectedState = m_selectedCountry.getStates().get(0);
	    m_selectedStartYear = m_selectedState.getYears().first();
	    m_selectedEndYear = m_selectedState.getYears().last();
    }
    
	
	 private void drawMainMenu() {
	    	m_window.clear(Color.WHITE);

	    	String[] menuItems = {
	    			"Type the menu number to select that option:",
	    			"",
	    			String.format("C     Set country: [%s]", m_selectedCountry),
	    			String.format("T     Set state: [%s]", m_selectedState),
	    			String.format("S     Set start year [%d]", m_selectedStartYear),
	    			String.format("E     Set end year [%d]", m_selectedEndYear),
	    			String.format("V     Set visualization [%s]", m_visState),
	    			String.format("P     Plot data"),
	    			String.format("Q     Quit"),
	    	};
	    	
	    	// enable drawing by "percentage" with the menu drawing
	        m_window.setXscale(0, 100);
			m_window.setYscale(0, 100);
			
			// draw the menu
	    	m_window.setPenColor(Color.BLACK);
			
			drawMenuItems(menuItems);
	    }

	private void drawMenuItems(String[] menuItems) {
		double yCoord = Constants.MENU_STARTING_Y;
		
		for(int i=0; i<menuItems.length; i++) {
			m_window.textLeft(Constants.MENU_STARTING_X, yCoord, menuItems[i]);
			yCoord -= Constants.MENU_ITEM_SPACING;
		}
	}
		
	@Override 
	public void keyPressed(int key) {
		boolean needsUpdate = false;
		boolean needsUpdatePlotData = false;
		Debugger.trace("key pressed '%c'", (char)key);
		// regardless of draw mode, 'Q' or 'q' means quit:
		if(key == 'Q') {
			System.out.println("Bye");
			System.exit(0);
		}
		else if(m_guiState.isMenu()) {
			if(key == 'P') {
				// plot the data
				m_guiState = m_guiState.Plot();
				if(m_plotData == null) {
					// first time going to render data need to generate the plot data
					needsUpdatePlotData = true;
				}
				needsUpdate = true;
			}
			else if(key == 'C') {
				// set the Country
				Object selectedValue = JOptionPane.showInputDialog(null,
			             "Choose a Country", "Input",
			             JOptionPane.INFORMATION_MESSAGE, null,
			             m_data.getDataCountries().toArray(), m_selectedCountry);
				if(selectedValue != null) {
					Debugger.info("User selected: '%s'", selectedValue);
					if(!selectedValue.equals(m_selectedCountry)) {
						// change in data
						m_selectedCountry = (Country) selectedValue;
						
						// sets the defaults states and year range for the country
						this.setDefaultState();
						
						needsUpdate = true;
						needsUpdatePlotData = true;
					}
				}
			}

			else if(key == 'T') {
				// set the state
				Object selectedValue = JOptionPane.showInputDialog(null,
			             "Choose a State", "Input",
			             JOptionPane.INFORMATION_MESSAGE, null,
			             m_selectedCountry.getStates().toArray(), m_selectedState);
				
				if(selectedValue != null) {
					Debugger.info("User selected: '%s'", selectedValue);
					if(!selectedValue.equals(m_selectedState)) {
						// change in data
						m_selectedState = (State) selectedValue;
						needsUpdate = true;
						needsUpdatePlotData = true;
					}
				}
			}
			else if(key == 'S') {
				// set the start year
				Object selectedValue = JOptionPane.showInputDialog(null,
			             "Choose the start year", "Input",
			             JOptionPane.INFORMATION_MESSAGE, null,
			             m_selectedState.getYears().toArray(), m_selectedStartYear);
				
				if(selectedValue != null) {
					Debugger.info("User seleted: '%s'", selectedValue);
					Integer year = (Integer)selectedValue;
					if(year.compareTo(m_selectedEndYear) > 0) {
						Debugger.error("new start year (%d) must not be after end year (%d)", year, m_selectedEndYear);
					}
					else {
						if(!m_selectedStartYear.equals(year)) {
							m_selectedStartYear = year;
							needsUpdate = true;
							needsUpdatePlotData = true;
						}
					}
				}
			}
			else if(key == 'E') {
				// set the end year
				Object selectedValue = JOptionPane.showInputDialog(null,
			             "Choose the end year", "Input",
			             JOptionPane.INFORMATION_MESSAGE, null,
			             m_selectedState.getYears().toArray(), m_selectedEndYear);
				
				if(selectedValue != null) {
					Debugger.info("User seleted: '%s'", selectedValue);
					Integer year = (Integer)selectedValue;
					if(year.compareTo(m_selectedStartYear) < 0) {
						Debugger.error("new end year (%d) must be not be before start year (%d)", year, m_selectedStartYear);
					}
					else {
						if(!m_selectedEndYear.equals(year)) {
							m_selectedEndYear = year;
							needsUpdate = true;
							needsUpdatePlotData = true;
						}
					}
				}
			}
			else if(key == 'V') {
				// set the visualization
				Object selectedValue = JOptionPane.showInputDialog(null,
						"Choose the visualization mode", "Input",
						JOptionPane.INFORMATION_MESSAGE, null,
						Constants.VISUALIZATION_MODES, m_visState);

				if(selectedValue != null) {
					System.out.println(selectedValue);
					System.out.println(m_visState);
					
					Debugger.info("User seleted: '%s'", selectedValue);
					VisState visualization = (VisState)selectedValue;
					if(!m_visState.equals(visualization)) {
						m_visState = visualization;
						needsUpdate = true;
					}
				}
			}

		}
		else if (!m_guiState.isMenu()) {
			if(key == 'M') {
				m_guiState = m_guiState.Menu();
				needsUpdate = true;
			}
		}
		else {
			throw new IllegalStateException(String.format("unexpected mode: %d", m_guiState));
		}
		if(needsUpdatePlotData) {
			// something changed with the data that needs to be plotted
			m_dataPlot.updatePlotData(m_selectedState, m_selectedStartYear, m_selectedEndYear);
		}
		if(needsUpdate) {
			this.updateObserver();;
		}
	}

	@Override
	public void keyReleased(int key) {}

	@Override
	public void keyTyped(char key) {}

	@Override
	public void mouseClicked(double x, double y) {}
	
	@Override
	public void mouseDragged(double x, double y) {}

	@Override
	public void mousePressed(double x, double y) {}

	@Override
	public void mouseReleased(double x, double y) {}

    @Override
	public void update() {    	
    	if(m_guiState.isMenu()) {
    		drawMainMenu();
    	}
    	else if(!m_guiState.isMenu()) {
    		m_dataPlot.drawData(m_selectedCountry, m_selectedState, m_selectedStartYear, m_selectedEndYear, m_visState);
    	}
    	else {
    		throw new IllegalStateException(String.format("Unexpected drawMode=%d", m_guiState));
    	}
        // for double-buffering
        m_window.show();
    }

    @Override
    public void updateObserver() {
		this.update();		
	} 
}
