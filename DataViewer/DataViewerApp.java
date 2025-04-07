package dataviewer3;

import java.io.FileNotFoundException;
import edu.du.dudraw.Draw;

public class DataViewerApp {
    // data storage
    private final String m_dataFile;
    
    // user selections
    private Country m_selectedCountry;
    private Integer m_selectedEndYear;
    private State m_selectedState;
    private Integer m_selectedStartYear;
    private VisState m_visState;
    
	// Window-variables
    private Draw m_window;
    private Data m_data;
    private DataPlot m_dataPlot;
    private MainMenu m_mainMenu;

    public DataViewerApp(String dataFile) throws FileNotFoundException {
    	// save the data file name for later use if user switches country
    	m_dataFile = dataFile;
    	
        // Setup the DuDraw board
        m_window = new Draw(Constants.WINDOW_TITLE);
        m_window.setCanvasSize(Constants.WINDOW_WIDTH, Constants.WINDOW_HEIGHT);
        m_window.enableDoubleBuffering(); // Too slow otherwise -- need to use .show() later
        
        // Load data
        m_data = new Data();
        m_data.loadData(dataFile);
        
        // Set default variables
	    m_selectedCountry = m_data.getDataCountries().get(2);
	    m_selectedState = m_selectedCountry.getStates().get(0);
	    m_selectedStartYear = m_selectedState.getYears().first();
	    m_selectedEndYear = m_selectedState.getYears().last();
	    m_visState = new RawVisState();
        
        m_dataPlot = new DataPlot(m_window);
        m_mainMenu = new MainMenu(m_data, m_window, m_dataPlot, m_dataFile, m_selectedState, m_selectedCountry, m_selectedStartYear, m_selectedEndYear, m_visState);

        // draw the screen for the first time
	    m_mainMenu.update();
    }
}